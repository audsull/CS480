#pragma once
#include "Word.h"
#include "Dec.h"
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
	ifstream testfile;


	int line = 1;
	char peek = ' ';
	char c;
	//Store in hashtable as lexeme, valueS
	std::map<string, Word> hashtable;
	std::map<int, string> valuemap;
	void reserve(Word);
	Lexer();
	Token scan(int&);
	Token scan2(int&);

	Token checkName(int&);
	Token checkNum(int&);
	Token checkOper(int&);
	Token checkString(int&);

	Token nextToken(int&); //next token lookaheads at the next lexeme

};

