#pragma once
#include<iostream>
#include "User.h"
class Administrator: public User
{
public:
	Administrator(char *, char *, char *, char*);
	~Administrator();
	void userMenu() override;
	bool logIn() override;
	void setAccount() override;
	void reviewAndManageUserAccounts();
	void currencyChange();
	void menagingUserAccounts();
	void newRequests();
	void reviewUserAccount();
	int deleteUser();
	void setUserAccount();
	void addAccount();
};

