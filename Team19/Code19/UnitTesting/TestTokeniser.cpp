#include "stdafx.h"
#include "CppUnitTest.h"
// #include "TNode.h"
#include "../source/SourceProcessor/SPTokenizer.h"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{		
	TEST_CLASS(TestTokeniser)
	{
	public:
		TEST_METHOD(Test_Tokenise_words)
		{
			Assert::AreEqual(
				size_t(2),
				TokenSplitter("abc def").tokenize().size()
			);
		}

		TEST_METHOD(Test_Tokenize_bracket)
		{
			Assert::AreEqual(
				size_t(4),
				TokenSplitter("abc (def)").tokenize().size()
			);
			
			std::vector <Token> a { 
				NameToken{ "abc" }, 
				SymbolToken{ "(" }, 
				NameToken{ "def" }, 
				SymbolToken{ ")" } 
			};
			std::vector <Token> b = TokenSplitter("abc (def)").tokenize();
			for (size_t i = 0; i < a.size(); i++)
			{
				std::vector<Token>::iterator aa = a.begin();
				std::vector<Token>::iterator bb = b.begin();
				Assert::AreEqual(
					 aa->value
					,bb->value
				);
				aa++;
				bb++;
			}
		}
	
		TEST_METHOD(Test_Tokenise_and)
		{
			Assert::AreEqual(
				size_t(3),
				TokenSplitter("abc&&def").tokenize().size()
			);
		}

		TEST_METHOD(Test_Tokenise_compare)
		{
			Assert::AreEqual(
				size_t(3),
				TokenSplitter("abc<=def").tokenize().size()
			);
		}

		TEST_METHOD(Test_Tokenise_terminal_comp)
		{
			Assert::AreEqual(
				size_t(2),
				TokenSplitter("abc<").tokenize().size()
			);
			Assert::AreEqual(
				size_t(2),
				TokenSplitter("abc=").tokenize().size()
			);
			Assert::AreEqual(
				size_t(2),
				TokenSplitter("abc&").tokenize().size()
			);
		}

		TEST_METHOD(Test_Tokenise_different_object)
		{
			// trying to ensure that multiple calls to tokenize will give a new vector object

			TokenSplitter ts = TokenSplitter("abc def");
			Assert::AreEqual(
				ts.tokenize().front().value,
				ts.tokenize().front().value
			);
			Assert::AreNotSame(
				ts.tokenize().front().value,
				ts.tokenize().front().value
			);
		}

		TEST_METHOD(Test_NewLine) {
			Assert::AreEqual(
				size_t(3),
				TokenSplitter("read var;").tokenize().size()
			);
			Assert::AreEqual(
				size_t(6),
				TokenSplitter("read var;\nread var;").tokenize().size()
			);
		}


	};
}