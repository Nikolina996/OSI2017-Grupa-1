#include<iostream>
#include<string>
#include<fstream>
#include "Analyst.h"
#include "User.h"
#include "Windows.h"
using namespace std;

Analyst::Analyst(char *a, char *b, char *c, char *d):User(a, b, c, d)
{}

Analyst::~Analyst()
{}

void Analyst::userMenu()
{
	int i;
	cout<<"/tMastermind Analyze"<<endl;
	cout << "Enter the number of the option:" << endl << "[1] Bills overview" << endl << "[2] Account control" << endl << "[0]Exit" << endl;
	cin>>i;
	if (i==0)
	    return;
	else if (i==1)
	    reviewOfProcessedData();
	else if (i==2)
	    accountControl();
	else userMenu();
}

bool Analyst::logIn()
{
	string username, PIN, tmpUser, tmpPIN, tmpName, tmpSurname;
	int check = 1; char c_check;
	do
	{
		cout << "Username: "; cin >> username;
		cout << "Password: "; cin >> PIN;
		ifstream userFile("korisnici.txt");
		cout << "Searching through files";
		for (int i = 0; i < 3; i++) cout << ".", Sleep(1000); cout << endl;
		if (userFile.is_open())
		{
			while (!userFile.eof() && username != tmpUser && PIN != tmpPIN)
				userFile >> tmpName >> tmpSurname >> tmpUser >> tmpPIN;
			if (username == tmpUser && PIN == tmpPIN)
			{
				cout << "Successful log in!" << endl;
				userFile.close();
				check = 0;
				return true;
			}
		}
		else
		{
			cout << "Error. Could not open 'korisnici.txt' file." << endl;
			return false;
		}
		ifstream userFile1("lista_neodobrenih.txt");
		if (userFile1.is_open())
		{
			tmpUser = "xxx";
			while (!userFile1.eof() && username != tmpUser)
				userFile1 >> tmpName >> tmpSurname >> tmpUser >> tmpPIN;
			if (username == tmpUser)
			{
				cout << "Your registration was not approved by admin." << endl;
				userFile1.close();
				check = 0;
				return false;
			}
		}
		else
		{
			cout << "Error. Could not open 'lista_neodobrenih.txt' file." << endl;
			return false;
		}
		ifstream userFile2("lista_cekanja.txt");
		if (userFile2.is_open())
		{
			tmpUser = "xxx";
			while (!userFile2.eof() && username != tmpUser)
				userFile2 >> tmpName >> tmpSurname >> tmpUser >> tmpPIN;
			if (username == tmpUser)
			{
				cout << "Your registration is waiting for approval." << endl;
				userFile2.close();
				check = 0;
				return false;
			}
		}
		else
		{
			cout << "Could not open 'lista_cekanja.txt' file." << endl;
			return false;
		}
		cout << "Username or password do not match." << endl;
		cout << "Please leave (enter E) if you are a malicious user that never registered here" << endl;
		cout << "or try again (enter A)" << endl;
		cin >> c_check;
		system("CLS");
		if (c_check == 'E') return false;
	} while (check || c_check == 'A');
}

void Analyst::setAccount()
{
}

void Analyst::reviewOfProcessedData()
{
}

