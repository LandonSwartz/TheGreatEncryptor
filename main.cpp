//Main.cpp
//C/C++ final project
//Landon Swartz, Rushil Thakker, Aaron Fuller

#include"fileRAII.h"
#include"ExceptionHandlers.cpp"
#include"HashClass.cpp"
#include<iostream>
#include<pthread.h>
#include<vector>
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
 * start_index, and end_index to read in thread in segments
 */
void *readFile(void *arg)
{
	int i; int c;
	struct ft* fi = (struct ft*)arg;
	string filename = fi->file.getFilename();
	cout<<"Filename is: "<< filename<<endl;
	ifstream in(filename);
	string word;
	while(in>>word)
	{
		fi->fileVector.push_back(word);
	}
	in.close();

	return NULL;
}

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

	hashing HashObj;
	string password;

	pthread_t threads[NUM_THREADS];

	int choice;
	int exitCode = 1;
	int rc;

	//creating threads
	while(exitCode)
	{
		printMenu();
		cin>>choice;

		switch(choice) {
			case 1:
				//read in file and prove that you've read it in
				//get size of file
				//divide into even chunks
				//send to the threads
				cout<<"What is the name of the file to hash?"<<endl;
				cin>>filename;
				cout<<"You choose to read in the file: "<<filename<<endl;
				cout<<"If wrong then please read in again"<<endl;
				args->file.open(filename);
				rc = pthread_create(&threads[0], NULL, readFile, (void *)args);
				pthread_join(threads[0], NULL);
				cout<<"File was readed!"<<endl;
				break;
			case 2: 
				//encrypt file
				


				/*
				cout<<"What would you like the password to be?"<<endl;
				cin>>password;
				cout<<"You entered: "<<password<<endl;
				HashObj.set_password(password);
				HashObj.set_hash_key_from_password();
				cout<<"Hash complete. Your hash key is: "<<HashObj.get_hash_key()<<endl;*/
				break;
			case 3:
				//encryption class
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
