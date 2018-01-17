#pragma once
#include<iostream>
#include <string>

class User
{
public:
	virtual bool logIn() = 0;
	void userMenu();
	virtual void signUp();
	void logInMenu();
	virtual void setAccount()=0;
};
