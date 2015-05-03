#pragma once
struct TableInfo{
	vector<ColumnTitle> Columns;
	string Tablename;
	ColumnTitle primaryKey;
	TableInfo(){}
	TableInfo(vector<ColumnTitle> Columns, string Tablename) :Columns(Columns), Tablename(Tablename){}
};
class TableManagement
{
public:
	TableManagement();
	~TableManagement();

	vector<TableInfo> TableInfomation;
	int TableNum = 0;//��¼��ǰ������������ڷ��ظ��س�ʼ����ʱ�������
	int hasTable(string name);
	int hasColumn(string TableName, string ColumnName);
	int hasColumn(string ColumnName);
	vector<TableInfo> getTablebyColumn(string Columnname);
	vector<string> getColumnbyTable(string TableName);
	ColumnTitle getPrimaryKey(string TableName);
	int addTable(TableInfo);
	DataType getDataType(string TableName, string ColumnName);
	int writeToDisk();//�������/���н���ʱд����̱���
	int initialFromDisk();//�����ʼ��ʱ�Ӵ��̶�ȡ��������Ϣ
};