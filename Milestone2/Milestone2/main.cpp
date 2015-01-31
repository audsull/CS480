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
	int offset = 0;
	Lexer lex;

	int size = 0;
	Token tokens[100];

	while (tokens[size].tag != (Tag::END)) {
		tokens[size] = lex.scan(offset);
		cout << tokens[size].tag << "\n";
		size++;
	}

	//lex.print_map();
	
	getchar();

	return 0;
}