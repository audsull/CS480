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



void Lexer::reserve(Word w) {
	hashtable.insert(std::pair<string, Word>(w.toString(), w)); //lexeme is the actual string, word is the variable type
	 return;
}
Lexer::Lexer()
{
	reserve(If);
	reserve(While);
	reserve(Let);

	//reserve(Word::TRUE);
}
Token Lexer::scan() {
	std::string keywords;
	std::string letters;
	char c;
	int size = 0;
	int cur = 0;

	ifstream testfile;
	testfile.open("testfile.txt");

	if (testfile.is_open()) {
		while (testfile.get(c)) {
			if (c == ' ' || c == '\t' || c == '\n') {
				letters.clear();
				continue;
			}
			//letters += c;

			//ops
			switch (c) {
			case '&':
				return Tag::AND;
			case '|':
				return Tag::OR;
			case '=':
				return Tag::EQUAL;
			case '!':
				return Tag::NOT;
			case '<':
				return Tag::LT;
			case '>':
				return Tag::GT;
			case ':=':
				return Tag::ASSIGN;
			}
			//if c is a digit
			if (isdigit(c)) {
				int v = 0;

			}
			//if c is a letter
			if (isalpha(c)) {
				string b;
				b += c;
			}
		}
		cout << letters;

	}

	testfile.close();
}

Lexer::~Lexer()
{
}
