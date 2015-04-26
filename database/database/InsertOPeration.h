#pragma once
#include "stdafx.h"
#include "Operation.h"

class InsertOpration :public Operation
{
public:
	InsertOperation();
	virtual Table exec();
	string tableName;
	vector<Data> data;
};

