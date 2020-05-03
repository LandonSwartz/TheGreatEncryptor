//Main.cpp
//C/C++ final project
//Landon Swartz, Rushil Thakker, Aaron Fuller

#include<iostream>
#include<pthread.h>
#include<vector>
#include"fileRAII.h"

using namespace std;

#define NUM_THREADS 5 //number of threads

//struct for passing to reading file. Contains file, start index, and end index
struct ft
{
	char *filename;
	int start_index;
	int end_index;
	//may need to add filecontents vector
}

/*Thread function that takes in arg struct with filename,
 * start_index, and end_index to read in thread in segments
 */
void *readFile(void *arg)
{
	int i; int c;
	struct ft* fi = (struct ft*)arg;
	FILE *file = fopen(fi->filename);
	fseek(file, fi->start_index, SEEK_SET);
	for(int i=0; i < fi->end_index - fi->start_index; i++)
	{
		//put into whatever to hash
	}
}

void printMenu()
{
	cout<<"----------MENU----------"<<endl;
	cout<<"1. Choose file to hash"<end;
	cout<<"2. Hash File"<<endl;
	cout<<"3. Exit program"<<endl;
}

//command line will be ./TheGreatEncryptor filename howtohash
int main(int argc, char*argv[])
{
	const char * filename = "testing.txt";
	vector<string> fileContents;
	File file(testing.txt);
	pthreads_t threads[NUM_THREADS];
	int choice;
	int exitCode = 1;

	//creating threads
	while(exitCode)
	{
		printMenu();
		cin>>choice;

		switch(choice) {
			case 1:
				//read in file and prove that you've read it in
				break;
			case 2: 
				//hash file
				break;
			case 3:
				//exit program
				break;
			default:
				//wrong choice
				break;
		}
	}
}
