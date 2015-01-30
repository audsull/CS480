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
	~Word();
};
/*
static Word Bool, True, False, And, Or, Not, Int, Real, String,
Plus, Minus, Mult, Div, Mod, Pow, Equal,
Lt, Gt, Le, Ge, Ne, Stdout, If, While, Let, Assign,
Sin, Cos, Tan;
*/