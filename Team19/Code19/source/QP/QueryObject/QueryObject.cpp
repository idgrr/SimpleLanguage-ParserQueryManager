#include "QueryObject.h"
#include "SuchThatClause.h"
#include "PatternClause.h"
#include "Declaration.h"

QueryObject::QueryObject(std::list<Declaration> declarations, 
	SuchThatClause suchThatClause, PatternClause patternClause, Declaration synToSelect) 
	: declarations(declarations), suchThatClause(suchThatClause), 
	patternClause(patternClause), synToSelect(synToSelect)
{

}

bool QueryObject::operator==(const QueryObject& qo) const {
	//return tie(declarations, suchThatClause, patternClause, synToSelect) == tie(qo.declarations, qo.suchThatClause, patternClause, synToSelect);
	return tie(declarations, synToSelect) == tie(qo.declarations, qo.synToSelect);
}