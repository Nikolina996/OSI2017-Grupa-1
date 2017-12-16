#include<iostream>
#include<fstream>
#include<string>
#include "User.h"
using namespace std;

void User::userMenu() //basic menu
{
	int i; 
	cout<<"/tMastermind Analyze"<<endl;
	cout << "Enter the number of the option:" << endl << "[1] Log in" << endl << "[2] Sign up" << endl << "[0]Exit" << endl;
	cin>>i;
	if (i==0)
	   return; 
	else if (i==1)
	    logIn();
	else if (i==2)
	     singUp();
	else
	     userMenu();
}

void User::signUp()
{
  string name, surname, username;
	string tmpName, tmpSurname, tmpUser;
	char PIN[5], tmpPIN[5];
	int check_user = 1, check_pin = 1, sum = 0;
	cout << "Name: "; cin >> name;
	cout << "Surname: "; cin >> surname;
	ifstream file("korisnici.txt");
	if (file.is_open())
	{
		do
		{
			cout << "Username: "; cin >> username;
			while (!file.eof() && username != tmpUser)
				file >> tmpName >> tmpSurname >> tmpUser >> tmpPIN;
			if (tmpUser == username)
				cout << "Username already exists. Please enter another." << endl;
			else check_user = 0;
		} while (check_user);
	}
	else
	{
		cout << "Could not open file 'korisnici.txt'." << endl;
		return;
	}
	do
	{
		cout << "Password: "; cin >> PIN;
		for (int i = 0; i < 4; i++)
			if (isdigit(PIN[i])) sum++;
		if (sum != 4)
		{
			cout << "Structure of password must be 4 positive numbers." << endl;
			sum = 0;
		}
		else check_pin = 0;
	} while (check_pin);
	ofstream object("lista_cekanja.txt", ios::app);
	if (object.is_open())
	{
		object << "\n" << name << ' ' << surname << ' ' << username << ' ' << PIN;
		object.close();
	}
	else
		cout << "Could not open file." << endl;
}

