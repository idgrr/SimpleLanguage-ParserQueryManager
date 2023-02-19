#include "EntityStorage.h"

#include <unordered_set>
#include <unordered_map>

EntityStorage::EntityStorage() {}

// insertion functions
void EntityStorage::insertEntity(Entity entity) {
	if (entity.getType() == "variable")
		EntityStorage::insertVariable(Variable(entity.getStmtNo(), entity.getName()));
	else if (entity.getType() == "constant")
		insertConstant(Constant(entity.getStmtNo(), entity.getName()));
	else if (entity.getType() == "procedure")
		insertProcedure(Procedure(entity.getName()));
	else
		insertStatement(Statement(entity.getStmtNo(), entity.getName()));
}

void EntityStorage::insertVariable(Ent::Variable variable) {
	EntityStorage::helperAddToBothMap(stmtNoToVariableMap, variableToStmtNoMap, variable);
}

void EntityStorage::insertConstant(Ent::Constant constant) {
	helperAddToBothMap(stmtNoToConstantMap, constantToStmtNoMap, constant);
}

void EntityStorage::insertProcedure(Ent::Procedure procedure) {

	std::string stmtNo = std::to_string(procedure.getStmtNo());
	std::string name = procedure.getName();

	helperAddToMap(procedureToStmtNoMap, name, stmtNo);
}

void EntityStorage::insertStatement(Ent::Statement statement) {
	std::string stmtNo = std::to_string(statement.getStmtNo());
	std::string stmtType = statement.getName();
	helperAddToMap(stmtTypeToStmtNoMap, stmtType, stmtNo);
}


// Get set of entity
std::unordered_set<std::string> EntityStorage::getAllVar(){
	return helperGetAllKeysMap(variableToStmtNoMap);
}

std::unordered_set<std::string> EntityStorage::getAllConstant() {
	return helperGetAllKeysMap(constantToStmtNoMap);
}


std::unordered_set<std::string> EntityStorage::getAllProc() {
	return helperGetAllKeysMap(procedureToStmtNoMap);
}


std::unordered_set<std::string> EntityStorage::getAllStmtFromType(std::string stmtType) {

	if (stmtTypeToStmtNoMap.find(stmtType) != stmtTypeToStmtNoMap.end()) {
		//if stmtNo exist
		return stmtTypeToStmtNoMap.at(stmtType);
	}

	return std::unordered_set<std::string>();
}



// Helper functions

void EntityStorage::helperAddToMap(std::unordered_map<std::string, std::unordered_set<std::string>>& mapAB, std::string key, std::string value) {

	if (mapAB.find(key) != mapAB.end()) {
		//if stmtNo exist
		mapAB.at(key).insert(value);
	}
	else {
		//if stmtNo does not exist
		std::unordered_set<std::string> newSet({ value });
		mapAB.emplace(key, newSet);
	}
}






void EntityStorage::helperAddToBothMap(std::unordered_map<std::string, std::unordered_set<std::string>>& mapAB,
	std::unordered_map<std::string, std::unordered_set<std::string>>& mapBA, Entity entity) {

	std::string stmtNo = std::to_string(entity.getStmtNo());
	std::string name = entity.getName();

	helperAddToMap(mapAB, stmtNo, name);
	helperAddToMap(mapBA, name, stmtNo);

}

std::unordered_set<std::string> EntityStorage::helperGetAllKeysMap(std::unordered_map<std::string, std::unordered_set<std::string>>& mapper) {

	std::unordered_set<std::string> varStrSet;

	for (auto k : mapper) {
		varStrSet.insert(k.first);
	}

	return varStrSet;

}