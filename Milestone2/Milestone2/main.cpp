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
class Token;

int main() {
	//char c;
	Lexer lex;

	int size = 0;
	Token tokens[100];

	tokens[size] = lex.scan();
	cout << tokens[size].tag;
	size++;

	tokens[size] = lex.scan();
	cout << tokens[size].tag;


	/*
	while (tokens[size].tag != (Tag::END)) {
		tokens[size] = lex.scan();
		cout << tokens[size].tag;
		size++;
	}
	*/
	//lex.print_map();
	
	getchar();

	return 0;
}