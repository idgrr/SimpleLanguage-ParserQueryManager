#include "ValidatorUtil.h"

bool ValidatorUtil::verifyName(std::string s)
{
	// if first char not alphabet, reject
	if (!isalpha(s[0])) {
		return false;
	}

	for (size_t i = 1; i < s.length(); i++) {
		if (!isalnum(s[i])) {
			return false;
		}
	}
	return true;
}
