#include "QueryEvaluator.h"
#include "SelectSynonymEvaluator.h"
#include "ResultConsolidator.h"


list<string> QueryEvaluator::evaluate(QueryObject queryObj, PKBFacade* pkb)
{
    Declaration synonymToSelect = queryObj.synToSelect;
    SuchThatClause suchThatClause = queryObj.suchThatClause;
    PatternClause patternClause = queryObj.patternClause;

    unordered_set<string> selectSynResult = SelectSynonymEvaluator::evaluate(synonymToSelect, pkb);
    list<string> consolidatedResult = ResultConsolidator::consolidate(selectSynResult, selectSynResult, selectSynResult);

    return consolidatedResult;
}
