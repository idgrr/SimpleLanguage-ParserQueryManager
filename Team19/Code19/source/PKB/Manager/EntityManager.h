#pragma once

#include "../Storage/EntityStorage.h"
#include "../../Entity/Entity.h"

using namespace Ent;

class EntityManager {
public:
	EntityManager();

	void insertEntity(Entity entity);

	std::unordered_set<std::string> getAllVar();
	std::unordered_set<std::string> getAllConstant();
	std::unordered_set<std::string> getAllProc();
	std::unordered_set<std::string> getAllStmtFromType(std::string stmtType);

private:
	EntityStorage* entityStorage;


};