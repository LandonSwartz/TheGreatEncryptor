// Aaron

#include<cstdlib>
#include<pthread.h>
#include<vector>
#include<string>
#include<cmath>
#include<iostream>
#include<sstream>
#include<fstream>
#include<iomanip>
#include<iterator>
#include "ExceptionHandlers.cpp"
#define NUM_ENCRYPTION_THREADS 10

using namespace std;

class encryption_base
{
	public:
		void encryption(string filename, int hash_key)
		{
			if(hash_key)
			{
				ifstream ifs;
				ifs.open(filename);

				vector<string>fileContent;
				string data = "";

				while (ifs >> data)
				{
					ifs >> data;

					fileContent.push_back(data);
				}

				ifs.close();

				ofstream ofs;
				string outputFilename = filename + "-ciphered";
				ofs.open(outputFilename, ios::out);			
				
				for (auto& value : fileContent)
				{
					value += 3;
					ofs << value;
				}
				
				ofs.close();
			}

			else
			{
				cout << "File not entered, please choose 1. and enter a file first." << endl;
			}

		}

};
