#include "stdafx.h"
#include "../source/QP/QueryParser.h"
#include "../source/QP/QueryObject/Declaration.h"
#include "../source/QP/QueryObject/QueryObject.h"
#include <codecvt>
#include <locale>
#include <string>

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {
			template<>
			static std::wstring ToString<Declaration>(const Declaration& dec) {
				std::string result = "Declaration with " + dec.synName;
				return std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(result);
			}

			template<>
			static std::wstring ToString<QueryObject>(const QueryObject& qo) {
				std::string result = "QueryObject with list<Decs> ";
				for (Declaration dec : qo.declarations) {
					result += dec.synName + " ";
				}
				result += "and selecting " + qo.synToSelect.synName;
				return std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(result);
			}
		}
	}
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;



namespace UnitTesting

{
	TEST_CLASS(TestQueryParser)
	{
	public:
		const string ERROR_MSG = "invalid query";

		TEST_METHOD(Test_Query_Basic_Validation) {
			Assert::AreEqual(string(""), QueryParser::basicQueryValidation("variable v; Select v"));
			Assert::AreEqual(string(""), QueryParser::basicQueryValidation("assign mockVar; Select mockVar"));
			Assert::AreEqual(ERROR_MSG, QueryParser::basicQueryValidation(""));
		}

		TEST_METHOD(Test_String_Trimming) {
			string whitespace = " \f\n\r\t\v";
			Assert::AreEqual(string("Select v"), QueryParser::trimString(" Select v ", whitespace));
			Assert::AreEqual(string("Select v"), QueryParser::trimString(" Select v", whitespace));
			Assert::AreEqual(string("Select v"), QueryParser::trimString("Select v ", whitespace));
		}

		TEST_METHOD(SplitSelectAndDeclarationClauses_SplitBasicVar_SplitClauses) {
			vector<string> expectedResult = { "variable v", "Select v" };
			vector<string> result = QueryParser::splitSelectAndDeclarationClauses("variable v; Select v");
			for (size_t it = 0; it < result.size() - 1; it++) {
				Assert::AreEqual(expectedResult[it], result[it]);
			}
		}

		TEST_METHOD(ValidateClauses_SplitBasicVar_EmptyErrorStr) {
			vector<string> clauses = { "variable v", "Select v" };
			string result = QueryParser::validateClauses(clauses);
			Assert::AreEqual(string(""), result);
		}

		TEST_METHOD(SplitDeclarationsClause_SplitBasicVar_SplitClauses) {
			string declarationStr = "variable v";
			list<Declaration> expectedResult = { Declaration(new DE::Variable(), "v")};
			optional<list<Declaration>> result = QueryParser::splitDeclarationsClause("variable v");
			auto begin_result_it = result.value().begin();
			auto begin_exp_res_it = expectedResult.begin();
			auto end_result_it = result.value().end();
			auto end_exp_res_it = expectedResult.end();
			Assert::AreEqual(*expectedResult.begin(), *result.value().begin());
			/*if (result) {
				while (begin_result_it != end_result_it) {
					Assert::AreEqual(*begin_result_it, *begin_exp_res_it);
					++begin_result_it;
					++begin_exp_res_it;
				}
			}
			else {
				Assert::Fail;
			}*/
		}

		TEST_METHOD(ValidateSelectClause_SplitBasicVar_EmptyErrorStr) {
			string selectStr = "Select v";
			string result = QueryParser::validateSelectClause(selectStr);
			Assert::AreEqual(string(""), result);
		}

		TEST_METHOD(Test_QueryParser_WrongVar_General_Parser) {
			Declaration mockDeclaration = Declaration(new DE::Variable(), "wrongVar");
			list<Declaration> mockDeclarations = { mockDeclaration };
			SuchThatClause mockSuchThat(SuchThatClause("", "", ""));
			PatternClause mockPattern(PatternClause(mockDeclaration, "", ""));
			QueryObject mockQueryObject(QueryObject(mockDeclarations, mockSuchThat, mockPattern, mockDeclaration));
			optional<QueryObject> consolidatedResult = QueryParser::parse("variable mockVar; Select mockVar");
			if (consolidatedResult) {
				Assert::AreNotEqual(mockQueryObject, consolidatedResult.value());
			} else {
				Assert::Fail();
			}
		}

		TEST_METHOD(Test_QueryParser_SyntaxError_Parse) {
			Declaration mockDeclaration = Declaration(new DE::Variable(), "wrongVar");
			list<Declaration> mockDeclarations = { mockDeclaration };
			SuchThatClause mockSuchThat(SuchThatClause("", "", ""));
			PatternClause mockPattern(PatternClause(mockDeclaration, "", ""));
			QueryObject mockQueryObject(QueryObject(mockDeclarations, mockSuchThat, mockPattern, mockDeclaration));
			optional<QueryObject> consolidatedResult = QueryParser::parse("Select mockVar");
			if (consolidatedResult) {
				Assert::AreNotEqual(mockQueryObject, consolidatedResult.value());
			}
			else {
				Assert::Fail();
			}
		}
		TEST_METHOD(Test_QueryParser_WrongVar_Clauses_Parser) {
			Declaration mockDeclaration = Declaration(new DE::Variable(), "wrongVar");
			list<Declaration> mockDeclarations = { mockDeclaration };
			SuchThatClause mockSuchThat(SuchThatClause("", "", ""));
			PatternClause mockPattern(PatternClause(mockDeclaration, "", ""));
			QueryObject mockQueryObject(QueryObject(mockDeclarations, mockSuchThat, mockPattern, mockDeclaration));
			optional<QueryObject> consolidatedResult = QueryParser::parse("variable mockVar; assign wrongVar; Select mockVar");
			/*if (consolidatedResult) {
				Assert::AreNotEqual(mockQueryObject, consolidatedResult.value());
			}
			else {
				Assert::Fail();
			}*/
			Assert::AreNotEqual(mockQueryObject, consolidatedResult.value());
		}

		TEST_METHOD(Test_QueryParser_BasicVar_Parse) {
			Declaration mockDeclaration = Declaration(new DE::Variable(), "v");
			list<Declaration> mockDeclarations = { mockDeclaration };
			SuchThatClause mockSuchThat(SuchThatClause("", "", ""));
			PatternClause mockPattern(PatternClause(mockDeclaration, "", ""));
			QueryObject mockQueryObject(QueryObject(mockDeclarations, mockSuchThat, mockPattern, mockDeclaration));
			QueryObject consolidatedResult = QueryParser::parse("variable v; Select v").value();
			Assert::AreEqual(mockQueryObject, consolidatedResult);
		}

		TEST_METHOD(Test_QueryParser_BasicAssign_Parse) {
			Declaration mockDeclaration = Declaration(new DE::Assign(), "a");
			list<Declaration> mockDeclarations = { mockDeclaration };
			SuchThatClause mockSuchThat(SuchThatClause("", "", ""));
			PatternClause mockPattern(PatternClause(mockDeclaration, "", ""));
			QueryObject mockQueryObject(QueryObject(mockDeclarations, mockSuchThat, mockPattern, mockDeclaration));
			QueryObject consolidatedResult = QueryParser::parse("assign a; Select a").value();
			Assert::AreEqual(mockQueryObject, consolidatedResult);
		}

		TEST_METHOD(Test_QueryParser_BasicRead_Parse) {
			Declaration mockDeclaration = Declaration(new DE::Read(), "r");
			list<Declaration> mockDeclarations = { mockDeclaration };
			SuchThatClause mockSuchThat(SuchThatClause("", "", ""));
			PatternClause mockPattern(PatternClause(mockDeclaration, "", ""));
			QueryObject mockQueryObject(QueryObject(mockDeclarations, mockSuchThat, mockPattern, mockDeclaration));
			QueryObject consolidatedResult = QueryParser::parse("read r; Select r").value();
			Assert::AreEqual(mockQueryObject, consolidatedResult);
		}

		TEST_METHOD(Test_QueryParser_BasicPrint_Parse) {
			Declaration mockDeclaration = Declaration(new DE::Print(), "p");
			list<Declaration> mockDeclarations = { mockDeclaration };
			SuchThatClause mockSuchThat(SuchThatClause("", "", ""));
			PatternClause mockPattern(PatternClause(mockDeclaration, "", ""));
			QueryObject mockQueryObject(QueryObject(mockDeclarations, mockSuchThat, mockPattern, mockDeclaration));
			QueryObject consolidatedResult = QueryParser::parse("print p; Select p").value();
			Assert::AreEqual(mockQueryObject, consolidatedResult);
		}

		TEST_METHOD(Test_Declarations_Comparison) {
			Declaration mockDec1 = Declaration(new DE::Variable(), "mockVar1");
			Declaration mockDec2 = Declaration(new DE::Variable(), "mockVar2");
			Declaration mockDec3 = Declaration(new DE::Assign(), "mockVar1");
			Assert::AreEqual(mockDec1, mockDec3);
		}


	};
}