#pragma once
#include "Tag.h"
#include "Token.h"
class Real :
	public Token
{
public:
	float value;
	Real();
	Real(float);
	string toString();
	double getValue();
	void print();
	virtual void printLexeme(std::ostream& ostream);
	~Real();
};

