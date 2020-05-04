//File RAII header file
//Landon Swartz

#include<cstdio>
#include<fstream>

using namespace std;
class file_error { };
class open_error : public file_error { };
class close_error : public file_error { };
class write_error : public file_error { };

class File
{
	public:
		File() { }
		
		~File()
		{
			if(m_file_handle.is_open())
			{
				m_file_handle.close();
			}
		}
		
		//opens file with filename
		void open(const string fileName);
		
		//takes in a string and writes it to the file
		//void write(const char* str);

		//takes in string and writes it to file with buffer and num of chars
		//void write(const char* buffer, size_t num_chars);
		
		//boolean function to see if file is open
		bool isOpen() const
		{
			return m_file_handle.is_open();
		}

		void close();

		string getFilename()
		{
			return filename;
		}

	//	std::string readLine();
	
	//	fstream operator=(const fstream &);

	private:
		fstream m_file_handle;
		string filename;
};
