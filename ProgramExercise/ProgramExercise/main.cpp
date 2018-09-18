#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <mutex>
#include <set>
#include <queue>
#include "FunDeclare_1.h"
#include "FunDeclare_2.h"
#include <assert.h>
#include <intsafe.h>
#include <utility>
#include <map>


using namespace std;

// 全局变量可以多次声明，但是不能多次定义
extern int GlobalVal;
//int GlobalVal = 6;

struct ListNode
{
	int val;
	struct ListNode *next;
	ListNode(int x) :
		val(x), next(NULL) 
	{}
};

class Solution
{
public:
	int LastRemaining_Solution(int n, int m)
	{
		if (n <= 1)return n;
		vector<int> stuNum;
		for (int i = 0; i < n; ++i)
		{
			stuNum.push_back(i);
		}

		int start = 0;
		while (stuNum.size() > 1)
		{
			int curNum = stuNum.size();
			//int removeStu = curNum % m ? curNum % m-1 : curNum-1 + start;
			//start = removeStu - 1;

			int removeStu = start + m;
			removeStu = removeStu % curNum;
			if (removeStu == 0)removeStu = curNum;
			stuNum.erase(stuNum.begin() + removeStu - 1);
			start = removeStu - 1;
			if (start < 1)
				start = stuNum.size();
		}

		return stuNum[0];
	}

	int Sum_Solution(int n)
	{
		int ans = n;
		ans && (ans += Sum_Solution(n - 1));
		return ans;
	}

	int Add(int num1, int num2)
	{
		int numWidth = 8 * sizeof(int);
		int retNum = 0;  //返回的结果
		bool carry = false;   //是否进位
		for (int i = 0; i < numWidth; ++i)
		{
			int num1Bit = (num1 >> i) & 1;
			int num2Bit = (num2 >> i) & 1;
			int tmp = 0;
			if (!num1Bit && !num2Bit)
			{
				if (carry)
					tmp = 1 << i;
				else
					tmp = 0 << i;

				carry = false;
			}
			else if (num1Bit && num2Bit)
			{
				if (carry)
					tmp = 1 << i;
				else
					tmp = 0 << i;
				carry = true;
			}
			else
			{
				if (carry)
				{
					carry = true;
					tmp = 0 << i;
				}
				else
				{
					tmp = 1 << i;
					carry = false;
				}
			}

			retNum |= tmp;
		}
		return retNum;
	}

	//优化版本
	int Add_1(int num1, int num2) 
	{
		while (num2 != 0) 
		{
			int temp = num1 ^ num2;   //计算相加的各位，没有进位
			num2 = (num1&num2) << 1;  //计算进位值
			num1 = temp;
		}
		return num1;
	}

	int StrToInt(string str)
	{
		if (str.size() == 0)return 0;

		int res = 0, digits = 1;
		int length = str.length();
		for (int i = length - 1; i >= 0; --i)
		{
			if (str[i] >= '0' && str[i] <= '9')
			{
				res += (str[i] - '0')*digits;
				digits *= 10;
				if (res > INT_MAX || res < INT_MIN)return 0;   //考虑溢出情况
			}
			else
			{
				if (str[i] != '-'&&str[i] != '+')
					return 0;
				if (i == 0 && str[i] == '-')
					res = -res;

			}
		}


		return res;
	}

	// Parameters:
	//        numbers:     an array of integers
	//        length:      the length of array numbers
	//        duplication: (Output) the duplicated number in the array number
	// Return value:       true if the input is valid, and there are some duplications in the array number
	//                     otherwise false
	bool duplicate(int numbers[], int length, int* duplication) 
	{
		//下面的方法不需要申请额外空间，使用数组本身进行标记，用数组下标来记录，因为数组元素范围在0-(length-1)
		for (int i = 0; i < length; i++) 
		{
			int index = numbers[i];

			if (index >= length) 
			{
				index -= length;
			}

			if (numbers[index] >= length) 
			{
				*duplication = index;
				return true;
			}

			numbers[index] = numbers[index] + length;
		}

		return false;
	}

	vector<int> multiply(const vector<int>& A) 
	{
		vector<int> res;
		if ((int)A.size() == 0)return res;
		int multiAll = 1;
		for (int i = 0; i < (int)A.size(); multiAll *= A[i++])
		{
			res.push_back(multiAll);
		}

		multiAll = 1;
		for (int j = (int)A.size() - 1; j >= 0; multiAll*=A[j--])
		{
			res[j] *= multiAll;
		}

		return res;
	}

	//字符串匹配
	bool match(char* str, char* pattern)
	{
		int patLen = strlen(pattern);
		int strLen = strlen(str);
		if (strLen == 0 && patLen == 0)return false;
		int patIndex = 0;
		char preChar;

		for (int i = 0; i < strLen; ++i)
		{
			if (patIndex < patLen)
			{
				if (pattern[patIndex] == '.')
				{
					patIndex++;
					continue;
				}
				if (pattern[patIndex] == '*')
				{
					if (patIndex > 0 && pattern[patIndex - 1] != '.'&&pattern[patIndex - 1] != '*')
					{
						preChar = pattern[patIndex - 1];
					}
					if (str[i] == preChar)
					{
						if (i == (strLen - 1) && patIndex == (patLen - 1))return true;
						continue;
					}
					if (str[i] != preChar)
					{
						i--;
						patIndex++;
						continue;
					}
				}
				if (str[i] == pattern[patIndex])
				{
					if (i == (strLen - 1) && patIndex == (patLen - 1))return true;
					patIndex++;
					continue;
				}
				else
				{
					if (patIndex + 1 < patLen && pattern[patIndex + 1] == '*')
					{
						i--;
						patIndex++;
						continue;
					}
						 
					return false;
				}
			}
		}

		return false;
	}

	bool match_1(char* str, char* pattern)
	{
		//下面的方法就是使用递归，代码更为简洁清晰
		if (*str == '\0')
		{
			if (*pattern == '\0' || (*(pattern + 1) == '*'&&*(pattern + 2) == '\0')) //空串和“b*”是匹配的
				return true;
			else return false;
		}
		if (*pattern == '\0')
			return false;
		if (*(pattern + 1) == '*') 
		{
			if (*pattern == *str || *pattern == '.')
				return match(str + 1, pattern) || match(str, pattern + 2);
			//两种情况，一种是出现次数大于0，那就是str+1，pattern不变;另一种是出现次数等于0
			else return match(str, pattern + 2);//不符合要求，当做出现次数为0
		}
		if (*pattern == *str || *pattern == '.')
			return match(str + 1, pattern + 1);
		return false;
	}

	bool isNumeric(char* string)
	{
		if (*string == '\0')return false;
		bool bHasOp = false; //是否有+-运算符
		bool bHasDot = false;
		bool bHasE = false;
		if (*string == '+' || *string == '-') { string++; bHasOp = false; }
		while (*string != '\0')
		{
			//if ((*string<'0' || *string>'9') && *string != 'e' && *string != 'E' && *string !='.')return false;

			/*if ((*string == '+' || *string == '-')&& !bHasOp && *string != 'e'&&*string != 'E')return false;

			if (*string == '.'&&(bHasDot||bHasOp))return false;
			else if (*string == '.' && (!bHasOp&&*(string - 1) < '0'&&*(string - 1) > '9')&&*(string + 1) < '0'&&*(string + 1) > '9'))return false;
			else { bHasDot = true; }*/

			if (*string == '+' || *string == '-')
			{
				if (*(string - 1) != 'e' && *(string - 1) != 'E')
					return false;
				string++;
				continue;
			}

			if (*string == '.')
			{
				if (bHasE)return false;
				if (bHasDot)return false;
				else bHasDot = true;

				string++;
				continue;
			}

			if (*string == 'e' || *string == 'E')
			{
				if (bHasE)return false;
				else bHasE = true;

				if (*(string + 1) == '\0')return false;

				string++;
				continue;
			}

			if (*string<'0' && *string>'9')return false;
			string++;
		}

		return true;
	}

	queue<char> curOnce;
	int monitor[128] = {0};

	//Insert one char from stringstream
	void Insert(char ch)
	{
		monitor[ch - '\0']++;
		if (monitor[ch - '\0'] == 0)
		{
			curOnce.push(ch);
		}
	}
	//return the first appearence once char in current stringstream
	char FirstAppearingOnce()
	{
		while (!curOnce.empty() && monitor[curOnce.front()] >= 2) curOnce.pop();
		if (curOnce.empty()) return '#';
		return curOnce.front();
	}

	ListNode* EntryNodeOfLoop(ListNode* pHead)
	{
		if (pHead == NULL)return NULL;

		vector<ListNode*> traceNodes;
		set<ListNode*> nodes;
		while (pHead != NULL)
		{
			if (pHead == NULL)return NULL;
			
			pair<set<ListNode*>::iterator, bool> res = nodes.insert(pHead);
			if (!res.second)return pHead;
			pHead = pHead->next;
		}
	}
};

// 下面是对C++基础测试代码
class Base
{
public:
	Base()
	{
		cout << "Base Construct" << endl;
		init();
	}

	virtual void ConstructFun()
	{
		cout << "Base ConstructFun" << endl;
	}

	void init()
	{
		ConstructFun();
	}

	virtual void implFun()
	{
		cout << "Base Fun" << endl;
	}

	void implFun(int a)
	{
		cout << "Base Overload" << endl;
	}

	virtual void defaultParam(int i = 0)
	{

	}

	//operator= 必须为成员函数
	Base& operator=(Base& Obj)
	{

	}

	virtual ~Base()
	{
		cout << "Base Destroy" << endl;
	}
};


class Derive :public Base 
{
public:
	//using Base::implFun;
	typedef void (Derive::*FunPtr)();
	
	Derive()
	{
		cout << "Derive Condtruct" << endl;
	}

	void ConstructFun()
	{
		cout << "Derive ConstructFun" << endl;
	}

	void fun(int i) {}

	void implFun()
	{
		cout << "Derive Fun" << endl;
	}

	void defaultParam(int i /* = 0 */)
	{
		cout << i << endl;
	}

	~Derive()
	{
		cout << "Derive Destroy" << endl;
	}
};



template<class T>
class Resource
{
public:
	Resource(T val)
	{
		ResourceHandle = val;
	}

	operator T()const 
	{
		return ResourceHandle;
	}
private:
	T ResourceHandle;
};

void fun_0()
{
	cout << ">>>>>>测试构造析构顺序<<<<<<" << endl;
	Derive derive;
	
}

void fun_1()
{
	cout << ">>>>>>测试多态下构造析构<<<<<<" << endl;
	Base* base = new Derive;
	delete base;
}

void fun_2()
{
	cout << ">>>>>>测试构造函数内多态<<<<<<" << endl;
	Base* base = new Derive;
	delete base;
}

void fun_3()
{
	mutex A;
	std::shared_ptr<int> integerPtr(new int(5)); 
	std::shared_ptr<int> integerPtr_1(std::shared_ptr<int>(new int(4)));

}

void fun_4()
{
	cout << ">>>>>>资源管理类<<<<<<" << endl;
	Resource<int> A = 5;

	int B = A;
	cout << B << endl;
}

void fun_5()
{
	set<int> s;
	s.insert({ 1,2,3 });
	set<int>::iterator sI;
	auto a = s.insert(2);
	pair<set<int>::iterator, bool> b = s.insert(6);
}

///<summary>
/// 测试namespace多文件
///</summary>
void fun_6()
{
	//测试多文件namespace方法测试
	FunLibrary::namespaceFun_1();

	FunLibrary::namespaceFun_2();
}

//测试断言
template<int  T>
void fun_7()
{
	cout << ">>>>>>测试断言<<<<<<" << endl;
	const int a = 6;
	static_assert(a == T, "wrong!");
	cout << ">>>>>>>测试完毕<<<<<<" << endl;
}

void fun_8()
{
	cout << ">>>>>>继承重载<<<<<<<" << endl;
	//Derive A;
	//A.implFun();
	//A.implFun(5);

	Base* B = new Derive;
	B->implFun();

	Derive C;
	C.implFun();
	C.Base::implFun();

	class LocalClass{};
	cout << sizeof(Base) << endl;
	cout << sizeof(Derive) << endl;
	cout << sizeof(LocalClass) << endl;
	delete B;
}

void fun_9()
{
	//函数指针的使用
	typedef tr1::function<void(int)> FunPtr;
	typedef	void(*FunPtr_1)(int);

	//类内函数指针
	typedef void(Derive::*FunPtr_2)(int);
	//FunPtr a = fun_6;
	//FunPtr_1 b = fun_6;
	//b();

	Derive A;
	FunPtr c = std::bind(&Derive::fun, A, placeholders::_1);

	class TestClass
	{
	public:
		void fun(int) {};
	};

	typedef tr1::function<void(TestClass, int) > FunPtr_Member;

	tr1::function<void()> STLFun = []() {cout << "lambda" << endl; };
}

void fun_10()
{
	Derive A;
	Base* B = &A;
	
	//下面可知缺省参数 会继承于基类，不是动态的
	B->defaultParam();
	//使用引用 实现多态，  
	//注意引用也可以实现多态
	Base& C = A; 
	C.defaultParam();
}

void GetMaxMultiRes()
{
	int stuNum = 0;
	vector<int> stuAbility;
	int k = 0, d = 0;
	int multiRes = 1;

	cin >> stuNum;
	stuAbility.resize(stuNum);
	for (int i = 0; i < stuNum; ++i)
		cin >> stuAbility[i];
	
	cin >> k >> d;

	vector<tuple<int, int>> curStus; //用来记录当前符合条件的数组
	curStus.resize(k);
	//初始化该数组
	for (int i = 0; i < k; ++i)
	{
		curStus[i] = tuple<int, int>(i, stuAbility[i]);
		multiRes *= stuAbility[i];
	}
		
	for (int i = k; i < stuNum; ++i)
	{

	}
}

void EnCodeString()
{
	string str, res;
	cin >> str;

	char tmp = str[0];
	int repeatLen = 1;
	for (int i = 1; i < str.length(); ++i)
	{
		if (str[i] == tmp)
		{
			repeatLen++;
		}
		else 
		{
			res += ('0' + repeatLen);
			res += tmp;
			tmp = str[i];
			repeatLen = 1;
		}

		if (str[i + 1] == '\0')
		{
			res += ('0' + repeatLen);
			res += tmp;
		}
	}

	cout << res;
}

void GetMaxSum()
{
	//vector<vector<int>> arrays;
	int N, D;
	cin >> N >> D;
	vector<vector<int>> arrays(N, vector<int>(N));
	
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			cin >> arrays[i][j];

	int maxSum = 0;
	//横向、纵向
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N - D + 1; ++j)
		{
			int tmp1 = 0, tmp2 = 0;
			for (int k = 0; k < D; ++k)
			{
				tmp1 += arrays[i][j + k];
				tmp2 += arrays[j + k][i];
			}
				
			maxSum = max(maxSum, max(tmp1, tmp2));
		}
	}

	//左上->左下，右上->右下
	for (int i = D - 1; i < N; ++i)
	{
		for (int j = 0; j < i - D + 1; ++j)
		{
			int tmp1 = 0, tmp2 = 0, tmp3 = 0, tmp4 = 0;
			for (int k = 0; k < D; ++k)
			{
				int x = j + k;
				int y = i - j - k;
				tmp1 += arrays[x][y];
				tmp2 += arrays[N - 1 - x][y];
				tmp3 += arrays[N - 1 - x][N - 1 - y];
				tmp4 += arrays[x][N - 1 - y];

				maxSum = max(maxSum, max(max(tmp1, tmp2), max(tmp3, tmp4)));
			}
		}
	}

	cout << maxSum;
}

//typedef pair<int, int> pos;
//
//int N, M;
//pos playerPos;
//pos boxPos;
//pos destPos;
//
//vector<vector<int>> map;
//
//int GetMinPath(int i, int j)
//{
//	//if(i>)
//	return 0;
//}
//
//
////推箱子
//void PushBox()
//{
//	cin >> N >> M;
//	vector<vector<int>> map (N, vector<int>(M));
//	for (int i = 0; i < N; ++i)
//		for (int j = 0; j < M; ++j)
//		{
//			cin >> map[i][j];
//			if (map[i][j] == 'X')
//				playerPos = pos(i, j);
//			if (map[i][j] == '@')
//				destPos = pos(i, j);
//			if (map[i][j] == '*')
//				boxPos = pos(i, j);
//		}
//}
//

// 多个整数组成最大整数
bool stringSort(string a, string b)
{
	if (a + b >= b + a)return true;
	else return false;
}

void maxNumberFromStrings()
{
	int numCounts = 0;
	char space;
	while (cin >> numCounts)
	{
		vector<string> strs(numCounts);
		for (int i = 0; i < numCounts; ++i)
		{
			int num = 0;
			cin >> num;
			//这里不需要检测空格，空格会自动跳过
			/*if (i != numCounts - 1)
				cin >> space;*/

			strs[i] = to_string(num);
		}

		sort(strs.begin(), strs.end(), stringSort);

		string tmp;
		for (auto it : strs)
		{
			tmp += it;
		}
		cout << tmp;
	}
}

int getTreeHeightImpl(int father, int index, vector<pair<int, int>>& nodes)
{
	int size = nodes.size();
	int left = 0, right = 0;
	for (int i = index; i < size; ++i)
	{
		if (nodes[i].first == father)
		{
			left = getTreeHeightImpl(nodes[i].second, i, nodes);
			if (i + 1 < size && nodes[i + 1].first == father)
			{
				right = getTreeHeightImpl(nodes[i + 1].second, i + 1, nodes);
			}
			break;
		}
	}

	return max(left, right) + 1;
}
//求树的高度
void getTreeHeight()
{
	typedef pair<int, int> node;
	int treeNodes = 0;
	cin >> treeNodes;
	vector<node> allNodes(treeNodes);

	for (int i = 0; i < treeNodes - 1; ++i)
		cin >> allNodes[i].first >> allNodes[i].second;

	cout << getTreeHeightImpl(0, 0, allNodes);
}

void reverseString()
{
	string str, tmp, ret;
	while (cin >> str)
	{
		ret = ' ' + str + ret;


		if (getchar() == '\n')break;
		//cout << "loop";
	}

	ret.erase(0,1);
	/*for (int i = 0; i < str.length(); ++i)
	{
		if (str[i] == ' ')
		{
			ret = ' ' + tmp + ret;
			tmp.clear();
			continue;
		}
		
		tmp += str[i];
	}

	if (tmp.size())ret = tmp + ret;*/

	cout << ret;
}

//计算分身
void getNumber()
{
	int T;
	while (cin >> T)
	{
		string input;
		while (T--)
		{
			cin >> input;
			map<char, size_t> help;
			for (auto& t : input)
			{
				help[t] += 1;
			}
			vector<size_t> count(10);
			count[0] = help['Z'];            //ZERO
			count[2] = help['W'];            //TWO
			count[4] = help['U'];            //FOUR
			count[1] = help['O'] - count[0] - count[2] - count[4];     //ONE
			count[6] = help['X'];            //SIX
			count[8] = help['G'];            //EIGHT
			count[3] = help['T'] - count[2] - count[8];        //TRHEE
			count[5] = help['F'] - count[4];            //FIVE
			count[7] = help['V'] - count[5];            //SEVEN
			count[9] = help['I'] - count[6] - count[5] - count[8];   //NINE          //NINE
			vector<size_t> numsBefore(10);
			for (size_t i = 0; i < 10; i++)
				numsBefore[(i + 2) % 10] = count[i];//号码还原
			for (size_t i = 0; i < 10; i++)
			{
				for (int j = 0; j < numsBefore[i]; j++)
					cout << i;
			}
			cout << endl;
		}
	}
}

void fun_11()
{
	int* a = 0;
	a += 6;
	cout << a << endl;
}

//结构体/类 对齐测试
struct AlignTest
{
	char a;
	int b;
	char c[9];
};

class D
{
public:
	D()
	{

	}

	static int b;
};

int D::b = 0;

int main()
{
	//Solution A;
	//std::string str = "123486";
	//auto iter = str.end();
	//int* res = new int(5);
	//int* a = (int*)malloc(sizeof(int));
	//*a = 10;
	//char charStr[20] = "aaa";
	//char charPat[20] = "ab*a";
	//char charNum[] = "123.45e+6";

	//cout << A.LastRemaining_Solution(5, 2) << endl;
	//cout << A.Add(100,50) << endl;
	//cout << A.StrToInt(str)<< endl;
	//cout << *res << endl;
	//cout << *a << endl;

	//fun_0();
	//fun_1();
	//fun_2();
	//fun_4();
	//
	//cout << endl;
	//cout << strlen(charStr) << endl;

	//if (A.match(charStr, charPat))
	//	cout << "匹配成功" << endl;
	//else cout << "匹配失败" << endl;

	//if (A.isNumeric(charNum))
	//	cout << "是数字" << endl;
	//else cout << "不是数字" << endl << endl;

	//delete res;
	//free(a);

	///*int m, n;
	//cin >> n >> m;
	//if (n<2 || n>1e10)return;
	//if (m < 1)return;
	//if (n % (2 * m))return;

	//int couples = n / (2 * m);
	//cout << couples * m * m;*/

	////vector<vector<int>> vec;
	//int numbers[10] = { 1,2,3,4,5,6,7,8,9,10 };
	//vector<int> numVec(numbers, numbers + 10);
	//numVec.push_back(2);
	//for (auto it : numVec)
	//{
	//	cout << it << ' ';
	//}
	//cout << endl;

	//fun_8();
	//fun_10();

	//cout << GlobalVal << endl;

	//string sortStr = "BCDAGF";
	//sort(sortStr.begin(), sortStr.end());

	//cout << sortStr << endl;
	//cout << sizeof(AlignTest) << endl;

	//int num = 10;
	//int* p = &num;
	//*p = 5;
	//cout << *p << endl;

	////char str2[] = { 'a','b','c','d' };  //错误，由于没有'\0'结束符
	//char str3[] = { 'a','b','c','d','\0' };  //正确
	//char str4[] = "abcd";                 //正确，直接申请的字符串，不需要 '\0'
	//char* str5 = str4;
	////str3 = str5;           //错误，此时str3是个常量，不能被更改，但是它所指的值是可以改变的
	//str5[1] = 'B';
	//cout << ++str5 << endl;  //正确
	////cout << ++str4 << endl;  //错误
	//int nums[] = { 1,2,3,4,5 };
	//int* numsPtr = nums;
	//cout << *nums << endl;
	//cout << *(++numsPtr) << endl;
	//GetMaxMultiRes();
	//EnCodeString();
	//GetMaxSum();
	//fun_10();

	/*int num = 2;
	void* arg = (void*)(&num);

	int b = 0; 
	b += num++;
	cout << b << endl;

	b = num++;
	cout << b << endl;*/

	//畅游笔试题
	/*typedef pair<int, int> pos;
	pos playerPos;
	int npcNum = 0;
	string npcPos_str;
	cin >> playerPos.first >> playerPos.second;
	cin >> npcNum;
	cin >> npcPos_str;
	npcPos_str += ',';
	vector<pos> npcPos(npcNum,pos(0,0));
	int dotIndex = 0;
	int fastNpc = 0;
	int minDistance = 10000000;
	for (int i = 0; i < npcNum; ++i)
	{
		int tmp = 0;
		tmp = npcPos_str.find(',', dotIndex);
		int posX = 0;
		sscanf_s(npcPos_str.substr(dotIndex, tmp - dotIndex).c_str(), "%d", &posX);
		
		dotIndex = tmp + 1;
		tmp = npcPos_str.find(',', dotIndex);
		int posY = 0;
		sscanf_s(npcPos_str.substr(dotIndex, tmp - dotIndex).c_str(), "%d", &posY);
		dotIndex = tmp + 1;
		npcPos[i].first = posX;
		npcPos[i].second = posY;

		int tmpDis = abs(posX - playerPos.first)*abs(posX - playerPos.first) + abs(posY - playerPos.second)*abs(posY - playerPos.second);
		if (tmpDis < minDistance)
		{
			minDistance = tmpDis;
			fastNpc = i;
		}
	}

	cout << "(" << npcPos[fastNpc].first << "," << npcPos[fastNpc].second << ")";
*/

	//int n, K;
	//cin >> n >> K;

	//int curMin = 0;

	//int a, b;
	//char c;
	//cin >> a >> c >> b;
	//cout << a << " " << b << endl;

	//maxNumberFromStrings();

	//getTreeHeight();
	//reverseString();
	
	class Test
	{
	public:
		int a = 0;
	private:
		int b = 1;
	};

	class VirtualBaseClass
	{
	public:
		virtual void fun() {};
	};

	class VirtualDeriveClass :VirtualBaseClass
	{
	public:
		virtual void fun() {};
	};

	class A
	{
	public:
		int a = 1;
	};

	class B
	{
	public:
		int b = 2;
	};

	class C :public A, public B
	{

	};

	
	/*int num = -123559;
	for (int i = 0; i < sizeof(int) * 8; ++i)
	{
		int tmp = num >> i;
		tmp &= 1;
		cout << tmp;
	}
	cout << endl;

	num = 123559;
	for (int i = 0; i < sizeof(int) * 8; ++i)
	{
		int tmp = num >> i;
		tmp &= 1;
		cout << tmp;
	}
	cout << endl;
	cout << sizeof(string) << endl;*/

	C c;
	A* a = (A*)(&c);
	cout << a->a << endl;

	cout << sizeof(VirtualDeriveClass) << endl;
	/*Test A;
	Test* B = &A;
	int* tmp = (int*)B;
	tmp++;
	*tmp += 2;
	cout << *tmp << endl;*/

	system("pause");
	return 0;
}