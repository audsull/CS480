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
	Token t;
	Token * k;

	while (t.tag != Tag::END) {
		t = lex.scan(offset);
		if (t.tag == 289) {
			Word& word = (Word&)t;
			//k = &word;
			//cout << k->toString();
			//cout << word.toString;
			cout << " String\n";
		}
		if (t.tag < 265 || (t.tag > 277 && t.tag < 285)) {
			Word& word = (Word&)t;
			//cout << ((Word)word).toString();
			cout << " Keyword\n";
		}
		if (t.tag == 286) {
			Word& word = (Word&)t;
			cout << " ID\n";
		}
		if (t.tag == 287) {
			Num& num = (Num&)t;
			cout << " Integer\n";
		}
		if (t.tag == 288) {
			Real& real = (Real&)t;
			cout << " Float\n";
		}
		if (t.tag > 264 && t.tag < 278) {
			Word& word = (Word&)t;
			cout << " Operator\n";
		}
	}

	getchar();
	return 0;
}