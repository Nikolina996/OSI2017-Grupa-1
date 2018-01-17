#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<conio.h>
#include "Analyst.h"
#include "User.h"
#include "Windows.h"
#include "LinkedList.h"
using namespace std;

static string t = ".txt", f1 = "F1_", f2 = "F2_", f3 = "F3_", f4 = "F4_";

void Analyst::setUsername(string user)
{
	username = user; //sets up a private information so that the username can be used in the account setup function 
					 //without re-entering it
}

void Analyst::userMenu() //Analyst menu
{
	int i;
	do {
		system("CLS");
		cout << "\t\tMastermind Analyze" << endl << endl;
		cout << "Enter the number of the option:" << endl << "[1] Review of processed data" << endl << "[2] Set account" << endl << "[0] Log out" << endl;
		cin >> i;
		if (i == 0)
			return;
		else if (i == 1)
			reviewOfProcessedData();
		else if (i == 2)
			setAccount();
	} while (i != 1 || i != 2);
}

bool Analyst::logIn() 
{
	string username, PIN, tmpUser, tmpPIN, tmpName, tmpSurname;
	int check = 1; char c_check, ch;
	do
	{
		system("CLS");
		cout << "\t\tMastermind Analyze" << endl << endl;
		cout << "Username: "; cin >> username;
		cout << "Password: "; 
		ch = _getch();
		while (ch != 13) {//character 13 is enter
			PIN.push_back(ch);
			cout << '*';
			ch = _getch();
		}
		cout << endl << "Searching through files";
		for (int i = 0; i < 3; i++) cout << ".", Sleep(1000); cout << endl;
		ifstream deleted("C:\\MasterMindAnalyze\\Users\\Deleted_users.txt");
		if (deleted.is_open())
		{
			tmpUser = "xxx";
			while (!deleted.eof() && username != tmpUser) //Check if the user is in the list of deleted users
				deleted >> tmpName >> tmpSurname >> tmpUser >> tmpPIN;
			if (username == tmpUser)
			{
				cout << endl << "Your account was deleted by administrator." << endl;
				Sleep(2000);
				deleted.close();
				check = 0;
				return false;
			}
		}
		else
		{
			cout << "Could not open info file." << endl;
			Sleep(2000);
			return false;
		}
		ifstream userFile("C:\\MasterMindAnalyze\\Users\\Users.txt");
		if (userFile.is_open())
		{
			while (!userFile.eof() && username != tmpUser && PIN != tmpPIN)
				userFile >> tmpName >> tmpSurname >> tmpUser >> tmpPIN;
			if (username == tmpUser && PIN == tmpPIN) //Check if there is a user and match the codes
			{
				cout << "Successful log in!" << endl;
				setUsername(username);
				Sleep(2000);
				userFile.close();
				check = 0;
				return true;
			}
		}
		else
		{
			cout << "Could not open info file." << endl; 
			Sleep(2000);
			return false;
		}
		ifstream userFile1("C:\\MasterMindAnalyze\\Users\\List_of_disapproved_users.txt");
		if (userFile1.is_open())
		{
			tmpUser = "xxx";
			while (!userFile1.eof() && username != tmpUser) //Check if the user is in the list of disapproved users
				userFile1 >> tmpName >> tmpSurname >> tmpUser >> tmpPIN;
			if (username == tmpUser)
			{
				cout << endl << "Your registration was not approved by administrator." << endl;
				Sleep(2000);
				userFile1.close();
				check = 0;
				return false;
			}
		}
		else
		{
			cout << "Could not open info file." << endl;
			Sleep(2000);
			return false;
		}
		ifstream userFile2("C:\\MasterMindAnalyze\\Users\\Waiting_list.txt");
		if (userFile2.is_open())
		{
			tmpUser = "xxx";
			while (!userFile2.eof() && username != tmpUser) //Verifying that the user's request is still in the waiting list
				userFile2 >> tmpName >> tmpSurname >> tmpUser >> tmpPIN;
			if (username == tmpUser)
			{
				cout << endl << "Your registration is waiting for approval." << endl;
				Sleep(2000);
				userFile2.close();
				check = 0;
				return false;
			}
		}
		else
		{
			cout << "Could not open info file." << endl;
			Sleep(2000);
			return false;
		}
		cout << "Username or password do not match." << endl;
		cout << "[1] Try again" << endl << "[0] Back" << endl;
		cin >> c_check;
		if (c_check == '0') return false;
	} while (check || c_check == '1');
}

void Analyst::setAccount()
{
	string PIN, oldPIN, newPIN, tmpUser; 
	int i, sum = 0;
	char ch;
	fstream file("C:\\MasterMindAnalyze\\Users\\Users.txt", ifstream::in);
	if (file.is_open())
	{
		while (!file.eof() && username != tmpUser)
			file >> tmpUser >> oldPIN;
		i = file.tellg();
		i -= 4; //Remembering the position at which the password should be changed
		file.close();
	}
	fstream fileX("C:\\MasterMindAnalyze\\Users\\Users.txt", ofstream::out | ifstream::in);
	if (fileX.is_open())
	{
		do
		{
			system("CLS");
			cout << "\t\tMastermind Analyze" << endl << endl;
			cout << "Please type in old password: "; 
			ch = _getch();
			while (ch != 13) {//character 13 is enter
				PIN.push_back(ch);
				cout << '*';
				ch = _getch();
			}
			if (PIN.compare(oldPIN) == 0)
			{
				do
				{
					cout << endl << "Enter new password: "; //cin >> newPIN; 
					ch = _getch();
					while (ch != 13) {//character 13 is enter
						newPIN.push_back(ch);
						cout << '*';
						ch = _getch();
					}
					newPIN.shrink_to_fit(); 
					for (int i = 0; i < 4; i++)
						if (isdigit(newPIN[i])) sum++; //Checks if the entered character is a number
					if (sum != 4)
					{
						cout << endl << "Structure of password must be 4 positive numbers." << endl;
						sum = 0;
					}
				} while (sum != 4);
			}
			else
			{
				cout << endl << "Passwords do not match. Enter again:" << endl;
				Sleep(2000);
			}
		} while (PIN.compare(oldPIN) != 0);
		fileX.seekg(i);
		fileX << newPIN;
		cout << endl << "Password successfuly changed!" << endl;
		Sleep(2000);
		fileX.close();
	}
	else
	{
		cout << "Could not open info file" << endl;
		Sleep(2000);
	}
}

void Analyst::reviewOfProcessedData() //Analyst submenu
{
	int i;
	do {
		system("CLS");
		cout << "\t\tMastermind Analyze" << endl << endl;
		cout << "Enter the number of the option:" << endl << "[1] Viewing data for a particular customer" << endl << "[2] Review data for a specific product" << endl << "[3] View data for a specific month" << endl << "[0] Back to the menu" << endl;
		cin >> i;
		if (i == 1)
			viewingDataForAParticularUser();
		else if (i == 2)
			reviewDataForASpecificProduct();
		else if (i == 3)
			viewDataForASpecificMonth();
		else if (i == 0)
			return;
	} while (i != 1 || i != 2 || i != 3);
}

void Analyst::viewingDataForAParticularUser()
{
	string name, filename, date, productname, code, line; int number, amount, numberOfProducts = -1; double price;

	system("CLS");
	cout << "\t\tMastermind Analyze" << endl << endl;
	cout << "Enter customer name: ";
	cin >> name;
	filename = name + t;
	ifstream file("C:\\MasterMindAnalyze\\ProcessedData\\"+filename);
	if (file.is_open())
	{
		while (!file.eof())
		{
			getline(file, line);
			numberOfProducts++;
		}
	}
	file.close();
	ifstream fileX("C:\\MasterMindAnalyze\\ProcessedData\\" + filename);
	if (fileX.is_open()) {
		system("CLS");
		cout << "\t\tMastermind Analyze" << endl << endl;
		cout << name << " - purchased products:" << endl << endl;
		cout << "----------------------------------------------" << endl;
		cout << left << setw(11) << "DATE" << left << setw(19) << "PRODUCT(name&code)" << left << setw(7) << "AMOUNT" << left << setw(10) << "PRICE" << endl;
		cout << "----------------------------------------------" << endl;
		while (numberOfProducts)
		{
			fileX >> date >> productname >> code >> amount >> price;
			cout << left << setw(11) << date << left << setw(11) << productname << left << setw(8) << code << left << setw(7) << amount << left << setw(10) << price << endl;
			numberOfProducts--;
		}
		cout << "----------------------------------------------" << endl;
	}
	else
		cout << "Could not open info file or there are no customers with that name." << endl;
	fileX.close();
	cout << "[0] Back" << endl;
	cin >> number;
	if (number == 0)
		return;
}

void Analyst::reviewDataForASpecificProduct()
{
	string code, name, filename, date, customer, line; int number, amount, numberOfPurchases=-1;
	system("CLS");
	cout << "\t\tMastermind Analyze" << endl << endl;
	cout << "Enter name: "; cin >> name; cout << "Enter code: "; cin >> code;
	filename = name + code + t;
	ifstream file("C:\\MasterMindAnalyze\\ProcessedData\\" + filename);
	if (file.is_open())
	{
		while (!file.eof())
		{
			getline(file, line);
			numberOfPurchases++;
		}
	}
	file.close();
	ifstream fileX("C:\\MasterMindAnalyze\\ProcessedData\\" + filename);
	if(fileX.is_open())
	{
		system("CLS");
		cout << "\t\tMastermind Analyze" << endl << endl;
		cout << "Product - " << name << code << endl << endl;
		cout << "------------------------------------" << endl;
		cout << left << setw(11) << "DATE" << left << setw(15) << "CUSTOMER" << left << setw(7) << "AMOUNT" << endl;
		cout << "------------------------------------" << endl;
		while (numberOfPurchases)
		{
			fileX >> date >> customer >> amount;
			cout << left << setw(11) << date << left << setw(15) << customer << left << setw(7) << amount << endl;
			numberOfPurchases--;
		}
		cout << "------------------------------------" << endl;
	}
	else
		cout << "Could not open info file or there are no products with that name and code." << endl;
	cout << "[0] Back" << endl;
	fileX.close();
	cin >> number;
	if (number == 0)
		return;
}

void Analyst::viewDataForASpecificMonth()
{
	string line, month, year, filename, date, customer, productname, code; 
	int number, amount, numberOfProducts=-1; 
	double price;
	system("CLS");
	cout << "\t\tMastermind Analyze" << endl << endl;
	cout << "Enter month: ";
	cin >> month; cout << "Enter year: "; cin >> year;
	filename = month + year + t;
	ifstream file("C:\\MasterMindAnalyze\\ProcessedData\\" + filename);
	if (file.is_open())
	{
		while (!file.eof())
		{
			getline(file, line);
			numberOfProducts++;
		}
		file.close();
	}
	ifstream fileX("C:\\MasterMindAnalyze\\ProcessedData\\"+filename);
	if (fileX.is_open()){
		system("CLS");
		cout << "\t\tMastermind Analyze" << endl << endl;
		cout << month << " " << year << endl << endl;
		cout << "-------------------------------------------------------------" << endl;
		cout << left << setw(11) << "DATE" << left << setw(19) << "PRODUCT(name&code)" << left << setw(7) << "AMOUNT" << left << setw(10) << "PRICE" << left << setw(15) << "CUSTOMER" << endl;
		cout << "-------------------------------------------------------------" << endl;
		while (numberOfProducts)
		{
			fileX >> date >> productname >> code >> amount >> price >> customer; 
			cout << left << setw(11) << date << left << setw(11) << productname << left << setw(8) << code << left << setw(7) << amount << left << setw(10) << price << left << setw(15) << customer << endl;
			--numberOfProducts;
		}
		cout << "-------------------------------------------------------------" << endl;
	}
	else
		cout << "Could not open info file or there's no data for that month" << endl;
	fileX.close();
	cout << "[0] Back" << endl;
	cin >> number;
	if (number == 0)
		return;
}

void Analyst::name() //a function that invokes bill-processing functions, depending on the format
{
	string filename = "*";
	while (filename != "Not exist") {
		filename = getname("F1.txt", f1);
		if (filename != "Not exist")
			processingFormat1(filename);
	}
	filename = getname("F2.txt", f2);
	while (filename != "Not exist") {
		if (filename != "Not exist")
			processingFormat2(filename);
		filename = getname("F2.txt", f2);
	}
	filename = getname("F3.txt", f3);
	while (filename != "Not exist") {
		if (filename != "Not exist")
			processingFormat3(filename);
		filename = getname("F3.txt", f3);
	}
	filename = getname("F4.txt", f4);
	while (filename != "Not exist") {
		if (filename != "Not exist")
			processingFormat4(filename);
		filename = getname("F4.txt", f4);
	}
	return;
}

string Analyst::getname(string format, string f) //Auxiliary function that returns the name of the new bill (if it exists)
{
	ifstream formatnumber("C:\\MasterMindAnalyze\\Bills\\FormatInfo\\"+format);
	string fs, filename;
	unsigned int fn;
	formatnumber >> fn;
	formatnumber.close();
	fn += 1;
	fs = to_string(fn);
	filename = f + fs;
	if (doesItExist(filename + t, fn, format))
		return filename;
	else
		return "Not exist";
}

bool Analyst::doesItExist(string filename, unsigned int f, string format) //An auxiliary function that checks for new raw bills
{
	ifstream file("C:\\MasterMindAnalyze\\Bills\\"+filename);
	if (file.is_open())
	{
		fstream formatnumber;
		formatnumber.open("C:\\MasterMindAnalyze\\Bills\\FormatInfo\\" + format, std::fstream::out | std::fstream::trunc);
		formatnumber << f;
		formatnumber.close();
		file.close();
		return true;
	}
	else
		return false;
}

void Analyst::processingFormat1(string filename)
{
	string filen = filename + t;
	fstream file("C:\\MasterMindAnalyze\\Bills\\"+filen, ifstream::in);
	LinkedList bill;
	string customer, date, productName = "/", code, s1, s2, s3, tempStr = "|";
	int amount; double price, total, pdv, inTotal, payment;
	if (file.is_open())
	{
		for (; tempStr != "ukupno"; file >> tempStr)
			if (tempStr == "Kupac:") file >> customer;
			else if (tempStr == "Datum:") file >> date;
			file >> productName >> code >> s1 >> amount >> s2 >> price >> s3 >> total;
			for (; productName[1] != '-';)
				bill.addArticle(productName, code, amount, price, total),
				file >> productName >> code >> s1 >> amount >> s2 >> price >> s3 >> total;
	} file.close();
	fstream fileX("C:\\MasterMindAnalyze\\Bills\\" + filen, ifstream::in);
	if (fileX.is_open())
	{

		while (!fileX.eof())
		{
			fileX >> tempStr;
			if (tempStr == "Ukupno:") fileX >> inTotal;
			else if (tempStr == "PDV:") fileX >> pdv;
			else if (tempStr == "placanje:") fileX >> payment;
		}
	} 
	fileX.close();
	bill.setBillData(inTotal, pdv, payment, customer, date);
	bill.inspect(filename);
	bill.inputCustomerData();
	bill.inputMonthData();
	bill.inputProductData();
}

void Analyst::processingFormat2(string filename)
{
	string filen = filename + t;
	string customer, date, productName = "/", code, s1, s2, s3, tempStr = "|";
	double price, total, pdv, inTotal, payment; int amount;
	LinkedList bill;
	fstream file("C:\\MasterMindAnalyze\\Bills\\" + filen, ifstream::in);
	if (file.is_open())
	{
		for (; tempStr[1] != '-'; file >> tempStr)
			if (tempStr == "Kupac:") file >> customer;
		file >> productName >> code >> s1 >> amount >> s2 >> price >> s3 >> total;
		while (productName[0] != '-')
		{
			bill.addArticle(productName, code, amount, price, total);
			file >> productName >> code >> s1 >> amount >> s2 >> price >> s3 >> total;
		}
	} file.close();
	fstream fileX("C:\\MasterMindAnalyze\\Bills\\" + filen, ifstream::in);
	if (fileX.is_open())
	{
		while (!fileX.eof())
		{
			fileX >> tempStr;
			if (tempStr == "Ukupno:") fileX >> inTotal;
			else if (tempStr == "PDV:") fileX >> pdv;
			else if (tempStr == "placanje:") fileX >> payment;
			else if (tempStr == "Datum:") fileX >> date;
		}
	} 
	fileX.close();
	bill.setBillData(inTotal, pdv, payment, customer, date);
	bill.inspect(filename);
	bill.inputCustomerData();
	bill.inputMonthData();
	bill.inputProductData();
}

void Analyst::processingFormat3(string filename)
{
	string filen = filename + t;
	string date, customer, productName = "*", code, tempStr = "*", s1, s2, s3, line = "*";
	double inTotal, price, PDV, total, payment; int amount;
	LinkedList bill;
	fstream file("C:\\MasterMindAnalyze\\Bills\\" + filen, ifstream::in);
	if (file.is_open())
	{
		while (!file.eof())
		{
			file >> tempStr;
			if (tempStr == "Kupac:") file >> customer;
			else if (tempStr == "Datum:") file >> date;
			else if (tempStr == "Ukupno:") file >> inTotal;
			else if (tempStr == "PDV:") file >> PDV;
			else if (tempStr == "placanje:") file >> payment;
		}
	}
	bill.setBillData(inTotal, PDV, payment, customer, date);
	file.close();
	fstream fileX("C:\\MasterMindAnalyze\\Bills\\" + filen, ifstream::in);
	if (fileX.is_open())
	{
		for (; tempStr[1] != '-'; fileX >> tempStr);
		if (tempStr[1] == '-')
			while (productName[1] != '-')
			{
				code = ""; s1 = ""; s2 = "";
				fileX >> productName >> line;
				if (productName[1] != '-') {
					int i = 0;
					while (line[i] != '=')
						code.push_back(line[i]), ++i;
					int length = code.length() + 6, len = line.length();
					string line1;
					for (; length < len; length++)
						line1.push_back(line[length]);
					line = ""; i = 0;
					while (line1[i] != '=')
						s1.push_back(line1[i]), ++i;
					amount = stoi(s1);
					length = s1.length() + 6; len = line1.length();
					for (; length < len; length++)
						line.push_back(line1[length]);
					i = 0; line1 = "";
					while (line[i] != '=')
						s2.push_back(line[i]), ++i;
					price = stod(s2);
					length = s2.length() + 6; len = line.length();
					for (; length < len; length++)
						line1.push_back(line[length]);
					total = stod(line1);
					bill.addArticle(productName, code, amount, price, total);
				}
			}
		fileX.close();
		bill.inspect(filename);
		bill.inputCustomerData();
		bill.inputMonthData();
		bill.inputProductData();
	}
}

void Analyst::processingFormat4(string filename)
{
	string filen = filename + t;
	string customer, date, productName = "/", code, tempStr = "|", s1, s2, s3;
	double inTotal, pdv, price, total, payment; int amount;
	fstream file("C:\\MasterMindAnalyze\\Bills\\" + filen, ifstream::in);
	LinkedList bill;
	if (file.is_open())
	{
		file >> tempStr; file >> customer;
		file >> tempStr; file >> date;
		for (; tempStr[1] != '-'; file >> tempStr);
		tempStr = "textWithNoPoint";
		file >> productName >> code >> s1 >> amount >> s2 >> price >> s3 >> total;
		for (; productName[0] != '-';)
			bill.addArticle(productName, code, amount, price, total),
			file >> productName >> code >> s1 >> amount >> s2 >> price >> s3 >> total;
	} file.close();
	fstream fileX("C:\\MasterMindAnalyze\\Bills\\" + filen, ifstream::in);
	if (fileX.is_open())
	{
		while (!fileX.eof())
		{
			fileX >> tempStr;
			if (tempStr == "Ukupno:") fileX >> inTotal;
			else if (tempStr == "PDV:") fileX >> pdv;
			else if (tempStr == "placanje:") fileX >> payment;
		}
	} fileX.close();
	bill.setBillData(inTotal, pdv, payment, customer, date);
	bill.inspect(filename);
	bill.inputCustomerData();
	bill.inputMonthData();
	bill.inputProductData();
}
