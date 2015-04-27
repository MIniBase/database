#pragma once
struct TableInfo{
	vector<ColumnTitle> Columns;
	string Tablename;
	TableInfo(){}
	TableInfo(vector<ColumnTitle> Columns, string Tablename) :Columns(Columns), Tablename(Tablename){}
};
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
	int TableNum=0;//��¼���ڹ��ı�����������ڷ��ظ��س�ʼ����ʱ�������
	DataType getDataType(string TableName, string ColumnName);
};