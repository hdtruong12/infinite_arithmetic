#pragma once
#include <iostream>
#include <math.h>
#include <string>

using namespace std;

struct node {
	long long data;
	node *next, *prev;
	node(long long a = 0) {
		data = a;
		next = prev = NULL;
	}
};



class doublyList {
public:
	doublyList(); //default constructor
	~doublyList();
	doublyList(const std::string& num, int digitsPerNode, bool neg); // user defined construct
	doublyList(const doublyList& list);  // copy construct
	doublyList& operator = (const doublyList& list);  // assignment consturct
public:
	doublyList operator + (const doublyList& list) const;
	doublyList operator * (const doublyList& list) const;
	doublyList operator - (const doublyList& list) const;
	bool operator<(const doublyList& list) const;
public:
	node* getHead() const;
	node* getTail() const;
	void delHead();
	const bool getSign() const;
	long long getNumOfNodes();
	void setSign(bool a);
	void changeSign();
	void addHead(long long a = 0);
	void addTail(long long a = 0);
	void printList() const;
	string toString();
	void delAll();
	bool isEmpty();
private:
	node *head, *tail;
	int m_digitsPernode;
	bool negative;
	long long numOfNodes;
};