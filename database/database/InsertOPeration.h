#pragma once
#include "stdafx.h"
#include "Operation.h"

class InsertOPeration :public Operation
{
public:
	InsertOPeration();
	virtual Table exec();
	string tableName;
	vector<Data> data;
};

