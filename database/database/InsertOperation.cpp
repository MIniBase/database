#include "stdafx.h"
#include "InsertOperation.h"


InsertOperation::InsertOperation(string tableName, vector<ColumnTitle> columns, vector<Data> datas)
	:tableName(tableName), title(columns), data(datas)
{
	//todo ѭ��֧��
}

InsertOperation::InsertOperation(string tableName, vector<Data> datas)
	: tableName(tableName), data(datas)
{

}

Table InsertOperation::exec(){
	BPlusTree temBptree(tableName, NULL);

	return Table();
}