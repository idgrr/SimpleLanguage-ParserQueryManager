#ifndef TESTWRAPPER_H
#define TESTWRAPPER_H

#include <string>
#include <iostream>
#include <list>
#include <fstream>
#include "../../source/PKB/PKBFacade.h"
#include "../../source/SourceProcessor/SPTokenizer.h"
#include "../../source/SourceProcessor/Parser.h"
#include "../../source/SourceProcessor/DesignExtractor/DesignExtractor.h"

// include your other headers here
#include "AbstractWrapper.h"
#include "../../source/QP/QueryManager.h"
#include "../../source/QP/QueryParser.h"
#include "../../source/QP/QueryEvaluator/QueryEvaluator.h"
#include "../../source/QP/QueryEvaluator/SelectSynonymEvaluator.h"
#include "../../source/QP/QueryEvaluator/ResultConsolidator.h"
#include "../../source/QP/QueryObject/QueryObject.h"
#include "../../source/QP/QueryObject/Declaration.h"
#include "../../source/QP/QueryObject/SuchThatClause.h"
#include "../../source/QP/QueryObject/PatternClause.h"
#include "../../source/QP/QueryObject/DesignEntity.h"
#include "../../source/Entity/Entity.h"

class TestWrapper : public AbstractWrapper {
 private:
	 PKBFacade* pkb;
	 QueryEvaluator* evaluator;
	 QueryManager* queryManager;
 public:
	 
  // default constructor
	 TestWrapper();
  
  // destructor
	 ~TestWrapper();
  
  // method for parsing the SIMPLE source
  virtual void parse(std::string filename);
  
  // method for evaluating a query
  virtual void evaluate(std::string query, std::list<std::string>& results);

};

#endif
