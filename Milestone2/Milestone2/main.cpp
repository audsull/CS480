#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>
#include <string>
#include "Tag.h"
#include "Token.h"
#include "Lexer.h"
#include "Parser.h"
#include "SyntaxTree.h"

using namespace std;
class Token;


int main() {
	ofstream outfile;
	outfile.open("output.txt");
	if (outfile.is_open())
		outfile << "Test";
	outfile.close();


	Token t;
	Parser parse;
	//t = parse.getToken();
	//parse.doLex();
	
	/*
	int test = 0;
	while (test != Tag::END) {
		test = parse.T();
		cout << "\n\n";
	}
	parse.result();

	int test = 0;

	while (test != 299) {
		test = parse.testToken();
		cout << test; 
		cout << "\n";
	}
	*/

	/*while (t.tag != 299) {
		t = parse.testValue();
		t = parse.T();
		cout << "\n\n";
	}*/	

	SyntaxTree tree;
	while (t.tag != 299) {
		t = tree.T_syntax(outfile);
	}



	getchar();
	return 0;
}