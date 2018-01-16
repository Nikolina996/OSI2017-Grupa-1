#pragma once
using namespace std;
#include<iostream>
#include "User.h"
#include "LinkedList.h"
class Analyst:public User, public LinkedList
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
	void name();
	string getname(string, string);
	bool doesItExist(string, unsigned int, string);
	void processingFormat1(string);
	void processingFormat2(string);
	void processingFormat3(string);
	void processingFormat4(string);
};
