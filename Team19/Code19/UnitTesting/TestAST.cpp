#include "stdafx.h"
#include "CppUnitTest.h"
//#include "TNode.h"
#include <stdexcept>
#include "../source/SourceProcessor/AST.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting {
	TEST_CLASS(TestAST) {
public:
	TEST_METHOD(Test_Template) {}

	/*TEST_METHOD(Test_ReadStatement) {

		std::vector<Token> validTokens {
			NameToken { "read" },
			NameToken { "var" },
			SymbolToken { ";" }
		};
		ReadStatementNode::make(validTokens);



		Assert::ExpectException<std::invalid_argument>(
			[]() {
				std::vector<Token> shortTokens {
					NameToken { "read" },
					NameToken { "var" },
					};
				ReadStatementNode::make(shortTokens); 
			}
		);
	}

	// TEST_METHOD(Test_IntegerConstruct) {
	// 	Integer::make("123");
	// 	Integer::make("0");
	// 	Assert::ExpectException<std::invalid_argument>(
	// 		[]() {Integer::make("0123"); }
	// 	);
	// 	Assert::ExpectException<std::invalid_argument>(
	// 		[]() {Integer::make("a123"); }
	// 	);
	// 	Assert::ExpectException<std::invalid_argument>(
	// 		[]() {Integer::make("1a23"); }
	// 	);

	// 	Integer::make(IntegerToken { "123" });
	// }
	// TEST_METHOD(Test_NameConstruct) {
	// 	Name::make("abc");
	// 	Name::make("abc123");
	// 	Assert::ExpectException<std::invalid_argument>(
	// 		[]() {Name::make("123"); }
	// 	);
	// 	Assert::ExpectException<std::invalid_argument>(
	// 		[]() {Name::make("1abc"); }
	// 	);
	// 	Assert::ExpectException<std::invalid_argument>(
	// 		[]() {Name::make("abc_"); }
	// 	);

	// 	Name::make(std::vector<Token> {NameToken { "a123" }});
	// 	Assert::ExpectException<std::invalid_argument>(
	// 		[]() { Name::make(std::vector<Token> {NameToken { "a123" }, NameToken { "a123" }}); }
	// 	);

	// }
	TEST_METHOD(Test_VariableConstruct) {
		VariableNode::make("abc");
		Assert::ExpectException<std::invalid_argument>(
			[]() {VariableNode::make("abc_"); }
		);
	}*/
	};
}