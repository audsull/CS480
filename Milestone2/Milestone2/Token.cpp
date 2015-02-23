#include "Token.h"
#include "Tag.h"


Token::Token() {

}
Token::Token(int t, string l)
{
	tag = t;
	lexeme = l;
}

Token::Token(int t, int v) {
	tag = t;
	value = v;
}
Token::Token(int t, float f) {
	tag = t;
	dec_value = f;
}



string Token::toString(Token t) {
	switch (t.tag) {
	case Tag::BOOL :
		return "bool";
	case Tag::AND :
		return "and";
	case Tag::ASSIGN :
		return "assign";
	case Tag::COS :
		return "cos";
	case Tag::DIV :
		return "div";
	case Tag::EQUAL :
		return "equal";
	case Tag::FALSE :
		return "false";
	case Tag::GE :
		return "greaterequal";
	case Tag::GT :
		return "greater";
	case Tag::ID :
		return "identifier";
	case Tag::IF :
		return "if";
	case Tag::INT :
		return "int";
	case Tag::INTTYPE :
		return "integertype";
	case Tag::LE :
		return "lessequal";
	case Tag::LET :
		return "let";
	case Tag::LPAR :
		return "(";
	case Tag::LT :
		return "lessthan";
	case Tag::MINUS :
		return "minus";
	case Tag::MOD :
		return "mod";
	case Tag::MULT :
		return "div";
	case Tag::NE :
		return "notequal";
	case Tag::NOT :
		return "not";
	case Tag::OR :
		return "or";
	case Tag::PLUS :
		return "plus";
	case Tag::POW :
		return "pow";
	case Tag::REAL :
		return "real";
	case Tag::REALTYPE :
		return "realtype";
	case Tag::RPAR :
		return ")";
	case Tag::SIN :
		return "sin";
	case Tag::STDOUT :
		return "stdout";
	case Tag::STRING :
		return "string";
	case Tag::STRINGTYPE :
		return "stringtype";
	case Tag::TAN :
		return "tan";
	case Tag::TRUE :
		return "true";
	case Tag::WHILE :
		return "while";
	}
}

