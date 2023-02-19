#include "Declaration.h"

Declaration::Declaration(DesignEntity* type, std::string name) 
	: synType(type), synName(name) 
{}

bool Declaration::operator==(const Declaration& dec) const {
	return tie(synName) == tie(dec.synName);
}

bool Declaration::operator!=(const Declaration& dec) const {
	return tie(synName) != tie(dec.synName);
}
