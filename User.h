#pragma once
#include<iostream>
#include <string>

class User
{
public:
	virtual bool logIn() = 0;
	virtual void userMenu();
	virtual void setAccount() = 0;
	virtual void signUp();
};
