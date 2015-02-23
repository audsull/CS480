#pragma once
#include <sstream>
#include <iostream>
#include <cstdlib>
#include "Token.h"
#include "Tag.h"
class Num :
	public Token
{
public:
	int value;
	int tag;
	Num();
	Num(int);
	string toString();
	int getValue(); 
	void print();
	virtual void printLexeme(std::ostream& ostream);
	~Num();
};

