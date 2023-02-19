#include "stdafx.h"
#include "CppUnitTest.h"
#include "../source/PKB/PKBFacade.h"
#include "../source/Entity/Entity.h"
//#include "TNode.h"
#include <cstddef>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
    TEST_CLASS(TestPKB)
    {
    public:

        TEST_METHOD(InsertBasic)
        {
            PKBFacade pkb = PKBFacade();
            std::vector<Entity> entList{};
            entList.push_back(Variable(1, "x"));
            entList.push_back(Variable(1, "y"));
            entList.push_back(Variable(2, "x"));
            entList.push_back(Variable(3, "z"));
            entList.push_back(Constant(1, "1"));
            entList.push_back(Constant(1, "2"));
            entList.push_back(Constant(2, "2"));
            entList.push_back(Constant(3, "3"));
            entList.push_back(Procedure("main"));
            entList.push_back(Procedure("ok"));
            entList.push_back(Procedure("hospital"));
            entList.push_back(Procedure("die"));

            for (auto& a : entList) {
                pkb.insertEntity(a);
            }

            std::vector<std::string> testName = { "print", "print", "read", "read", "assignment", "assignment", "print" };
            std::vector<int> testStmt = { 1, 2, 5, 6 , 3, 7, 4 };
            for (int i = 0; i < 7; i++) {
                Statement k = Statement(testStmt[i], testName[i]);
                pkb.insertEntity(k);
            }



            // variable working
            std::string check = "y";
            int sizeTvar = pkb.getAllVar().size();
            Assert::AreEqual(*pkb.getAllVar().find(check), check);
            Assert::AreEqual(sizeTvar, 3);

            //constant working
            std::string checkc = "3";
            int sizeTconst = pkb.getAllConstant().size();
            Assert::AreEqual(*pkb.getAllConstant().find(checkc), checkc);
            Assert::AreEqual(sizeTconst, 3);

            // procedures working
            std::string checkp = "die";
            int sizeTproc = pkb.getAllProc().size();
            Assert::AreEqual(*pkb.getAllProc().find(checkp), checkp);
            Assert::AreEqual(sizeTproc, 4);

            std::string checkprint = "4";
            Assert::AreEqual(*pkb.getAllStmtFromType("print").find(checkprint), checkprint);
            int sizePrint = pkb.getAllStmtFromType("print").size();
            Assert::AreEqual(sizePrint, 3);

            std::string checkread = "6";
            Assert::AreEqual(*pkb.getAllStmtFromType("read").find(checkread), checkread);
            int sizeRead = pkb.getAllStmtFromType("read").size();
            Assert::AreEqual(sizeRead, 2);

            std::string checkassign = "7";
            Assert::AreEqual(*pkb.getAllStmtFromType("assignment").find(checkassign), checkassign);
            int sizeAssignment = pkb.getAllStmtFromType("assignment").size();
            Assert::AreEqual(sizeAssignment, 2);


        }

    };
}