#pragma once
#include <iostream>
#include "token.h"
class Parser
{
public:
	Parser();
	//void populateTree(Token token, SyntaxTree tree);
	int os = 0;
	int nextos = 0;
	int lvl = 0;
	Token cur;
	Token next;
	bool pass;

	void result();
	void doLex();
	Token getToken();
	Token getNextToken();

	int testToken();
	Token testValue();

	void printVal(Token);

	Token T();
	bool S();
	bool S1();
	bool e();
	bool expr();
	bool oper();
	bool binops();
	bool unops();
	bool constants();
	bool strings();
	bool ids();
	bool ints();
	bool floats();
	bool stmts();
	bool printstmts();
	bool ifstmts();
	bool whilestmts();
	bool exprlist();
	bool letstmts();
	bool varlist();
	bool type();
};

