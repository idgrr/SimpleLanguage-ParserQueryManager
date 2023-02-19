#include "PKBFacade.h"

PKBFacade::PKBFacade() {
	entityManager = new EntityManager;
	patternManager = new PatternManager;
}

// remove once SP is done
void PKBFacade::insertStatement(Ent::Statement statement) {}
void PKBFacade::insertVariable(Ent::Variable variable) {}
void PKBFacade::insertConstant(Ent::Constant constant) {}
void PKBFacade::insertProcedure(Ent::Procedure procedure) {}


void PKBFacade::insertEntity(Entity entity) {
	entityManager->insertEntity(entity);
}

//void PKBFacade::insertPattern(Pattern pattern) {
//
//}

std::unordered_set<std::string> PKBFacade::getAllVar()
{
	return entityManager->getAllVar();
}

std::unordered_set<std::string> PKBFacade::getAllConstant() {
	return entityManager->getAllConstant();
}

std::unordered_set<std::string> PKBFacade::getAllProc() {
	return entityManager->getAllProc();
}

std::unordered_set<std::string> PKBFacade::getAllStmtFromType(std::string stmtType) {
	return entityManager->getAllStmtFromType(stmtType);
}