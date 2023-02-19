#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "../AST.h"
#include "../../Entity/Entity.h"
#include "../../Relationship/Relationship.h"

using namespace SP;

class ModifiesExtractor {
private:
	vector<Modifies> modifiesRelationships{};
public:
	ModifiesExtractor();

	vector<Modifies> extractModifies(const unique_ptr<ProgramNode> &AST);
};