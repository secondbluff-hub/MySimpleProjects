#pragma once

#include <sstream>
#include <vector>
using namespace std;

enum class TokenType {
	DATE, // 2017-06-01
	EVENT, // 1st of June
	COLUMN, // date, event
	LOGICAL_OP, // Or, And
	COMPARE_OP, // <, <=, >, >=, ==, !=
	PAREN_LEFT, // (
	PAREN_RIGHT, // )
};

struct Token {
	const string value;
	const TokenType type;
};

vector<Token> Tokenize(istream& cl);