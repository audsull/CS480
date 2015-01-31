#include "Word.h"

Word::Word() {

}
Word::Word(int t, string s)
{
	token = t;
	lexeme = s;

	Token::Token(token);
}
string Word::toString() {
	return lexeme;
}

Word::~Word()
{
}

string Word::get_lexeme(Token t) {
	return lexeme;
}

void print_word(Word w) {
	cout << w.lexeme << "\n";
	cout << w.tag << "\n";
}