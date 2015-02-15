#include "Token.h"
#include "Tag.h"


Token::Token() {

}
Token::Token(int t)
{
	tag = t;
}

void Token::print() {
	switch (tag) {
	case Tag::BOOL:
		cout << "bool";
	case Tag::AND:
		cout << "and";
	case Tag::ASSIGN:
		cout << ":=";
	case Tag::COS:
		cout << "cos";
	case Tag::DIV:
		cout << "/";
	case Tag::EQUAL:
		cout << "=";
	case Tag::FALSE:
		cout << "false";
	case Tag::GE:
		cout << ">=";
	case Tag::GT:
		cout << ">";
	case Tag::ID:
		cout << "identifier";
	case Tag::IF:
		cout << "if";
	case Tag::INT:
		cout << "int";
	case Tag::INTTYPE:
		cout << "interger type";
	case Tag::LE:
		cout << "<=";
	case Tag::LET:
		cout << "let";
	case Tag::LPAR:
		cout << "(";
	case Tag::LT:
		cout << "<";
	case Tag::MINUS:
		cout << "-";
	case Tag::MOD:
		cout << "%";
	case Tag::MULT:
		cout << "*";
	case Tag::NE:
		cout << "!=";
	case Tag::NOT:
		cout << "!";
	case Tag::OR:
		cout << "or";
	case Tag::PLUS:
		cout << "+";
	case Tag::POW:
		cout << "^";
	case Tag::REAL:
		cout << "real";
	case Tag::REALTYPE:
		cout << "real type";
	case Tag::RPAR:
		cout << ")";
	case Tag::SIN:
		cout << "sin";
	case Tag::STDOUT:
		cout << "stdout";
	case Tag::STRING:
		cout << "string";
	case Tag::STRINGTYPE:
		cout << "string type";
	case Tag::TAN:
		cout << "tan";
	case Tag::TRUE:
		cout << "true";
	case Tag::WHILE:
		cout << "while";
	}
}

string Token::toString() {
	//return "" + (char)tag;
	switch (tag) {
	case Tag::BOOL :
		return "bool";
	case Tag::AND :
		return "and";
	case Tag::ASSIGN :
		return ":=";
	case Tag::COS :
		return "cos";
	case Tag::DIV :
		return "/";
	case Tag::EQUAL :
		return "=";
	case Tag::FALSE :
		return "false";
	case Tag::GE :
		return ">=";
	case Tag::GT :
		return ">";
	case Tag::ID :
		return "identifier";
	case Tag::IF :
		return "if";
	case Tag::INT :
		return "int";
	case Tag::INTTYPE :
		return "interger type";
	case Tag::LE :
		return "<=";
	case Tag::LET :
		return "let";
	case Tag::LPAR :
		return "(";
	case Tag::LT :
		return "<";
	case Tag::MINUS :
		return "-";
	case Tag::MOD :
		return "%";
	case Tag::MULT :
		return "*";
	case Tag::NE :
		return "!=";
	case Tag::NOT :
		return "!";
	case Tag::OR :
		return "or";
	case Tag::PLUS :
		return "+";
	case Tag::POW :
		return "^";
	case Tag::REAL :
		return "real";
	case Tag::REALTYPE :
		return "real type";
	case Tag::RPAR :
		return ")";
	case Tag::SIN :
		return "sin";
	case Tag::STDOUT :
		return "stdout";
	case Tag::STRING :
		return "string";
	case Tag::STRINGTYPE :
		return "string type";
	case Tag::TAN :
		return "tan";
	case Tag::TRUE :
		return "true";
	case Tag::WHILE :
		return "while";
	}
}
void Token::printLexeme(std::ostream& ostream) {
	//const char* function_name = "Token::printLexeme()";

	ostream << this->toString().c_str();
}
Token::~Token()
{
}
