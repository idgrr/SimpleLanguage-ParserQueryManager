#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include "Parser.h"
#include "AST.h"

using namespace std;
using namespace SP;

bool Parser::isEndOfFile() {
    try {
        Token token = tokens.at(index);
        return false;
    }
    catch (out_of_range) {
        return true;
    }
}

bool Parser::check(string str) {
    return tokens.at(index).value == str;
}

void Parser::expect(string str) {
    if (tokens.at(index).value != str) throw invalid_argument("Expected " + str);
    index++;
}

Token Parser::advance() {
    Token token = tokens.at(index);
    index++;

    return token;
}

int Parser::findRelationalFactorEndIndex(int start) {
    int end = start;
    int openBracketCounter = 0;

    // To find the close bracket that indicate end of relational factor
    while(tokens.at(end).value != ")" || openBracketCounter != 0) {
        if (tokens.at(end).value == "(") openBracketCounter++;

        if (tokens.at(end).value == ")") openBracketCounter--;
        
        end++;
    }

    return end;
}

unique_ptr<ProgramNode> Parser::parseProgram() {
    vector<unique_ptr<ProcedureNode>> procedures {};

    while (true) {
        auto procedure = parseProcedure();

        if (!procedure) break;

        procedures.push_back(move(procedure));
    }

    return make_unique<ProgramNode>(move(procedures));
}

unique_ptr<ProcedureNode> Parser::parseProcedure() {
    if (isEndOfFile()) return nullptr;
    expect("procedure");

    string name = advance().value;

    expect("{");

    auto statements = parseStatementList();

    expect("}");

    return make_unique<ProcedureNode>(name, move(statements));
}

vector<StatementNode> Parser::parseStatementList() {
    vector<StatementNode> statements{};

    while (true) {
        auto statement = parseStatement();

        if (!statement) break;

        statements.push_back(move(*statement));
    }

    return statements;
}

optional<StatementNode> Parser::parseStatement() {
    if (check("}")) return nullopt; // End of a procedure

    auto readStatement = parseReadStatement();
    if (readStatement) return readStatement;

    auto printStatement = parsePrintStatement();
    if (printStatement) return printStatement;

    auto callStatement = parseCallStatement();
    if (callStatement) return callStatement;

    auto whileStatement = parseWhileStatement();
    if (whileStatement) return whileStatement;

    auto ifStatement = parseIfStatement();
    if (ifStatement) return ifStatement;

    auto assignStatement = parseAssignment();
    if (assignStatement) return assignStatement;

    return nullopt;
}

unique_ptr<ReadStatementNode> Parser::parseReadStatement() {
    if (!check("read")) return nullptr;
    expect("read");

    if (check("=")) {
        index--;
        return nullptr;
    }
    auto variable = parseVariableName();

    expect(";");

    statementNo++;

    return make_unique<ReadStatementNode>(statementNo, move(variable));
}

unique_ptr<PrintStatementNode> Parser::parsePrintStatement() {
    if (!check("print")) return nullptr;
    expect("print");

    if (check("=")) {
        index--;
        return nullptr;
    }

    auto variable = parseVariableName();

    expect(";");

    statementNo++;

    return make_unique<PrintStatementNode>(statementNo, move(variable));
}

unique_ptr<CallStatementNode> Parser::parseCallStatement() {
    if (!check("call")) return nullptr;
    expect("call");

    if (check("=")) {
        index--;
        return nullptr;
    }

    auto procedure = parseVariableName();

    expect(";");

    statementNo++;

    return make_unique<CallStatementNode>(statementNo, move(procedure));
}

unique_ptr<WhileStatementNode> Parser::parseWhileStatement() {
    if (!check("while")) return nullptr;
    expect("while");

    if (check("=")) {
        index--;
        return nullptr;
    }

    statementNo++;
    int whileStatementNo = this->statementNo;

    expect("(");

    auto conditionalExpression = parseConditionalExpression();

    expect(")");
    expect("{");

    auto statements = parseStatementList();

    expect("}");

    return make_unique<WhileStatementNode>(whileStatementNo,
        move(conditionalExpression), move(statements));
}

unique_ptr<IfStatementNode> Parser::parseIfStatement() {
    if (!check("if")) return nullptr;
    expect("if");

    if (check("=")) {
        index--;
        return nullptr;
    }

    statementNo++;
    int ifStatementNo = this->statementNo;

    expect("(");

    auto conditionalExpression = parseConditionalExpression();

    expect(")");
    expect("then");
    expect("{");

    auto thenStatements = parseStatementList();

    expect("}");
    expect("else");
    expect("{");

    auto elseStatements = parseStatementList();

    expect("}");

    return make_unique<IfStatementNode>(ifStatementNo,
        move(conditionalExpression), move(thenStatements), move(elseStatements));
}

unique_ptr<AssignStatementNode> Parser::parseAssignment() {
    auto name = parseVariableName();

    expect("=");

    auto expression = parseExpression();

    expect(";");

    statementNo++;

    return make_unique<AssignStatementNode>(statementNo,
        move(name), move(expression));
}

unique_ptr<ConditionalExpressionNode> Parser::parseConditionalExpression() {
    if (check("!")) { // NOT operator
        expect("!");
        expect("(");

        auto conditionalExpression = parseConditionalExpression();

        expect(")");

        return make_unique<NotConditionalExpressionNode>(move(conditionalExpression));
    }

    if (check("(")) { // AND or OR operator
        expect("(");

        auto LHS = parseConditionalExpression();

        expect(")");

        string op = advance().value;

        expect("(");

        auto RHS = parseConditionalExpression();

        expect(")");

        if (op == "&&") {
            return make_unique<AndConditionalExpressionNode>(move(LHS), move(RHS));
        } else {
            return make_unique<OrConditionalExpressionNode>(move(LHS), move(RHS));
        }
    }

    // RelationalExpression
    auto relationalExpression = parseRelationalExpression();
    return relationalExpression;

}

unique_ptr<RelationalExpressionNode> Parser::parseRelationalExpression() {
    unordered_set<string> comparators({">", ">=", "<", "<=", "==", "!="});

    int current = this->index;
    while(comparators.find(tokens.at(current).value) == comparators.end()) current++;

    string op = tokens.at(current).value;

    int startLHS = this->index;
    int endLHS = current;
    int startRHS = current + 1;
    int endRHS = findRelationalFactorEndIndex(startRHS);

    auto LHS = parseRelationalFactor(startLHS, endLHS);
    auto RHS = parseRelationalFactor(startRHS, endRHS);

    this->index = endRHS;
    return make_unique<RelationalExpressionNode>(move(LHS), op, move(RHS));
}

unique_ptr<RelationalFactorNode> Parser::parseRelationalFactor(int start, int end) {
    string relationalFactor = "";
    vector<unique_ptr<VariableNode>> variables{};
    vector<unique_ptr<ConstantNode>> constants{};

    while(start < end) {
        Token token = tokens.at(start);
        relationalFactor += token.value;
        if (token.type == "name") variables.push_back(make_unique<VariableNode>(token.value));
        if (token.type == "integer") constants.push_back(make_unique<ConstantNode>(token.value));
        start++;
    }

    return make_unique<RelationalFactorNode>(relationalFactor, move(variables), move(constants));
}

unique_ptr<ExpressionNode> Parser::parseExpression() {
    string expression = "";
    vector<unique_ptr<VariableNode>> variables{};
    vector<unique_ptr<ConstantNode>> constants{};

    while (tokens.at(index).value != ";") {
        Token token = advance();
        expression += token.value;
        if (token.type == "name") variables.push_back(make_unique<VariableNode>(token.value));
        if (token.type == "integer") constants.push_back(make_unique<ConstantNode>(token.value));
    }

    return make_unique<ExpressionNode>(expression, move(variables), move(constants));
}

unique_ptr<VariableNode> Parser::parseVariableName() {
    Token token = advance();

    if (token.type != "name") return nullptr;

    string name = token.value;

    return make_unique<VariableNode>(name);
}

unique_ptr<ConstantNode> Parser::parseConstantValue() {
    Token token = advance();

    if (token.type != "integer") return nullptr;

    string value = token.value;

    return make_unique<ConstantNode>(value);
}

Parser::Parser(vector<Token> tokens) : tokens(tokens) {}

unique_ptr<ProgramNode> Parser::parseTokens() {
    auto AST = parseProgram();

    return AST;
}
