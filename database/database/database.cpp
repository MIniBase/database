#include "stdafx.h"
using namespace std;

//字符串分割函数
vector<string> split(string str, string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str += pattern;//扩展字符串以方便操作
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

vector<string> split(string str, string pattern, string pattern2)//去掉括号函数creat时使用
{
	std::string::size_type pos;
	std::string::size_type minpos;
	std::vector<std::string> result;
	str += " ";//扩展字符串以方便操作
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
TableColumn TransTandC(string t)//转换 string里面t.c为具体表列，select时使用
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

ColumnTitle TransCandT(string t)//转换 string里面a string为具体表的属性，create时使用
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
bool isNotConst(string t){//判断运算符两侧的字符串是常量否
	if (t.at(0) == '"'&&t.at(t.size() - 1) == '"')//如果是string类型常量，应该由双引号包裹，直接返回false
		return false;
	if (split(t, ".").size() == 1)//如果是其他类型常量，则中间不会包含.，因此可以用是否包含点来判断
		return false;
	return true;//两个都不符合，不是常量
}
Condition Transcond(string t){
	Condition temp;
	vector<string> cond;
	Data ld, rd;
	if ((cond = split(t, "==")).size() == 2)
	{
		temp.op = isEQ;//==
		goto fuzhi;
	}
	else{
		if ((cond = split(t, ">")).size() == 2)
		{
			temp.op = isGT;//>
			goto fuzhi;
		}
		else
			if ((cond = split(t, "<")).size() == 2)
			{
				temp.op = isLT;//<
				goto fuzhi;
			}
			else
				if ((cond = split(t, "!=")).size() == 2)
				{
					temp.op = isNE;//!=
					goto fuzhi;
				}
				else
					if ((cond = split(t, ">=")).size() == 2)
					{
						temp.op = isGE;//>=
						goto fuzhi;
					}
					else
						if ((cond = split(t, "<=")).size() == 2)
						{
							temp.op = isLE;//<=
							goto fuzhi;
						}
	}
fuzhi:	
	if (isNotConst(cond.at(0)))
	{
		temp.left = TransTandC(cond.at(0));
	}
	else{
		ld = Data(DB_CONST, cond.at(0));
		temp.isLeftConst = TRUE;
		temp.leftData = ld;
	}
	if (isNotConst(cond.at(1)))
	{
		temp.right = TransTandC(cond.at(1));
	}
	else{
		rd = Data(DB_CONST, cond.at(1));
		temp.isRightConst = TRUE;
		temp.rightData = rd;
	}
	return temp;
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
	if (issubQuery(t)){//如有括号包裹，去掉括号
		t = t.substr(1, t.length() - 2);
	}
	string type = t.substr(0, 6);//操作类型
	Operation *op = NULL;
	int count = 0;

	if (type == "SELECT" || type == "select")//判断类型
	{
		vector<string> allwords = split(t, " ");//按照空格先分词
		count++;
		vector<string> columnandtable = split(allwords.at(count), ",");
		count++;
		vector<TableColumn> TC;

		for (int i = 0; i < columnandtable.size(); i++){//抽取表-列对应关系
			TC.push_back(TransTandC(columnandtable.at(i)));
		}
		if (allwords.at(count) != "from"&&allwords.at(count) != "FROM"){
			cerr << "Illegal Input";
		}
		count++;
		vector<string> table = split(allwords.at(count), ",");//获取表名
		/*		vector<Table> tables;
		for (int i = 0; i<tabledef.size(); i++)//把表准备好
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
		vector<string> equations = split(allwords.at(count), ",");//条件用,分词
		vector<Condition> conds;
		for (int i = 0; i < equations.size(); i++)
		{
			conds.push_back(Transcond(equations.at(i)));
		} 
		op = new QueryOperation(TC, table, conds);
	}
	else{
		//分词时注意类型表名后面必须接 空格；主键不能接空格，必须直接接括号
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
			if ("primary key" != keyCmp && keyCmp != "PRIMARY KEY"){
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
		getline(cin, input);
		try{
			Operation* operation = parser(input);
			const Table& result = operation->exec();
			cout << "success! " << result.data.size() << " rows affected\n";
			cout << "--------" << result.tableName <<"------------"<< endl;

			for (const auto& title : result.title){
				cout << setw(8) << title.column_name<< "|";
			}
			cout << endl;

			for (const auto& row : result.data){
				for (const auto& data : row){
					cout << setw(8) << data << "|";
				}
				cout << endl;

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


