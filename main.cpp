//Main.cpp
//C/C++ final project
//Landon Swartz, Rushil Thakker, Aaron Fuller

#include"fileRAII.h"
//#include"ExceptionHandlers.cpp"
#include"HashClass.cpp"
#include "EncryptionClass.cpp"
#include<iostream>
#include<pthread.h>
#include<vector>
#include<iterator>
#include<mutex>
#include<string>
#include<cstdlib>

using namespace std;

#define NUM_THREADS 1 //number of threads

//struct for passing to reading file. Contains filevector that has all the strings and file pointer 
struct ft
{
	vector<string> fileVector;
	File file; //to pass file to multi-thread function	
};

/*Thread function that takes in arg struct with filename,
 * start_index, and end_index to read in thread in segments*/
void *readFile(void *arg)
{
	int i; int c;
	struct ft* fi = (struct ft*)arg;
	string filename = fi->file.getFilename();
	cout<<"Filename is: "<< filename<<endl;
	ifstream in(filename);
	if(!in)
	{
		cout<<"Failure to open file, try again. Spelling counts"<<endl;
		return NULL;
	}
	string word;
	while(in>>word)
	{
		fi->fileVector.push_back(word);
	}
	in.close();
	cout<<"File was read!"<<endl;

	return NULL;
}

//newFile
//pthread function to create new file with encrypted data
void *newFile(void *arg)
{
	ofstream file;
	struct ft* fi = (struct ft*)arg;

	file.open("NewFile.txt");
	ostream_iterator<string> output_iterator(file, "\n");
	copy(fi->fileVector.begin(), fi->fileVector.end(), output_iterator);

	return NULL;
}

//Prints menu for program
void printMenu()
{
	cout<<"----------MENU----------"<<endl;
	cout<<"1. Choose file to hash and/or encrypt"<<endl;
	cout<<"2. Encrypt File"<<endl;
	cout<<"3. Decrypt file"<<endl;
	cout<<"4. Exit program"<<endl;
}

int main(int argc, char*argv[])
{
	string filename;
	vector<string> fileContents;

	struct ft * args = new (struct ft);
	if(!args)
	{
		cerr<<"Memory allocation failed!"<<endl;
		exit(1);
	}
	args->fileVector = fileContents;

	hashing HashObj_encrypt;
	hashing HashObj_decrypt;

	// Using one variable for password may be confusing. This has been changed because in one instance,
	// a password is set, and in another, it is entered. Having separate variables should also improve
	// the overall security of the program.
	string password_set;
	string password_entered;

	// Create the base encryption class object
	encryption_base encryptionObj;
	encryption_base decryptionObj;

	pthread_t threads[NUM_THREADS];

	int choice;
	int exitCode = 1;
	int rc;

	//creating threads
	while(exitCode)
	{
		printMenu();
		cin>>choice;
		cin.ignore();
		cin.clear();

		switch(choice) {
			case 1:
				//read in file and prove that you've read it in
				//get size of file
				//divide into even chunks
				//send to the threads
				cout<<"What is the name of the file to hash?"<<endl;
				cin>>filename;
				cin.ignore();
				cin.clear();
				cout<<"You choose to read in the file: "<<filename<<endl;
				cout<<"If wrong then please read in again"<<endl;
				args->file.open(filename);
				rc = pthread_create(&threads[0], NULL, readFile, (void *)args);
				pthread_join(threads[0], NULL);
				break;
			case 2: 
				//encrypt file
				
				cout<<"What would you like the password to be?"<<endl;
				cin>>password_set;
				cin.ignore();
				cin.clear();
				cout<<"You entered: "<< password_set <<endl;
				HashObj_encrypt.set_password(password_set);
				HashObj_encrypt.set_hash_key_from_password();

				cout<<"Hash key is: "<<HashObj_encrypt.get_hash_key()<<endl;
				
				// Once the password has been retrieved, set the hash key in the encryption object
				encryptionObj.set_hash_key(HashObj_encrypt.get_hash_key());

				// The encryption class is ready to do some encryption. Give the class the data to work with.
				// Data being sent to this function should not already be encrypted.
				encryptionObj.set_decrypted_data(&(args->fileVector));

				// Call the getter function on the encryption object. Even if the data is not retrieved, calling
				// the getter function will perform the actual encryption. (This technically returns the address
				// of the agrs->fileVector retrieved earlier, but we already have it.)
				encryptionObj.get_encrypted_data();

				// Landon & Rushil, the data is modified in the vector, now what function do I call to update the file??
				/* 
				Call function here to update file based on the now modified vector
				*/
				rc = pthread_create(&threads[0], NULL, newFile, (void*)args);
				pthread_join(threads[0], NULL);
				cout<<"Thank you for using our program. Please come again"<<endl;
				exitCode =0;
				break;
			case 3:
				//decrypt file

				cout << "Enter your password to decrypt the file: " << endl;
				cin >> password_entered;
				cin.ignore();
				cin.clear();
				cout << "You entered:" << password_entered << endl;
				HashObj_decrypt.set_password(password_entered);
				HashObj_decrypt.set_hash_key_from_password();

				// Set the hash key in the decryption object.
				decryptionObj.set_hash_key(HashObj_decrypt.get_hash_key());

				// Set the data based on what is stored in the file.
				decryptionObj.set_encrypted_data(&(args->fileVector));

				// Call the getter function to ensure the decryption happens.
				decryptionObj.get_decrypted_data();

				// Call the function necessary to overwrite the data in the file based on modifications made
				// to the vector which contains the file contents.
				rc = pthread_create(&threads[0], NULL, newFile, (void*)args);
				pthread_join(threads[0], NULL);
				break;
			case 4:
				//exit program
				exitCode = 0;
				break;
			default:
				//wrong choice
				cout<<"Please choose a choice between 1-4"<<endl;
				printMenu();
				break;
		}
	}

	return 0;
}
