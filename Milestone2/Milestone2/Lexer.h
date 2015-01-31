#pragma once
#include "Word.h"
//#include "Word.cpp"

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>
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
	
	//Print hashmap to file!
	void print_map();
	void print_tokens();
	~Lexer();
};

