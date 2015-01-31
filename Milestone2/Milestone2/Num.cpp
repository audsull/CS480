#include "Num.h"

Num::Num() {

}
Num::Num(int v)
{
	Token::Token(Tag::INT);
	value = v;
}
string Num::toString() {
	//return "" + value;
	string result;
	ostringstream convert;
	convert << value;
	result = convert.str();
	return result;
}

Num::~Num()
{
}
