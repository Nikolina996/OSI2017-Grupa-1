#include<iostream>
#include<fstream>
#include<string>
#include <iomanip>
#include<conio.h>
#include "Administrator.h"
#include "User.h"
#include "Windows.h"
using namespace std;
std::string tempCurrency = "bam"; //global streaming valute

void Administrator::userMenu() //Aministrator menu 
{
	int i; 
	do {
		system("CLS");
		std::cout << "\t\tMastermind Analyze" << endl << endl;
		std::cout << "Enter the number of the option:" << endl << "[1] Currency adjustment" << endl << "[2] Review and manage user accounts" << endl << "[3] Set account " << endl << "[0] Log out" << endl;
		cin >> i;
		if (i == 0)
			return;
		else if (i == 1)
			changeCurrency();
		else if (i == 2)
			reviewAndManageUserAccounts();
		else if (i == 3)
			setAccount();
	} while (i != 1 || i != 2 || i!=3);
}

bool Administrator::logIn()
{
	string username, password, user, pass, name, surname; 
	int input;
	char ch;
	do {
		password = "";
		system("CLS");
		cout << "\t\tMastermind Analyze" << endl << endl;
		cout << "Username: ";
		cin >> username;
		cout << "Password (If you enter the wrong password, just press 'Enter' and you will be able to\nenter the password again): ";
		ch = _getch();
		while (ch != 13) {//character 13 is enter
			password.push_back(ch);
			cout << '*';
			ch = _getch();
		}
		ifstream adminFile("C:\\MasterMindAnalyze\\Users\\Admin_file.txt");
		if (adminFile.is_open())
		{
			adminFile >> name >> surname >> user >> pass;
			if (username == user && password == pass)
			{
				cout << endl << "Login successful!" << endl;
				Sleep(2000);
				return true; 
			}
			else
			{
				cout << endl << "Username or password do not match." << endl;
				cout << "[1] Try again" << endl << "[0] Back" << endl;
				cin >> input;
				if(input==0)
					return false;
			}
		}
		else {
			cout << "Could not open info file." << endl;
			Sleep(2000); 
		}
	} while (input == 1);
}

void Administrator::setAccount()
{
	string name, surname, username, PIN, password, oldPIN;
	int sum = 0;
	char ch;
	ifstream file("C:\\MasterMindAnalyze\\Users\\Admin_file.txt");
	if (file.is_open())
	{
		file >> name >> surname >> username >> password;
		file.close();
	}
	else
	{
		cout << "Could not open info file." << endl;
		Sleep(2000);
	}
	do
	{
		oldPIN = "";
		system("CLS");
		cout << "\t\tMastermind Analyze" << endl << endl;
		cout << "Please type in old password: ";
		ch = _getch();
		while (ch != 13) {//character 13 is enter
			oldPIN.push_back(ch);
			cout << '*';
			ch = _getch();
		}
		oldPIN.shrink_to_fit();
		if (password.compare(oldPIN) == 0)
		{
			do
			{
				PIN = "";
				cout << endl << "Enter new password: ";
				ch = _getch();
				while (ch != 13) {//character 13 is enter
					PIN.push_back(ch);
					cout << '*';
					ch = _getch();
				}
				for (int i = 0; i < 4; i++)
					if (isdigit(PIN[i])) sum++;//Checks if the entered character is a number
				if (sum != 4)
				{
					cout << endl << "Structure of password must be 4 positive numbers." << endl;
					sum = 0;
				}
			} while (sum != 4);
		}
		else cout << endl << "Passwords do not match. Enter again:" << endl;
	} while (password.compare(oldPIN) != 0);
	ofstream newInfo("C:\\MasterMindAnalyze\\Users\\Admin_file.txt", ofstream::out | ofstream::trunc);
	if (newInfo.is_open())
	{
		PIN.shrink_to_fit();
		newInfo << name << " " << surname << " " << username << " " << PIN;
		newInfo.close();
		cout << endl << "Password successfuly changed!" << endl;
		Sleep(2000);
	}
	else {
		cout << "Could not open info file" << endl;
		Sleep(2000);
	}
}

void Administrator::reviewAndManageUserAccounts() //Administrator submenu
{
	int i;
	do {
		system("CLS");
		cout << "\t\tMastermind Analyze" << endl<<endl;
		cout << "Enter the number of the option:" << endl << "[1] New requests" << endl << "[2] Delete user" << endl << "[3] Review user accounts" << endl << "[0] Back to the menu" << endl;
		cin >> i;
		if (i == 0)
			return;
		else if (i == 1)
			newRequests();
		else if (i == 2)
			deleteUser();
		else if (i == 3)
			reviewUserAccounts();
	} while (i != 1 || i != 2 || i != 3);
}

void Administrator::changeCurrency()
{
	system("CLS");
	cout << "\t\tMastermind Analyze" << endl << endl;
	cout << "Function will be available in the next update." << endl;
	//Temporary currency is global string
	int option; string newCURR;
	cout << "Temporary currency: " << tempCurrency << endl;
	Sleep(3000);
	/*cout << "Change to:" << endl << "[1]bam [2]usd [3]euro" << endl;
	do { cin >> option; } while (option < 1 || option > 3);
	if (option == 1) newCURR = "bam";
	else if (option == 2) newCURR = "usd";
	else if (option == 3) newCURR = "euro";
	1) OPEN ALL NEEDED FILES
	2) OVERWRITE CURRENCY VIA currencyConverter(string, string, double) function
	2) CLOSE ALL FILES
	*/
}

void Administrator::deleteUser()
{
	string user, name, surname, username="*", PIN, tmp="*"; 
	int input, i, size;
	do {
		system("CLS");
		cout << "\t\tMasterMind Analyze" << endl << endl;
		cout << "[1] Look at the list of registered users" << endl << "[2] Enter username of the user you want to delete:" << endl << "[0] Back" << endl;
		cin >> input;
		if (input == 1)
			reviewUserAccounts();
		else if (input == 2)
		{
			system("CLS");
			cout << "\t\tMasterMind Analyze" << endl << endl;
			cout << "Enter username of the user you want to delete: ";
			cin >> user; 
			user.shrink_to_fit();
			ifstream file("C:\\MasterMindAnalyze\\Users\\Users.txt");
			if (file.is_open())
			{
				while (!file.eof() && user != username)
					file >> name >> surname >> username >> PIN;
				i = file.tellg();
				file.close();
				size = i - (name.length() + surname.length() + username.length() + PIN.length() + 3);
			}
			fstream fileX("C:\\MasterMindAnalyze\\Users\\Users.txt", ofstream::out | ifstream::in);
			if (fileX.is_open())
			{
				fileX.seekg(size);
				fileX << tmp;
				cout << "User successfully deleted." << endl;
				Sleep(2000);
				fstream object("C:\\MasterMindAnalyze\\Users\\Deleted_users.txt", ofstream::out | ofstream::app);
				object << name << " " << surname << " " << username << " " << PIN << "\n";
				object.close();
				fileX.close();
			}
		}
		else if (input == 0)
			return;
	} while (input != 1 || input != 2);
}

double Administrator::currencyConverter(string oldCurrency, string newCurrency, double oldCurrencyValue)
{
	/*1 bam = 0.51 e, 1 bam = 0.62 usd, 1 e = 1.95 bam, 1 e = 1.21 usd, 1 usd = 1.6 bam, 1 usd = 0.81 e*/
	if (oldCurrency == "bam" && newCurrency == "usd")
		return oldCurrencyValue * 0.62;
	else if (oldCurrency == "bam" && newCurrency == "euro")
		return oldCurrencyValue * 0.51;
	else if (oldCurrency == "usd" && newCurrency == "bam")
		return oldCurrencyValue * 1.6;
	else if (oldCurrency == "usd" && newCurrency == "euro")
		return oldCurrencyValue * 0.81;
	else if (oldCurrency == "euro" && newCurrency == "bam")
		return oldCurrencyValue * 1.95;
	else if (oldCurrency == "euro" && newCurrency == "usd")
		return oldCurrencyValue * 1.25;
	else
		cout << "Currency is already set";
}

void Administrator::newRequests() //The function that checks are there any new registration requests, and if there are the 
{								  //admin is given the option to approve or disapprove the request.
	system("CLS");
	cout << "\t\tMastermind Analyze" << endl << endl;
	string name, surname, username, line, tmp, s1, s2, s3, s4; 
	char PIN[5], cp = '/', cc = '/'; 
	int input, numberOfRequests = 0, in;
	ifstream file("C:\\MasterMindAnalyze\\Users\\Waiting_list.txt");
	if (file.is_open())
	{
		do {
			cp = file.peek();
			if (isalpha(cp))
			{
				while (!file.eof())
				{
					file >> s1 >> s2 >> s3 >> s4;
					numberOfRequests++;
				}
				numberOfRequests -= 1;
				cout << "You have " << numberOfRequests << " new requests." << endl;
				file.close();
				ifstream fileX("C:\\MasterMindAnalyze\\Users\\Waiting_list.txt");
				ofstream object("C:\\MasterMindAnalyze\\Users\\Users.txt", ios::app); 
				ofstream disapproved("C:\\MasterMindAnalyze\\Users\\List_of_disapproved_users.txt", ios::app);
				if (object.is_open() && disapproved.is_open())
				{
					while (!fileX.eof())
					{
						fileX >> name >> surname >> username >> PIN;
						if (numberOfRequests != 0) {
							cout << endl << "Request from: " << endl;
							cout << name << " " << surname << " " << username << endl << endl;
							do {
								cout << "[1] Approve the registration request" << endl;
								cout << "[0] Disapprove the registration request" << endl;
								cin >> input;
								if (input == 1) {
									object << name << ' ' << surname << ' ' << username << ' ' << PIN << "\n";
									cout << "User has been successfully added to the user list" << endl;
									Sleep(2000);
									numberOfRequests--;
								}
								else if (input == 0)
								{
									disapproved << name << ' ' << surname << ' ' << username << ' ' << PIN << "\n";
									cout << "The user has been added to the list of unauthorized users." << endl;
									Sleep(2000);
									numberOfRequests--;
								}
							} while (input != 0 && input != 1);
						}
					}
					fileX.close();
					object.close(); disapproved.close();
				}
				else {
					cout << "Could not open info file." << endl;
					Sleep(2000);
				}
			}
			system("CLS");
			cout << "\t\tMastermind Analyze" << endl << endl;
			cout << "No new registration requirements." << endl << "[0] Back" << endl; 
			cin >> in;
		} while (in != 0);
	}
	else
	{
		cout << "Could not open info file." << endl;
		Sleep(2000);
	}
	std::ofstream ofs;
	ofs.open("C:\\MasterMindAnalyze\\Users\\Waiting_list.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

void Administrator::reviewUserAccounts()
{
	int numberOfUsers = 0, input; 
	do {

		system("CLS");
		cout << "\t\tMastermind Analyze" << endl << endl;
		cout << "List of all registered users:" << endl;
		ifstream file("C:\\MasterMindAnalyze\\Users\\Users.txt");
		string name, surname, username, PIN, s1, s2, s3, s4, tmp = "/";
		cout << "_______________________________________________________" << endl;
		cout << left << setw(15) << "Name" << left << setw(15) << "Surname" << left << setw(25) << "Username" << endl;
		cout << "_______________________________________________________" << endl;
		if (file.is_open())
		{
			while (!file.eof())
			{
				file >> s1 >> s2 >> s3 >> s4;
				if(s1[0]!='*' && tmp!=s3)
					numberOfUsers++;
				tmp = s3;
			}
			file.close();
		}
		else
		{
			cout << "Could not open info file." << endl;
			Sleep(2000);
		}
		ifstream fileX("C:\\MasterMindAnalyze\\Users\\Users.txt");
		if (fileX.is_open()) {
			while (numberOfUsers != 0)
			{
				fileX >> name >> surname >> username >> PIN;
				if (name[0] != '*') {
					cout << left << setw(15) << name << left << setw(15) << surname << left << setw(25) << username << endl;
					numberOfUsers--;
				}
			}
			fileX.close();
		}
		else
		{
			cout << "Could not open info file." << endl;
			Sleep(2000);
		}
		cout << "_______________________________________________________" << endl;
		cout << "[0] Back" << endl; cin >> input;
	} while (input != 0);
	if (input == 0)
		return;
}
