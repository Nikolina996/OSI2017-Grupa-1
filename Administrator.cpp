#include<iostream>
#include<fstream>
#include<string>

#include "Administrator.h"
#include "User.h"


Administrator::Administrator(char *a, char *b, char *c, char *d):User(a, b, c, d)
{
}

Administrator::~Administrator()
{

}

void Administrator::userMenu()
{
	cout<<"/tMastermind Analyze"<<endl;
	cout << "Enter the number of the option:" << endl << "[1] Currency adjustment" << endl << "[2] Review and manage user accounts" << endl << "[0]Exit" << endl;
}

bool Administrator::logIn()
{
	string username, password, user, pass, name, surname;
	cout << "Your username and password: ";
	cin >> username >> password;
	ifstream adminFile("admin_podaci.txt");
	if (adminFile.is_open())
	{
		adminFile >> name >> surname >> user >> pass;
		if (username == user && password == pass)
		{
			cout << "Login successful!" << endl;
			return true;
		}
		else
		{
			cout << "Username or password do not match." << endl;
			return false;
		}
	}
	else
	{
		cout << "Could not open info file." << endl;
		return false;
	}
}

void Administrator::setAccount()
{
}

void Administrator::currencyChange()
{
}

void Administrator::menagingUserAccounts()
{
}

int Administrator::deleteUser()
{
	return 0;
}

int Administrator::addUser()
{
	return 0;
}

void Administrator::setUserAccount()
{
}

void Administrator::addAccount()
{
}
