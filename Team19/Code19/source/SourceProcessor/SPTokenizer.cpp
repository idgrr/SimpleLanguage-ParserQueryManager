#include "SPTokenizer.h"
#include <iostream>
#include <algorithm>

Token::Token(string t, string s) : type(t), value(s) {}

Token::Token(string t, char c) : type(t), value(string(1, c)) {}

NameToken::NameToken(string value) : Token("name", value) {}

IntegerToken::IntegerToken(string value) : Token("integer", value) {}

SymbolToken::SymbolToken(string value) : Token("symbol", value) {}

void TokenSplitter::buffer_flush() {
	if (buffer.empty()) return;

	if (isalnum(buffer.at(0)) == 0) { // Symbol
		tokens.push_back(SymbolToken { buffer });
	} else if (isdigit(buffer.at(0)) == 0) { // Name
		tokens.push_back(NameToken { buffer });
	} else { // Integer
		tokens.push_back(IntegerToken { buffer });
	}

	buffer = "";
};
void TokenSplitter::buffer_append(char c) {
	buffer.append(std::string(1, c));
};



std::vector<Token> TokenSplitter::tokenize() {
	if (tokens.size() > 0) {return tokens;}

	for (auto it = source_code.begin(); it != source_code.end(); ++it)
	{
		if (contains(to_flush,*it) ) {
			// if single special character, flush buffer and self
			buffer_flush();
			buffer_append(*it);
			buffer_flush();
			continue;
		}
		if (contains(whitespace, *it)) {
			//buffer only, ignore whitespace character
			buffer_flush();
			continue;
		}
		if (contains(pairs, *it)) {
			// 2 character combinations
			buffer_flush();
			buffer_append(*it);
			if (++it != source_code.end() && buffer.at(0)==*it) {
				// is dupe
				buffer_append(*it);
			} else { // not dupe
				it--; // reset for next round
			};
			buffer_flush();
			continue;
		}
		if (contains(pair_heads, *it)) {
			//2 character combinations
			buffer_flush();
			buffer_append(*it);
			if (++it != source_code.end() && *it == '=') {
				buffer_append(*it);
			} else { // not =
				it--; // reset for next round
			};
			buffer_flush();
			continue;
		}
		// add to buffer if not special character
		buffer_append(*it);
	}
	buffer_flush();
	return tokens;
};
