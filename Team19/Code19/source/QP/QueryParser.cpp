#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "QueryParser.h"
#include <unordered_set>
#include "../ValidatorUtil.h"
#include "QueryObject/Declaration.h"
#include "QueryObject/DesignEntity.h"
#include <unordered_map>
#include <optional>

using namespace std;

string whitespace = " \f\n\r\t\v";
int maxInt = numeric_limits<int>::max();
ValidatorUtil validatorUtil;

const string ERROR_MSG = "invalid query";
const string SELECT_KEYWORD = "Select";
const unordered_set<string> validDecSynType = {
	"procedure", "stmt", "read", "print", "assign", "call", "while", "if", "variable", "constant"
};
const char DEC_DELIMITER = ';';
const char DEC_MULT_VAR_DELIMITER = ',';
std::list<Declaration> declarations;

/*
Parses query input into a QueryObject with:
declarations: List<Declarations> (synTye, synName)
suchThatClause: SuchThatClause (relationType, ent1, ent2)
patternClause: PatternClause (synName, lhs, rhs)
synToSelect: String
*/
optional<QueryObject> QueryParser::parse(string query)
{
	string errors;
	
	errors = basicQueryValidation(query);
	if (errors != "") {
		return nullopt;
	}

	// splitting and validating declaration and select clauses
	vector<string> clauses = splitSelectAndDeclarationClauses(query);
	errors = validateClauses(clauses);
	if (errors != "") {
		return nullopt;
	}

	// splitting and validating declarations individually
	for (size_t it = 0; it < clauses.size() - 1; it++) {
		optional<list<Declaration>> newDeclarations = splitDeclarationsClause(clauses[it]);
		if (newDeclarations) {
			declarations.splice(declarations.end(), newDeclarations.value());
		}
		else {
			return nullopt;
		}
	}
	/*for (list<Declaration>::iterator it = declarations.begin(); it != declarations.end(); it++) {
		errors = validateDeclaration(*it);
		if (errors != "") {
			return;
		}
	}*/
	/*for (int it = 0; it < clauses.size() - 1; it++) {
		errors = validateDeclaration(*it);
		if (errors != "") {
			return;
		}
	}*/

	// splitting and validating select statement
	string selectStmt = clauses[clauses.size() - 1];
	errors = validateSelectClause(selectStmt);
	if (errors != "") {
		return nullopt;
	}
	Declaration synToSelect = splitSelectClause(selectStmt);
	SuchThatClause mockSuchThat(SuchThatClause("", "", ""));
	PatternClause mockPattern(PatternClause(synToSelect, "", ""));

	return QueryObject(declarations, mockSuchThat, mockPattern, synToSelect);
	//return QueryObject("x");
}

vector<string> QueryParser::splitSelectAndDeclarationClauses(string query)
{
	vector<string> output;
	int startIt = 0;
	int endIt = query.find(DEC_DELIMITER);

	while (endIt != -1) {
		// while declarations exist before Select statement
		output.push_back(trimString(query.substr(startIt, endIt - startIt), whitespace));
		// since clause has been saved into output
		startIt = endIt + 1; 
		endIt = query.find(DEC_DELIMITER, startIt);
	}

	output.push_back(trimString(query.substr(startIt), whitespace));
	return output;
}

optional<list<Declaration>> QueryParser::splitDeclarationsClause(string declarationStr)
{
	list<Declaration> output;
	string synType = declarationStr.substr(0, declarationStr.find_first_of(whitespace));
	string varNames = declarationStr.substr(declarationStr.find_first_of(whitespace));
	DesignEntity* synEntType;

	if (synType == "stmt") {
		synEntType = new DE::Statement();
	}
	else if (synType == "procedure") {
		synEntType = new DE::Procedure();
	}
	else if (synType == "read") {
		synEntType = new DE::Read();
	}
	else if (synType == "print") {
		synEntType = new DE::Print();
	}
	else if (synType == "assign") {
		synEntType = new DE::Assign();
	}
	else if (synType == "call") {
		synEntType = new DE::Call();
	}
	else if (synType == "while") {
		synEntType = new DE::While();
	}
	else if (synType == "if") {
		synEntType = new DE::If();
	}
	else if (synType == "variable") {
		synEntType = new DE::Variable();
	}
	else if (synType == "constant") {
		synEntType = new DE::Constant();
	}
	else {
		// TODO: throw error on undiscovered DesignEntity being used
		synEntType = new DE::Statement();
	}

	int mult_var_first_it = varNames.find(DEC_MULT_VAR_DELIMITER);
	if (mult_var_first_it != -1) {
		// if multiple variables are named in the clause
		int startIt = 0;
		int endIt = mult_var_first_it;

		while (endIt != -1) {
			string newVarName = trimString(varNames.substr(startIt, endIt - startIt), whitespace);
			startIt = endIt + 1;
			endIt = varNames.find(DEC_MULT_VAR_DELIMITER, startIt);
			output.push_back(Declaration(synEntType, newVarName));
		}		
	}
	else {
		output.push_back(Declaration(synEntType, trimString(varNames, whitespace)));
	}
	return output;
}

Declaration QueryParser::splitSelectClause(string selectStr)
{
	int firstWhitespace = selectStr.find_first_of(whitespace);
	string varName = trimString(selectStr.substr(firstWhitespace), whitespace);

	//list<Declaration>::iterator declarationsInt = find(declarations.begin(), declarations.end(), varName);
	//return *declarationsInt;
	list<Declaration>::iterator it;
	for (it = declarations.begin(); it != declarations.end(); it++) {
		if (it->synName == varName) {
			return *it;
		}
	}
	return *declarations.end();
}

/*
Checks whether query input string follows criteria:
- has length > 0
- contains substring "Select"
- has declarations only before "Select" clause
Returns: errors, or empty string
*/
string QueryParser::basicQueryValidation(string query)
{
	if (query.length() <= 0) {
		return ERROR_MSG;
	}
	else if (query.find(SELECT_KEYWORD) <= 0) {
		// either declarations missing or keyword not found
		return ERROR_MSG;
	}
	return "";
}

/*
Checks whether declaration clauses and select line follow the criteria:
- "Select" clause appears only after all declaration clauses (last clause is Select)
- Each declaration clause consists of synType and synName
*/
string QueryParser::validateClauses(vector<string> clauses)
{
	int selectClauseInt = clauses.size() - 1;

	if (clauses[selectClauseInt].find("Select") == -1) {
		return ERROR_MSG;
	}

	if (clauses[selectClauseInt].find(" ") == -1) {
		// Select clause not of format "Select<whitespace>synName"
		return ERROR_MSG;
	}

	for (size_t it = 0; it < clauses.size() - 1; it++) {
		if (clauses[it].find(" ") == -1) {
			// declaration clause not of format "synType<whitespace>synName"
			return ERROR_MSG;
		}
	}
	return "";
}

/*
Checks whether a declaration follows the criteria:
- design-entity in declaration is valid and referenced correctly
- synonym follows name grammar rule
*/
//string QueryParser::validateDeclaration(Declaration declaration)
//{
//	if (validDecSynType.find(declaration.synType) == validDecSynType.end()) {
//		return ERROR_MSG;
//	}
//	if (!validatorUtil.verifyName(declaration.synName)) {
//		return ERROR_MSG;
//	}
//	return "";
//}

/*
Checks whether Select clause string follows criteria:
- synonym should follow name grammar rules
- synonym has been declared before
Returns: errors, or empty string
*/
string QueryParser::validateSelectClause(string selectStmt)
{
	int firstWhitespace = selectStmt.find_first_of(whitespace);
	string varName = trimString(selectStmt.substr(firstWhitespace), whitespace);
	if (!validatorUtil.verifyName(varName)) {
		return "varName invalid";
	}
	/*list<Declaration>::iterator declarationsInt = find(declarations.begin(), declarations.end(), varName);
	if (declarationsInt == declarations.end()) {
		return ERROR_MSG;
	}*/

	list<Declaration>::iterator it;
	bool doesDecExist = false;
	for (it = declarations.begin(); it != declarations.end(); it++) {
		if (it->synName == varName) {
			doesDecExist = true;
		}
	}
	if (doesDecExist) {
		return "";
	}
	else {
		return ERROR_MSG;
	}
}

string QueryParser::trimString(string str, string whitespaces)
{
	int startOfStr = str.find_first_not_of(whitespace);
	int endOfStr = str.find_last_not_of(whitespace);

	if ((startOfStr > endOfStr) || (startOfStr == string::npos)) {
		return "";
	}
	if (startOfStr > endOfStr) {
		return "";
	}

	int newStrLength = endOfStr - startOfStr + 1;
	return str.substr(startOfStr, newStrLength);
}

