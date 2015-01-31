#include "Lexer.h"

static Word Bool = Word(Tag::BOOL, "bool"), True = Word(Tag::TRUE, "true"), False = Word(Tag::FALSE, "false"),
And = Word(Tag::AND, "&&"), Or = Word(Tag::OR, "||"), Not = Word(Tag::NOT, "!"),
Int = Word(Tag::INT, "int"), Real = Word(Tag::REAL, "real"), String = Word(Tag::STRING, "string"),
Plus = Word(Tag::PLUS, "+"), Minus = Word(Tag::MINUS, "-"), Mult = Word(Tag::MULT, "*"), Div = Word(Tag::DIV, "/"),
Mod = Word(Tag::MOD, "%"), Pow = Word(Tag::POW, "^"), Equal = Word(Tag::EQUAL, "="),
Lt = Word(Tag::LT, "<"), Gt = Word(Tag::GT, ">"), Le = Word(Tag::LE, "<="), Ge = Word(Tag::GE, ">="),
Ne = Word(Tag::NE, "!="), Stdout = Word(Tag::STDOUT, "stdout"),
If = Word(Tag::IF, "if"), While = Word(Tag::WHILE, "while"), Let = Word(Tag::LET, "let"), Assign = Word(Tag::ASSIGN, ":="),
Sin = Word(Tag::SIN, "sin"), Cos = Word(Tag::COS, "cos"), Tan = Word(Tag::TAN, "tan");

class Num;
//char c;

void Lexer::reserve(Word w) {
	hashtable.insert(std::pair<string, Word>(w.toString(), w)); //lexeme is the actual string, word is the variable type
	 return;
}


Lexer::Lexer()
{
	//reserved keywords
	reserve(If);
	reserve(While);
	reserve(Let);
	//reserve(Assign);
	reserve(Sin);
	reserve(Cos);
	reserve(Tan);
	reserve(True);
	reserve(False);
	reserve(Bool);
	reserve(Int);
	reserve(Real);
	reserve(String);
	reserve(Stdout);


	//reserve(Word::TRUE);
}
Token Lexer::scan(int &offset) {
	//char c = input.get();
	//cout << "[IN LEXER]: ";
	int cur = 0;

	ifstream testfile;
	testfile.open("testfile.txt");

	testfile.seekg(offset);

	if (testfile.is_open()) {
		while (testfile.get(c)) {
			offset++;
			std::cout << "Checking for spaces..\n";
			if (c == ' ' || c == '\t' || c == '\n') {
				std::cout << "Found one\n";
				continue;
			}
			else {
				//cout << "None\n";
				break;
			}
		}
			//letters += c;
		//cout << c;
		
		while (true) {
			std::cout << "Checking for operators..\n";
			if (isalpha(c) || isdigit(c) || c == ' ' || c == '\t' || c == '\n') {
				//cout << "None\n";
				break;
			}
			else {
				printf("Found one!\n");
				
				//operators
				switch (c) {
				case '&':
					return Tag::AND;
				case '|':
					return Tag::OR;
				case '+':
					return Tag::PLUS;
				case '-':
					return Tag::MINUS;
				case '*':
					reserve(Mult);
					return Tag::MULT;
				case '/':
					return Tag::DIV;
				case '^':
					//cout << "Pow";
					return Tag::POW;
				case '%':
					return Tag::MOD;
				case '=':
					//cout << "Equal ";
					return Tag::EQUAL;
				case '!':
					return Tag::NOT;
				case '<':
					return Tag::LT;
				case '>':
					return Tag::GT;
				case ':':
					return Tag::ASSIGN;
				}
				//cout << "Get here";
				testfile.get(c);
				offset++;
			}
		}

		

		//numbers		
		//while (testfile.get(c)) {
		//cout << c;
			std::cout << "Checking for numbers..\n";
			if (isdigit(c)) {
				//cout << "Found one\n";
				//cout << c;

				int v = 0;
				do {
					v = 10 * c;
					testfile.get(c);
					offset++;
				} while (isdigit(c));
				if (c != '.') {
					return Tag::INT;
				}
				
				//cout << v;
			}
			else {
				//break;
			}
		//}
		


		//letters
		if (isalpha(c)) {
			std::cout << "Checking for words..\n";
			string b;
				//Word it;
			do {
				b += c;
				testfile.get(c);
				offset++;
			} while (isalpha(c) || isdigit(c));
				/*
				//it = hashtable.find(b);
				if (1) {
				return it;
				}
				it = Word(Tag::ID, b);
				hashtable.insert(std::pair<string, Word>(it.toString(), it));
				return it;
				*/
			//cout << b << "\n";
			return Tag::ID;
		}
		std::cout << "Got out";
	}
	testfile.close();

	//cout << "Reached EOF\n";
	return Tag::END;
}

void Lexer::print_map() {
	int size = hashtable.size();
	//std::ofstream out("out.txt");

	std::cout << "\nPrinting Table:\n";

	for (std::map<string, Word>::const_iterator it = hashtable.begin(); 
		it != hashtable.end(); ++it) {
		cout << "<" << it->first << ", " << it->second.lexeme << ", " << it->second.token << ">\n";
	}
}

void Lexer::print_tokens() {

}

Lexer::~Lexer()
{
}
