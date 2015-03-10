#pragma once
#include "Tag.h"
#include "Token.h"
#include "Parser.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//2 3 : ^ 1 swap 0 u+do over * loop nip ; ^
//or typecase f**

class SyntaxTree
{
public:
	SyntaxTree();

	int os = 0;
	int nextos = 0;
	int lvl = 0;
	bool powop = false;
	bool unopReal = false;
	bool newBinop = false;
	bool newReal = false;
	bool newInt = false;
	bool newMismatch = false;
	Token variable;

	Token cur;
	Token next;
	bool pass;
	Parser parse;
	Token getToken_syntax();
	Token getToken_syntax(bool&,bool&);
	Token getNext_syntax();
	void printVal_syntax(Token, ofstream&);

	Token T_syntax(ofstream&);
	bool S_syntax(ofstream&);
	bool S1_syntax(ofstream&);
	bool expr_syntax(ofstream&);
	bool oper_syntax(ofstream&);
	bool binops_syntax(ofstream&);
	bool unops_syntax(ofstream&, bool&, bool&);
	bool constants_syntax(ofstream&);
	bool strings_syntax(ofstream&);
	bool ids_syntax(ofstream&);
	bool ints_syntax(ofstream&);
	bool floats_syntax(ofstream&);
	bool stmts_syntax(ofstream&);
	bool printstmts_syntax(ofstream&);
	bool ifstmts_syntax(ofstream&);
	bool whilestmts_syntax(ofstream&);
	bool exprlist_syntax(ofstream&);
	bool letstmts_syntax(ofstream&);
	bool varlist_syntax(ofstream&);
	bool type_syntax(ofstream&);

};

