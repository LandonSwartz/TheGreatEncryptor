//File RAII header file
//Landon Swartz

#include<cstdio>

using namespace std;
class file_error { };
class open_error : public file_error { };
class close_error : public file_error { };
class write_error : public file_error { };

class File
{
	public:
		File(const char* filename) : m_file_handle(fopen(filename, "w+"))
		{
			if(m_file_handle == NULL)
			{
				throw open_error();
			}
		}

		~File()
		{
			fclose(m_file_handle);
		}
		
		//takes in a string and writes it to the file
		void write(const char* str);

		//takes in string and writes it to file with buffer and num of chars
		void write(const char* buffer, size_t num_chars);

	private:
		FILE * m_file_handle;
		File(const File &);
		File & operator=(const File &);
};
