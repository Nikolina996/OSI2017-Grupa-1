#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class LinkedList
{
private:
	struct Article
	{
		string name, code;
		double price, total;
		int amount;
		Article *next;
		Article(string, string, int, double, double, Article*);
		Article(string, string, int, double, double);
	};
	Article *head;
	int numberOfNodes;
	double inTotal, PDV, payment;
	string customerName, date;
	void copy(const LinkedList&);
	void move(LinkedList&&);
public:
	LinkedList();
	LinkedList(const LinkedList&);
	LinkedList(LinkedList&&);
	~LinkedList();
	LinkedList& operator = (const LinkedList&);
	LinkedList& operator = (LinkedList&&);
	void addArticle(string, string, int, double, double);
	void inspect(string);
	void inputErrorDescription(string, string);
	void setBillData(double, double, double, string, string);
	void printBillData();
	void inputCustomerData();
	void inputProductData();
	void inputMonthData();
};
