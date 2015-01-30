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

Real::~Real()
{
}
