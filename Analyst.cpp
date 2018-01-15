#include<iostream>
#include<string>
#include<fstream>
#include "Analyst.h"
#include "User.h"
#include "Windows.h"
using namespace std;

static string t = ".txt", f1="F1_", f2="F2_", f3="F3_", f4="F4_";

void Analyst::userMenu()
{
	int i;
	cout<<"/tMastermind Analyze"<<endl;
	cout << "Enter the number of the option:" << endl <<"[1] Review of processed data" << endl << "[2] Set account" << endl << "[0] Log out" << endl;
	cin>>i;
	if (i==0)
	    User::userMenu();
	else if (i==1)
	    reviewOfProcessedData();
	else if (i==2)
	    setAccount();
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

void setAccount()
{
	string username, PIN,oldPIN, newPIN, tmpUser; int i, sum=0;
	tmpUser=getUsername();
	fstream file("korisnici.txt", ofstream::out | ifstream::in);
	if (file.is_open())
	{
		while (!file.eof() && username != tmpUser)
			file >> username>>oldPIN;
		i = file.tellp();
		file.seekp(i-4);
		do
		{
			cout << "Please type in old password: "; cin >> PIN;
			if (PIN.compare(oldPIN) == 0)
			{
				do
				{
					cout << "Enter new password: "; cin >> newPIN;
					for (int i = 0; i < 4; i++)
						if (isdigit(newPIN[i])) sum++;
					if (sum != 4)
					{
						cout << "Structure of password must be 4 positive numbers." << endl;
						sum = 0;
					}
				} while (sum != 4);
			}
			else cout << "Passwords do not match. Enter again:" << endl;
		} while (PIN.compare(oldPIN) != 0);
		file << newPIN;
		cout << "Password successfuly changed!" << endl;
	}
	else
		cout << "Could not open 'users.txt' file" << endl;
}

void Analyst::reviewOfProcessedData()
{
	int i; 
	system ("CLS");
	cout<<"/tMastermind Analyze"<<endl;
	cout << "Enter the number of the option:" << endl <<"[1] Viewing data for a particular user"<<endl<<"[2] Review data for a specific product"<<endl<<"[3] View data for a specific month"<<endl<<"[0] Back to the menu"<<endl;
	if (i==1)
		ViewingDataForAParticularUser();
	else if(i==2)
		RewievDataForASpecificProduct();
	else if (i==3)
		ViewDataForASpecificMonth(); 
	else if (i==0)
		userMenu(); 
	else reviewOfProcessedData();
}

void Analyst::viewingDataForAParticularUser()
{
	string name, filename, line; int number; 
	do {
		system("CLS");
		cout << "[0] Back to menu" << endl << "[1] Enter name" << endl;
		cin >> number;
		if (number == 1) {
			cout << "Enter customer name: ";
			cin >> name;
			filename = name + t;
			ifstream file(filename);
			if (file.is_open())
			{
				system("CLS");
				cout << name << " - purchased products:" << endl << endl;
				cout << "DATE NAME&CODE AMOUNT PRICE" << endl << endl;
				while (!file.eof())
				{
					getline(file, line);
					cout << line << endl;

				}
				getchar();
				getchar();

			}
			else
				cout << "Could not open info file or there are no users with that name." << endl;
		}
		if(number==0)
			return;
	} while (number != 0);
}

void Analyst::reviewDataForASpecificProduct()
{
	string code, name, filename, line; int number;
	do
	{
		system("CLS");
		cout << "[0] Back to menu" << endl << "[1] Enter code and name of product" << endl;
		cin >> number;
		if (number == 1)
		{
			cout << "Enter name and code:"; cin >> name >> code;
			filename = name + code + t;
			ifstream file(filename);
			if (file.is_open())
			{
				system("CLS");
				cout << "Product - " << name << code << endl << endl;
				cout << "DATE CUSTOMER AMOUNT" << endl << endl;
				while (!file.eof())
				{
					getline(file, line);
					cout << line << endl;
				}
				getchar();
				getchar();
			}
			else
				cout << "Could not open info file or there are no products with that name and code." << endl;
		}
		if (number == 0)
			return;
	} while (number != 0);
}

void Analyst::viewDataForASpecificMonth()
{
		string line, month, year, filename; int number;
	do
	{
		system("CLS");
		cout << "[0] Back to menu" << endl << "[1] Enter month and year" << endl;
		cin >> number;
		if (number == 1)
		{
			cout << "Enter month and year: ";
			cin >> month >> year;
			filename = month + year + t;
			ifstream file(filename);
			if (file.is_open())
			{
				system("CLS");
				cout << month << " " << year << endl << endl;
				cout << "DATE NAME&CODE AMOUNT CUSTOMER PRICE" << endl << endl;
				while (!file.eof())
				{
					getline(file, line);
					cout << line << endl;
				}
			}
			else
				cout << "Could not open info file or there's no data for that month" << endl;
		}
		if (number == 0)
			return;
	} while (number != 0);
}

void getBills()
{
	string filename; 
	do {
		filename = name();
		//obrada svakog racuna
	} while (filename != "error");
}

string name()
{
	string filename;
	filename = getname("F1.txt", f1);
	if (filename != "Not exist")
		return filename;
	else
		filename = getname("F2.txt", f2);
	if (filename != "Not exist")
		return filename;
	else
		filename= getname("F3.txt", f3);
	if (filename != "Not exist")
		return filename;
	else
		filename = getname("F4.txt", f4);
	if (filename != "Not exist")
		return filename;
	return "error";
}

string getname(string format, string f) 
{
	ifstream formatnumber(format);
	string fs, filename;
	unsigned int fn;
	formatnumber >> fn;
	formatnumber.close();
	fn += 1;
	fs = to_string(fn);
	filename = f + fs + t;
	if (doesItExist(filename, fn, format))
		return filename;
	else
		return "Not exist";
}

bool doesItExist(string filename, unsigned int f, string format)
{
	ifstream file(filename);
	if (file.is_open())
	{
		fstream formatnumber;
		formatnumber.open(format, std::fstream::out | std::fstream::trunc);
		formatnumber << f;
		formatnumber.close();
		file.close();
		return true;
	}
	else
		return false;
}
