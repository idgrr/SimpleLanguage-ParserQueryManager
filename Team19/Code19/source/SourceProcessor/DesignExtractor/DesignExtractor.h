#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "../AST.h"
#include "../../Entity/Entity.h"
#include "../../Relationship/Relationship.h"
#include "EntityExtractor.h"
#include "FollowsExtractor.h"
#include "ModifiesExtractor.h"
#include "ParentExtractor.h"
#include "UsesExtractor.h"

using namespace SP;

class DesignExtractor {
private:
	unique_ptr<ProgramNode> AST;

	vector<Entity> entities{};

	vector<Follows> followsRelationships{};
	vector<Parent> parentRelationships{};
	vector<Modifies> modifiesRelationships{};
	vector<Uses> usesRelationships{};
	vector<Relationship> relationships{};

public:
	DesignExtractor(unique_ptr<ProgramNode> AST);

	vector<Entity> getEntities();

	vector<Relationship> getRelationships();

	void extractAST();
};