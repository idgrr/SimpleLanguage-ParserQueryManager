#pragma once

#include "../../Entity/Entity.h"

#include <unordered_map>
#include <unordered_set>

using namespace Ent;

class EntityStorage {
public:
	EntityStorage();

	void insertEntity(Entity entity);

	std::unordered_set<std::string> getAllVar();
	std::unordered_set<std::string> getAllConstant();
	std::unordered_set<std::string> getAllProc();
	std::unordered_set<std::string> getAllStmtFromType(std::string stmtType);

	void insertVariable(Ent::Variable variable);
	void insertStatement(Ent::Statement statement);
	void insertConstant(Ent::Constant constant);
	void insertProcedure(Ent::Procedure procedure);


private:

	// helper functions
	void helperAddToMap(std::unordered_map<std::string, std::unordered_set<std::string>>& mapAB, std::string key, std::string value);

	void helperAddToBothMap(std::unordered_map<std::string, std::unordered_set<std::string>>& mapAB,
		std::unordered_map<std::string, std::unordered_set<std::string>>& mapBA, Entity);

	std::unordered_set<std::string> helperGetAllKeysMap(std::unordered_map<std::string, std::unordered_set<std::string>>& mapper);



	std::unordered_map<std::string, std::unordered_set<std::string>> stmtNoToVariableMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> variableToStmtNoMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> stmtNoToConstantMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> constantToStmtNoMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> procedureToStmtNoMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> stmtTypeToStmtNoMap;
};