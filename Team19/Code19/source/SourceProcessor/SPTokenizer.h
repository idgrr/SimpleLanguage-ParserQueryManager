#pragma once
#include <string>
#include <vector>

using namespace std;

/*
Holds a token string
*/
struct Token {
public:
	// Should token store the line number?
	string type;
	string value;

	Token(string t, string s);
	Token(string t, char c);
};

struct NameToken : Token {
	NameToken(string value);
};

struct IntegerToken : Token {
	IntegerToken(string value);
};

struct SymbolToken : Token {
	SymbolToken(string value);
};

/*
Splits SIMPLE code into a list of Token objects for further processing
*/
class TokenSplitter {
	// consts
	const vector<char> to_flush = { '+','-', '/','%','*',';', '{' ,'}','(',')' };
	const vector<char> whitespace = { ' ','\n','\t' };
	const vector<char> pairs = { '&','|' };
	const vector<char> pair_heads = { '!','<','>', '=' }; // second char will be a =

	string source_code;
	string buffer = "";
	vector<Token> tokens {};
	void buffer_flush();
	void buffer_append(char c);

public:
	TokenSplitter(string source_code) :
		source_code(source_code) {}

	vector<Token> tokenize();

private:
	bool contains(vector<char> vec, char target) {
		return find(vec.begin(), vec.end(), target) != vec.end();
	}

};