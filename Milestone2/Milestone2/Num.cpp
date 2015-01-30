#include "Num.h"

Num::Num() {

}
Num::Num(int v)
{
	Token::Token(Tag::INT);
	value = v;
}
string Num::toString() {
	return "" + value;
}

Num::~Num()
{
}
