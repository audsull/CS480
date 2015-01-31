#pragma once
#include "Token.h"
#include "Tag.h"
#include <string>
using namespace std;


class Word :
	public Token
{
public:
	string lexeme;
	int token;
	
	Word();
	Word(int, string);
	string toString();
	string get_lexeme(Token);
	~Word();
};
