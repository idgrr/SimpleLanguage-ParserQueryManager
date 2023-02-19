#include "AST.h"
#include <vector>
#include <string>
#include <variant>
#include <cctype>
#include <stdexcept>

using namespace SP;

ConstantNode::ConstantNode(string value) : value(value) {}

VariableNode::VariableNode(string name) : name(name) {}

ExpressionNode::ExpressionNode(string expression,
	vector<unique_ptr<VariableNode>> variables, vector<unique_ptr<ConstantNode>> constants) :
	expression(expression), variables(move(variables)), constants(move(constants)) {}

RelationalFactorNode::RelationalFactorNode(string relationalFactor,
	vector<unique_ptr<VariableNode>> variables, vector<unique_ptr<ConstantNode>> constants) :
	relationalFactor(relationalFactor), variables(move(variables)), constants(move(constants)) {}

ConditionalExpressionNode::ConditionalExpressionNode(string op) : op(op) {}

ConditionalExpressionNode::ConditionalExpressionNode(string op,
	unique_ptr<ConditionalExpressionNode> condLHS):
	op(op), condLHS(move(condLHS)) {}

ConditionalExpressionNode::ConditionalExpressionNode(string op,
	unique_ptr<ConditionalExpressionNode> condLHS, unique_ptr<ConditionalExpressionNode> condRHS):
	op(op), condLHS(move(condLHS)), condRHS(move(condRHS)) {}

ConditionalExpressionNode::ConditionalExpressionNode(string op,
	unique_ptr<RelationalFactorNode> relLHS, unique_ptr<RelationalFactorNode> relRHS):
	op(op), relLHS(move(relLHS)), relRHS(move(relRHS)) {}

NotConditionalExpressionNode::NotConditionalExpressionNode(unique_ptr<ConditionalExpressionNode> LHS) :
	ConditionalExpressionNode("!", move(LHS)) {}

AndConditionalExpressionNode::AndConditionalExpressionNode(
	unique_ptr<ConditionalExpressionNode> LHS, unique_ptr<ConditionalExpressionNode> RHS) :
	ConditionalExpressionNode("&&", move(LHS), move(RHS)) {}

OrConditionalExpressionNode::OrConditionalExpressionNode(
	unique_ptr<ConditionalExpressionNode> LHS, unique_ptr<ConditionalExpressionNode> RHS) :
	ConditionalExpressionNode("||", move(LHS), move(RHS)) {}

RelationalExpressionNode::RelationalExpressionNode(
	unique_ptr<RelationalFactorNode> LHS, string op, unique_ptr<RelationalFactorNode> RHS) :
	ConditionalExpressionNode(op, move(LHS), move(RHS)) {}

ReadStatementNode::ReadStatementNode(int statementNo, unique_ptr<VariableNode> name) :
	statementNo(statementNo), name(move(name)) {}

PrintStatementNode::PrintStatementNode(int statementNo, unique_ptr<VariableNode> name) :
	statementNo(statementNo), name(move(name)) {}

CallStatementNode::CallStatementNode(int statementNo, unique_ptr<VariableNode> procName) :
	statementNo(statementNo), procName(move(procName)) {}

WhileStatementNode::WhileStatementNode(
	int statementNo, unique_ptr<ConditionalExpressionNode> condition, vector<StatementNode> statements) :
	statementNo(statementNo), condition(move(condition)), statements(move(statements)) {}

IfStatementNode::IfStatementNode(int statementNo, unique_ptr<ConditionalExpressionNode> condition,
	vector<StatementNode> thenStatements, vector<StatementNode> elseStatements) :
	statementNo(statementNo), condition(move(condition)),
	thenStatements(move(thenStatements)), elseStatements(move(elseStatements)) {}

AssignStatementNode::AssignStatementNode(
	int statementNo, unique_ptr<VariableNode> LHS, unique_ptr<ExpressionNode> RHS) :
	statementNo(statementNo), LHS(move(LHS)), RHS(move(RHS)) {}

ProcedureNode::ProcedureNode(string name, vector<StatementNode> statements) :
	name(name), statements(move(statements)) {}

ProgramNode::ProgramNode(vector<unique_ptr<ProcedureNode>> procedures) : procedures(move(procedures)) {}






// structures here not needed for MS1
// BnOpExpressionNode::BnOpExpressionNode(ExpressionNode LHS, string op, TermNode RHS) :
// 	LHS(move(LHS)), op(op), RHS(move(RHS)) {}


// PlusExpressionNode::PlusExpressionNode(ExpressionNode LHS, TermNode RHS) :
// 	BnOpExpressionNode(move(LHS), "+", move(RHS)) {}

// MinusExpressionNode::MinusExpressionNode(ExpressionNode LHS, TermNode RHS) :
// 	BnOpExpressionNode(move(LHS), "-", move(RHS)) {}

// BnOpTermNode::BnOpTermNode(TermNode LHS, string op, FactorNode RHS) :
// 	LHS(move(LHS)), op(op), RHS(move(RHS)) {}

// MultiplyTermNode::MultiplyTermNode(TermNode LHS, FactorNode RHS) :
// 	BnOpTermNode(move(LHS), "*", move(RHS)) {}

// DivideTermNode::DivideTermNode(TermNode LHS, FactorNode RHS) :
// 	BnOpTermNode(move(LHS), "/", move(RHS)) {}

// ModuloTermNode::ModuloTermNode(TermNode LHS, FactorNode RHS) :
// 	BnOpTermNode(move(LHS), "%", move(RHS)) {}

