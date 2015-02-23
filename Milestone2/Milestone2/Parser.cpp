#include "Parser.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>
#include "Tag.h"
#include "Token.h"
#include "Lexer.h"


Parser::Parser()
{

}
Token Parser::getToken() {
	Lexer lex;
	Token t;

	t = lex.scan(os);
	next = getNextToken();

	//cout << "CUR: " << cur.tag << " NEXT: " << next.tag << "\n";
	return t;
}
Token Parser::getNextToken() {
	Lexer nextLex;
	Token tnext;

	tnext = nextLex.scan(nextos);
	return tnext;
}

int Parser::testToken() {
	return getToken().tag;
}
Token Parser::testValue() {
	Token t;
	t = getToken();
	if (t.tag == 289) {
		cout << t.tag << " " << t.lexeme << " String\n";
	}
	if (t.tag < 265 || (t.tag > 277 && t.tag < 285)) {
		cout << t.tag << " " << t.lexeme << " Keyword\n";
	}
	if (t.tag == 286) {
		cout << t.tag << " " << t.lexeme << " ID\n";
	}
	if (t.tag == 287) {
		cout << t.tag << " " << t.value << " Integer\n";
	}
	if (t.tag == 288) {
		cout << t.tag << " " << t.dec_value << " Float\n";
	}
	if (t.tag > 264 && t.tag < 278 || t.tag > 289 && t.tag < 292) {
		cout << t.tag << " " << t.lexeme << " Operator\n";
	}
	if (t.tag == 299) {
		cout << "End";
	}
	return t;
}
void Parser::printVal(Token cur) {
	if (cur.tag == 289) {
		cout << cur.toString(cur) << " " << cur.lexeme << "\n";
	}
	if (cur.tag < 265 || (cur.tag > 277 && cur.tag < 285)) {
		cout << cur.toString(cur) << " " << cur.lexeme << "\n";
	}
	if (cur.tag == 286) {
		cout << cur.toString(cur) << " " << cur.lexeme << "\n";
	}
	if (cur.tag == 287) {
		cout << cur.toString(cur) << " " << cur.value << "\n";
	}
	if (cur.tag == 288) {
		cout << cur.toString(cur) << " " << cur.dec_value << "\n";
	}
	if (cur.tag > 264 && cur.tag < 278 || cur.tag > 289 && cur.tag < 292) {
		cout << cur.toString(cur) << " " << cur.lexeme << "\n";
	}
}

void Parser::doLex() {
	int offset = 0;
	Lexer lex;
	Token t;

	while (t.tag != Tag::END) {
		t = lex.scan(offset);

		if (t.tag == 289) {
			cout << t.tag << " " << t.lexeme << " String\n";
		}
		if (t.tag < 265 || (t.tag > 277 && t.tag < 285)) {
			cout << t.tag << " " << t.lexeme << " Keyword\n";
		}
		if (t.tag == 286) {
			cout << t.tag << " " << t.lexeme << " ID\n";
		}
		if (t.tag == 287) {
			cout << t.tag << " " << t.value << " Integer\n";
		}
		if (t.tag == 288) {
			cout << t.tag << " " << t.dec_value << " Float\n";
		}
		if (t.tag > 264 && t.tag < 278 || t.tag > 289 && t.tag < 292) {
			cout << t.tag << " " << t.lexeme << " Operator\n";
		}
		if (t.tag == 299) {
			cout << "End";
		}
	}

}

void Parser::result() {
	if (pass)
		cout << "Success\n";
	else
		cout << "Failure\n";
}

Token Parser::T() {
	//cout << "[T]\n";
	pass = false;

	//setting cur and next tokens
	next = Parser::getNextToken();
	cur = Parser::getToken();

	pass = Parser::S();

	cout << "\nT finished with pass: " << pass << "\n";
	return cur;
}
bool Parser::S() {
	//cout << "[S]\n";
	bool status = false;

	//cout << "CUR: " << cur.tag << " NEXT: " << next.tag << "\n";

	if (next.tag == Tag::END) {
		return false;
	}

	switch (cur.tag) {

	case Tag::LPAR:
		//()S1
		if (next.tag == Tag::RPAR) {
			//cout << "S->()S1\n";
			cout << "(\n";
			cout << ")\n";

			status = Parser::S1();
			return status;
		}
		//(S)S1
		else {
			//cout << "S->(S)S1\n";
			if (next.tag == Tag::LPAR) {
				
				for (int i = 0; i < lvl; i++) {
					cout << "\t";
				}
				cout << "(\n";
				lvl++;

				//cout << "Before S again\n";
				cur = Parser::getToken();
				status = Parser::S();

				//cout << "After S again\n";

				lvl--;

				for (int i = 0; i < lvl; i++) {
					cout << "\t";
				}
				if (lvl >= 0)
					cout << ")\n";

				status = Parser::S1();
			}
			else {
				//cout << "S->exprS1\n";
				for (int i = 0; i < lvl; i++) {
					cout << "\t";
				}
				cout << "(\n";					//first LPAR
				lvl++;

				status = Parser::expr();
				cur = Parser::getToken();

				//cout << "got here\n";

				Parser::S1();
			}
		}
		//exprS1
	case Tag::RPAR:
		//cout << "I see RPAR\n";

		if (next.tag == Tag::END) {
			lvl--;
			for (int i = 0; i < lvl; i++) {
				cout << "\t";
			}
			if(lvl >= 0)
				cout << ")\n";
			return true;
		}
		else {
			lvl--;

			for (int i = 0; i < lvl; i++) {
				cout << "\t";
			}
			if (lvl >= 0)
				cout << ")\n";
			//cout << lvl << "\n";
			//cout << "CUR: " << cur.tag << " NEXT: " << next.tag << "\n";

			cur = Parser::getToken();
			//cout << "next token\n";
			//cout << "CUR: " << cur.tag << " NEXT: " << next.tag << "\n";

			status = Parser::S1();
		}
	case Tag::END:
		return status;
	default:
		//cout << "\nS->exprS1\n";

		status = Parser::expr();
		cur = Parser::getToken();
		
		//cout << "CUR: " << cur.tag << " NEXT: " << next.tag << "\n";
		status = Parser::S1();
		return true;
	}
	return status;
}
bool Parser::S1() {
	bool status = false;
	//cout << "[S1]\n";

	if (next.tag == Tag::END) {
		//cout << "END";
		return true;
	}

	status = Parser::S();
	if (status)
		status = Parser::S1();

	//cout << status;
	return status;
}

bool Parser::expr() {
	//cout << "[EXPR]\n";
	bool status = false;
	
	//oper
	status = Parser::oper();
	//stmts
	if (!status) {
		status = Parser::stmts();
	}
	return status;
}
bool Parser::oper() {
	//cout << "[OPER]\n";
	bool status = false;

	//cout << "CUR: " << cur.tag << " NEXT: " << next.tag << "\n";

	if (cur.tag == Tag::LPAR) {

		if (next.tag == Tag::ASSIGN) {
			//cout << "(:= id oper)\n";
			//cout << "[ASSIGN]\n";

			for (int i = 0; i < lvl; i++) {
				cout << "\t";
			}
			cout << "(\n";
			lvl++;

			for (int i = 0; i < lvl; i++) {
				cout << "\t";
			}
			Parser::printVal(next);

			cur = Parser::getToken();

			//cout << "CUR: " << cur.tag << " NEXT: " << next.tag << "\n";
			status = Parser::ids();

			cur = Parser::getToken();
			//cout << "CUR: " << cur.tag << " NEXT: " << next.tag << "\n";

			if (next.tag == Tag::LPAR) {
				cur = Parser::getToken();
				for (int i = 0; i < lvl; i++) {
					cout << "\t";
				}
				cout << "(\n";
				lvl++;
				//cout << "CUR: " << cur.tag << " NEXT: " << next.tag << "\n";
			}
			status = Parser::oper();
			cur = Parser::getToken();

//			cout << "CUR: " << cur.tag << " NEXT: " << next.tag << "\n";

			if (next.tag == Tag::RPAR) {
				cur = Parser::getToken();
				lvl--;
				for (int i = 0; i < lvl; i++) {
					cout << "\t";
				}
				cout << ")\n";
				return status;
			}
		}
		//(binops oper oper)
		if (next.tag >= 265 && next.tag <= 276) {
			//cout << "(binops oper oper)\n";

			for (int i = 0; i < lvl; i++) {
				cout << "\t";
			}
			cout << "(\n";
			lvl++;

			
			status = Parser::binops();
			
			//cout << "FINISHED BINOP\n";
			if (next.tag == Tag::RPAR) {

				lvl--;
				for (int i = 0; i < lvl; i++) {
					cout << "\t";
				}
				cout << ")\n";
			}

			return status;
		}

		if (next.tag == 261 || (next.tag >= 282 && next.tag <= 284)) {
			//(unops oper)
			//cout << "(unops oper)\n";

			//cur = Parser::getToken();

			if (next.tag == Tag::LPAR) {
				cur = Parser::getToken();
				for (int i = 0; i < lvl; i++) {
					cout << "\t";
				}
				cout << "(\n";
				lvl++;
				//cout << "CUR: " << cur.tag << " NEXT: " << next.tag << "\n";
			}

			status = Parser::unops();
			cur = Parser::getToken();
			
			status = Parser::oper();
			cur = Parser::getToken();

			//cout << "CUR: " << cur.tag << " NEXT: " << next.tag << "\n";
			
			if (next.tag == Tag::RPAR) {
				cur = Parser::getToken();
				lvl--;
				for (int i = 0; i < lvl; i++) {
					cout << "\t";
				}
				cout << ")\n";
				return status;
			}
		}
		else {
			//return status;
		}
	}
		//constants
	if ((next.tag == Tag::STRINGTYPE ) || (next.tag == Tag::INTTYPE) || (next.tag == Tag::REALTYPE)) {
		status = Parser::constants();
	}
		//ids
	if (next.tag == Tag::ID) {
		status = Parser::ids();
	}
	return status;
}

bool Parser::binops() {
	bool status = false;
	//cout << "[BINOPS]\n";

	//cout << "binops\n";
	//lvl++;
	for (int i = 0; i < lvl; i++) {
		cout << "\t";
	}

	Parser::printVal(next);

	//cout << "CUR: " << cur.tag << " NEXT: " << next.tag << "\n";

	cur = Parser::getToken();
	status = Parser::oper();



	if (status) {

		cur = Parser::getToken();
		status = Parser::oper();

		if (status) {
			cur = Parser::getToken();
			//cout << "CUR: " << cur.tag << " NEXT: " << next.tag << "\n";

		}
		else
			return false;

	}


	return status;
}
bool Parser::unops() {
	//cout << "[UNOPS]\n";
	//cout << "\t\t\t";
	bool status = false;
	for (int i = 0; i < lvl; i++) {
		cout << "\t";
	}

	if (next.tag == Tag::MINUS || next.tag == Tag::NOT || next.tag == Tag::SIN || next.tag == Tag::COS || next.tag == Tag::TAN) {
		Parser::printVal(next);
		status = true;
	}
	return status;
}
bool Parser::constants() {
	//cout << "[CONSTANTS]\n";
	//cout << "CUR: " << cur.tag << " NEXT: " << next.tag << "\n";
	bool status = false;
	//strings
	switch (next.tag) {
	case Tag::STRINGTYPE:
		status = Parser::strings();
		break;
	case Tag::INTTYPE:
		status = Parser::ints();
		break;
	case Tag::REALTYPE:
		status = Parser::floats();
		break;
	}
	return status;
}
bool Parser::strings() {
	//cout << "\t\t\t[STRINGS]\n";
	cur = Parser::getToken();
	bool status = false;

	if (cur.tag == Tag::STRINGTYPE || cur.tag == Tag::TRUE || cur.tag == Tag::FALSE) {
		Parser::printVal(next);
		status = true;
	}
	return status;
}
bool Parser::ids() {
	//cout << "\t\t\t[IDS]\n";
	//cout << "CUR: " << cur.tag << " NEXT: " << next.tag << "\n";
	
	if (next.tag == Tag::ID) { 
		for (int i = 0; i < lvl; i++) {
			cout << "\t";
		}
		Parser::printVal(next);
		return true;
	}
	return false;
}
bool Parser::ints() {
	//cout << "\t\t\t[INTS]\n";
	//cout << "CUR: " << cur.tag << " NEXT: " << next.tag << "\n";
	
	if (next.tag == Tag::INTTYPE) {
		for (int i = 0; i < lvl; i++) {
			cout << "\t";
		}
		Parser::printVal(next);
		return true;
	}
	return false;
}
bool Parser::floats() {
	if (next.tag == Tag::REALTYPE) {
		for (int i = 0; i < lvl; i++) {
			cout << "\t";
		}
		Parser::printVal(next);
		return true;
	}
	return false;
}
bool Parser::stmts() {
	bool status = false;	
	while (!status) {
		if (next.tag == Tag::IF)
			status = ifstmts();
		if (next.tag == Tag::WHILE)
			status = whilestmts();
		if (next.tag == Tag::LET) {
			status = letstmts();
		}
		if (next.tag == Tag::STDOUT)
			status = printstmts();
		else
			break;
	}
	return status;
}
bool Parser::printstmts() {
	//cout << "[PRINTSTMTS]\n";

	if (cur.tag == Tag::LPAR) {
		//for (int i = 0; i < lvl; i++) {
			//cout << "\t";
		//}
		//cout << "(\n";
		//lvl++;
		cur = Parser::getToken();

		if (cur.tag == Tag::STDOUT) {
			
			for (int i = 0; i < lvl; i++) {
				cout << "\t";
			}
			Parser::printVal(cur);
		}
		Parser::oper();
		//cur = Parser::getToken();


		if (cur.tag == Tag::RPAR) {
			lvl--;
			for (int i = 0; i < lvl; i++) {
				cout << "\t";
			}
			cout << ")\n";
			return true;
		}
	}
	return false;
}
bool Parser::ifstmts() {
	//cout << "[IFSTMTS]\n";
	//cout << "CUR: " << cur.tag << " NEXT: " << next.tag << "\n";

	if (cur.tag == Tag::LPAR && next.tag == Tag::IF) {
		for (int i = 0; i < lvl; i++) {
			cout << "\t";
		}
		Parser::printVal(next);

		cur = Parser::getToken();
		//cout << "CUR: " << cur.tag << " NEXT: " << next.tag << "\n";
		if (next.tag == Tag::LPAR) {
			cur = Parser::getToken();
		}
		Parser::expr();
		cur = Parser::getToken();

		//cout << "CUR: " << cur.tag << " NEXT: " << next.tag << "\n";
		Parser::expr();
		cur = Parser::getToken();


		if (next.tag == Tag::RPAR) {
			return true;
		}
		else {
			Parser::expr();
			if (next.tag == Tag::RPAR) {
				return true;
			}
		}
	}
	return false;
}
bool Parser::whilestmts() {
	//cout << "\t\t\t[WHILESTMTS]\n";
	//cout << "CUR: " << cur.tag << " NEXT: " << next.tag << "\n";

	if (cur.tag == Tag::LPAR && next.tag == Tag::WHILE) {
		for (int i = 0; i < lvl; i++) {
			cout << "\t";
		}
		Parser::printVal(next);

		cur = Parser::getToken();
		//cout << "CUR: " << cur.tag << " NEXT: " << next.tag << "\n";
		if (next.tag == Tag::LPAR) {
			cur = Parser::getToken();
		}
		Parser::expr();

		//cout << "CUR: " << cur.tag << " NEXT: " << next.tag << "\n";
		Parser::exprlist();
		if (next.tag == Tag::RPAR) {
			for (int i = 0; i < lvl; i++) {
				cout << "\t";
			}
			cout << ")\n";
			
			return true;
		}
	}
	return false;
}
bool Parser::exprlist() {
	//cout << "[EXPRLIST]\n";
	bool status = false;
	status = expr();
	if (!status)
		expr();
	return status;
}
bool Parser::letstmts() {
	//cout << "[LETSTMTS]\n";
	bool status;

	//cout << "CUR: " << cur.tag << " NEXT: " << next.tag << "\n";

	if (cur.tag == Tag::LPAR && next.tag == Tag::LET) {
		for (int i = 0; i < lvl; i++) {
			cout << "\t";
		}
		Parser::printVal(next);

		cur = Parser::getToken();

		if (next.tag == Tag::LPAR) {
			//cur = Parser::getToken();
			for (int i = 0; i < lvl; i++) {
				cout << "\t";
			}
			cout << "(\n";
			lvl++;

			status = Parser::varlist();
			
			if (status) {
				//cout << "HERE";

				cur = Parser::getToken();


				if (next.tag == Tag::RPAR) {
					//cur = Parser::getToken();
					lvl--;
					for (int i = 0; i < lvl; i++) {
						cout << "\t";
					}
					cout << ")\n";
				}
			}

			else {
				return false;
			}
		}
		return false;
	}
	return false;
}
bool Parser::varlist() {
	bool status = false;
	//cout << "[VARLIST]\n";

	if (next.tag == Tag::LPAR) {
		cur = Parser::getToken();
		//cout << "CUR: " << cur.tag << " NEXT: " << next.tag << "\n";
		status = Parser::ids();

		cur = Parser::getToken();

		//cout << "CUR: " << cur.tag << " NEXT: " << next.tag << "\n";


		if (!status) {
			return false;
		}
		status = Parser::type();
		cur = Parser::getToken();
		
		if (next.tag == Tag::RPAR) {
			lvl--;
			for (int i = 0; i < lvl; i++) {
				cout << "\t";
			}
			cout << ")\n";
			cur = Parser::getToken();

			if (next.tag == Tag::LPAR) {
				status = Parser::varlist();
			}
			else {
				if (next.tag == Tag::RPAR) {
					lvl--;
					for (int i = 0; i < lvl; i++) {
						cout << "\t";
					}
					cout << ")\n";
				}
				return true;
			}

			return false;
		}
		return false;
	}
	return false;
}
bool Parser::type() {
	//cout << "\t[TYPE]\n";
	for (int i = 0; i < lvl; i++) {
		cout << "\t";
	}

	Parser::printVal(next);
	return false;
}
