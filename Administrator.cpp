#include<iostream>
#include<fstream>
#include<string>
#include <iomanip>

#include "Administrator.h"
#include "User.h"

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
	string name, surname, username, password;
	char PIN[5], oldPIN[5]; int sum = 0;
	ifstream file("admin.txt");
	if (file.is_open())
	{
		file >> name >> surname >> username >> password;
		file.close();
	}
	else cout << "Could not open 'admin.txt' file." << endl;
	do
	{
		cout << "Please type in old password: "; cin >> oldPIN;
		if (password.compare(oldPIN) == 0)
		{
			do
			{
				cout << "Enter new password: "; cin >> PIN;
				for (int i = 0; i < 4; i++)
					if (isdigit(PIN[i])) sum++;
				if (sum != 4)
				{
					cout << "Structure of password must be 4 positive numbers." << endl;
					sum = 0;
				}
			} while (sum != 4);
		}
		else cout << "Passwords do not match. Enter again:" << endl;
	} while (password.compare(oldPIN) != 0);
	ofstream newInfo("admin.txt", ofstream::out | ofstream::trunc);
	if (newInfo.is_open())
	{
		newInfo << name << " " << surname << " " << username << " " << PIN;
		newInfo.close();
		cout << "Password successfuly changed!" << endl;
	}
	else
		cout << "Could not open 'admin.txt' file" << endl;
}

void Administrator::currencyChange()
{
}

void Administrator::deleteUser()
{
}

void Administrator::newRequests()
{
	string name, surname, username, line; char PIN[5]; int input, numberOfRequests = 0; int c=NULL;
	ifstream file("lista_cekanja.txt");
	if (file.is_open())
	{
		c = file.peek(); 
		if(c==-1)
			cout << "No new registration requirements." << endl;
		else
		{
			while (!file.eof())
			{
				getline(file, line); numberOfRequests++;
			}
			cout << "You have " << numberOfRequests << " new requests." << endl;
			file.seekg(0);
			ofstream object("korisnici.txt", ios::app); ofstream disapproved("lista_neodobrenih.txt", ios::app);
			if (object.is_open() && disapproved.is_open())
			{
				while (!file.eof())
				{
					file >> name >> surname >> username >> PIN;
					cout << endl << "Request from: " << endl;
					cout << name << " " << surname << " " << username << " " << PIN << endl << endl;
					do {
						cout << "[1] Approve the registration request" << endl;
						cout << "[0] Disapprove the registration request" << endl;
						cin >> input;
						if (input == 1) {
							object << "\n" << name << ' ' << surname << ' ' << username << ' ' << PIN;
							cout << "User has been successfully added to the user list" << endl;
						}
						else if (input == 0)
						{
							disapproved << "\n" << name << ' ' << surname << ' ' << username << ' ' << PIN;
							cout << "The user has been added to the list of unauthorized users." << endl;
						}
					} while (input != 0 && input != 1);
				}
				object.close(); disapproved.close();
			}
			else
				cout << "Could not open info file." << endl;
		}
	}
	else
		cout << "Could not open info file." << endl;
	file.close();
	std::ofstream ofs;
	ofs.open("lista_cekanja.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}
void reviewUserAccounts()
{
	cout << "List of all registered users:" << endl;
	ifstream file("korisnici.txt");
	string name, surname, username, PIN;
	cout << "_______________________________________________________" << endl;
	if (file.is_open())
	{
		while (!file.eof())
		{
			file >> name >> surname >> username >> PIN;
			cout << setw(15) << name << setw(15) << surname << setw(25) << username << endl;
		}
	}
	else
		cout << "Could not open 'korisnici.txt' file." << endl;
	cout << "_______________________________________________________" << endl;
}
