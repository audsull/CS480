#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>
#include "Tag.h"
#include "Token.h"
#include "Word.h"
#include "Num.h"
//#include "Lexer.h"

using namespace std;

int main() {

	//Lexer lex;
	//Parser parse;

	std::string keywords;
	std::string letters;
	char c;
	int size = 0;
	int cur = 0;

	ifstream testfile;
	testfile.open("test.txt");
	printf("Opened the file.\n");

	if (testfile.is_open()) {
		while(testfile.get(c)) {
			if (c == ' ') { 
				letters.clear();
			}
			else {
				letters += c;
			}

		}
		//printf("%s", letters.c_str());
		cout << letters;

	}
	printf("\nWrote the content of the file.\n");

	testfile.close();
	
	static Word Bool = Word(Tag::BOOL, "bool"), True = Word(Tag::TRUE, "true"), False = Word(Tag::FALSE, "false"),
		and = Word(Tag::AND, "&&"), or = Word(Tag::OR, "||"), not = Word(Tag::NOT, "!"),
		Int = Word(Tag::INT, "int"), real = Word(Tag::REAL, "real"), string = Word(Tag::STRING, "string"),
		plus = Word(Tag::PLUS, "+"), minus = Word(Tag::MINUS, "-"), mult = Word(Tag::MULT, "*"), div = Word(Tag::DIV, "/"),
		mod = Word(Tag::MOD, "%"), pow = Word(Tag::POW, "^"), equal = Word(Tag::EQUAL, "="),
		lt = Word(Tag::LT, "<"), gt = Word(Tag::GT, ">"), le = Word(Tag::LE, "<="), ge = Word(Tag::GE, ">="),
		ne = Word(Tag::NE, "!="), Stdout = Word(Tag::STDOUT, "stdout"),
		If = Word(Tag::IF, "if"), While = Word(Tag::WHILE, "while"), Let = Word(Tag::LET, "let"), assign = Word(Tag::ASSIGN, ":="),
		sin = Word(Tag::SIN, "sin"), cos = Word(Tag::COS, "cos"), tan = Word(Tag::TAN, "tan");


	getchar();
	return 0;
}