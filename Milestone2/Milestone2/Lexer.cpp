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
class Word;
class Real;



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
}
Token Lexer::scan(int &offset) {
	int cur = 0;
	ifstream testfile;
	testfile.open("testfile.txt");
	testfile.seekg(offset);

	if (testfile.is_open()) {
		while (testfile.get(c)) {
			offset++;
			if (c == ' ' || c == '\t' || c == '\n') {
				continue;
			}
			else {
				break;
			}
		}
		
		while (true) {
			if (isalpha(c) || isdigit(c) || c == ' ' || c == '\t' || c == '\n') {
				break;
			}
			else {		
				stringstream ss;
				string s;
				ss << c;
				ss >> s;

				cout << c << " ";

				switch (c) {
				case '&':
					And.lexeme = c;
					//return And;
					
					return Tag::AND;
				case '|':
					return Tag::OR;
				case '+':
					return Tag::PLUS;
				case '-':
					return Tag::MINUS;
				case '*':
					//reserve(Mult);
					//return Mult;
					//std::cout << s << "\n";
					//return Word(Tag::MULT, s);
					return Tag::MULT;
				case '/':
					return Tag::DIV;
				case '^':
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
					if (testfile.peek() == '=') {
						testfile.get(c);
						return Tag::ASSIGN;
					}
				}
				testfile.get(c);
				offset++;
			}
		}

		//numbers		
			if (isdigit(c)) {
				int v = 0;
				do {
					v = 10 * v + (char)c;
					testfile.get(c);
					offset++;
				} while (isdigit(c));
				if (c != '.') {
					//return Num(v);
					cout << v << " ";
					return Tag::INTTYPE;
				}
				float x = (float)v;
				float d = 10;
				for (;;) {
					testfile.get(c);
					if (!isdigit(c)) break;
					x = x + (int)c / d;
					d = d * 10;
				}
				//return Real(x);
				cout << x << ' ';
				return Tag::REALTYPE;
			}

			//string
			if (c == '\"') {
				cout << "String? ";
				while (testfile.peek() != '\"') {
					testfile.get(c);
				}
				return Tag::STRING;
			}

		//letters
		if (isalpha(c)) {
			string b;
			Word w;
			do {
				b += c;
				testfile.get(c);
				offset++;
			} while (isalpha(c) || isdigit(c));
				//lookup = hashtable.find(b);
				
				//if (1) {
					//return lookup;
				//}
				//lookup = Word(Tag::ID, b);
				//hashtable.insert(std::pair<string, Word>(lookup.toString(), lookup));
				//return lookup;
			cout << b << " ";

			if (b.compare("and") == 0) {
				w = Word(Tag::AND, b);
				hashtable.insert(std::pair<string, Word>(b, w));
				//valuemap.insert(pair<Tag::AND, b>);
				
				return Tag::AND;
			}
			if (b.compare("or") == 0) {
				return Tag::OR;
			}
			if (b.compare("not") == 0) {
				return Tag::NOT;
			}
			if (b.compare("true") == 0) {
				return Tag::TRUE;
			}
			if (b.compare("false") == 0) {
				return Tag::FALSE;
			}
			if (b.compare("bool") == 0) {
				return Tag::BOOL;
			}
			if (b.compare("int") == 0) {
				return Tag::INT;
			}
			if (b.compare("real") == 0) {
				return Tag::REAL;
			}
			if (b.compare("string") == 0) {
				return Tag::STRING;
			}
			if (b.compare("sin") == 0) {
				return Tag::SIN;
			}
			if (b.compare("cos") == 0) {
				return Tag::COS;
			}
			if (b.compare("tan") == 0) {
				return Tag::TAN;
			}
			if (b.compare("if") == 0) {
				return Tag::IF;
			}
			if (b.compare("while") == 0) {
				return Tag::WHILE;
			}
			if (b.compare("let") == 0) {
				return Tag::LET;
			}
			if (b.compare("stdout") == 0) {
				return Tag::STDOUT;
			}
			else { 
				return Tag::ID;
			}
		}
	}
	testfile.close();


	if (testfile.peek() < 0) {
	//cout << "Reached EOF\n";		
		return Tag::END;
	}

}

void Lexer::print_map() {
	int size = hashtable.size();
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
