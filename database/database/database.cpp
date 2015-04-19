// database.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<string>
#include<iostream>
#include<vector>
#include<sstream>
#include<vector>
//#include"CreateOperation.h"
#include"QueryOperation.h"

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


void parser(string t)//��������
{
	string type = t.substr(0, 6);
	string left = t.substr(6, t.size() - 6);
	if (type == "SELECT" || type == "select")
	{

	}
	else{
		if (type == "CREATE" || type == "create")
		{

		}
	}
}


int main()
{
	parser("select ");
	return 0;
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
RecordSet findtables(string tablename);

Operation *parser(string t)
{
	if (issubQuery(t)){//�������Ű�����ȥ������
		t = t.substr(1, t.length() - 2);
	}
	string type;//��������
	Operation *op;
	int count = 0;
	vector<string> allwords = split(t, " ");//���տո��ȷִ�
	type = allwords[count];
	count++;
	if (type == "SELECT" || type == "select")//�ж�����
	{
		vector<string> columns = split(allwords.at(count), ",");
		count++;

		if (allwords.at(count) != "from"&&allwords.at(count) != "FROM"){
			cerr << "Illegal Input";
			abort();
		}
		count++;
		vector<string> tabledef = split(allwords.at(count), ",");
		vector<RecordSet> tables;
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
		count++;
		vector<RecordSet>::iterator it = tables.begin(), end = tables.end();
		vector<ColumnAndTable> colandtab;
		for (int i = 0; i<columns.size(); i++)//�кͱ�ƥ��
		{
			if (iscolandtab(columns[i]))//ָ���˱����
			{
				vector<string> thisline = split(columns[i], ".");
				ColumnAndTable temp;
				temp.first = line[0];
				temp.second = line[1];
				colandtab.push_back(temp);
				continue;
			}
			for (it = tables.begin(); it != end; it++){//δָ����ȫ��ƥ��
				ColumnAndTable temp;
				temp.first = columns[i];
				temp.second = "";//(*it).//�˴������⣬����ǵݹ����ɵı���ô��ʾ��
				colandtab.push_back(temp);
			}
		}
		if (allwords.at(count) != "where"&&allwords.at(count) != "WHERE"){
			cerr << "Illegal Input";
			abort();
		}
		count++;
		vector<string> equations = split(allwords.at(count), ",");
		op = new QueryOperation(tables, colandtab, equations);
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
			cout << tableName << endl;
			vector<string> columnAndType = split(allwords.at(1), ",");
			vector<column> cAndTs;
			for (int i = 0; i < columnAndType.size() - 1; i++)
			{
				new columnsAndType;
				columnsAndType.
					cout << columnAndType.at(i) << endl;
			}
			string primaryKey = split(columnAndType.at(columnAndType.size() - 1), "(", ")").at(1);
			cout << "primary key:" << primaryKey;
		}
	}
	return op;
}
int main()
{
	parser("select ab,c,d from e,f where ab>1");
	return 0;
}




