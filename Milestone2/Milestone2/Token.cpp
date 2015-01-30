#include "Token.h"


Token::Token() {

}
Token::Token(int t)
{
	tag = t;
}
string Token::toString() {
	return "" + (char)tag;
}

Token::~Token()
{
}
