#pragma once
#include "doublyList.h"
#include <string>
#include <iostream>
#include <cctype>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <stdexcept>

template <class T>
class Stack
{
private:
	vector<T> elems; // elements 
public:
	void push(T const& elem) {
		elems.push_back(elem);
	}// push element 
	void pop() {
		if (elems.empty())
		{
			throw out_of_range("Stack<>::pop(): empty stack");
		}

		// remove last element 
		elems.pop_back();
	} // pop element 
	T top() const {
		if (elems.empty())
		{
			throw out_of_range("Stack<>::top(): empty stack");
		}
		// return copy of last element 
		return elems.back();
	}// return top element 
	bool empty() const
	{       // return true if empty.
		return elems.empty();
	}
};

class infixToPostfix
{
private:
	string ifx = "";
	string pfx = "";
public:
	bool isOperator(const char c)
	{
		if ((c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '^') || (c == '%'))
			return true;
		else
			return false;
	}
	/*Converts the infix expression into a postfix expression.
	The resulting postfix expression is stored in pfx.*/
	void convertToPostfix()
	{
		Stack<char>c_stack; //Stack of characters;
		string temp = ifx;
		temp += ')';
		c_stack.push('(');

		unsigned int i = 0;
		do //loop through infix 
		{

			if (isOperator(temp[i])) //if the current position = operator
			{
				if (isOperator(c_stack.top()))
				{
					if (precedence(temp[i], c_stack.top()) == 0)
					{
						pfx = pfx + c_stack.top() + " ";
						c_stack.pop();
					}
					else if (precedence(temp[i], c_stack.top()) == 1)
					{
						c_stack.push(temp[i]);
						i++;
					}
					else
					{
						pfx = pfx + c_stack.top() + " ";
						c_stack.pop();
					}
				}
				else
				{
					c_stack.push(temp[i]);
					i++;
				}
			}
			else
			{
				if (temp[i] == ')')
				{
					while (c_stack.top() != '(')
					{
						pfx = pfx + c_stack.top() + " ";
						c_stack.pop();
					}
					/*pop '(' from the stack*/
					c_stack.pop();
					i++;
				}
				else if (temp[i] == '(')
				{
					/*push onto stack if neither operator nor operand*/
					c_stack.push(temp[i]);
					i++;
				}
				else
				{
					/*in case of operand, copy the operand to stack*/
					/*ifx -> pfx*/
					while (isdigit(temp[i])) {
						pfx = pfx + temp[i];
						i++;
					}
					pfx = pfx + " ";
				}
			}
			if (temp[i] == '\r') break;
		} while (i < temp.length());
		while (!c_stack.empty() && isOperator(c_stack.top())) {
			pfx = pfx + c_stack.top() + " ";
			c_stack.pop();
		}
	}
	/*Determines the precedence between two operators.*/
	int precedence(char opr1, char opr2)
	{
		int pre1, pre2; // variables to compare precedence

		if ((opr1 == '+') || (opr1 == '-')) //low precedence
			pre1 = 0;
		else if ((opr1 == '*') || (opr1 == '/') || (opr1 == '%')) // high precedence
			pre1 = 1;
		if ((opr2 == '+') || (opr2 == '-')) //low precedence
			pre2 = 0;
		else if ((opr2 == '*') || (opr2 == '/') || (opr2 == '%')) // high precedence
			pre2 = 1;

		/*Compare and return the precedence of opr1 and opr2*/
		if (pre1 == pre2)
			return 0;
		else if (pre1 > pre2) // if higher precedence of opr1 > opr2
			return 1;
		else //lower precedence
			return -1;
	}
	void getInfix(string &infix) //stores the infix expression
	{
		ifx = infix;
	}
	void showInfix() //output the infix expression
	{
		cout << "\nInfix Expression: " << ifx;
	}
	void showPostfix() //output the postfix expression
	{
		cout << "\nPostfix Expression: " << pfx;
	}
	string getPostfix() {
		return pfx;
	}
	infixToPostfix(string = "") //Default constructor
	{
		ifx = "";
		pfx = "";
	}
	string calculate(int dig) {
		std::stringstream ss(pfx.c_str());
		std::string str;
		Stack<string>s_stack;
		while (ss >> str) {
			if (isdigit(str[0]))
				s_stack.push(str);
			else {
				string n2 = s_stack.top();
				s_stack.pop();
				string n1 = s_stack.top();
				s_stack.pop();
				bool neg1 = false, neg2 = false;
				if (n1[0] == '-') {
					n1 = n1.substr(1);
					neg1 = true;
				}
				if (n2[0] == '-') {
					n2 = n2.substr(1);
					neg2 = true;
				}
				int a = n1.length();
				int b = n2.length();
				for (int i = 0; i < a - 1; i++) {
					if (n1[0] != '0')
						break;
					n1.erase(0, 1);
				}
				for (int i = 0; i < b - 1; i++) {
					if (n2[0] != '0')
						break;
					n2.erase(0, 1);
				}
				doublyList num2(n2, dig, neg2);
				
				doublyList num1(n1, dig, neg1);
				
				doublyList result;
				if (str == "*") {
					result = num1*num2;
					if (num1.getSign() != num2.getSign()) result.setSign(true);
					else result.setSign(false);
				}
				else if (str == "+") {
					if (num1.getSign() != num2.getSign()) {
						if (num1.getSign() == true) {
							//num2-num1
							num1.changeSign();
							if (num2 < num1) {
								result = num1 - num2;
								result.changeSign();
							}
							else result = num2 - num1; 
						}
						else {
							//num1-num2
							num2.changeSign();
							if (num1 < num2) {
								result = num2 - num1;
								result.changeSign();
							}
							else result = num1 - num2;
						}
					}
					else result = num1 + num2;
				}
				else if (str == "-") {
					if (num1.getSign() != num2.getSign()) {
						result = num1 + num2;
						result.setSign(num1.getSign());
					}
					else {
						if (num1.getSign() == true) {
							if (num1 < num2) 
								result = num1 - num2;
							else {
								result = num2 - num1;
								result.changeSign();
							}
						}
						else {
							if (num1 < num2) {
								result = num2 - num1;
								result.changeSign();
							}
							else result = num1 - num2;
						}
					}
				}
				s_stack.push(result.toString());
			}
		}
		if (s_stack.top() == "-0") return "0";
		return (s_stack.top());
	}
};