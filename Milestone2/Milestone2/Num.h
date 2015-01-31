#pragma once
#include <sstream>
#include "Token.h"
#include "Tag.h"
class Num :
	public Token
{
public:
	int value;
	Num();
	Num(int);
	string toString();
	~Num();
};

