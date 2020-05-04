//File RAII implementation file
//Landon Swartz

#include"fileRAII.h"

void File::open(const string fileName)
{
	m_file_handle.open(fileName);
	filename = fileName;
}

void File::close()
{
	if(m_file_handle.is_open())
	{
		m_file_handle.close();
	}
}

/*std::string File::readLine()
{
	return m_file_handle.readsome();
}*/

/*void File::write(const char*str)
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
}*/
