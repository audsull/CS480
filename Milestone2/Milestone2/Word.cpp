#include "Word.h"

Word::Word() {

}
Word::Word(int t, string s)
{
	//tag = t;
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

