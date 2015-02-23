#include "Dec.h"


Dec::Dec() {

}
Dec::Dec(float v)
{
	//Token::Token(Tag::REAL);
	tag = Tag::REALTYPE;
	value = v;
}
string Dec::toString() {
	return to_string(value);
}

double Dec::getValue() {
	return this->value;
}

void Dec::print() {
	Token::print();
	cout << value;
}

void Dec::printLexeme(std::ostream& ostream) {
	ostream << this->value;
}
