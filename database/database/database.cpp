#include "stdafx.h"
using namespace std;
TableManagement TableManager;
stringstream ss;
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
vector<string> splitnotbracket(string str, string pattern)//对split函数做出修改，使得不会分割()中的内容
{
	std::string::size_type pos;
	std::string::size_type bracketl;
	std::string::size_type bracketr;
	std::vector<std::string> result;
	str += pattern;//扩展字符串以方便操作
	int size = str.size();

	for (int i = 0; i<size; i++)
	{
		if (str.at(i) != '(')
		{
			pos = str.find(pattern, i);
			if (pos < size)
			{
				std::string s = str.substr(i, pos - i);
				if (pos - i != 0)
					result.push_back(s);
				i = pos + pattern.size() - 1;
			}
		}
		else
		{
			pos = str.find(")", i);
			if (pos < size)
			{
				std::string s = str.substr(i, pos - i + 1);
				if (pos - i != 0)
					result.push_back(s);
				i = pos + pattern.size() - 1;
			}
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
vector<string> split(string str, string pattern, string pattern2, string pattern3, string pattern4)//去掉括号函数insert时使用
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
		minpos = (minpos < pos ? minpos : pos);
		pos = str.find(pattern3, i);
		minpos = (minpos < pos ? minpos : pos);
		pos = str.find(pattern4, i);

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
		if (TableManager.hasColumn(tandc.at(0), tandc.at(1))){
			temp.tableName = tandc.at(0);
			temp.colunmName = tandc.at(1);
			return temp;
		}
		else{
			throw  "Column " + tandc.at(1) + "Not Found In Table " + tandc.at(0);
		}
	}
	else{
		if (TableManager.getTablebyColumn(t).size() == 1)
		{
			temp.tableName = TableManager.getTablebyColumn(t).at(0).Tablename;
			temp.colunmName = t;
			return temp;
		}
		else if (TableManager.getTablebyColumn(t).size() == 0){
			throw  "Column " + t + " Not Found";

		}
		else{
			throw  "Column " + t + " Found In Many Tables";

		}
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
			throw "Illegal Data Type" ;
			
		}
		return temp;
	}
	else{
		throw "Illegal Input ColumnandTable" ;
		
	}
}
bool isNotConst(string t){//判断运算符两侧的字符串是常量否
	if (t.at(0) == '"'&&t.at(t.size() - 1) == '"')//如果是string类型常量，应该由双引号包裹，直接返回false
		return false;
	if (split(t, ".").size() == 1)//如果是中间不包含.，则要判断是否是省略了表名，
	{
		if (!TableManager.hasColumn(t)){
			return false;
		}
	}
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
	temp.isLeftConst = !isNotConst(cond.at(0));
	temp.isRightConst = !isNotConst(cond.at(1));
	if (!(temp.isLeftConst) || !(temp.isRightConst))
	{
		if (!temp.isLeftConst&&!temp.isRightConst)
		{
			temp.left = TransTandC(cond.at(0));
			temp.right = TransTandC(cond.at(1));
		}
		else{
			if (temp.isRightConst){
				temp.left = TransTandC(cond.at(0));
				rd = Data(TableManager.getDataType(temp.left.tableName, temp.left.colunmName), cond.at(1));
				temp.isRightConst = TRUE;
				temp.rightData = rd;
			}
			else{
				temp.right = TransTandC(cond.at(1));
				ld = Data(TableManager.getDataType(temp.right.tableName, temp.right.colunmName), cond.at(0));
				temp.isLeftConst = TRUE;
				temp.leftData = ld;
			}
		}
	}
	else{
		throw  "Condition Not Valid";
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
Operation *parser(string t)
{
	while (issubQuery(t)){//如最外层有括号包裹，去掉括号
		t = t.substr(1, t.length() - 2);
	}
	string type = t.substr(0, 6);//操作类型
	Operation *op = NULL;
	int count = 0;

	if (type == "SELECT" || type == "select")//判断类型
	{
		vector<string> allwords = splitnotbracket(t, " ");//按照空格先分词,如果是括号包裹的，先不分
		for (int i = 0; i < allwords.size(); i++){
			if (issubQuery(allwords.at(i)))
			{
				Table result=parser(allwords.at(i))->exec();
				ss << TableManager.TableNum;
				ss >> result.tableName;
				allwords.at(i) = result.tableName;
			}
		}
		vector<TableColumn> TC;
		bool selectallcolumns=false;
		count++;
		vector<string> columnandtable = split(allwords.at(count), ",");
		if (allwords.at(count) == "*"){
			selectallcolumns = true;
		}
		else{
		for (int i = 0; i < columnandtable.size(); i++){//抽取表-列对应关系
			TC.push_back(TransTandC(columnandtable.at(i)));
		}
		}
		count++;
		if (allwords.at(count) != "from"&&allwords.at(count) != "FROM"){
			throw  "KeyWord \"From\" Not Found";
		}
		count++;
		vector<string> table = split(allwords.at(count), ",");//获取表名
		if (selectallcolumns){//如果是select * ，则将所有表中的所有列放进TC中
			for (int i = 0; i < table.size(); i++){
				TableColumn temp;
				if (TableManager.hasTable(table.at(i))){
					temp.tableName = table.at(i);
					vector<string> Column = TableManager.getColumnbyTable(temp.tableName);
					for (int j = 0; j < Column.size(); j++){
						temp.colunmName = Column.at(j);
						TC.push_back(temp);
					}
				}
				else{
					throw  "Table" + table.at(i) + " Not Found" ;
				}
		}
		}
		count++;
		if (allwords.size()>count){
		if (allwords.at(count) != "where"&&allwords.at(count) != "WHERE"){
				throw  "Keyword Where Not Found";
		}
		count++;
		}
		vector<string> equations = split(allwords.at(count), ",");//条件用,分词
		vector<Condition> conds;
		for (int i = 0; i < equations.size(); i++)
		{

			conds.push_back(Transcond(equations.at(i)));
		} 
		op = new QueryOperation(TC, table, conds);
	}
	else if(type == "CREATE" || type == "create")//creat table by TZH//分词时注意类型表名后面必须接 空格；主键不能接空格，必须直接接括号
		{
			string tableName = "";//
			vector<string> allwords = split(t, " (", ") ");
			/*for (int i = 0; i < allwords.size(); i++)
			cout << allwords.at(i) << endl;*/
			vector<string> firstPart = split(allwords.at(0), " ");
			tableName = firstPart.at(2);//third word is the table name
			//cout << tableName << endl;

			if (TableManager.hasTable(tableName))
			{
				throw "Table already exist!";
			}

			vector<string> columnAndType = split(allwords.at(1), ",");
			vector<ColumnTitle> CTs;

			for (int i = 0; i < columnAndType.size() - 1; i++)
			{
				CTs.push_back(TransCandT(columnAndType.at(i)));
				//cout << columnAndType.at(i) << endl;
			}

			string keyCmp = split(columnAndType.at(columnAndType.size() - 1), "(", ")").at(0);
			if ("primary key" != keyCmp && keyCmp != "PRIMARY KEY"){
				throw  "Illegal input,need primary key";
			}
			string primaryKey = split(columnAndType.at(columnAndType.size() - 1), "(", ")").at(1);

			//cout << "primary key:" << primaryKey;


			op = new CreateOperation(tableName, CTs, primaryKey);

			//to manage the table list
			TableInfo newtableinfo(CTs, tableName, primaryKey);
			TableManager.addTable(newtableinfo);
		}
	else if (type == "INSERT" || type == "insert")
	{
		string tableName = "";//
		vector<Data> datas;
		vector<ColumnTitle> titles;
		vector<string> allwords = split(t, " values ");
		/*for (int i = 0; i < allwords.size(); i++)
		cout << allwords.at(i) << endl;*/
		vector<string> firstPart = split(allwords.at(0), " ");
		tableName = firstPart.at(2);//third word is the table name

		if (!TableManager.hasTable(tableName))
		{
			throw "Table "+tableName+"is not exist!";
		}

		vector<string> stringDatas = split(allwords.at(1), ",", "'", "(", ")");

		for (int i = 0; i < stringDatas.size(); i++)
		{
			datas.push_back(Data((DataType)0, stringDatas.at(i)));
			//cout << columnAndType.at(i) << endl;
		}
		Data primaryData;

		vector<string> realTitle = TableManager.getColumnbyTable(tableName);
		int size = realTitle.size();

		for (int j = 0; j < size; j++)
		{
			if (TableManager.getPrimaryKey(tableName).column_name == realTitle.at(j))//todo
			{
				primaryData = Data(TableManager.getPrimaryKey(tableName).datatype, stringDatas.at(j));
			}
		}

		if (firstPart.size() == 4)//to support title input
		{
			vector<string> stringTitle = split(firstPart.at(3), ",", " ", "(", ")");
			if (stringTitle.size() != stringDatas.size())
				throw "numbers of column is not equal to numbers of data";
			
			for (int j = 0; j < stringTitle.size(); j++)
			{
				bool flag = false;
				for (int i = 0; i < size; i++)
				{
					if (realTitle.at(i) == stringTitle.at(j))
					{
						titles.push_back(ColumnTitle(stringTitle.at(j), (DataType)0));
						flag = true;
					}					
				}
				if (!flag)
					throw "error column " + stringTitle.at(j) + "not exist";
			}

			op = new InsertOperation(tableName, titles, datas,primaryData);
			/*cout << "columnname" << endl;
			for (int i = 0; i < titles.size(); i++)
			{
				cout << titles.at(i).column_name << endl;
			}*/
		}

		
		//cout << tableName << endl;
		//cout << tableName << endl;



		/*cout << "data test" << endl;
		for (int i = 0; i < datas.size(); i++)
		{
			cout << datas.at(i).data << "///" << endl;
		}*/
		else
		{
			if (realTitle.size() == datas.size())
				op = new InsertOperation(tableName, datas, primaryData);//todo
			else
				throw "error number of values";

		}
		
	}
	else if (type == "DELETE" || type == "delete")
	{

	}
	return op;
}

int main()
{
	/*parser("select ab,c,d from e,f where ab>1");*/
	freopen("in2.txt", "r", stdin);
	cout << "MIniBase Beta 0.9\n";
	string input;
	while (!cin.eof()){
		//cout << "MIniBase>";
		getline(cin, input);
		try{
			Operation* operation = parser(input);
			//operation->exec();
			Table& result = operation->exec();
			//cout << "success! " << result.data.size() << " rows affected\n";
			//cout << "--------" << result.tableName <<"------------"<< endl;
			
			result.showTable();

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


