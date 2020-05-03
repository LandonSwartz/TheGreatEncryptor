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
		file(const char* filename) : m_file_handle(fopen(filename, "w+"))
		{
			if(m_file_handle == NULL)
			{
				throw open_error();
			}
		}

		~file()
		{
			fclose(m_file_handle);
		}

		void write(const char* str);

		void write(const char* buffer, size_t num_chars);

	private:
		FILE * m_file_handle;
		file(const file &);
		file & operator=(const file &);
}
