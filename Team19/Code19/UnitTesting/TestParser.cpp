#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include "../source/SourceProcessor/SPTokenizer.h"
#include "../source/SourceProcessor/AST.h"
#include "../source/SourceProcessor/Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting {
	TEST_CLASS(TestParser) {
	public:
		//TEST_METHOD(Test_Parse_Variable_Name) {
		//	NameToken token = NameToken{ "" };
		//	// Not sure how to test the parser... all methods are private
		//	Assert::AreEqual(
		//		size_t(2),
		//		TokenSplitter("abc def").tokenize().size()
		//	);
		//}
	};
}