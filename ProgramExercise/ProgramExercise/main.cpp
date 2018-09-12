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

using namespace std;

//extern int GlobalVal;

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
		int retNum = 0;  //���صĽ��
		bool carry = false;   //�Ƿ��λ
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

	//�Ż��汾
	int Add_1(int num1, int num2) 
	{
		while (num2 != 0) 
		{
			int temp = num1 ^ num2;   //������ӵĸ�λ��û�н�λ
			num2 = (num1&num2) << 1;  //�����λֵ
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
				if (res > INT_MAX || res < INT_MIN)return 0;   //����������
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
		//����ķ�������Ҫ�������ռ䣬ʹ�����鱾����б�ǣ��������±�����¼����Ϊ����Ԫ�ط�Χ��0-(length-1)
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
		//����ķ�������ʹ�õݹ飬�����Ϊ�������
		if (*str == '\0')
		{
			if (*pattern == '\0' || (*(pattern + 1) == '*'&&*(pattern + 2) == '\0')) //�մ��͡�b*����ƥ���
				return true;
			else return false;
		}
		if (*pattern == '\0')
			return false;
		if (*(pattern + 1) == '*') 
		{
			if (*pattern == *str || *pattern == '.')
				return match(str + 1, pattern) || match(str, pattern + 2);
			//���������һ���ǳ��ִ�������0���Ǿ���str+1��pattern����;��һ���ǳ��ִ�������0
			else return match(str, pattern + 2);//������Ҫ�󣬵������ִ���Ϊ0
		}
		if (*pattern == *str || *pattern == '.')
			return match(str + 1, pattern + 1);
		return false;
	}

	bool isNumeric(char* string)
	{
		if (*string == '\0')return false;
		bool bHasOp = false; //�Ƿ���+-�����
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

	//operator= ����Ϊ��Ա����
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
	cout << ">>>>>>���Թ�������˳��<<<<<<" << endl;
	Derive derive;
	
}

void fun_1()
{
	cout << ">>>>>>���Զ�̬�¹�������<<<<<<" << endl;
	Base* base = new Derive;
	delete base;
}

void fun_2()
{
	cout << ">>>>>>���Թ��캯���ڶ�̬<<<<<<" << endl;
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
	cout << ">>>>>>��Դ������<<<<<<" << endl;
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
/// ����namespace���ļ�
///</summary>
void fun_6()
{
	//���Զ��ļ�namespace��������
	FunLibrary::namespaceFun_1();

	FunLibrary::namespaceFun_2();
}

//���Զ���
template<int  T>
void fun_7()
{
	cout << ">>>>>>���Զ���<<<<<<" << endl;
	const int a = 6;
	static_assert(a == T, "wrong!");
	cout << ">>>>>>>�������<<<<<<" << endl;
}

void fun_8()
{
	cout << ">>>>>>�̳�����<<<<<<<" << endl;
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
	//����ָ���ʹ��
	typedef tr1::function<void(int)> FunPtr;
	typedef	void(*FunPtr_1)(int);

	//���ں���ָ��
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
	int* a = 0;
	a += 6;
	cout << a << endl;
}

struct AlignTest
{
	char a;
	int b;
	char c[9];
};

int main()
{
	Solution A;
	std::string str = "123486";
	auto iter = str.end();
	int* res = new int(5);
	int* a = (int*)malloc(sizeof(int));
	*a = 10;
	char charStr[20] = "aaa";
	char charPat[20] = "ab*a";
	char charNum[] = "123.45e+6";

	cout << A.LastRemaining_Solution(5, 2) << endl;
	cout << A.Add(100,50) << endl;
	cout << A.StrToInt(str)<< endl;
	cout << *res << endl;
	cout << *a << endl;

	fun_0();
	fun_1();
	fun_2();
	fun_4();
	
	cout << endl;
	cout << strlen(charStr) << endl;

	if (A.match(charStr, charPat))
		cout << "ƥ��ɹ�" << endl;
	else cout << "ƥ��ʧ��" << endl;

	if (A.isNumeric(charNum))
		cout << "������" << endl;
	else cout << "��������" << endl << endl;

	delete res;
	free(a);

	/*int m, n;
	cin >> n >> m;
	if (n<2 || n>1e10)return;
	if (m < 1)return;
	if (n % (2 * m))return;

	int couples = n / (2 * m);
	cout << couples * m * m;*/

	//vector<vector<int>> vec;
	int numbers[10] = { 1,2,3,4,5,6,7,8,9,10 };
	vector<int> numVec(numbers, numbers + 10);
	numVec.push_back(2);
	for (auto it : numVec)
	{
		cout << it << ' ';
	}
	cout << endl;

	//fun_7<5>();
	fun_8();
	fun_10();

	cout << GlobalVal << endl;

	string sortStr = "BCDAGF";
	sort(sortStr.begin(), sortStr.end());

	cout << sortStr << endl;
	cout << sizeof(AlignTest) << endl;

	int num = 10;
	int* p = &num;
	*p = 5;
	cout << *p << endl;
	system("pause");
	//getchar();
	return 0;
}