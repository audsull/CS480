#pragma once
#include "Word.h"
#include "Real.h"
#include "Num.h"

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
	char c;
	//Store in hashtable as lexeme, valueS
	std::map<string, Word> hashtable;
	std::map<int, string> valuemap;
	void reserve(Word);
	Lexer();
	Token scan(int&);
	//void readch();
	//bool reachch(char);
	void print_map();
	void print_tokens();
	~Lexer();
};

