//Main.cpp
//C/C++ final project
//Landon Swartz, Rushil Thakker, Aaron Fuller

#include<iostream>
#include<pthread.h>
#include<vector>
#include"fileRAII.cpp"

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
{`
	int i; int c;
	struct ft* fi = (struct ft*)arg;
	FILE *file = fopen(fi->filename);
	fseek(file, fi->start_index, SEEK_SET);
	for(int i=0; i < fi->end_index - fi->start_index; i++)
	{
		//put into whatever to hash
	}
}

int main()
{
	vector<string> fileContents;  

	//reading in file

}
