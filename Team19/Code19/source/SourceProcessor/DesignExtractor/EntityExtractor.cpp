#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "EntityExtractor.h"

//using namespace std;
using namespace SP;

void EntityExtractor::extractProcedureEntity(const unique_ptr<ProcedureNode> &procedure) {
	Ent::Procedure entity{ 0, procedure->name }; // procedure has no statement number
	entities.push_back(entity);

	extractStatementListEntity(procedure->statements);
}

void EntityExtractor::extractStatementListEntity(const vector<StatementNode> &statements) {
	for (const auto& statement: statements) {
		visit([this](auto& stmt) {
			extractStatementEntity(stmt);
			}, statement);
	}
}

void EntityExtractor::extractStatementEntity(const unique_ptr<ReadStatementNode> &read) {
	Ent::Statement entity{ read->statementNo, "read" };
	entities.push_back(entity);

	extractVariableEntity(read->name);
}

void EntityExtractor::extractStatementEntity(const unique_ptr<PrintStatementNode> &print) {
	Ent::Statement entity{ print->statementNo, "print" };
	entities.push_back(entity);

	extractVariableEntity(print->name);
}

void EntityExtractor::extractStatementEntity(const unique_ptr<AssignStatementNode> &assign) {
	Ent::Statement entity{ assign->statementNo, "assign" };
	entities.push_back(entity);

	extractVariableEntity(assign->LHS);

	extractExpressionEntity(assign->RHS);
}

void EntityExtractor::extractStatementEntity(const unique_ptr<WhileStatementNode> &whiles) {
	Ent::Statement entity { whiles->statementNo, "while" };
	entities.push_back(entity);

	extractConditionEntity(whiles->condition);

	extractStatementListEntity(whiles->statements);
}

void EntityExtractor::extractStatementEntity(const unique_ptr<IfStatementNode> &ifs) {
	Ent::Statement entity { ifs->statementNo, "if" };
	entities.push_back(entity);

	extractConditionEntity(ifs->condition);

	extractStatementListEntity(ifs->thenStatements);
	extractStatementListEntity(ifs->elseStatements);
}

void EntityExtractor::extractStatementEntity(const unique_ptr<CallStatementNode> &call) {
	Ent::Statement entity{ call->statementNo, "call" };
	entities.push_back(entity);
}

void EntityExtractor::extractConditionEntity(const unique_ptr<ConditionalExpressionNode> &condition) {
	if (condition->op == "!") { // NOT operator
		extractConditionEntity(condition->condLHS);
	} else if (condition->op == "&&" || condition->op == "||") { // AND or OR operator
		extractConditionEntity(condition->condLHS);
		extractConditionEntity(condition->condRHS);
	} else { // Relational Expression
		extractRelationalFactorEntity(condition->relLHS);
		extractRelationalFactorEntity(condition->relRHS);
	}
}

void EntityExtractor::extractRelationalFactorEntity(const unique_ptr<RelationalFactorNode> &factor) {
	for (const auto& variable : factor->variables) {
		extractVariableEntity(variable);
	}

	for (const auto& constant : factor->constants) {
		extractConstantEntity(constant);
	}
}

void EntityExtractor::extractExpressionEntity(const unique_ptr<ExpressionNode> &expression) {
	for (const auto& variable : expression->variables) {
		extractVariableEntity(variable);
	}

	for (const auto& constant : expression->constants) {
		extractConstantEntity(constant);
	}
}

void EntityExtractor::extractVariableEntity(const unique_ptr<VariableNode> &variable) {
	Ent::Variable entity{ 0, variable->name }; // no need store statement number
	entities.push_back(entity);
}

void EntityExtractor::extractConstantEntity(const unique_ptr<ConstantNode> &constant) {
	Ent::Constant entity{ 0, constant->value }; // no need store statement number
	entities.push_back(entity);
}

EntityExtractor::EntityExtractor() {}

vector<Entity> EntityExtractor::extractEntities(const unique_ptr<ProgramNode> &AST) {
	for (const auto& procedure : AST->procedures) {
		extractProcedureEntity(procedure);
	}

	return entities;
}