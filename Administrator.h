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
	void changeCurrency();
	void newRequests();
	void reviewUserAccounts();
	void deleteUser();
	double currencyConverter(std::string, std::string, double);
};

