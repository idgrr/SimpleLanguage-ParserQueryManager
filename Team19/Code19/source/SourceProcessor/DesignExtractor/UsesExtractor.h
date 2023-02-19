#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "../AST.h"
#include "../../Entity/Entity.h"
#include "../../Relationship/Relationship.h"

using namespace SP;

class UsesExtractor {
private:
	vector<Uses> usesRelationships{};
public:
	UsesExtractor();

	vector<Uses> extractUses(const unique_ptr<ProgramNode> &AST);
};