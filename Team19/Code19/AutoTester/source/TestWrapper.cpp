#include "TestWrapper.h"
#include <unordered_set>

// implementation code of WrapperFactory - do NOT modify the next 5 lines
AbstractWrapper* WrapperFactory::wrapper = 0;
AbstractWrapper* WrapperFactory::createWrapper() {
  if (wrapper == 0) wrapper = new TestWrapper;
  return wrapper;
}
// Do not modify the following line
volatile bool TestWrapper::GlobalStop = false;

// a default constructor
TestWrapper::TestWrapper() {
  // create any objects here as instance variables of this class
  // as well as any initialization required for your spa program


	pkb = new PKBFacade();
	queryManager = new QueryManager();
	evaluator = new QueryEvaluator();

	std::cout << "constructed\n";
}


TestWrapper::~TestWrapper() {}

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename) {
	std::ifstream ifs(filename);
	std::string content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));

	vector<Token>  tokens = TokenSplitter(content).tokenize();
	Parser parser = Parser(tokens);
	size_t lineNo = 1;

	unique_ptr<ProgramNode> AST = parser.parseTokens();

	DesignExtractor de = DesignExtractor(move(AST));
	de.extractAST();

	for (auto& entity : de.getEntities()) {
		cout << entity.getStmtNo() << ": " << entity.getName() << endl;
	}

}


// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results){
// call your evaluator to evaluate the query here
  // ...code to evaluate query...
	

	////std::string input = "variable v; Select v";
	///*std::string input = "nothing";*/
	optional<QueryObject> qObj = QueryParser::parse(query);
	if (qObj) {
		/*std::cout << query << std::endl;
		std::cout << qObj.value().synToSelect.synName << std::endl;*/
		list<string> consolidatedResult = evaluator->evaluate(qObj.value(), pkb);
		results = consolidatedResult;
	} else {
		results = { "SyntaxError" };
	}


  // store the answers to the query in the results list (it is initially empty)
  // each result must be a string.
	

	
}
