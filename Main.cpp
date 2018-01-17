#include<iostream>
#include<string>
#include<fstream>
#include <Windows.h>
#include <MMSystem.h>
#include"User.h"
#include"Administrator.h"
#include"Analyst.h"
#include"LinkedList.h"
using namespace std;

void main()
{
	int i, j;
	Sleep(3000);
	Analyst analyst;
	Administrator admin;
	User *user1 = &analyst, *user2 = &admin;
	string username;
	PlaySound(TEXT("Welcome.wav"), NULL, SND_SYNC);
	do {
		user1->User::userMenu();
		cin >> i;
		if (i == 0)
			return;
		if (i == 1)
		{
			user1->User::logInMenu();
			cin >> j;
			if (j == 1) {
				if (admin.logIn())
					admin.userMenu();
			}
			else if (j == 2) {
				if (analyst.logIn())
				{
					analyst.name();
					analyst.userMenu();
				}
			}
		}
		else if (i == 2)
			user1->User::signUp();
	} while (i != 0);
}
