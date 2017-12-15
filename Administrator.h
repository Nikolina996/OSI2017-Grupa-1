#pragma once
#include<iostream>
#include "User.h"
class Administrator: public User
{
public:
	Administrator();
	~Administrator();
	void userMenu() override;
	bool logIn() override;
	void setAccount() override;
	void currencyChange();
	void menagingUserAccounts();
	int deleteUser();
	int addUser();
	void setUserAccount();
	void addAccount();
};

