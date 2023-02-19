#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class SuchThatClause {
    public:
        std::string relationshipType;
        std::string entity1;
        std::string entity2;

        SuchThatClause(std::string relationshipType, std::string entity1, std::string entity2);
};
