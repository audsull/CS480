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
	lex.scan();

	lex.print_map();
	/*
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
	testfile.close();*/
	getchar();

	return 0;
}