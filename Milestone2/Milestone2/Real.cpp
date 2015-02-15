#include "Real.h"


Real::Real() {

}
Real::Real(float v)
{
	Token::Token(Tag::REAL);
	value = v;
}
string Real::toString() {
	return to_string(value);
}

double Real::getValue() {
	return this->value;
}

void Real::print() {
	Token::print();
	cout << value;
}

void Real::printLexeme(std::ostream& ostream) {
	ostream << this->value;
}

Real::~Real()
{
}
