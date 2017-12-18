#pragma once
#include<iostream>
#include "User.h"
class Analyst:public User
{
public:
	void userMenu() override;
	bool logIn() override;
	void setAccount() override;
	void reviewOfProcessedData();
	void accountControl();
	void viewingDataForAParticularUser();
	void reviewDataForASpecificProduct();
	void viewDataForASpecificMonth();
};

