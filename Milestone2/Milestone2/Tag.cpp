#include "Tag.h"



Tag::Tag()
{
	static int BOOL = 256;
	static int NE = 276;
	/*TRUE = 257, FALSE = 258, AND = 259, OR = 260, NOT = 261,
		INT = 262, REAL = 263, STRING = 264, 
		PLUS = 265, MINUS = 266, MULT = 267, DIV = 268, MOD = 269, POW = 270, 
		EQUAL = 271, LT = 272, GT = 273, LE = 274, GE = 275, NE = 276,
		STDOUT = 277, IF = 278, WHILE = 279, LET = 280, ASSIGN = 281,
		SIN = 282, COS = 283, TAN = 284;*/
}


Tag::~Tag()
{
}
