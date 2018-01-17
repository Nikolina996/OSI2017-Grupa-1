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
	inTotal = bill.inTotal;
	PDV = bill.PDV;
	payment = bill.payment;
	customerName = bill.customerName;
	date = bill.date;
}

void LinkedList::move(LinkedList &&bill)
{
	numberOfNodes = bill.numberOfNodes;
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

bool LinkedList::inspect(string fileName)
{
	double totalSum = 0.0;
	bool errorCode = false;
	for (Article *temp = head; temp != nullptr; temp = temp->next)
	{
		if (temp->amount * temp->price != temp->total)
		{
			errorCode = true;
			inputErrorDescription(temp->name + " - Incorrect amount * price value.", fileName);
		}
		totalSum += temp->amount * temp->price;
	}
	if (errorCode)
		return false;
	if ((totalSum * 17) / 100 != PDV)
	{
		inputErrorDescription("PDV incorect.", fileName);
		return false;
	}
	if (totalSum + PDV != payment)
	{
		inputErrorDescription("Payment incorrect.", fileName);
		cout << totalSum << " " << PDV << " " << inTotal << endl;
		return false;
	}
	return true;
}

void LinkedList::inputErrorDescription(string text, string fileName)
{
	ofstream file("C:\\MasterMindAnalyze\\Bills\\BillsWithErrors\\" + fileName + "_error.txt", ios::app);
	if (file.is_open())
		file << text << endl;
	else
		cout << "Could not open file." << endl;
}

void LinkedList::setBillData(double inTotal, double PDV, double payment, string customerName, string date)
{
	this->inTotal = inTotal;
	this->PDV = PDV;
	this->payment = payment;
	this->customerName = customerName;
	this->date = date;
}

void LinkedList::printBillData()
{
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

void LinkedList::inputCustomerData()
{
	ofstream file("C:\\MasterMindAnalyze\\ProcessedData\\" + customerName + ".txt", ios::app);
	if (file.is_open())
		for (Article *A = head; A != nullptr; A = A->next)
			file << date << " " << A->name << " " << A->code << " " << A->amount << " " << A->price << endl;
	file.close();
}

void LinkedList::inputProductData()
{
	for (Article *A = head; A != nullptr; A = A->next)
	{
		ofstream file("C:\\MasterMindAnalyze\\ProcessedData\\" + A->name + A->code + ".txt", ios::app);
		if (file.is_open())
			file << date << " " << customerName << " " << A->amount<<endl;
		file.close();
	}
}

void LinkedList::inputMonthData()
{
	string year, month, mon;
	for (int i = 0, j = 3; i < 2; month.push_back(date[j++]), i++);
	for (int i = 0, j = 6; i < 4; year.push_back(date[j++]), i++);
	int checkMon = stoi(month);
	switch (checkMon)
	{
	case 1: mon = "January"; break; case 2: mon = "February"; break;
	case 3: mon = "March"; break; case 4: mon = "April"; break;
	case 5: mon = "May"; break; case 6: mon = "June"; break;
	case 7: mon = "July"; break; case 8: mon = "August"; break;
	case 9: mon = "September"; break; case 10: mon = "October"; break;
	case 11: mon = "November"; break; case 12: mon = "December"; break;
	default: mon = "Error";
	}
	ofstream file("C:\\MasterMindAnalyze\\ProcessedData\\" + mon + year + ".txt", ios::app);
	if (file.is_open())
	{
		for (Article *A = head; A != nullptr; A = A->next)
			file << date << " " << A->name << " " << A->code << " " << A->amount << " " << A->price << " " << customerName << endl;
	} file.close();
}
