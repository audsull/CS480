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
#include "Parser.h"

using namespace std;
class Token;

int main() {
	Token t;
	Parser parse;
	//t = parse.getToken();
	//parse.doLex();
	
	int test = 0;
	while (test != Tag::END) {
		test = parse.T();
		cout << "\n\n";
	}

	parse.result();

	/*
	while (test != 299) {
		test = parse.testToken();
		cout << test; 
		cout << "\n";
	}
	*/
	//cout << t.tag;

	getchar();
	return 0;
}