#pragma once

#include "./Manager/EntityManager.h"
#include "./Manager/RelationshipManager.h"
#include "./Manager/PatternManager.h"

#include <stdio.h>
#include "../../source/Entity/Entity.h"

#include <vector>
#include <unordered_set>

using namespace Ent;

class PKBFacade {
public:
	PKBFacade();

	void insertEntity(Entity entity);

	//to delete once SP settles their part
	void insertVariable(Ent::Variable variable);
	void insertStatement(Ent::Statement statement);
	void insertProcedure(Ent::Procedure procedure);
	void insertConstant(Ent::Constant constant);

	// Returns a set of enities
	std::unordered_set<std::string> getAllVar();
	std::unordered_set<std::string> getAllConstant();
	std::unordered_set<std::string> getAllProc();
	std::unordered_set<std::string> getAllStmtFromType(std::string stmtType);


private:
	EntityManager* entityManager;
	RelationshipManager* relationshipManager;
	PatternManager* patternManager;
};