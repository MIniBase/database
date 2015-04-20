
#include "stdafx.h"
#include<string>
#include<iostream>
#include<vector>
#include<sstream>
#include<vector>
#include"CreateOperation.h"
#include"QueryOperation.h"
#include"Operation.h"
#include"Table.h"
#include <iomanip>
using namespace std;

//�ַ����ָ��
vector<string> split(string str, string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str += pattern;//��չ�ַ����Է������
	int size = str.size();

	for (int i = 0; i<size; i++)
	{
		pos = str.find(pattern, i);
		if (pos<size)
		{
			std::string s = str.substr(i, pos - i);
			if (pos - i != 0)
				result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}

vector<string> split(string str, string pattern, string pattern2)//ȥ�����ź���creatʱʹ��
{
	std::string::size_type pos;
	std::string::size_type minpos;
	std::vector<std::string> result;
	str += " ";//��չ�ַ����Է������
	int size = str.size();

	for (int i = 0; i<size; i++)
	{
		minpos = str.find(pattern, i);
		pos = str.find(pattern2, i);
		pos = (minpos < pos ? minpos : pos);
		if (pos<size)
		{
			std::string s = str.substr(i, pos - i);
			if (pos - i != 0)
				result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}
TableColumn TransTandC(string t)//ת�� string����t.cΪ������У�selectʱʹ��
{
	TableColumn temp;
	vector<string> tandc = split(t, ".");
	if (tandc.size() == 2)
	{
		temp.tableName = tandc.at(0);
		temp.colunmName = tandc.at(1);
		return temp;
	}
	else{
		cerr << "Illegal Input ColumnandTable" << endl;
		abort();
	}
}

ColumnTitle TransCandT(string t)//ת�� string����a stringΪ���������ԣ�createʱʹ��
{
	ColumnTitle temp;
	vector<string> tandc = split(t, " ");
	if (tandc.size() == 2)
	{
		temp.column_name = tandc.at(0);
		if (tandc.at(1) == "CONST" || tandc.at(1) == "const")
			temp.datatype = (DataType)0;
		else if (tandc.at(1) == "INT" || tandc.at(1) == "int")
			temp.datatype = (DataType)1;
		else if (tandc.at(1) == "DOUBLE" || tandc.at(1) == "double")
			temp.datatype = (DataType)2;
		else if (tandc.at(1) == "BOOL" || tandc.at(1) == "bool")
			temp.datatype = (DataType)3;
		else if (tandc.at(1) == "STRING" || tandc.at(1) == "string")
			temp.datatype = (DataType)4;
		else
		{
			cerr << "Illegal Data Type" << endl;
			abort();
		}
		return temp;
	}
	else{
		cerr << "Illegal Input ColumnandTable" << endl;
		abort();
	}
}

Condition Transcond(string t){
	Condition temp;
	vector<string> cond;
	if ((cond = split(t, "==")).size() == 2)
	{
		temp.left = TransTandC(cond.at(0));
		temp.right = TransTandC(cond.at(1));
		temp.op = isEQ;//==
	}
	else{
		if ((cond = split(t, ">")).size() == 2)
		{
			temp.left = TransTandC(cond.at(0));
			temp.right = TransTandC(cond.at(1));
			temp.op = isGT;//>
		}
		else
			if ((cond = split(t, "<")).size() == 2)
			{
				temp.left = TransTandC(cond.at(0));
				temp.right = TransTandC(cond.at(1));
				temp.op = isLT;//<
			}
			else
				if ((cond = split(t, "!=")).size() == 2)
				{
					temp.left = TransTandC(cond.at(0));
					temp.right = TransTandC(cond.at(1));
					temp.op = isNE;//!=
				}
				else
					if ((cond = split(t, ">=")).size() == 2)
					{
						temp.left = TransTandC(cond.at(0));
						temp.right = TransTandC(cond.at(1));
						temp.op = isGE;//>=
					}
					else
						if ((cond = split(t, "<=")).size() == 2)
						{
							temp.left = TransTandC(cond.at(0));
							temp.right = TransTandC(cond.at(1));
							temp.op = isLE;//<=
						}
	}
}
bool issubQuery(string str)
{
	if (str.at(0) == '('&&str.at(str.length() - 1) == ')')
		return true;
	else
		return false;
}
bool iscolandtab(string str)
{
	if (str.find(".") != str.npos)
		return true;
	else
		return false;
}
Table findtables(string tablename);

Operation *parser(string t)
{
	if (issubQuery(t)){//�������Ű�����ȥ������
		t = t.substr(1, t.length() - 2);
	}
	string type = t.substr(0, 6);//��������
	Operation *op;
	int count = 0;

	if (type == "SELECT" || type == "select")//�ж�����
	{
		vector<string> allwords = split(t, " ");//���տո��ȷִ�
		count++;
		vector<string> columnandtable = split(allwords.at(count), ",");
		count++;
		vector<TableColumn> TC;

		for (int i = 0; i < columnandtable.size(); i++){//��ȡ��-�ж�Ӧ��ϵ
			TC.push_back(TransTandC(columnandtable.at(i)));
		}
		if (allwords.at(count) != "from"&&allwords.at(count) != "FROM"){
			cerr << "Illegal Input";
		}
		count++;
		vector<string> table = split(allwords.at(count), ",");//��ȡ����
		/*		vector<Table> tables;
		for (int i = 0; i<tabledef.size(); i++)//�ѱ�׼����
		{
		if (issubQuery(tabledef.at(i)))
		{
		Operation *subquery = parser(tabledef.at(i));
		tables.push_back(subquery.exec());
		continue;
		}
		tables.push_back(findtables(tabledef.at(i)));
		}
		*/
		count++;
		if (allwords.at(count) != "where"&&allwords.at(count) != "WHERE"){
			cerr << "Illegal Input";
			abort();
		}
		count++;
		vector<string> equations = split(allwords.at(count), ",");//������,�ִ�
		vector<Condition> conds;
		for (int i = 0; i < equations.size(); i++)
		{
			conds.push_back(Transcond(equations.at(i)));
		}
		op = new QueryOperation(TC, table, conds);
	}
	else{
		//�ִ�ʱע�����ͱ����������� �ո��������ܽӿո񣬱���ֱ�ӽ�����
		if (type == "CREATE" || type == "create")//creat table by TZH
		{
			string tableName = "";//
			vector<string> allwords = split(t, " (", ") ");
			/*for (int i = 0; i < allwords.size(); i++)
			cout << allwords.at(i) << endl;*/
			vector<string> firstPart = split(allwords.at(0), " ");
			tableName = firstPart.at(2);//third word is the table name
			//cout << tableName << endl;

			vector<string> columnAndType = split(allwords.at(1), ",");
			vector<ColumnTitle> CTs;

			for (int i = 0; i < columnAndType.size() - 1; i++)
			{
				CTs.push_back(TransCandT(columnAndType.at(i)));
				//cout << columnAndType.at(i) << endl;
			}

			string keyCmp = split(columnAndType.at(columnAndType.size() - 1), "(", ")").at(0);
			if ("primary key" != keyCmp || keyCmp != "PRIMARY KEY"){
				cerr << "Illegal input,need primary key";
				abort();
			}
			string primaryKey = split(columnAndType.at(columnAndType.size() - 1), "(", ")").at(1);

			//cout << "primary key:" << primaryKey;
			op = new CreateOperation(tableName, CTs, primaryKey);
		}
	}
return op;
}

int main()
{
	/*parser("select ab,c,d from e,f where ab>1");*/
	cout << "MIniBase Beta 0.1\n";
	string input;
	while (true){
		cout << "MIniBase>";
		cin >> input;
		try{
			Operation* operation = parser(input);
			const Table& result = operation->exec();
			cout << "success! " << result.data.size() << "rows affected\n";
			cout << "     " << result.tableName << endl;

			for (const auto& title : result.title){
				cout << setw(8) << title.column_name;
				if (title == result.title.back()){
					cout << endl;
				}
				else{
					cout << "|";
				}

			}

			for (const auto& row : result.data){
				for (const auto& data : row){
					cout << setw(8) << data;
					if (data == row.back()){
						cout << endl;
					}
					else{
						cout << "|";
					}
				}

			}

			delete operation;
		}
		catch (string e){
			cout << e << endl;
		}
		catch (exception e){
			cout << e.what() << endl;
		}

	}
	return 0;
}


