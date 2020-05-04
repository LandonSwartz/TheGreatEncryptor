//Main.cpp
//C/C++ final project
//Landon Swartz, Rushil Thakker, Aaron Fuller

#include"fileRAII.h"
#include<iostream>
#include<pthread.h>
#include<vector>
#include<mutex>
#include<cstdlib>

using namespace std;

#define NUM_THREADS 5 //number of threads

//struct for passing to reading file. Contains file, start index, and end index
struct ft
{
//	char *filename; Dont need
	vector<string> fileVector;
	int start_index;
	int end_index;
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
	//FILE *readFile = fi->file;
	//fseek(fi->file.returnFileHandle(), fi->start_index, SEEK_SET);
	ifstream in(filename);
	string word;
	while(in>>word)
	{
		fi->fileVector.push_back(word);
		cout<<fi->fileVector.back()<<endl;
	}
	in.close();

	return NULL;
}

void printMenu()
{
	cout<<"----------MENU----------"<<endl;
	cout<<"1. Choose file to hash"<<endl;
	cout<<"2. Hash File"<<endl;
	cout<<"3. Exit program"<<endl;
}

int main(int argc, char*argv[])
{
	const char * filename = "testing.txt";
	vector<string> fileContents;

	struct ft * args = new (struct ft);
	if(!args)
	{
		cerr<<"Memory allocation failed!"<<endl;
		exit(1);
	}
	args->fileVector = fileContents;
	args->file.open(filename);
	args->start_index = 0;
	args->end_index = 5;

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
				rc = pthread_create(&threads[0], NULL, readFile, (void *)args);
				pthread_join(threads[0], NULL);

				cout<<"File was readed!"<<endl;
				break;
			case 2: 
				//hash file
				break;
			case 3:
				//exit program
				exitCode = 0;
				break;
			default:
				//wrong choice
				break;
		}
	}

	return 0;
}
