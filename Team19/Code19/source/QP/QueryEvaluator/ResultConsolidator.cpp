#include "ResultConsolidator.h"


list<string> ResultConsolidator::consolidate(unordered_set<string> selectSynResult, 
    unordered_set<string> suchThatResult, unordered_set<string> patternResult)
{

    list<string> consolidatedResult;
    list<string>::iterator it = consolidatedResult.begin();

    unordered_set<string> result = intersect(intersect(selectSynResult, suchThatResult), patternResult);
    for (string const& k : result) {
        consolidatedResult.insert(it, k);
    }
    return consolidatedResult;
   
}

unordered_set<string> ResultConsolidator::intersect(unordered_set<string> list1, unordered_set<string> list2)
{
    unordered_set<string> s;
    unordered_set<string> intersection;

    for (string const& i : list1) {
        s.insert(i);
    }
    for (string const& j : list2) {
        if (s.find(j) != s.end()) {
            intersection.insert(j);
        };
    }
    return intersection;
}
