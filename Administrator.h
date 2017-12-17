#pragma once
#include<iostream>
#include "User.h"
class Administrator: public User
{
public:
	void userMenu() override;
	bool logIn() override;
	void setAccount() override;
	void reviewAndManageUserAccounts();
	void currencyChange();
	void newRequests();
	void reviewUserAccounts();
	void deleteUser();
};

