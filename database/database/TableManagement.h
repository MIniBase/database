#pragma once
class TableManagement
{
public:
	TableManagement();
	~TableManagement();
	vector<TableInfo> TableInfomation;
	bool hasTable(string name);
	bool hasColumn(string TableName, string ColumnName);
	void addTable(TableInfo);
};

