#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>
#include "Tag.h"
#include "Token.h"
#include "Word.h"
#include "Num.h"
#include "Lexer.h"

using namespace std;

int main() {

	Lexer lex;
	Token input = lex.scan(); //input this into map somehow like VVV
	//lex.reserve(Word(input));

	lex.print_map();
	
	getchar();

	return 0;
}