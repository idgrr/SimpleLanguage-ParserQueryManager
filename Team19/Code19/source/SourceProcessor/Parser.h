#pragma once
#include <optional>
#include "AST.h"
#include "SPTokenizer.h"

using namespace std;

using namespace SP;

class Parser {
private:
	vector<Token> tokens;
	int index = 0;
	int statementNo = 0;

	bool isEndOfFile();

	/**
	 * @brief Checks if the current token has value str.
	 * 
	 * @param str the string to check
	 * @return true if the current token has value str, and false otherwise.
	 */
	bool check(string str);

	/**
	 * @brief Expect token at current index to have value str.
	 * 
	 * Increments index if true, and throws exception otherwise.
	 */
	void expect(string str);

	/**
	 * @brief Get the token at current index and increment the index.
	 * 
	 * @return Token at current index.
	 */
	Token advance();

	int findRelationalFactorEndIndex(int start);

	unique_ptr<ProgramNode> parseProgram();

	unique_ptr<ProcedureNode> parseProcedure();

	vector<StatementNode> parseStatementList();

	optional<StatementNode> parseStatement();

	unique_ptr<ReadStatementNode> parseReadStatement();

	unique_ptr<PrintStatementNode> parsePrintStatement();

	unique_ptr<CallStatementNode> parseCallStatement();

	unique_ptr<WhileStatementNode> parseWhileStatement();

	unique_ptr<IfStatementNode> parseIfStatement();

	unique_ptr<AssignStatementNode> parseAssignment();

	unique_ptr<ConditionalExpressionNode> parseConditionalExpression();

	unique_ptr<RelationalExpressionNode> parseRelationalExpression();

	unique_ptr<RelationalFactorNode> parseRelationalFactor(int start, int end);

	unique_ptr<ExpressionNode> parseExpression();

	// unique_ptr<TermNode> parseTerm();

	// unique_ptr<FactorNode> parseFactor();

	unique_ptr<VariableNode> parseVariableName();

	unique_ptr<ConstantNode> parseConstantValue();

public:
	Parser(vector<Token> tokens);

	unique_ptr<ProgramNode> parseTokens();
};
