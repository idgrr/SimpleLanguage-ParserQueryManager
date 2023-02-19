#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "../PKB/PKBFacade.h"

using namespace std;

class QueryManager {
public:
	list<string> getQueryResponse(string input, PKBFacade* pkb);
};