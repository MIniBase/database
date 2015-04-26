#include "stdafx.h"

TableManagement::TableManagement()
{
}


TableManagement::~TableManagement()
{
}
int TableManagement::hasTable(string name){
	for (int i = 0; i < TableInfomation.size(); i++)
	{
		if (TableInfomation.at(i).Tablename == name)
			return true;
	}
	return false;
}
int TableManagement::hasColumn(string TableName, string ColumnName){
	for (int i = 0; i < TableInfomation.size(); i++)
	{
		if (TableInfomation.at(i).Tablename == TableName)
		{
			for (int j = 0; j < TableInfomation.at(i).Columns.size(); j++)
			{
				if (TableInfomation.at(i).Columns.at(j).column_name == ColumnName)
					return true;
			}
		}
	}
	return false;
}
int TableManagement::addTable(TableInfo t){
	if (hasTable(t.Tablename))
		return false;
	else
		TableInfomation.push_back(t);
	return true;
}
vector<TableInfo> TableManagement::getTablebyColumn(string ColumnName){
	vector<TableInfo> Tables;
	for (int i = 0; i < TableInfomation.size(); i++)
	{
	
		for (int j = 0; j < TableInfomation.at(i).Columns.size(); j++)
		{
			if (TableInfomation.at(i).Columns.at(j).column_name == ColumnName)
				Tables.push_back(TableInfomation.at(i));
		}
	}
	return Tables;
}