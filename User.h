#pragma once
#include<iostream>
#include <string>

class User
{
public:
	User(char *, char*, char*, char*);
	~User();
	virtual bool logIn() = 0;
	virtual void userMenu();
	virtual void setAccount() = 0;
	virtual void signUp();
protected:
        char *name, *surname, *user_name, *password;

};
