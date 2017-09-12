#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <stdexcept>

using namespace std;

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
