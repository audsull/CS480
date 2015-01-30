#include "Word.h"

Word::Word() {

}
Word::Word(int t, string s)
{
	//tag = t;
	Token::Token(t);
	lexeme = s;
}
string Word::toString() {
	return lexeme;
}

Word::~Word()
{
}

