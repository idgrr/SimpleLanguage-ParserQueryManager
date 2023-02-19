#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "../AST.h"
#include "../../Entity/Entity.h"

using namespace SP;

class EntityExtractor {
private:
	vector<Entity> entities{};

	void extractProcedureEntity(const unique_ptr<ProcedureNode> &procedure);

	void extractStatementListEntity(const vector<StatementNode> &statements);

	void extractStatementEntity(const unique_ptr<ReadStatementNode> &read);

	void extractStatementEntity(const unique_ptr<PrintStatementNode> &print);

	void extractStatementEntity(const unique_ptr<AssignStatementNode> &assign);

	void extractStatementEntity(const unique_ptr<WhileStatementNode> &whiles);

	void extractStatementEntity(const unique_ptr<IfStatementNode> &ifs);

	void extractStatementEntity(const unique_ptr<CallStatementNode> &call);

	void extractConditionEntity(const unique_ptr<ConditionalExpressionNode> &condition);

	void extractRelationalFactorEntity(const unique_ptr<RelationalFactorNode> &factor);

	void extractExpressionEntity(const unique_ptr<ExpressionNode> &expression);

	void extractVariableEntity(const unique_ptr<VariableNode> &variable);

	void extractConstantEntity(const unique_ptr<ConstantNode> &constant);

public:
	EntityExtractor();

	vector<Entity> extractEntities(const unique_ptr<ProgramNode> &AST);
};