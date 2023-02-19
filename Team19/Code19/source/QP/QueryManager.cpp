#include "QueryManager.h"
#include "QueryParser.h"
#include "QueryEvaluator/QueryEvaluator.h"
#include <list>
#include <string>

using namespace std;

list<string> QueryManager::getQueryResponse(string input, PKBFacade* pkb)
{
	optional<QueryObject> queryObj = QueryParser::parse(input);
	if (!queryObj) {
		return {"SyntaxError"};
	}
	list<string> queryResult = QueryEvaluator::evaluate(queryObj.value(), pkb);
	return queryResult;
}
