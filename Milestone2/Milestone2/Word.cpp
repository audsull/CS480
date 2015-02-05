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
Word Word::setValues(int t, string s) {
	Word w;
	w.token = t;
	w.lexeme = s;
	return w;
}
Word::~Word()
{
}

void Word::print_word(Word w) {
	cout << w.lexeme << "\n";
	cout << w.tag << "\n";
}