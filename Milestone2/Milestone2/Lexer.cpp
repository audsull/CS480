#include "Lexer.h"

void Lexer::reserve(Word w) {
	hashtable.insert(std::pair<string, Word>(w.lexeme, w));
	return;
}
Lexer::Lexer()
{
	//reserve(Word(Tag::IF,"if"));
	//reserve(Word(Tag::WHILE, "while"));
	//reserve(Word(Tag::LET, "let"));

	//reserve(Word::TRUE);
}
/*Token Lexer::scan() {
	std::string keywords;
	std::string letters;
	char c;
	int size = 0;
	int cur = 0;

	ifstream testfile;
	testfile.open("test.txt");

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
				return and;
				//return And;
			case '|':
				return;
				//return Or;
			case '=':
				return;
				//return Equal;
			case '!':
				return;
				//return Not;
			case '<':
				return;
				//return Lt;
			case '>':
				return;
				//return Gt;
			case ':=':
				//return Assign;
				return;
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
*/
Lexer::~Lexer()
{
}
