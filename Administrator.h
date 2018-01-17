#pragma once
#include<iostream>
#include "User.h"
class Administrator : public User
{
public:
	void userMenu();
	bool logIn();
	void setAccount();
	void reviewAndManageUserAccounts();
	void changeCurrency();
	void newRequests();
	void reviewUserAccounts();
	void deleteUser();
	double currencyConverter(std::string, std::string, double);
};
