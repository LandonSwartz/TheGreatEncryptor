/*
*	This file contains the hashing class. Returns the same hash key for a given string. 
*		Can either set the password, set the hash key using the passing, or get the hash key
*			Included test function to show how the class works
*	
*	Authors: Rushil Thakker, Aaron Fuller, Landon Swartz
*/

#include <iostream>
#include <functional>
#include <string>

using namespace std;

//void test_function();

class hashing
{
	private:
			int hash_key = 0;
			string password;
			
	public:
			void set_password(string entered_password)
			{
				password = entered_password;
			}

			int get_hash_key()
			{
				return hash_key;
			}

			void set_hash_key_from_password()
			{
				hash<string> hash_obj;

				hash_key = hash_obj(password);
			}
};

/*int main(void)
{
	test_function();

	return 0;
}*/

//	Below is a test for the above hashing class

/*void test_function()
{
	hashing hashing_obj;
	hashing hashing_obj2;
	hashing hashing_obj3;
	hashing hashing_obj4;

	cout << "Enter a password: ";
	string password1;
	cin >> password1;
	hashing_obj.set_password(password1);

	hashing_obj2.set_password("1e$mE!n?");
	hashing_obj3.set_password("/M!z&Z0u");
	hashing_obj4.set_password("JustMakingThisReallyLongForNoReasonInParticular!");

	hashing_obj.set_hash_key_from_password();
	hashing_obj2.set_hash_key_from_password();
	hashing_obj3.set_hash_key_from_password();
	hashing_obj4.set_hash_key_from_password();

	if (hashing_obj.get_hash_key() == hashing_obj2.get_hash_key())
	{
		cout << "Passwords 1 and 2 are same :)" << endl;
	}
	else
	{
		cout << "Passwords 1 and 2 are different :(" << endl;
	}

	if (hashing_obj3.get_hash_key() == hashing_obj4.get_hash_key())
	{
		cout << "Passwords 3 and 4 are the same :)" << endl;
	}
	else
	{
		cout << "Passwords 3 and 4 are different :(" << endl;
	}
}*/
