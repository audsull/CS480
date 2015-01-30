#pragma once
#include "Word.h"
//#include "Word.cpp"

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

class Word;

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

