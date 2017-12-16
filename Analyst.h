#pragma once
#include<iostream>
#include "User.h"
class Analyst:public User
{
public:
	Analyst(char*, char*, char*, char*);
	~Analyst();
	void userMenu() override;
	bool logIn() override;
	void setAccount() override;
	void reviewOfProcessedData();
	void accountControl();
};

