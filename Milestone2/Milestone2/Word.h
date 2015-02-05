#pragma once
#include "Token.h"
#include "Tag.h"
#include <string>
using namespace std;


class Word :
	public Token
{
public:
	int token;
	string lexeme;
	
	Word();
	Word(int, string);
	Word setValues(int, string);
	string toString();
	void print_word(Word);
	~Word();
};
