#pragma once
#include "Word.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

class Lexer
{
public:
	int line = 1;
	char peek = ' ';
	//Store in hashtable as lexeme, valueS
	std::map<string, Word> hashtable;
	void reserve(Word);
	Lexer();
	Token scan();

	~Lexer();
};

