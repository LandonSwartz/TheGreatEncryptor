//File RAII header
//Landon Swartz

#include<cstdio>

using namespace std;

//exceptions
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

		void write(const char*str)
		{
			if(fputs(str, m_file_handle) == EOF)
			{
				throw write_error();
			}
		}

		void write(const char* buffer, size_t num_chars)
		{
			if(num_chars != 0 && fwrite(buffer, num_chars, 1, m_file_handle) == 0)
			{
				throw write_error();
			}
		}

	private:
		FILE* m_file_handle;

		file(const file &);
		file & operator=(const file &);
}
