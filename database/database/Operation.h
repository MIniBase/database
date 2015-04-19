#include <string>
#include <vector>
#include <map>
using std::string;
using std::vector;
using std::pair;
typedef pair<string, string> ColumnAndTable; //�к����ڵı�
typedef pair<ColumnAndTable, ColumnAndTable> Equation;// �����е���ȹ�ϵ
typedef vector<string> record;
struct RecordSet{
	vector<ColumnAndTable> titles; //��¼�ı�ͷ
	vector<record> data; //����
};
class Operation{
public:
	virtual RecordSet exec() = 0;
};