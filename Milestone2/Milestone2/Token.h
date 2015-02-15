#pragma once
#include <iostream>
#include <string>

using namespace std;
class Tag;

class Token
{
public:
	int tag;

	Token();
	Token(int);
	virtual string toString();
	virtual void print();
	virtual void printLexeme(std::ostream&);

	~Token();
};

