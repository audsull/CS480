#pragma once
#include "Tag.h"
#include "Token.h"
class Dec :
	public Token
{
public:
	float value;
	int tag;
	Dec();
	Dec(float);
	string toString();
	double getValue();
	void print();
	virtual void printLexeme(std::ostream& ostream);
};

