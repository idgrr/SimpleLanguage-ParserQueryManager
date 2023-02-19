#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "../QueryObject/QueryObject.h"
#include "../../PKB/PKBFacade.h"

using namespace std;

class QueryEvaluator {

    public:
        static list<string> evaluate(QueryObject queryObj, PKBFacade* pkb);

};
