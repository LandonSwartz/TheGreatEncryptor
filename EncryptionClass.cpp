// Aaron

#include<cstdlib>
#include<pthread.h>
#include<vector>
#include<string>
#include "ExceptionHandlers.cpp"
#define NUM_ENCRYPTION_THREADS 10

using namespace std;

// Create a typecast to use the non-static virtual functions in a thread
typedef void * (*thread_function)(void *);

// The encryption class handles all encryption and decryption of the data
class encryption_base
{
private:
    // Data state has three values: 0 for data is nonexistant, 1 for encrypted data, and 2 for decrypted data
    int data_state = 0;
    vector<string> * data;
    int hash_key = 0;

    typedef struct algorithm_parameters {
        // The threads will need a reference to the vector with all the data in it.
        vector<string> * data;
        // Tell this specific thread where to start and end.
        int start_index;
        int end_index;
    } alg_prms;

    // The function which does the actual encryption. For the base class, this will be a simple cipher.
    void * encryption_algorithm(void * params_void) {
        // Encryption algorithm, basic code necessary for other implementations of this function
        algorithm_parameters * params = static_cast<algorithm_parameters *>(params_void);

        // Calculate the cipher offset.
        int cipher_offset = this->hash_key % 255;

        // Traverse through each string this thread is responsible for.
        for (int i = params->start_index; i <= params->end_index; i++) {
            // The syntax below explained:
                // params is a reference to a struct
                // use -> notation because params is a reference to retrieve data member of struct
                // data member of struct is reference to a vector object of strings, so dereference it
                // use [] notation to access index of given string from dereferenced vector object
                // after the string is indexed, get its address so the string can be modified
            string * current_string = &((*(params->data))[i]);
            // At this point, we have a reference to the string that should be encrypted.
            for (int c = 0; c < current_string->length(); c++) {
                // Iterate through every character in the string, apply the cipher.
                int current_char = ((int)((*current_string)[c]));
                current_char += cipher_offset;
                if (current_char > 255)
                    current_char -= 255;
                (*current_string)[c] = (char)current_char;
            }
        }
    };

    bool encrypt_data() {
        if (this->hash_key == 0) {
            throw file_encryption_error("no hash key has been set");
            return false;
        }
        if (data_state == 0) {
            throw file_encryption_error("there is no data to encrypt");
            return false;
        } else if (data_state == 1) {
            throw file_encryption_error("the data is already encrypted");
            return false;
        }

        // Set up the structs for the threads which will encrypt the data.
        vector<alg_prms *> encryption_alg_prms_vect;
        int indices_per_thread;
        int num_threads;
        int end_additional_increment = 0;
        // Ensure there will be at least one string per thread
        if (data->size() >= NUM_ENCRYPTION_THREADS) {
            indices_per_thread = (data->size()) / NUM_ENCRYPTION_THREADS;
            end_additional_increment = (data->size()) % NUM_ENCRYPTION_THREADS;
            num_threads = NUM_ENCRYPTION_THREADS;
        }
        // If there will not be one string per thread, simply use one thread
        else {
            num_threads = 1;
            indices_per_thread = data->size();
        }
        // Create structs for each thread
        for (int i = 0; i < num_threads; i++) {
            alg_prms * alg_prms_strc = new alg_prms();
            alg_prms_strc->data = this->data;
            alg_prms_strc->start_index = (i * indices_per_thread);
            alg_prms_strc->end_index = ((i + 1) * indices_per_thread) - 1;
            encryption_alg_prms_vect.push_back(alg_prms_strc);
        }
        // Add end_additional_increment
        encryption_alg_prms_vect.back()->end_index += end_additional_increment;

        // Create the threads to encrypt the data
        vector<pthread_t> encryption_threads;
        for (auto prm_vct : encryption_alg_prms_vect) {
            pthread_t new_thread;
            pthread_create(&new_thread, NULL, (thread_function)(&encryption_base::encryption_algorithm), prm_vct);
            encryption_threads.push_back(new_thread);
        }

        // Now that the threads are running, join them so the function will yield
        for (auto thread : encryption_threads) {
            pthread_join(thread, NULL);
        }

        // Delete the dynamically allocated structs once all thread operation has completed
        for (auto prm_vct : encryption_alg_prms_vect) {
            delete prm_vct;
        }

        // Return true to indicate the encryption was successful.
        return true;
    };
    
    virtual void * decryption_algorithm(void * params_void) {
        // Encryption algorithm, basic code necessary for other implementations of this function
        algorithm_parameters * params = static_cast<algorithm_parameters *>(params_void);

        // Calculate the cipher offset.
        int cipher_offset = this->hash_key % 255;

        // Traverse through each string this thread is responsible for.
        for (int i = params->start_index; i <= params->end_index; i++) {
            // The syntax below explained:
                // params is a reference to a struct
                // use -> notation because params is a reference to retrieve data member of struct
                // data member of struct is reference to a vector object of strings, so dereference it
                // use [] notation to access index of given string from dereferenced vector object
                // after the string is indexed, get its address so the string can be modified
            string * current_string = &((*(params->data))[i]);
            // At this point, we have a reference to the string that should be encrypted.
            for (int c = 0; c < current_string->length(); c++) {
                // Iterate through every character in the string, apply the cipher.
                int current_char = ((int)((*current_string)[c]));
                current_char -= cipher_offset;
                if (current_char < 0)
                    current_char += 255;
                (*current_string)[c] = (char)current_char;
            }
        }
    };
    
    bool decrypt_data() {
        if (this->hash_key == 0) {
            throw file_decryption_error("no hash key has been set");
            return false;
        }
        if (data_state == 0) {
            throw file_decryption_error("there is no data to decrypt");
            return false;
        } else if (data_state == 2) {
            throw file_decryption_error("the data has already been decrypted");
            return false;
        }
        
        // Set up the structs for the threads which will encrypt the data.
        vector<alg_prms *> encryption_alg_prms_vect;
        int indices_per_thread;
        int num_threads;
        int end_additional_increment = 0;
        // Ensure there will be at least one string per thread
        if (data->size() >= NUM_ENCRYPTION_THREADS) {
            indices_per_thread = (data->size()) / NUM_ENCRYPTION_THREADS;
            end_additional_increment = (data->size()) % NUM_ENCRYPTION_THREADS;
            num_threads = NUM_ENCRYPTION_THREADS;
        }
        // If there will not be one string per thread, simply use one thread
        else {
            num_threads = 1;
            indices_per_thread = data->size();
        }
        for (int i = 0; i < num_threads; i++) {
            alg_prms * alg_prms_strc = new alg_prms();
            alg_prms_strc->data = this->data;
            alg_prms_strc->start_index = (i * indices_per_thread);
            alg_prms_strc->end_index = ((i + 1) * indices_per_thread) - 1;
            encryption_alg_prms_vect.push_back(alg_prms_strc);
        }
        // Add end_additional_increment
        encryption_alg_prms_vect.back()->end_index += end_additional_increment;

        // Create the threads to encrypt the data
        vector<pthread_t> encryption_threads;
        for (auto prm_vct : encryption_alg_prms_vect) {
            pthread_t new_thread;
            pthread_create(&new_thread, NULL, (thread_function)(&encryption_base::decryption_algorithm), prm_vct);
            encryption_threads.push_back(new_thread);
        }

        // Now that the threads are running, join them so the function will yield
        for (auto thread : encryption_threads) {
            pthread_join(thread, NULL);
        }

        // Delete the dynamically allocated structs once all thread operation has completed
        for (auto prm_vct : encryption_alg_prms_vect) {
            delete prm_vct;
        }

        // Return true to indicate the encryption was successful.
        return true;
    };
public:
    // Give the class some data to work with, call the appropriate function so it knows if the data is encrypted
    // or decrypted to begin with.
    void set_encrypted_data(vector<string> * data_ref) {
        this->data_state = 1;
        this->data = data_ref;
    };
    void set_decrypted_data(vector<string> * data_ref) {
        this->data_state = 2;
        this->data = data_ref;
    }

    // The hash key must be set before any encryption or decryption can happen
    void set_hash_key(int key) {
        if (to_string(key).length() == 9)
            this->hash_key = key;
    };

    // Note: these two getter functions must be called from within a try block
    vector<string> * get_decrypted_data() {
        if (data_state == 2)
            return this->data;
        else if (data_state == 1) {
            this->decrypt_data();
            return this->data;
        } else if (data_state == 0) {
            return nullptr;
        }
    };
    vector<string> * get_encrypted_data() {
        if (data_state == 1)
            return this->data;
        else if (data_state == 2) {
            this->encrypt_data();
            return this->data;
        } else if (data_state == 0) {
            return nullptr;
        }
    }

    
};
