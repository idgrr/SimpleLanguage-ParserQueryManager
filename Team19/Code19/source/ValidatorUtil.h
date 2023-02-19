#pragma once

#include <string>

class ValidatorUtil {
public:
	/*
	verifyName checks that a given string is a valid name according to grammar rules, 
	of the form LETTER(LETTER|DIGIT)
	*/
	bool verifyName(std::string s);
};
