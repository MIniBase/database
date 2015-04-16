#pragma once
#include "Operation.h"

class QueryOperation :public Operation
{
public:
	QueryOperation(vector<string> tables, vector<ColumnAndTable> columns, vector<Equation> equations);
	virtual RecordSet exec() = 0;
private:
	vector<string> tables; //Ҫ��ѯ�����б���
	vector<ColumnAndTable> columns; //��ѯ�����������ڱ���
	vector<Equation> equations;
};

