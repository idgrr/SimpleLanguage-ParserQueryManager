#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "Declaration.h"
#include "PatternClause.h"
#include "SuchThatClause.h"

using namespace std;

class QueryObject {
public:
    std::list<Declaration> declarations;
    SuchThatClause suchThatClause;
    PatternClause patternClause;
    Declaration synToSelect;

    bool operator==(const QueryObject& qo) const;

    QueryObject(std::list<Declaration> declarations, SuchThatClause suchThatClause, 
        PatternClause patternClause, Declaration synToSelect);
};
