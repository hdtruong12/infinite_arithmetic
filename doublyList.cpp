#include "doublyList.h"



doublyList::doublyList()
{
	head = tail = NULL;
}

doublyList::doublyList(const std::string& num, int digitsPerNode, bool neg) {
	head = tail = NULL;
	numOfNodes = num.length() / digitsPerNode;
	int firstNodeDigits = num.length() % digitsPerNode;
	if (firstNodeDigits != 0) {
		addTail(std::stoi(num.substr(0, firstNodeDigits)));
	}
	for (int i = 0; i < numOfNodes; i++)
		addTail(std::stoi(num.substr(firstNodeDigits + i*digitsPerNode, digitsPerNode)));
	negative = neg;
	m_digitsPernode = digitsPerNode;
}

doublyList::doublyList(const doublyList& list) {
	delAll();
	m_digitsPernode = list.m_digitsPernode;
	node* temp = list.getHead();
	while (temp != NULL) {
		addTail(temp->data);
		temp = temp->next;
	}
}


doublyList& doublyList::operator=(const doublyList& list) {
	delAll();
	m_digitsPernode = list.m_digitsPernode;
	node* temp = list.getHead();
	while (temp != NULL) {
		addTail(temp->data);
		temp = temp->next;
	}
	return *this;
}

doublyList::~doublyList()
{
	delAll();
}

bool doublyList::isEmpty() { return (head = NULL); }

node* doublyList::getHead() const {
	return head;
}
node* doublyList::getTail() const {
	return tail;
}
const bool doublyList::getSign() const{
	return negative;
}

void doublyList::setSign(bool a) {
	negative = a;
}

void doublyList::changeSign() {
	if (negative == true) negative = false;
	else negative = true;
}

long long doublyList::getNumOfNodes() {
	node *temp = head;
	long long count = 0;
	while (temp != NULL) {
		count++;
		temp = temp->next;
	}
	return count;
}

void doublyList::addHead(long long a) {
	if (!head) {
		head = new node(a);
		return;
	}
	else if (!tail) {
		node* add = new node(a);
		add->next = head;
		head->prev = add;
		tail = head;
		head = add;
	}
	else {
		node *add = new node(a);
		add->next = head;
		head->prev = add;
		head = add;
	}
}
void doublyList::delHead() {
	node* temp = head;
	head = head->next;
	delete temp;
}

void doublyList::addTail(long long a) {
	if (head == NULL) {
		head = new node(a);
		return;
	}
	else if (tail == NULL) {
		tail = new node(a);
		head->next = tail;
		tail->prev = head;
	}
	else {
		node *add = new node(a);
		tail->next = add;
		add->prev = tail;
		tail = add;
	}
}

void doublyList::printList() const { //could be << overloading
	if (head == NULL) {
		cout << "NULL";
		return;
	}
	else {
		node* temp = head;
		if (negative) cout << "-";
		while (temp != NULL) {
			if (temp != head) {
				string snum = std::to_string(temp->data);
				for (int i = snum.length(); i < m_digitsPernode; i++)
					cout << "0";
			}
			cout << temp->data;
			temp = temp->next;
		}
	}
}

string doublyList::toString() {
	string result = "";
	node* temp = head;
	if (negative)  result = result + "-";
	while (temp != NULL) {
		if (temp != head) {
			string snum = std::to_string(temp->data);
			for (int i = snum.length(); i < m_digitsPernode; i++)
				result = result + "0";
		}
		result = result + std::to_string(temp->data);
		temp = temp->next;
	}
	return result;
}

void doublyList::delAll() {
	node *temp;
	if (head = NULL)
		return;
	while (head != NULL) {
		temp = head;
		head = head->next;
		delete temp;
	}
	head = tail = NULL;
}

doublyList doublyList::operator+(const doublyList& list) const {
	int carry = 0, sum = 0;
	doublyList res;
	res.m_digitsPernode = m_digitsPernode;
	res.negative = negative;
	int max = pow(10, m_digitsPernode);
	node *ln1 = (tail == NULL ? head : tail);
	node *ln2 = (list.getTail() == NULL ? list.head : list.tail);
	while (ln1 != NULL || ln2 != NULL) {
		sum = carry + (ln1 ? ln1->data : 0) + (ln2 ? ln2->data : 0);
		carry = sum / max;
		sum = sum % max;
		res.addHead(sum);
		ln1 = (ln1 ? ln1->prev : NULL);
		ln2 = (ln2 ? ln2->prev : NULL);
	}
	if (carry != 0) res.addHead(carry);
	return res;
}

doublyList doublyList::operator*(const doublyList& list) const {
	long long carry = 0, gap = 0;
	long long product;
	int max = pow(10, m_digitsPernode);
	doublyList res("0", m_digitsPernode, false);
	doublyList subres;
	node *ln1 = (tail == NULL ? head : tail);
	node *ln2 = (list.getTail() == NULL ? list.head : list.tail);
	while (ln2 != NULL) {
		while (ln1 != NULL) {
			product = carry + (ln1->data * ln2->data);
			carry = product / max;
			product = product % max;
			subres.addHead(product);
			ln1 = ln1->prev;
		}
		if (carry != 0)
			subres.addHead(carry);
		for (int i = 0; i < gap; i++)
			subres.addTail(0);
		gap++;
		res = res + subres;
		ln2 = ln2->prev;
		ln1 = (tail == NULL ? head : tail);
		carry = 0;
		subres.delAll();
	}
	return res;
}

//operator- apply for same sign calculation only
doublyList doublyList::operator-(const doublyList& list) const { //if list > this -> swap //or consider this for each node calculation
	int borrow = 0, diff = 0;
	doublyList res;
	res.m_digitsPernode = m_digitsPernode;
	res.negative = negative;
	int max = pow(10, m_digitsPernode);
	node *ln1 = (tail == NULL ? head : tail);
	node *ln2 = (list.getTail() == NULL ? list.head : list.tail);
	while (ln1 != NULL || ln2 != NULL) {
		if (-borrow + (ln1 ? ln1->data : 0) - (ln2 ? ln2->data : 0) < 0) {
			diff = -borrow + max + (ln1 ? ln1->data : 0) - (ln2 ? ln2->data : 0);
			borrow = 1;
		}
		else {
			diff = -borrow + (ln1 ? ln1->data : 0) - (ln2 ? ln2->data : 0);
			borrow = 0;
		}
		res.addHead(diff);
		ln1 = (ln1 ? ln1->prev : NULL);
		ln2 = (ln2 ? ln2->prev : NULL);
	}
	if (res.head->data == 0 && res.head->next != NULL) {
		node* temp = res.head;
		res.head = res.head->next;
		delete temp;
	}
	return res;
}

bool doublyList::operator<(const doublyList& list) const {

	if (negative != list.negative) {
		if (negative == true)
			return true;
		return false;
	}
	else {
		if (numOfNodes != list.numOfNodes) {
			if (numOfNodes > list.numOfNodes) {
				if (negative == true) return true;
				return false;
			}
			else {
				if (negative == true) return false;
				return true;
			}
		}
		node* temp1 = head;
		node* temp2 = list.head;
		if (negative == true) {
			while (temp1 != NULL && temp2 != NULL) {
				if (temp1->data != temp2->data) {
					if (temp1->data > temp2->data)
						return true;
					return false;
				}
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
			return false;
		}
		else {
			while (temp1 != NULL && temp2 != NULL) {
				if (temp1->data != temp2->data) {
					if (temp1->data > temp2->data)
						return false;
					return true;
				}
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
			return true;
		}
	}
}
