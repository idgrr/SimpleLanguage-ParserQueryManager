#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_set>

#include "../QueryObject/Declaration.h"
#include "../../PKB/PKBFacade.h"

using namespace std;

class SelectSynonymEvaluator {

    public:
        static unordered_set<string> evaluate(Declaration declaration, PKBFacade* pkb);
        
    private:
        // Disallow creating an instance of this object
        SelectSynonymEvaluator() {}
};

