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

