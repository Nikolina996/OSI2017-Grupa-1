#include "LinkedList.h"
#include <utility>

LinkedList::Article::Article(string name, string code, int amount, double price, double total, Article *next) : name(name), code(code), amount(amount), price(price), total(total), next(next) {}

LinkedList::Article::Article(string nm, string cd, int am, double pr, double tot) : Article(nm, cd, am, pr, tot, nullptr) {}

void LinkedList::copy(const LinkedList &bill)
{
	Article *temp = bill.head;
	if (temp != nullptr)
	{
		numberOfNodes++;
		Article *localTemp = head = new Article(temp->name, temp->code, temp->amount, temp->price, temp->total);
		while (temp->next)
		{
			localTemp->next = new Article(temp->next->name, temp->next->code, temp->next->amount, temp->next->price, temp->next->total);
			numberOfNodes++;
			temp = temp->next;
			localTemp = localTemp->next;
		}
	}
	else head = nullptr;
	billName = bill.billName;
	format = bill.format;
	inTotal = bill.inTotal;
	PDV = bill.PDV;
	payment = bill.payment;
	customerName = bill.customerName;
	date = bill.date;
}

void LinkedList::move(LinkedList &&bill)
{
	numberOfNodes = bill.numberOfNodes;
	billName = bill.billName;
	format = bill.format;
	inTotal = bill.inTotal;
	PDV = bill.PDV;
	payment = bill.payment;
	customerName = bill.customerName;
	date = bill.date;
	head = std::move(bill.head);
	bill.head = nullptr;
}

LinkedList::LinkedList() : head(nullptr), numberOfNodes(0) {}

LinkedList::LinkedList(const LinkedList &bill) { copy(bill); }

LinkedList::LinkedList(LinkedList &&bill) { move(std::move(bill)); }

LinkedList::~LinkedList()
{
	numberOfNodes = 0;
	inTotal = PDV = payment = 0.0;
	for (Article *temp = head, *next = nullptr; temp != nullptr; temp = next)
	{
		next = temp->next;
		delete temp;
	}
	head = nullptr;
}

LinkedList & LinkedList::operator=(const LinkedList &bill)
{
	if (this == &bill) return *this;
	this->~LinkedList();
	copy(bill); return *this;
}

LinkedList & LinkedList::operator=(LinkedList &&bill)
{
	if (this == &bill) return *this;
	this->~LinkedList();
	move(std::move(bill)); return *this;
}

void LinkedList::addArticle(string name, string code, int amount, double price, double total)
{
	head = new Article(name, code, amount, price, total, head);
	numberOfNodes++;
}

void LinkedList::inspect()
{
	double totalSum = 0.0;
	bool errorCode = false;
	for (Article *temp = head; temp != nullptr; temp = temp->next)
	{
		if (temp->amount * temp->price != temp->total)
		{
			errorCode = true;
			inputErrorDescription(temp->name + " - Incorrect amount * price value.");
		}
		totalSum += temp->amount * temp->price;
	}
	if (errorCode)
	{
		cout << billName << " - "; 
		cout << "Invalid bill data. To check description go to this bill's txt file." << endl;
		return;
	}
	if (totalSum + PDV != inTotal)
	{
		inputErrorDescription("Total price incorrect.");
		cout << billName << " - ";
		cout << "Invalid bill data. To check description go to this bill's txt file." << endl;
		return;
	}
	if (totalSum + PDV > payment)
	{
		inputErrorDescription("Payment incorrect.");
		cout << billName << " - ";
		cout << "Invalid bill data. To check description go to this bill's txt file." << endl << endl;
		return;
	}
}

void LinkedList::inputErrorDescription(string text)
{
	ofstream file(billName + "_error.txt", ios::app);
	if (file.is_open())
		file << text << endl;
	else
		cout << "Could not open file." << endl;
}

void LinkedList::setBillData(double inTotal, double PDV, double payment, string billName, string format, string customerName, string date)
{
	this->inTotal = inTotal;
	this->PDV = PDV;
	this->payment = payment;
	this->billName = billName;
	this->format = format;
	this->customerName = customerName;
	this->date = date;
}

void LinkedList::printBillData()
{
	cout << billName << "_" << format << endl << endl;
	int counter = 1;
	for (Article *A = head; A != nullptr; A = A->next, counter++)
	{
		cout << "A R T I C L E  " << counter << endl;
		cout << "Name and Code: " << A->name << " " << A->code << endl;
		cout << "Price and Amount: " << A->price << " " << A->amount << endl;
		cout << "Total: " << A->total << endl;
		cout << endl;
	}
}
