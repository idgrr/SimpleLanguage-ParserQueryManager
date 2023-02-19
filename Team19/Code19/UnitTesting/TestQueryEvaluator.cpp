#include "stdafx.h"
#include "../source/QP/QueryEvaluator/QueryEvaluator.h"
#include "../source/QP/QueryObject/Declaration.h"
#include "../source/QP/QueryObject/QueryObject.h"
#include <codecvt>
#include <locale>
#include <string>


namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {
			template<>
			static std::wstring ToString<list<string>>(const list<string>& strList) {
				std::string result = "list<string> with strings: ";
				for (string str : strList) {
					result += str + " ";
				}
				return std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(result);
			}
		}
	}
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting

{
	TEST_CLASS(TestQueryEvaluator)
	{
	public:
		//TODO: FIX BUG HERE
		//const string ERROR_MSG = "invalid query";
		//QueryEvaluator queryEvaluator = QueryEvaluator();

		//TEST_METHOD(Test_QueryEvaluator_BasicVar_Parse) {
		//	Declaration mockDeclaration = Declaration(DesignEntity::VARIABLE, "v");
		//	list<Declaration> mockDeclarations = { mockDeclaration };
		//	SuchThatClause mockSuchThat(SuchThatClause("", "", ""));
		//	PatternClause mockPattern(PatternClause(mockDeclaration, "", ""));
		//	QueryObject mockQueryObject(QueryObject(mockDeclarations, mockSuchThat, mockPattern, mockDeclaration));

		//	list<string> receivedResult = queryEvaluator.evaluate(mockQueryObject);
		//	Assert::AreEqual({ "v" }, receivedResult);
		//}
	};
}