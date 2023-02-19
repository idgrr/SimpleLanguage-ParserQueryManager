#include "EntityManager.h"

EntityManager::EntityManager() {
	entityStorage = new EntityStorage;
}

void EntityManager::insertEntity(Entity entity) {
	entityStorage->insertEntity(entity);
}

std::unordered_set<std::string> EntityManager::getAllVar()
{
	return entityStorage->getAllVar();
}

std::unordered_set<std::string> EntityManager::getAllConstant()
{
	return entityStorage->getAllConstant();
}

std::unordered_set<std::string> EntityManager::getAllProc() {
	return entityStorage->getAllProc();
}

std::unordered_set<std::string> EntityManager::getAllStmtFromType(std::string stmtType) {
	return entityStorage->getAllStmtFromType(stmtType);
}