#pragma once
#include <iostream>
#include <string>

using namespace std;

class Token
{
public:
	int tag;

	Token();
	Token(int);
	string toString();
	~Token();
};

