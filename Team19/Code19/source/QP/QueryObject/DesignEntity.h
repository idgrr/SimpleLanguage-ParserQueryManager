#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_set>
#include "../../PKB/PKBFacade.h"

using namespace std;

class DesignEntity {
public:
	virtual std::unordered_set<std::string> getSynonymFromPKB(PKBFacade* pkb);
};


namespace DE {
	class Procedure : public DesignEntity {
	public:
		std::unordered_set<std::string> getSynonymFromPKB(PKBFacade* pkb) override;
	};

	class Statement : public DesignEntity {
	public:
		std::unordered_set<std::string> getSynonymFromPKB(PKBFacade* pkb) override;
	};

	class Read : public DesignEntity {
	public:
		std::unordered_set<std::string> getSynonymFromPKB(PKBFacade* pkb) override;
	};

	class Print : public DesignEntity {
	public:
		std::unordered_set<std::string> getSynonymFromPKB(PKBFacade* pkb) override;
	};

	class Assign : public DesignEntity {
	public:
		std::unordered_set<std::string> getSynonymFromPKB(PKBFacade* pkb) override;
	};

	class Call : public DesignEntity {
	public:
		std::unordered_set<std::string> getSynonymFromPKB(PKBFacade* pkb) override;
	};

	class While : public DesignEntity {
	public:
		std::unordered_set<std::string> getSynonymFromPKB(PKBFacade* pkb) override;
	};

	class If : public DesignEntity {
	public:
		std::unordered_set<std::string> getSynonymFromPKB(PKBFacade* pkb) override;
	};

	class Variable : public DesignEntity {
	public:
		std::unordered_set<std::string> getSynonymFromPKB(PKBFacade* pkb) override;
	};

	class Constant : public DesignEntity {
	public:
		std::unordered_set<std::string> getSynonymFromPKB(PKBFacade* pkb) override;
	};
}

