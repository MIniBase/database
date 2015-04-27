#pragma once
class TableManagement
{
public:
	TableManagement();
	~TableManagement();
	vector<TableInfo> TableInfomation;
	int hasTable(string name);
	int hasColumn(string TableName, string ColumnName);
	vector<TableInfo> getTablebyColumn(string Columnname);
	vector<string> getColumnbyTable(string TableName);
	int addTable(TableInfo);
};

