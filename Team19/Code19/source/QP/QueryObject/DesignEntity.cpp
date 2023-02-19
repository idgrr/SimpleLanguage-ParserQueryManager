#include "DesignEntity.h"

using namespace DE;

std::unordered_set<std::string> DesignEntity::getSynonymFromPKB(PKBFacade* pkb) {
	return {};
};

std::unordered_set<std::string> DE::Procedure::getSynonymFromPKB(PKBFacade* pkb) {
	return pkb->getAllProc();
}

std::unordered_set<std::string> DE::Statement::getSynonymFromPKB(PKBFacade* pkb) {
	/*return pkb->getAllStmt;*/
	return {};
}

std::unordered_set<std::string> DE::Read::getSynonymFromPKB(PKBFacade* pkb) {
	return pkb->getAllStmtFromType("read");
}

std::unordered_set<std::string> DE::Print::getSynonymFromPKB(PKBFacade* pkb) {
	return pkb->getAllStmtFromType("print");
}

std::unordered_set<std::string> DE::Assign::getSynonymFromPKB(PKBFacade* pkb) {
	return pkb->getAllStmtFromType("assign");
}

std::unordered_set<std::string> DE::Call::getSynonymFromPKB(PKBFacade* pkb) {
	/*return pkb->getAllCall();*/
	return {};
}

std::unordered_set<std::string> DE::While::getSynonymFromPKB(PKBFacade* pkb) {
	/*return pkb->getAllWhile();*/
	return {};
}

std::unordered_set<std::string> DE::If::getSynonymFromPKB(PKBFacade* pkb) {
	/*return pkb->getAllIf();*/
	return {};
}

std::unordered_set<std::string> DE::Variable::getSynonymFromPKB(PKBFacade* pkb) {
	return pkb->getAllVar();
}

std::unordered_set<std::string> DE::Constant::getSynonymFromPKB(PKBFacade* pkb) {
	return pkb->getAllConstant();
}
