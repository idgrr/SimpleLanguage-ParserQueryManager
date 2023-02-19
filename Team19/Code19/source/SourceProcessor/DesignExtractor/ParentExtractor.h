#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "../AST.h"
#include "../../Entity/Entity.h"
#include "../../Relationship/Relationship.h"

using namespace SP;

class ParentExtractor {
private:
	vector<Parent> parentRelationships{};
public:
	ParentExtractor();

	vector<Parent> extractParent(const unique_ptr<ProgramNode> &AST);
};