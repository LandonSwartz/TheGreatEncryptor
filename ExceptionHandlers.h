/*	
*	This header file contains all of our classes for our program's custom exception handling
*	Authors: Rushil Thakker, Landon Swartz, Aaron Fuller
*/

#include <stdexcept>
#include <string>

using namespace std;

class command_line_error : public runtime_error
{
	public:
			explicit command_line_error(const char *mess_arg) : std::runtime_error( mess_arg ) {}
			explicit command_line_error(const std::string &mess_arg) : std::runtime_error( mess_arg) {}
};

class file_not_found_error : public runtime_error
{
	public:
			explicit file_not_found_error(const char *mess_arg) : std::runtime_error( mess_arg ) {}
			explicit file_not_found_error(const std::string &mess_arg) : std::runtime_error( mess_arg ) {}			
};

class file_empty_error : public runtime_error
{
	public:
			explicit file_empty_error(const char *mess_arg) : std::runtime_error( mess_arg ) {}
			explicit file_empty_error(const std::string &mess_arg) : std::runtime_error( mess_arg ) {}			
};

class file_encryption_error : public runtime_error
{
	public:
			explicit file_encryption_error(const char *mess_arg) : std::runtime_error( mess_arg ) {}
			explicit file_encryption_error(const std::string &mess_arg) : std::runtime_error( mess_arg ) {}			
};

class file_decryption_error : public runtime_error
{
	public:
			explicit file_decryption_error(const char *mess_arg) : std::runtime_error( mess_arg ) {}
			explicit file_decryption_error(const std::string &mess_arg) : std::runtime_error( mess_arg ) {}			
};
