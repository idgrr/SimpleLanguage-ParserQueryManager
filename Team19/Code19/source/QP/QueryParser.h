#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "QueryObject/QueryObject.h"
#include "QueryObject/Declaration.h"
#include "QueryObject/PatternClause.h"
#include "QueryObject/SuchThatClause.h"
#include <optional>

using namespace std;

class QueryParser {
	string query;

public:
	QueryParser(string query) :
		query(query) {}

	static optional<QueryObject> parse(string query);

//private:
	static vector<string> splitSelectAndDeclarationClauses(string query);
	static optional<list<Declaration>> splitDeclarationsClause(string declarationStr);
	static Declaration splitSelectClause(string selectStr);
	static string basicQueryValidation(string query);
	static string validateClauses(vector<string> clauses);
	static string validateDeclaration(Declaration declaration);
	static string validateSelectClause(string selectStmt);
	static string trimString(string str, string whitespaces);
};