#pragma once
using namespace std;
#include<iostream>
#include "User.h"
class Analyst:public User
{
public:
	void userMenu() override;
	bool logIn() override;
	void setAccount() override;
	string getUsername();
	void reviewOfProcessedData();
	void viewingDataForAParticularUser();
	void reviewDataForASpecificProduct();
	void viewDataForASpecificMonth();
};

