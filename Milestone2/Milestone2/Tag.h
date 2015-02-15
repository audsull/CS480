#pragma once
#include "Lexer.h"
class Tag
{
public:
	Tag();
	~Tag();
	static const int BOOL = 256, TRUE = 257, FALSE = 258, AND = 259, OR = 260, NOT = 261,
		INT = 262, REAL = 263, STRING = 264,
		PLUS = 265, MINUS = 266, MULT = 267, DIV = 268, MOD = 269, POW = 270,
		EQUAL = 271, LT = 272, GT = 273, LE = 274, GE = 275, NE = 276, ASSIGN = 277,
		IF = 278, WHILE = 279, LET = 280, STDOUT = 281,
		SIN = 282, COS = 283, TAN = 284, ID = 286, INTTYPE = 287, REALTYPE = 288, STRINGTYPE = 289,
		LPAR = 290, RPAR = 291, END = 299;
};
