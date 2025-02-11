#pragma once
#include <iostream>
#include <string>


using namespace std;
class Tag;

class Token
{
public:
	int tag;
	string lexeme;
	int value;
	float dec_value;

	int storedInt;
	float storedFloat;
	string storedString;
	bool storedBool;

	Token();
	Token(int, string);
	Token(int, int);
	Token(int, float);

	string toString(Token);
};

