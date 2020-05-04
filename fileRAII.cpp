//File RAII implementation file
//Landon Swartz

#include"fileRAII.h"

void File::write(const char*str)
{
	if(fputs(str, m_file_handle) == EOF)
	{
		throw write_error();
	}
}

void File::write(const char* buffer, size_t num_chars)
{
	if(num_chars != 0 && fwrite(buffer, num_chars, 1, m_file_handle) == 0)
	{
		throw write_error();
	}
}
