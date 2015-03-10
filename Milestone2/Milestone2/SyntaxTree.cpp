#include "SyntaxTree.h"

std::map<std::string, int> varInts;
std::map<std::string, float> varFloats;
std::map <std::string, std::string> varStrings;
std::map <std::string, bool> varBools;

SyntaxTree::SyntaxTree()
{
	
}

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
	if (cur.tag > 264 && cur.tag < 278 || cur.tag > 289 && cur.tag < 292) {
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
	//cout << "[S]";
	bool status = false;
	if (next.tag == Tag::END) {
		return false;
	}
	switch (cur.tag) {
	case Tag::LPAR:
		//()S1
		if (next.tag == Tag::RPAR) {
			//cout << "S->()S1\n";

			status = SyntaxTree::S1_syntax(outfile);
			return status;
		}
		//(S)S1
		else {
			//cout << "S->(S)S1\n";
			if (next.tag == Tag::LPAR) {
				cur = SyntaxTree::getToken_syntax();
				status = SyntaxTree::S_syntax(outfile);
				status = SyntaxTree::S1_syntax(outfile);
			}
			else {
				//cout << "S->exprS1\n";
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
		//cout << "\nS->exprS1\n";
		status = SyntaxTree::expr_syntax(outfile);
		cur = SyntaxTree::getToken_syntax();
		status = SyntaxTree::S1_syntax(outfile);
		return true;
	}
	return status;
}
bool SyntaxTree::S1_syntax(ofstream& outfile) {
	bool status = false;
	//cout << "[S1]\n";

	if (next.tag == Tag::END) {
		//cout << "END";
		return true;
	}

	status = SyntaxTree::S_syntax(outfile);
	if (status)
		status = SyntaxTree::S1_syntax(outfile);

	return status;
}

bool SyntaxTree::expr_syntax(ofstream& outfile) {
	//cout << "[EXPR]\n";
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
	//cout << "[OPER]\n";
	bool status = false;

	//cout << "cur: " << cur.tag << " next: " << next.tag << "\n";

	if (cur.tag == Tag::LPAR) {
		if (next.tag == Tag::ASSIGN) {
			//cout << "[ASSIGN]\n";
			//SyntaxTree::printVal_syntax(next);

			cur = SyntaxTree::getToken_syntax();

			status = SyntaxTree::ids_syntax(outfile);
			//cout << "trying to store " << next.lexeme << endl;
			string curid = next.lexeme;

			cur = SyntaxTree::getToken_syntax();
			//cout << "trying to store " << next.value << endl;
			

			
			Token var = cur; //var is the id
			string excla = " !";
			if (next.tag == Tag::INTTYPE) {
				varInts[curid] = next.value;
			}
			if (next.tag == Tag::REALTYPE) {
				excla = " f!";
				varFloats[curid] = next.dec_value;

			}
			if (next.tag == Tag::STRINGTYPE) {
				varStrings[curid] = next.lexeme;
			}

			//cout << varInts[curid] << endl;
			//cout << varFloats[curid] << endl;
			//cout << varStrings[curid] << endl;

			//cout << "variable " << var.lexeme << "\n";

			if (next.tag == Tag::LPAR) {
				cur = SyntaxTree::getToken_syntax();
			}
			status = SyntaxTree::oper_syntax(outfile);


			cur = SyntaxTree::getToken_syntax();



			cout << " " << var.lexeme << excla << "\n";

			if (next.tag == Tag::RPAR) {
				cur = SyntaxTree::getToken_syntax();
				return status;
			}
		}
		//(binops oper oper)
		if ((next.tag >= 265 && next.tag <= 276) || (next.tag == Tag::AND) || next.tag == Tag::OR) {
			//cout << "(binops oper oper)\n";


			Token b = next;
			//cout << b.tag;

			//cout << "cur: " << cur.tag << " next: " << next.tag << "\n";
			if (b.tag == Tag::POW)
				powop = true;
			
				
			status = SyntaxTree::binops_syntax(outfile);
			//cout << cur.tag;
			//cout << next.tag;
			//if (cur.tag < 0) {
				//cout << "negate ";
				//return true;
			//}
			//cout << status;
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
			//int negate
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

	//cout << "\nisReal = " << isReal << " isInt = " << isInt << "\n";

	//cout << "[BINOPS]\n";

	cur = SyntaxTree::getToken_syntax(isReal, isInt);

	if (next.tag == Tag::LPAR) {
		cur = SyntaxTree::getToken_syntax(isReal, isInt);
	}


	status = SyntaxTree::oper_syntax(outfile); //oper1

	//cout << cur.value;

	if (powop)
		cout << "s>f ";

	//cout << "oper1good ";

	//cout << "\nisReal = " << isReal << " isInt = " << isInt << "\n";

	//cout << "status: " << status;

	if (status) {
		if (cur.tag != Tag::STRINGTYPE)
			cur = SyntaxTree::getToken_syntax(isReal, isInt);

		if (next.tag == Tag::LPAR) {
			cur = SyntaxTree::getToken_syntax(isReal, isInt);
		}

		status = SyntaxTree::oper_syntax(outfile); //oper2
		
		if (!status)
			//cout << "status: " << status;
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
	//cout << "[UNOPS]\n";
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
	//cout << "[CONSTANTS]\n";
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
		//cout << "printingstring ";
		SyntaxTree::printVal_syntax(cur, outfile);
		status = true;
	}

	return status;
}
bool SyntaxTree::ids_syntax(ofstream& outfile) {
	//cout << "\t\t\t[IDS]\n";
	if (next.tag == Tag::ID) {
		//SyntaxTree::printVal_syntax(next);
		//cout << next.lexeme << endl;
		variable = next;
		return true;
	}
	return false;
}
bool SyntaxTree::ints_syntax(ofstream& outfile) {
	//cout << "\t\t\t[INTS]\n";
	if (next.tag == Tag::INTTYPE) {
		SyntaxTree::printVal_syntax(next, outfile);
		return true;
	}
	return false;
}
bool SyntaxTree::floats_syntax(ofstream& outfile) {
	if (next.tag == Tag::REALTYPE) {
		//cout << "f";
		//initReal = true;
		SyntaxTree::printVal_syntax(next, outfile);
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
	//cout << "[PRINTSTMTS]\n";
	Token printy;
	bool yesPrint = false;

	if (cur.tag == Tag::LPAR) {

		cur = SyntaxTree::getToken_syntax();
		if (cur.tag == Tag::STDOUT) {
			printy = cur;
			yesPrint = true;
			//SyntaxTree::printVal_syntax(cur);
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
	//cout << "[IFSTMTS]\n";

	if (cur.tag == Tag::LPAR && next.tag == Tag::IF) {
		SyntaxTree::printVal_syntax(next, outfile);

		cur = SyntaxTree::getToken_syntax();
		if (next.tag == Tag::LPAR) {
			cur = SyntaxTree::getToken_syntax();
		}
		SyntaxTree::expr_syntax(outfile);
		cur = SyntaxTree::getToken_syntax();

		SyntaxTree::expr_syntax(outfile);
		cur = SyntaxTree::getToken_syntax();


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
	//cout << "\t\t\t[WHILESTMTS]\n";
	if (cur.tag == Tag::LPAR && next.tag == Tag::WHILE) {
		SyntaxTree::printVal_syntax(next, outfile);

		cur = SyntaxTree::getToken_syntax();

		if (next.tag == Tag::LPAR) {
			cur = SyntaxTree::getToken_syntax();
		}
		SyntaxTree::expr_syntax(outfile);

		SyntaxTree::exprlist_syntax(outfile);
		if (next.tag == Tag::RPAR) {
			return true;
		}
	}
	return false;
}
bool SyntaxTree::exprlist_syntax(ofstream& outfile) {
	//cout << "[EXPRLIST]\n";
	bool status = false;
	status = expr_syntax(outfile);
	if (!status)
		expr_syntax(outfile);
	return status;
}
bool SyntaxTree::letstmts_syntax(ofstream& outfile) {
	//cout << "[LETSTMTS]\n";
	bool status;

	if (cur.tag == Tag::LPAR && next.tag == Tag::LET) {
		//SyntaxTree::printVal_syntax(next, outfile);

		cur = SyntaxTree::getToken_syntax();

		if (next.tag == Tag::LPAR) {
			//cur = SyntaxTree::getToken_syntax();
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
	bool status = false;
	//cout << "[VARLIST]\n";

	if (next.tag == Tag::LPAR) {
		//cout << " in varlist ";

		cur = SyntaxTree::getToken_syntax();
		status = SyntaxTree::ids_syntax(outfile);

		cur = SyntaxTree::getToken_syntax();

		//cout << cur.lexeme;

		if (!status) {
			return false;
		}
		status = SyntaxTree::type_syntax(outfile);
		cur = SyntaxTree::getToken_syntax();

		//cout << next.tag << endl;

		if (next.tag == Tag::RPAR) {
			
			cur = SyntaxTree::getToken_syntax();
			//cout << next.tag;

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
	//cout << "\t[TYPE]\n";
	//SyntaxTree::printVal_syntax(next, outfile);
	//cout << next.tag;
	if (next.tag == Tag::REAL) {
		cout << "f";
	}
	return true;
}
