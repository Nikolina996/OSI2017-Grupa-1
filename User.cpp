#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include "User.h"
#include"Windows.h"
using namespace std;

void User::userMenu() //basic menu
{
	system("CLS");
	cout << "\t\tMastermind Analyze" << endl << endl;
	cout << "Enter the number of the option:" << endl << "[1] Log in" << endl << "[2] Sign up" << endl << "[0] Exit" << endl;
}

void User::signUp() //Function for registration
{
	system("CLS");
	cout << "\t\tMastermind Analyze" << endl << endl;
	string name, surname, username, PIN, tmpPIN;
	string tmpName, tmpSurname, tmpUser;
	int check_user = 1, check_pin = 1, sum = 0;
	char ch;
	cout << "Name: "; cin >> name;
	cout << "Surname: "; cin >> surname;
	ifstream file("C:\\MasterMindAnalyze\\Users\\Users.txt");
	if (file.is_open())
	{
		do
		{
			cout << "Username: "; cin >> username;
			while (!file.eof() && username != tmpUser)
				file >> tmpName >> tmpSurname >> tmpUser >> tmpPIN;
			if (tmpUser == username) { //Checking if the same username already exists
				cout << "Username already exists. Please enter another." << endl;
				Sleep(1000); Sleep(1000);
			}
			else check_user = 0;
		} while (check_user);
	}
	else
	{
		cout << "Could not open info file" << endl;
		Sleep(1000); Sleep(1000);
		return;
	}
	do
	{
		cout << "Password (4 numbers): "; 
		ch = _getch();
		while (ch != 13) {//character 13 is enter
			PIN.push_back(ch);
			cout << '*';
			ch = _getch();
		}
		for (int i = 0; i < 4; i++)
			if (isdigit(PIN[i])) sum++; //Checks if the entered character is a number
		if (sum != 4)
		{
			cout << "Structure of password must be 4 positive numbers." << endl;
			sum = 0;
		}
		else check_pin = 0;
	} while (check_pin);
	PIN.shrink_to_fit();
	ofstream object("C:\\MasterMindAnalyze\\Users\\Waiting_list.txt", ios::app);
	if (object.is_open())
	{
		object << name << ' ' << surname << ' ' << username << ' ' << PIN << "\n";
		object.close();
		cout << endl << "Your registration request has been successfully sent." << endl;
		Sleep(2000);
	}
	else
	{
		cout << "Could not open file." << endl;
		Sleep(2000);
	}
}

void User::logInMenu() //submenu
{
	system("CLS");
	cout << "\t\tMastermind Analyze" << endl << endl;
	cout << "\tLog in menu" << endl;
	cout << "Enter the number of the option:" << endl << "[1] Administrator" << endl << "[2] Analyst" << endl << "[0] Back" << endl;
}
