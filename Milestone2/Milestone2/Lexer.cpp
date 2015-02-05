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
			//looking for operators or strings
			if (isalpha(c) || isdigit(c) || c == ' ' || c == '\t' || c == '\n') {
				break;
			}
			else {		
				stringstream ss;
				string s;
				ss << c;
				ss >> s;

				Word op;
				op.lexeme = s;

				Word str;

				//string
				if (c == '\"') {
					string st;
					testfile.get(c);
					offset++;
					while (testfile.peek() != '\"') {
						st += c;
						testfile.get(c);
						offset++;
					}
					st += c;
					offset++;
					//cout << st << " ";
					str.tag = Tag::STRINGTYPE;
					str.lexeme = st;

					//str = Word(289, st);
					cout << str.lexeme;
					//cout << str.tag;

					return str;
				}


				Word n;
				cout << c;

				switch (c) {
				case '&':
					//n = Word(Tag::AND, s);
					op.tag = Tag::AND;
					return op;
				case '|':
					op.tag = Tag::OR;
					return op;
				case '+':
					op.tag = Tag::PLUS;
					return op;
				case '-':
					op.tag = Tag::MINUS;
					return op;
				case '*':
					op.tag = Tag::MULT;
					return op;
				case '/':
					op.tag = Tag::DIV;
					return op;
				case '^':
					op.tag = Tag::POW;
					return op;
				case '%':
					op.tag = Tag::MOD;
					return op;
				case '=':
					op.tag = Tag::EQUAL;
					return op;
				case '!':
					op.tag = Tag::NOT;
					return op;
				case '<':
					op.tag = Tag::LT;
					return op;
				case '>':
					op.tag = Tag::GT;
					return op;
				case ':':
					if (testfile.peek() == '=') {
						testfile.get(c);
						op.lexeme += c;
						op.tag = Tag::ASSIGN;
						return op;
					}
				}
				testfile.get(c);
				offset++;
			}
		} //out of loop; can look for nums, reals, keywords, or ids now


		Num n;
		//Real r;
		int v = 0;
		float x = 0;
		string l;

		//numbers		
			if (isdigit(c)) {
				while (isdigit(c)) {
					l += c;
					testfile.get(c);
					offset++;
				}
				
				if (c == '.') {
					l += c; // add the decimal
					//cout << l;
					testfile.get(c);
					//cout << c;
					while (isdigit(c)) {
						l += c; 
						testfile.get(c);
						offset++;
					}
					cout << l;
					x = stof(l);
					//cout << x;
					return Tag::REALTYPE;
				}
				else {
					//return Num(v);
					v = stoi(l);
					cout << v;
					n.tag = Tag::INTTYPE;
					n.value = v;
					return n;
				}
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

			w.lexeme = b;
			cout << b;
			if (b.compare("and") == 0) {
				w.tag = Tag::AND;
				w = Word(Tag::AND, b);
				return w;
			}
			if (b.compare("or") == 0) {
				w.tag = Tag::OR;
				return w;
			}
			if (b.compare("not") == 0) {
				w.tag = Tag::NOT;
				return w;
			}
			if (b.compare("true") == 0) {
				w.tag = Tag::TRUE;
				return w;
			}
			if (b.compare("false") == 0) {
				w.tag = Tag::FALSE;
				return w;
			}
			if (b.compare("bool") == 0) {
				w.tag = Tag::BOOL;
				return w;
			}
			if (b.compare("int") == 0) {
				w.tag = Tag::INT;
				return w;
			}
			if (b.compare("real") == 0) {
				w.tag = Tag::REAL;
				return w;
			}
			if (b.compare("string") == 0) {
				w.tag = Tag::STRING;
				return w;
			}
			if (b.compare("sin") == 0) {
				w.tag = Tag::SIN;
				return w;
			}
			if (b.compare("cos") == 0) {
				w.tag = Tag::COS;
				return w;
			}
			if (b.compare("tan") == 0) {
				w.tag = Tag::TAN;
				return w;
			}
			if (b.compare("if") == 0) {
				w.tag = Tag::IF;
				return w;
			}
			if (b.compare("while") == 0) {
				w.tag = Tag::WHILE;
				return w;
			}
			if (b.compare("let") == 0) {
				w.tag = Tag::LET;
				return w;
			}
			if (b.compare("stdout") == 0) {
				w.tag = Tag::STDOUT;
				return w;
			}
			else { 
				w.tag = Tag::ID;
				return w;
			}
		}

	}
	testfile.close();

	if (testfile.peek() < 0) {
	cout << "Reached EOF\n";		
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
