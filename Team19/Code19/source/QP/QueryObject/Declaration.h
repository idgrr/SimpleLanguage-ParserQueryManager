#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "DesignEntity.h"

using namespace std;

class Declaration {
    public:

        DesignEntity* synType;
        std::string synName;

        bool operator==(const Declaration& dec) const;
        bool operator!=(const Declaration& dec) const;

        Declaration(DesignEntity* type, std::string name);
};
