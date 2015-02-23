#pragma once
#include "Token.h"
#include "Tag.h"

#include <cstdio>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <map>


class Lexer
{

public:
	ifstream testfile;


	int line = 1;
	char peek = ' ';
	char c;
	//Store in hashtable as lexeme, valueS

	Lexer();
	Token scan(int&);
	Token scan2(int&);

	Token checkName(int&);
	Token checkNum(int&);
	Token checkOper(int&);
	Token checkString(int&);

	Token nextToken(int&); //next token lookaheads at the next lexeme

};

