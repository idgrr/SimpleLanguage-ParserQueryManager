#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_set>

using namespace std;

class ResultConsolidator {

    public:
        static list<string> consolidate(unordered_set<string> selectSynResult, 
            unordered_set<string> suchThatResult, unordered_set<string> patternResult);
    
    private:
        // Disallow creating an instance of this object
        ResultConsolidator() {}

        static unordered_set<string> intersect(unordered_set<string> list1, unordered_set<string> list2);
};

