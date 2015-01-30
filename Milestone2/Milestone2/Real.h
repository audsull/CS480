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
	~Real();
};

