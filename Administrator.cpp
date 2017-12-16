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
	int i; 
	cout<<"/tMastermind Analyze"<<endl;
	cout << "Enter the number of the option:" << endl << "[1] Currency adjustment" << endl << "[2] Review and manage user accounts" << endl << "[0]Exit" << endl;
	cin>>i;
	if (i==0)
	    return; 
	else if (i==1)
		currencyChange();
	else if (i==2)
		reviewAndManageUserAccount();
	else userMenu();
	
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
void reviewAndManageUserAccounts()
{
int i;
cout<<"/tMastermind Analyze"<<endl;
	cout << "Enter the number of the option:" << endl << "[1] New requests" << endl << "[2] Delete requests" <<"[3] Manage user accounts"<<"[4] Review user accounts"<<"[5] Add accounts" << endl << "[0]Exit" << endl;
        cin>>i;
	if (i==0)
           return;
	else if (i==1)
	   newRequests();
	else if (i==2)
	   deleteUser();
	else if (i==3)
	    menagingUserAccounts();
	else if (i==4)
	    reviewUserAccount();
	else if (i==5)
	    addAccount();
	else reviewAndManageUserAccounts();
	
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

void Administrator::setUserAccount()
{
}

void Administrator::addAccount()
{
}
