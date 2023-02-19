#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "Declaration.h"

using namespace std;

class PatternClause {
    public:

        Declaration synonym;
        std::string arg1;
        std::string arg2;

        PatternClause(Declaration syn, std::string arg1, std::string arg2);
};
