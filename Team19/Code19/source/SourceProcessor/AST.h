#pragma once
#include <vector>
#include <string>
#include <variant>
#include <memory>
#include <stdexcept>
#include "SPTokenizer.h"

using namespace std;

namespace SP {
	struct Node {}; // base virtual node for all other nodes to inherit from

	struct ReadStatementNode;
	struct PrintStatementNode;
	struct WhileStatementNode;
	struct IfStatementNode;
	struct AssignStatementNode;
	struct CallStatementNode;
	using StatementNode = variant<
		unique_ptr<ReadStatementNode>, unique_ptr<PrintStatementNode>,
		unique_ptr<WhileStatementNode>, unique_ptr<IfStatementNode>,
		unique_ptr<AssignStatementNode>, unique_ptr<CallStatementNode>
	>;

	/*
		const_value: INTEGER
	*/
	struct ConstantNode : Node {
		string value;

		ConstantNode(string value);
	};

	/*
		var_name, proc_name: NAME
	*/
	struct VariableNode : Node {
		string name;

		VariableNode(string name);
	};

	/*
		Temp for MS1: storing it as a string
	*/
	struct ExpressionNode : Node {
		string expression;
		vector<unique_ptr<VariableNode>> variables;
		vector<unique_ptr<ConstantNode>> constants;

		ExpressionNode(string expression,
			vector<unique_ptr<VariableNode>> variables, vector<unique_ptr<ConstantNode>> constants);
	};

	/*
		Temp for MS1: storing it as a string
	*/
	struct RelationalFactorNode : Node {
		string relationalFactor;
		vector<unique_ptr<VariableNode>> variables;
		vector<unique_ptr<ConstantNode>> constants;

		RelationalFactorNode(string relationalFactor,
			vector<unique_ptr<VariableNode>> variables, vector<unique_ptr<ConstantNode>> constants);
	};

	/*
		cond_expr: rel_expr | '!' '(' cond_expr ')' |
           '(' cond_expr ')' '&&' '(' cond_expr ')' |
           '(' cond_expr ')' '||' '(' cond_expr ')'
	 */
	struct ConditionalExpressionNode : Node {
		string op;
		unique_ptr<ConditionalExpressionNode> condLHS = nullptr;
		unique_ptr<ConditionalExpressionNode> condRHS = nullptr;
		unique_ptr<RelationalFactorNode> relLHS = nullptr;
		unique_ptr<RelationalFactorNode> relRHS = nullptr;

		ConditionalExpressionNode(string op);
		ConditionalExpressionNode(string op, unique_ptr<ConditionalExpressionNode> condLHS);
		ConditionalExpressionNode(string op,
			unique_ptr<ConditionalExpressionNode> condLHS, unique_ptr<ConditionalExpressionNode> condRHS);
		ConditionalExpressionNode(string op,
			unique_ptr<RelationalFactorNode> relLHS, unique_ptr<RelationalFactorNode> relRHS);


		virtual void toString() {}
	};

	struct NotConditionalExpressionNode : ConditionalExpressionNode {
		unique_ptr<ConditionalExpressionNode> LHS;

		NotConditionalExpressionNode(unique_ptr<ConditionalExpressionNode> LHS);
	};

	struct AndConditionalExpressionNode : ConditionalExpressionNode {
		unique_ptr<ConditionalExpressionNode> LHS;
		unique_ptr<ConditionalExpressionNode> RHS;

		AndConditionalExpressionNode(
			unique_ptr<ConditionalExpressionNode> LHS, unique_ptr<ConditionalExpressionNode> RHS);
	};

	struct OrConditionalExpressionNode : ConditionalExpressionNode {
		unique_ptr<ConditionalExpressionNode> LHS;
		unique_ptr<ConditionalExpressionNode> RHS;

		OrConditionalExpressionNode(
			unique_ptr<ConditionalExpressionNode> LHS, unique_ptr<ConditionalExpressionNode> RHS);
	};

	/*
		rel_expr: rel_factor '>' rel_factor | rel_factor '>=' rel_factor |
          rel_factor '<' rel_factor | rel_factor '<=' rel_factor |
          rel_factor '==' rel_factor | rel_factor '!=' rel_factor
	*/
	struct RelationalExpressionNode : ConditionalExpressionNode {
		unique_ptr<RelationalFactorNode> LHS;
		unique_ptr<RelationalFactorNode> RHS;

		RelationalExpressionNode(
			unique_ptr<RelationalFactorNode> LHS, string op, unique_ptr<RelationalFactorNode> RHS);
	};

	/*
		read: 'read' var_name';'
	*/
	struct ReadStatementNode : Node {
		int statementNo;
		unique_ptr<VariableNode> name;

		ReadStatementNode(int statementNo, unique_ptr<VariableNode> name);
	};

	/*
		print: 'print' var_name';'
	*/
	struct PrintStatementNode : Node {
		int statementNo;
		unique_ptr<VariableNode> name;

		PrintStatementNode(int statementNo, unique_ptr<VariableNode> name);
	};

	/*
		call: 'call' proc_name';'
	*/
	struct CallStatementNode : Node {
		int statementNo;
		unique_ptr<VariableNode> procName;

		CallStatementNode(int statementNo, unique_ptr<VariableNode> procName);
	};

	/*
		while: 'while' '(' cond_expr ')' '{' stmtLst '}'
	*/
	struct WhileStatementNode : Node {
		int statementNo;
		unique_ptr<ConditionalExpressionNode> condition;
		vector<StatementNode> statements;

		WhileStatementNode(int statementNo,
			unique_ptr<ConditionalExpressionNode> condition, vector<StatementNode> statements);
	};

	/*
		if: 'if' '(' cond_expr ')' 'then' '{' stmtLst '}' 'else' '{' stmtLst '}'
	*/
	struct IfStatementNode : Node {
		int statementNo;
		unique_ptr<ConditionalExpressionNode> condition;
		vector<StatementNode> thenStatements;
		vector<StatementNode> elseStatements;

		IfStatementNode(int statementNo, unique_ptr<ConditionalExpressionNode> condition,
			vector<StatementNode> thenStatements, vector<StatementNode> elseStatements);
	};

	/*
		assign: var_name '=' expr ';'
	*/
	struct AssignStatementNode : Node {
		int statementNo;
		unique_ptr<VariableNode> LHS;
		unique_ptr<ExpressionNode> RHS;

		AssignStatementNode(int statementNo, unique_ptr<VariableNode> LHS, unique_ptr<ExpressionNode> RHS);
	};

	/*
		procedure: 'procedure' proc_name '{' stmtLst '}'
	*/
	struct ProcedureNode : Node {
		string name;
		vector<StatementNode> statements;

		ProcedureNode(string name, vector<StatementNode> statements);
	};

	/*
		program: procedure+
	*/
	struct ProgramNode : Node {
		vector<unique_ptr<ProcedureNode>> procedures;

		ProgramNode(vector<unique_ptr<ProcedureNode>> procedures);
	};









	// structures here not needed for MS1
	// struct VariableNode;
	// struct ConstantNode;
	// struct BnOpExpressionNode;
	// struct BnOpTermNode;
	// struct PlusExpressionNode;
	// struct MinusExpressionNode;
	// struct MultiplyTermNode;
	// struct DivideTermNode;
	// struct ModuloTermNode;
	// using ExpressionNode = variant<
	// 	unique_ptr<VariableNode>, unique_ptr<ConstantNode>,
	// 	unique_ptr<BnOpExpressionNode>, unique_ptr<BnOpTermNode>
	// >;

	// using FactorNode = ExpressionNode;
	// using RelationalFactorNode = ExpressionNode;

	// using TermNode = variant<
	// 	unique_ptr<VariableNode>, unique_ptr<ConstantNode>,
	// 	unique_ptr<BnOpTermNode>
	// >;

	// struct BnOpExpressionNode : Node {
	// 	ExpressionNode LHS;
	// 	string op;
	// 	TermNode RHS;

	// 	BnOpExpressionNode(ExpressionNode LHS, string op, TermNode RHS);
	// };

	// struct PlusExpressionNode : BnOpExpressionNode {
	// 	PlusExpressionNode(ExpressionNode LHS, TermNode RHS);
	// };

	// struct MinusExpressionNode : BnOpExpressionNode {
	// 	MinusExpressionNode(ExpressionNode LHS, TermNode RHS);
	// };

	// struct BnOpTermNode : Node {
	// 	TermNode LHS;
	// 	string op;
	// 	FactorNode RHS;

	// 	BnOpTermNode(TermNode LHS, string op, FactorNode RHS);
	// };

	// struct MultiplyTermNode : BnOpTermNode {
	// 	MultiplyTermNode(TermNode LHS, FactorNode RHS);
	// };

	// struct DivideTermNode : BnOpTermNode {
	// 	DivideTermNode(TermNode LHS, FactorNode RHS);
	// };

	// struct ModuloTermNode : BnOpTermNode {
	// 	ModuloTermNode(TermNode LHS, FactorNode RHS);
	// };
}
