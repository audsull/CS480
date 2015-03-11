#include "SyntaxTree.h"

std::map<std::string, int> varInts;
std::map<std::string, float> varFloats;
std::map <std::string, std::string> varStrings;
std::map <std::string, bool> varBools;

SyntaxTree::SyntaxTree()
{}

Token SyntaxTree::getToken_syntax() {
	Lexer lex;
	Token t;
	t = lex.scan(os);
	next = getNext_syntax();
	return t;
}
Token SyntaxTree::getToken_syntax(bool &isReal, bool &isInt) {
	Lexer lex;
	Token t;
	t = lex.scan(os);
	next = getNext_syntax();
	if (next.tag == Tag::REALTYPE || cur.tag == Tag::REALTYPE)
		isReal = true;
	if (next.tag == Tag::INTTYPE || cur.tag == Tag::INTTYPE)
		isInt = true;
	return t;
}

Token SyntaxTree::getNext_syntax() {
	Lexer nextLex;
	Token tnext;
	tnext = nextLex.scan(nextos);
	return tnext;
}
void SyntaxTree::printVal_syntax(Token cur, ofstream& outfile) {
	//string
	if (cur.tag == Tag::LPAR || cur.tag == Tag::RPAR)
		return;
	if (cur.tag == 289) {
		cout << "s\" " << cur.lexeme << "\" "; //TYPE ";
		outfile << cur.lexeme << " ";
	}
	if (cur.tag < 265 || (cur.tag > 277 && cur.tag < 285)) {
		cout << cur.lexeme << " ";
		outfile << cur.lexeme << " ";
	}
	if (cur.tag == 286) {
		cout << cur.lexeme << " ";
		outfile << cur.lexeme << " ";
	}
	if (cur.tag == 287) {
		cout << cur.value << " ";
		outfile << cur.value << " ";
	}
	if (cur.tag == 288) {
		cout << cur.dec_value << "e ";
		outfile << cur.dec_value << "e ";
	}
	if (cur.tag > 264 && cur.tag < 278 || cur.tag > 289 && cur.tag < 293) {
		cout << cur.lexeme << " ";
		outfile << cur.lexeme << " ";
	}
}

Token SyntaxTree::T_syntax(ofstream& outfile) {
	pass = false;
	next = SyntaxTree::getNext_syntax();
	cur = SyntaxTree::getToken_syntax();
	pass = SyntaxTree::S_syntax(outfile);
	return cur;
}
bool SyntaxTree::S_syntax(ofstream& outfile) {
	bool status = false;
	if (next.tag == Tag::END) {
		return false;
	}
	switch (cur.tag) {
	case Tag::LPAR:
		//()S1
		if (next.tag == Tag::RPAR) {
			status = SyntaxTree::S1_syntax(outfile);
			return status;
		}
		//(S)S1
		else {
			if (next.tag == Tag::LPAR) {
				cur = SyntaxTree::getToken_syntax();
				status = SyntaxTree::S_syntax(outfile);
				status = SyntaxTree::S1_syntax(outfile);
			}
			else {
				status = SyntaxTree::expr_syntax(outfile);
				cur = SyntaxTree::getToken_syntax();
				SyntaxTree::S1_syntax(outfile);
			}
		}
		//exprS1
	case Tag::RPAR:
		if (next.tag == Tag::END) {
			return true;
		}
		else {			
			cur = SyntaxTree::getToken_syntax();
			status = SyntaxTree::S1_syntax(outfile);
		}
	case Tag::END:
		return status;
	default:
		status = SyntaxTree::expr_syntax(outfile);
		cur = SyntaxTree::getToken_syntax();
		status = SyntaxTree::S1_syntax(outfile);
		return true;
	}
	return status;
}
bool SyntaxTree::S1_syntax(ofstream& outfile) {
	bool status = false;

	if (next.tag == Tag::END) {
		return true;
	}

	status = SyntaxTree::S_syntax(outfile);
	if (status)
		status = SyntaxTree::S1_syntax(outfile);

	return status;
}

bool SyntaxTree::expr_syntax(ofstream& outfile) {
	bool status = false;

	//oper
	status = SyntaxTree::oper_syntax(outfile);
	//stmts
	if (!status) {
		status = SyntaxTree::stmts_syntax(outfile);
	}
	return status;
}
bool SyntaxTree::oper_syntax(ofstream& outfile) {
	bool status = false;

	//assign
	if (cur.tag == Tag::LPAR) {
		if (next.tag == Tag::ASSIGN) {


			cur = SyntaxTree::getToken_syntax();

			status = SyntaxTree::ids_syntax(outfile);
			string curid = next.lexeme;

			cur = SyntaxTree::getToken_syntax();
			
			Token var = cur; //var is the id
			//string excla = " !";

			//cout << next.tag << endl;

			if (next.tag == Tag::INTTYPE) {
				varInts[curid] = next.value;
			}
			if (next.tag == Tag::REALTYPE) {
				varFloats[curid] = next.dec_value;
			}
			if (next.tag == Tag::STRINGTYPE) {
				varStrings[curid] = next.lexeme;
			}

			//cout << declared_int << declared_real << endl;

			//cout << varInts[curid] << endl;
			//cout << varFloats[curid] << endl;
			//cout << varStrings[curid] << endl;

			if (next.tag == Tag::LPAR) {
				cur = SyntaxTree::getToken_syntax();
			}
			status = SyntaxTree::oper_syntax(outfile);

			if (next.tag == Tag::REALTYPE) {
				//cout << "real-type";
				excla = " f!";
			}

			cur = SyntaxTree::getToken_syntax();

			cout << " " << var.lexeme << excla << "\n";

			if (next.tag == Tag::RPAR) {
				cur = SyntaxTree::getToken_syntax();
				return status;
			}
		}
		//(binops oper oper)
		if ((next.tag >= 265 && next.tag <= 276) || (next.tag == Tag::AND) || next.tag == Tag::OR) {
			Token b = next;

			if (b.tag == Tag::POW)
				powop = true;
							
			status = SyntaxTree::binops_syntax(outfile);

			if (!status) {
				cout << "negate ";
				return true;
			}
			if (next.tag == Tag::RPAR) {
				status = true;
			}
			if (b.tag == Tag::MOD) {
				cout << "mod ";
			}
			else if (b.tag == Tag::POW) {
				cout << "f** ";
				if (newInt)
					cout << "f>s";
			}
			else if (b.tag == Tag::NE) {
				cout << "<> ";
			}
			else if (b.tag == Tag::AND) {
				cout << "and ";
			}
			else if (b.tag == Tag::OR) {
				cout << "or ";
			}

			else
				SyntaxTree::printVal_syntax(b, outfile);
			
			return status;
		}

		if (next.tag == 261 || (next.tag >= 282 && next.tag <= 284)) {
			//(unops oper) 
			bool isReal = false;
			bool isInt = false;

			if (next.tag == Tag::LPAR) {
				cur = SyntaxTree::getToken_syntax();
			}

			status = SyntaxTree::unops_syntax(outfile, isReal, isInt);

			if (next.tag == Tag::RPAR) {
				cur = SyntaxTree::getToken_syntax();
				return status;
			}
		}
		else {
			//return status;
		}
	}
	//constants
	if ((next.tag == Tag::STRINGTYPE) || (next.tag == Tag::INTTYPE) || (next.tag == Tag::REALTYPE)) {
		status = SyntaxTree::constants_syntax(outfile);
	}
	//ids
	if (next.tag == Tag::ID) {
		status = SyntaxTree::ids_syntax(outfile);
	}
	return status;
}

bool SyntaxTree::binops_syntax(ofstream& outfile) {
	bool status = false;
	bool isReal = false;
	bool isInt = false;

	cur = SyntaxTree::getToken_syntax(isReal, isInt);

	if (next.tag == Tag::LPAR) {
		cur = SyntaxTree::getToken_syntax(isReal, isInt);
	}

	status = SyntaxTree::oper_syntax(outfile); //oper1

	//cout << cur.value;

	if (powop)
		cout << "s>f ";

	if (status) {
		if (cur.tag != Tag::STRINGTYPE)
			cur = SyntaxTree::getToken_syntax(isReal, isInt);

		if (next.tag == Tag::LPAR) {
			cur = SyntaxTree::getToken_syntax(isReal, isInt);
		}

		status = SyntaxTree::oper_syntax(outfile); //oper2
		
		if (!status)
			return status;

		if (powop)
			cout << "s>f ";

		if (cur.tag == Tag::STRINGTYPE)
			cout << " s";

		if (status) {
			if (unopReal) {
				cout << "f";
				newReal = true;
				unopReal = false;
			}
			if ((isReal && isInt)) {
				newReal = true;
				newMismatch = true;
			}
			else if ((isReal && !isInt)) {
				newReal = true;
				isInt = false;
				cout << "f";
			}
			else if (isInt && !isReal) {
				//newReal = false;
				newInt = true;
			}

			if (newInt && newReal && isInt) {
				newMismatch = true;
			}

			if (newMismatch) {
				cout << "s>f fswap f";
				newReal = true;
				newMismatch = false;
			}
			cur = SyntaxTree::getToken_syntax(isReal, isInt);
		}
		else
			return false;
	}
	return status;
}
bool SyntaxTree::unops_syntax(ofstream& outfile, bool& isReal, bool&isInt) {
	bool status = false;

	if (next.tag == Tag::MINUS || next.tag == Tag::NOT || next.tag == Tag::SIN || next.tag == Tag::COS || next.tag == Tag::TAN) {
		status = true;
		Token uo;
		if (status)
			uo = next;

		cur = SyntaxTree::getToken_syntax(isReal, isInt);
		if (next.tag == Tag::LPAR) {
			cur = SyntaxTree::getToken_syntax(isReal, isInt);
		}

		status = SyntaxTree::oper_syntax(outfile);
		Token val = next;
		cur = SyntaxTree::getToken_syntax(isReal, isInt);

		if (uo.tag == Tag::SIN || uo.tag == Tag::COS || uo.tag == Tag::TAN) {
			if (val.tag != Tag::REALTYPE) {
				cout << " s > f ";
				isInt = true;
			}
			else {
				isReal = true;
				unopReal = true;
			}
			//cout << " s>f ";
			cout << "f" << uo.lexeme << " ";
		}
		else if (uo.tag == Tag::NOT) {
			cout << "invert ";
		}
		else if(uo.tag == Tag::MINUS) {
			cout << "negate ";
		}
	}
	return status;
}
bool SyntaxTree::constants_syntax(ofstream& outfile) {
	bool status = false;
	//strings
	switch (next.tag) {
	case Tag::STRINGTYPE:
		status = SyntaxTree::strings_syntax(outfile);
		break;
	case Tag::INTTYPE:
			status = SyntaxTree::ints_syntax(outfile);
		break;
	case Tag::REALTYPE:
			status = SyntaxTree::floats_syntax(outfile);
		break;
	}
	return status;
}
bool SyntaxTree::strings_syntax(ofstream& outfile) {
	cur = SyntaxTree::getToken_syntax();
	bool status = false;
	if (cur.tag == Tag::STRINGTYPE || cur.tag == Tag::TRUE || cur.tag == Tag::FALSE) {
		SyntaxTree::printVal_syntax(cur, outfile);
		status = true;
	}
	return status;
}
bool SyntaxTree::ids_syntax(ofstream& outfile) {
	if (next.tag == Tag::ID) {
		variable = next;
		return true;
	}
	return false;
}
bool SyntaxTree::ints_syntax(ofstream& outfile) {
	if (next.tag == Tag::INTTYPE) {
		//cout << "here";
		//cout << declared_real << endl;
		if (declared_real) {
			//cout << "declared real\n";
			next.tag = Tag::REALTYPE;
			next.dec_value = (float)next.value;
			SyntaxTree::printVal_syntax(next, outfile);
		}
		else {
			SyntaxTree::printVal_syntax(next, outfile);
		}
		return true;
	}
	return false;
}
bool SyntaxTree::floats_syntax(ofstream& outfile) {
	if (next.tag == Tag::REALTYPE) {
		if (declared_int) {
			//cout << "declared int\n";
			next.tag = Tag::INTTYPE;
			next.value = (int)next.dec_value;
			SyntaxTree::printVal_syntax(next, outfile);
		}
		else {
			SyntaxTree::printVal_syntax(next, outfile);
		}
		return true;
	}
	return false;
}
bool SyntaxTree::stmts_syntax(ofstream& outfile) {
	bool status = false;
	while (!status) {
		if (next.tag == Tag::IF)
			status = ifstmts_syntax(outfile);
		if (next.tag == Tag::WHILE)
			status = whilestmts_syntax(outfile);
		if (next.tag == Tag::LET) {
			status = letstmts_syntax(outfile);
		}
		if (next.tag == Tag::STDOUT)
			status = printstmts_syntax(outfile);
		else
			break;
	}
	return status;
}
bool SyntaxTree::printstmts_syntax(ofstream& outfile) {
	Token printy;
	bool yesPrint = false;

	if (cur.tag == Tag::LPAR) {

		cur = SyntaxTree::getToken_syntax();
		if (cur.tag == Tag::STDOUT) {
			printy = cur;
			yesPrint = true;
			cur = SyntaxTree::getToken_syntax();

		}
		SyntaxTree::oper_syntax(outfile);
		SyntaxTree::printVal_syntax(cur, outfile);

		if (yesPrint)
			cout << " TYPE";

		if (cur.tag == Tag::RPAR) {
			return true;
		}
	}
	return false;
}
bool SyntaxTree::ifstmts_syntax(ofstream& outfile) {
	if (cur.tag == Tag::LPAR && next.tag == Tag::IF) {
		string curf = funct + to_string(fn);
		cout << " : " << curf << " ";
		fn++;

		//SyntaxTree::printVal_syntax(next, outfile);

		cur = SyntaxTree::getToken_syntax();
		if (next.tag == Tag::LPAR) {
			cur = SyntaxTree::getToken_syntax();
		}
		SyntaxTree::expr_syntax(outfile);
		cur = SyntaxTree::getToken_syntax();
		cur = SyntaxTree::getToken_syntax();

		cout << " if ";

		SyntaxTree::expr_syntax(outfile);
		cur = SyntaxTree::getToken_syntax();

		cout << " then ; "<< curf;

		if (next.tag == Tag::RPAR) {
			return true;
		}
		else {
			SyntaxTree::expr_syntax(outfile);
			if (next.tag == Tag::RPAR) {
				return true;
			}
		}
	}
	return false;
}
bool SyntaxTree::whilestmts_syntax(ofstream& outfile) {
	if (cur.tag == Tag::LPAR && next.tag == Tag::WHILE) {
		string curf = funct + to_string(fn);
		cout << " : " << curf << " begin ";
		fn++;

		//SyntaxTree::printVal_syntax(next, outfile);
		
		cur = SyntaxTree::getToken_syntax();

		if (next.tag == Tag::LPAR) {
			cur = SyntaxTree::getToken_syntax();
		}

		SyntaxTree::expr_syntax(outfile);
		cur = SyntaxTree::getToken_syntax();
		cur = SyntaxTree::getToken_syntax();

		cout << " while ";

		SyntaxTree::exprlist_syntax(outfile);

		if (next.tag == Tag::RPAR) {
			cout << " repeat ; " << curf;
			return true;
		}
	}
	return false;
}
bool SyntaxTree::exprlist_syntax(ofstream& outfile) {
	bool status = false;
	status = expr_syntax(outfile);
	if (!status)
		expr_syntax(outfile);

	return status;
}
bool SyntaxTree::letstmts_syntax(ofstream& outfile) {
	bool status;

	if (cur.tag == Tag::LPAR && next.tag == Tag::LET) {
		cur = SyntaxTree::getToken_syntax();

		if (next.tag == Tag::LPAR) {
			Token var = next;

			status = SyntaxTree::varlist_syntax(outfile);

			cout << "variable " << variable.lexeme << "\n";

			if (status) {
				cur = SyntaxTree::getToken_syntax();

				if (next.tag == Tag::RPAR) {
					//cur = Parser::getToken();
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
bool SyntaxTree::varlist_syntax(ofstream& outfile) {
	//cout << "in varlist";
	bool status = false;
	if (next.tag == Tag::LPAR) {
		cur = SyntaxTree::getToken_syntax();
		status = SyntaxTree::ids_syntax(outfile);
		cur = SyntaxTree::getToken_syntax();

		if (!status) {
			return false;
		}
		status = SyntaxTree::type_syntax(outfile);
		cur = SyntaxTree::getToken_syntax();

		if (next.tag == Tag::REALTYPE)
			cout << "f";




		if (next.tag == Tag::RPAR) {
			cur = SyntaxTree::getToken_syntax();
			if (next.tag == Tag::RPAR) {
				return true;
			}
			//if (next.tag == Tag::LPAR) {
				//cout << "got here somehow";
				//status = SyntaxTree::varlist_syntax(outfile);
			//}
			else {
				if (next.tag == Tag::RPAR) {
					return true;
				}
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}
bool SyntaxTree::type_syntax(ofstream& outfile) {
	//cout << next.tag;

	if (next.tag == Tag::REAL) {
		cout << "f";
		declared_real = true;
		declared_int = false;
	}
	else {
		declared_real = false;
		declared_int = true;
	}
	return true;
}
