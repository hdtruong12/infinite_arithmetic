#include <iostream>
#include <fstream>
#include "doublyList.h"
#include "infixToPostfix.h"
#include "ArgumentManager.h"

using namespace std;

int main(int argc, char* argv[]) {
	/*if (argc < 2) {
		std::cerr << "Usage: infinitearithmetic \"input=xyz.txt;digitsPerNode=<number>\"\n";
	}
	ArgumentManager am(argc, argv);
	std::string filename = am.get("input");
	int digitsPerNode = std::stoi(am.get("digitsPerNode"));*/
	ifstream infile("9.txt");
	infixToPostfix* InfixExp = new infixToPostfix();
	string line;
	string copy;
	if (!infile)
	{
		cout << "Cannot open input file, terminating program..." << endl; return 1;
	}

	while (getline(infile, line)) {
		copy = line;
		int i = 0;
		int add = 0;
		while (i < line.length()) {
			if (i == 0 && (copy[i + add] == '+' || copy[i + add] == '-')) {
				copy.insert(0, "0");
				add++;
			}
			if ((copy[i + add] == '+' || copy[i + add] == '-') && (!isdigit(copy[i - 1 + add]) && copy[i - 1 + add] != ')')) {
				copy.insert(i+add, "0");
				add++;
			}
			i++;
		}
		InfixExp = new infixToPostfix();
		InfixExp->getInfix(copy);
		InfixExp->convertToPostfix();
		cout << line << "=";
		cout << InfixExp->calculate(3) << endl;
		delete InfixExp;
	}
	infile.close();
	system("pause");
	return 0;
}