#include "stdafx.h"
#include "../source/QP/QueryManager.h"
#include "../source/PKB/PKBFacade.h"
#include <codecvt>
#include <locale>
#include <string>

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {
			template<>
			static std::wstring ToString<list<string>>(const list<string>& strList) {
				std::string result = "list<string> with strings: ";
				for (string str: strList) {
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
	TEST_CLASS(TestQueryManager)
	{
	public:
		//TODO: FIX BUG HERE
		/*const string ERROR_MSG = "invalid query";
		QueryManager queryManager = QueryManager();

		TEST_METHOD(Test_QueryManager_BasicVar_Parse) {
			list<string> receivedResult = queryManager.getQueryResponse("variable v; Select v");
			Assert::AreEqual({ "v" }, receivedResult);
		}*/
	};
}