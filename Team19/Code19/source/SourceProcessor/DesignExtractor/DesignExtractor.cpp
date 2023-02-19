#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "DesignExtractor.h"

using namespace SP;

DesignExtractor::DesignExtractor(unique_ptr<ProgramNode> AST) : AST(move(AST)) {}

vector<Entity> DesignExtractor::getEntities() {
	return entities;
}

vector<Relationship> DesignExtractor::getRelationships() {
	return relationships;
}

void DesignExtractor::extractAST() {
	entities = EntityExtractor().extractEntities(AST);
	followsRelationships = FollowsExtractor().extractFollows(AST);
	parentRelationships = ParentExtractor().extractParent(AST);
	modifiesRelationships = ModifiesExtractor().extractModifies(AST);
	usesRelationships = UsesExtractor().extractUses(AST);
}