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
		
		//destructor that closes stream when done
		~File()
		{
			if(m_file_handle.is_open())
			{
				m_file_handle.close();
			}
		}
		
		//opens file with filename
		void open(const string fileName);
		
		//boolean function to see if file is open
		bool isOpen() const
		{
			return m_file_handle.is_open();
		}

		//closes file
		void close();

		//returns filename property
		string getFilename()
		{
			return filename;
		}

	private:
		fstream m_file_handle;
		string filename; //name of file
};
