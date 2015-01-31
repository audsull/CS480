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
	string temp;

	int size = 0;
	Token tokens[100];

	while (tokens[size].tag != (Tag::END)) {
		tokens[size] = lex.scan(offset);
		
		//cout << (tokens[size]).toString() << "\n";
		if (tokens[size].tag < 265 || (tokens[size].tag > 277 && tokens[size].tag < 285)) {
			cout << tokens[size].tag;
			cout << " Keyword\n";
		}
		if (tokens[size].tag == 286) {
			cout << tokens[size].tag;
			cout << " Id\n";
		}
		if (tokens[size].tag == 287) {
			cout << tokens[size].tag;
			cout << " Integer\n";
		}
		if (tokens[size].tag == 288) {
			cout << tokens[size].tag;
			cout << " Real\n";
		}
		if (tokens[size].tag > 264 && tokens[size].tag < 278) {
			cout << tokens[size].tag;
			cout << " Operator\n";
		}
		size++;
	}

	getchar();
	return 0;
}