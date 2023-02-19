#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "../AST.h"
#include "../../Entity/Entity.h"
#include "../../Relationship/Relationship.h"

using namespace SP;

class FollowsExtractor {
private:
	vector<Follows> followsRelationships{};
public:
	FollowsExtractor();

	vector<Follows> extractFollows(const unique_ptr<ProgramNode> &AST);
};