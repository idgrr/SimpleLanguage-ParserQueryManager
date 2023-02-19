#include "SelectSynonymEvaluator.h"
#include "../QueryObject/DesignEntity.h"

unordered_set<string> SelectSynonymEvaluator::evaluate(Declaration declaration, PKBFacade* pkb)
{
    unordered_set<string> result = {};
    result = declaration.synType->getSynonymFromPKB(pkb);
    
    return result;
}
