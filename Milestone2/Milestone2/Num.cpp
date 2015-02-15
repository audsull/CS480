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

int Num::getValue() {
	return this->value;
}
void Num::print() {
	Token::print();
	std::cout << this->value;
}

void Num::printLexeme(std::ostream& ostream) {
	ostream << this->value;
}

Num::~Num()
{
}
