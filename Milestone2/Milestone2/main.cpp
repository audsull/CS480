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

	string keywords;
	string letters;
	char c;
	int size = 0;
	int cur = 0;

	ifstream testfile;
	testfile.open("testfile.txt");
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
		And = Word(Tag::AND, "&&"), Or = Word(Tag::OR, "||"), Not = Word(Tag::NOT, "!"),
		Int = Word(Tag::INT, "int"), Real = Word(Tag::REAL, "real"), String = Word(Tag::STRING, "string"),
		Plus = Word(Tag::PLUS, "+"), minus = Word(Tag::MINUS, "-"), mult = Word(Tag::MULT, "*"), div = Word(Tag::DIV, "/"),
		Mod = Word(Tag::MOD, "%"), Pow = Word(Tag::POW, "^"), Equal = Word(Tag::EQUAL, "="),
		Lt = Word(Tag::LT, "<"), Gt = Word(Tag::GT, ">"), Le = Word(Tag::LE, "<="), Ge = Word(Tag::GE, ">="),
		Ne = Word(Tag::NE, "!="), Stdout = Word(Tag::STDOUT, "stdout"),
		If = Word(Tag::IF, "if"), While = Word(Tag::WHILE, "while"), Let = Word(Tag::LET, "let"), Assign = Word(Tag::ASSIGN, ":="),
		Sin = Word(Tag::SIN, "sin"), Cos = Word(Tag::COS, "cos"), Tan = Word(Tag::TAN, "tan");


	getchar();
	return 0;
}