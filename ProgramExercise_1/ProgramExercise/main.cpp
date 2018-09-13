#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <numeric>
#include <map>
#include "haiaimiStuff.h"
#include <stack>
#include <queue>

using namespace std;

struct TreeNode 
{
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
		val(x), left(NULL), right(NULL) 
	{}
};

struct RandomListNode
{
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) 
	{}
};

struct ListNode 
{
	int val;
	struct ListNode *next;
	ListNode(int x) :
		val(x), next(NULL) 
	{}
};

struct TreeLinkNode 
{
	int val;
	struct TreeLinkNode *left;
	struct TreeLinkNode *right;
	struct TreeLinkNode *next;
	TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {

	}
};

bool CompareVectorNum(vector<int> i, vector<int> j)
{
	return i.size() > j.size();
}

class Solution
{
public:
	bool VerifySquenceOfBST(vector<int> sequence) 
	{
		if (sequence.empty())
			return false;

		if (sequence.size() == 1)
			return true;

		int last = sequence.back();

		vector<int> left, right;
		left.clear();
		right.clear();

		bool bCanAddToLeft = true;
		auto iterLast = --sequence.cend();

		for (auto iter = sequence.cbegin(); iter != iterLast; iter++)
		{
			if (*iter < last)
			{
				left.push_back(*iter);

				if (!bCanAddToLeft)
					return false;
			}
			else
			{
				right.push_back(*iter);
				bCanAddToLeft = false;
			}
		}

		if (left.empty())
			return VerifySquenceOfBST(right);
		else if (right.empty())
			return VerifySquenceOfBST(left);
		else
			return VerifySquenceOfBST(left) && VerifySquenceOfBST(right);
	}

	void Accumulate(TreeNode* root, int expectNumber)
	{
		if (Temp.empty())
		{
			vector<int> first = { root->val };
			Temp.push_back(first);
		}
		else
		{
			if (root)
				Temp.back().push_back(root->val);
		}

		if (!root->left && !root->right)
		{
			int sum = accumulate(Temp.back().begin(), Temp.back().end(), 0);
			Temp.push_back(Temp.back());

			if (sum != expectNumber)
			{
				Temp.erase(--Temp.end());
			}

			Temp.back().erase(--Temp.back().end());

			return;
		}

		if (root->left)
			Accumulate(root->left, expectNumber);

		if (root->right)
			Accumulate(root->right, expectNumber);

		Temp.back().erase(--Temp.back().end());
	}

	vector<vector<int> > FindPath(TreeNode* root, int expectNumber) 
	{
		Temp.clear();
		
		Accumulate(root, expectNumber);

		sort(Temp.begin(), Temp.end(), CompareVectorNum);

		for (auto iter = Temp.begin(); iter != Temp.end(); iter++)
		{
			if ((*iter).size() == 0)
			{
				Temp.erase(iter);
				break;
			}
		}
        
		return Temp;
	}

	RandomListNode* Clone(RandomListNode* pHead)
    {	
		if (!pHead) return NULL;
        RandomListNode *cur = pHead;

        while(cur)
		{
			// 在原来的链表中添加新节点，就是重复上一个节点 如A,A*,B,B*,C,C*
            RandomListNode *node = new RandomListNode(cur->label);
            node->next = cur->next;    //
            cur->next = node;
            cur = node->next;
        }//直到cur指向了原先链表的结尾null处

		//为后面新建的节点设置random节点
        cur = pHead;
        RandomListNode *p;
        while(cur)
		{
             p = cur->next;
            if(cur->random)
			{
                p->random = cur->random->next;
            }
            cur = p->next;
        }
         
        RandomListNode *pCloneHead = pHead->next;
        RandomListNode *tmp;

		//跳过原有的节点
        cur = pHead;
        while(cur->next)
		{
            tmp = cur->next;
            cur->next = tmp->next;
            cur = tmp;
        }

        return pCloneHead;
    }

public:
	TreeNode * Node = NULL;

	TreeNode* InternalConvert(TreeNode* pRootOfTree)
	{
		TreeNode* tmp;
		if (pRootOfTree == NULL)
			return NULL;

		if (pRootOfTree->left == NULL && pRootOfTree->right == NULL)
		{
			if (Node != NULL)
				Node = pRootOfTree;
			return pRootOfTree;
		}

		if (pRootOfTree->left)
		{
			tmp = Convert(pRootOfTree->left);
			tmp->right = pRootOfTree;
			pRootOfTree->left = tmp;
			tmp = pRootOfTree;
		}
		if(pRootOfTree->right)
		{
			tmp = Convert(pRootOfTree->right);
			tmp->left = pRootOfTree;
			pRootOfTree->right = tmp;
		}

		return tmp;
	}

	TreeNode* Convert(TreeNode* pRootOfTree)
	{
		InternalConvert(pRootOfTree);

		return Node;
	}

	vector<string> result;
	vector<string> Permutation(string str) 
	{
		if(str.length()==0)
		{
			return result;
		}
		Permutation1(str,0);
		sort(result.begin(),result.end());
		return result;
	}
	void Permutation1(string str,int begin)
	{
		if(begin == str.length())
		{
			result.push_back(str);
			return ;
		}
		for(int i = begin; str[i]!='\0';i++)
		{
			if(i != begin && str[begin] == str[i])
				continue;
			swap(str[begin], str[i]);
			Permutation1(str, begin+1);
			swap(str[begin], str[i]);
		}

	}

	int MoreThanHalfNum_Solution(vector<int> numbers) 
	{
		map<int, int> tmp;
		int length = numbers.size();
		int halfLength = length / 2;
		
		if (numbers.size() == 1)
			return numbers[0];

		for (auto iter = numbers.begin(); iter!=numbers.end(); iter++)
		{
			if (tmp.find(*iter) == tmp.end())
			{
				tmp.insert(pair<int, int>(*iter, 1));
			}
			else
			{
				int curCount = tmp.find(*iter)->second;
				tmp.find(*iter)->second = ++curCount;
				if (curCount > halfLength)
					return *iter;
			}
		}

		return 0;
	}

	vector<int> GetLeastNumbers_Solution(vector<int> input, int k) 
	{
		vector<int> tmp;
		tmp.resize(0);
		int size = input.size();
		if (k > size)
			return tmp;

		for (int i = 0; i < size; ++i)
		{
			if (tmp.size() == 0)
				tmp.push_back(input[i]);
			else
			for (auto iter = tmp.begin(); iter != tmp.end(); iter++)
			{
				if (input[i] <= *iter)
				{
					tmp.insert(iter, input[i]);
					break;
				}
				auto iter1 = iter + 1;
				if (input[i] > *iter)
				{
					if (iter1 == tmp.end())
					{
						tmp.insert(iter1, input[i]);
						break;
					}
				}
				else if (input[i] <= *iter1)
				{
					tmp.insert(iter1, input[i]);
					break;
				}
			}

			if (tmp.size() > (size_t)k)
				tmp.resize(k);
		}
		return tmp;
	}

	int FindGreatestSumOfSubArray(vector<int> array) 
	{
		/*int sum = 0;
		for (int& iter : array)
		{
			sum += iter;
		}

		int left = array[0], right = sum;
		int i = 0, j = array.size();
		while (i < j)
		{
			if (left < right)
				left += array[++i];
			if (j - i == 1)
				return left;
			if (right <= left)
				right -= array[--j];
		}

		return left;*/

		int maxx = INT_MIN;
		int cursum = 0;
		for (int i = 0; i < (int)array.size(); i++)
		{
			if (cursum < 0)
				cursum = array[i];
			else
				cursum += array[i];
			maxx = max(maxx, cursum);
		}
		return maxx;
	}

	int NumberOf1Between1AndN_Solution(int n)
	{
		  
	}

	string PrintMinNumber(vector<int> numbers) 
	{
		/*int numCount = numbers.size();
		int maxWidth = 0, selectedIndex = 0;
		vector<int> numWidths;
		vector<int> newNum;
		numWidths.resize(0);
		newNum.resize(0);

		for (int i = 0; i < numCount; ++i)
		{
			int tmp = numbers[i];
			int width = 0;
			while (tmp != 0)
			{
				tmp /= 10;
				width++;
			}
			numWidths.push_back(width);
			newNum.push_back(numbers[i]);
			if (width > maxWidth)
				maxWidth = width;
		}

		for (int j = 0; j < numCount; ++j)
		{
			if (numWidths[j] < maxWidth)
			{
				int subWidth = maxWidth = numWidths[j];
				int lastNum = numbers[j] % 10;
				while (subWidth)
				{
					newNum[j] *= 10;
					newNum[j] += lastNum;
					subWidth--;
				}
			}
		}*/

		//可以直接使用标准库字符串比较方法来解决问题，字符串比较就是比在相同位数下，就直接比大小
		int numCount = numbers.size();
		vector<string> numStrings;
		for (int i = 0; i < numCount; ++i)
		{
			numStrings.push_back(to_string(numbers[i]));
		}
		//冒泡排序
		for (int i = 0; i < numCount; ++i)
			for (int j = i + 1; j < numCount; ++j)
			{
				string a = numStrings[i] + numStrings[j];
				string b = numStrings[j] + numStrings[i];

				if (a > b)
					swap(numStrings[i], numStrings[j]);
			}
		string res;
		for (auto iter : numStrings)
			res += iter;
		 
		return res;
	}

	int GetUglyNumber_Solution(int index) 
	{
		int curIndex = 1;
		int curNum = 2;
		if (index == 1)
			return 1;
		while (1)
		{
			int tmp = curNum;
			while (tmp != 1)
			{
				if (tmp % 2 == 0)
				{
					tmp /= 2;
					continue;
				}
				else if (tmp % 3 == 0)
				{
					tmp /= 3;
					continue;
				}
				else if (tmp % 5 == 0)
				{
					tmp /= 5;
					continue;
				}
				else
				{
					break;
				}
			}

			if (tmp == 1)
			{
				curIndex++;
				if (curIndex == index)
				{
					return curNum;
				}
			}
			
			curNum++;
			
		}

		return curNum;
	}
	int FirstNotRepeatingChar(string str) 
	{
		int size = str.size();
		string foundChar;

		for (int i = 0; i < size; ++i)
		{
			int tmpFound = foundChar.find(str[i]);
			if (tmpFound > static_cast<int>(foundChar.size()))   //当前还不存在已查找列表
			{
				char tmp = str[i];
				int res = str.find(tmp, i + 1);
				if (res > 0 && res < size)
					foundChar.push_back(tmp);
				else
					return i;
			}
			else
				continue;
		}
		return -1;
	}

	int InversePairs(vector<int> data) 
	{
		int size = data.size();
		int sum = 0;
		for (int i = 0; i < size-1; ++i)
		{
			if (data[i] > data[i + 1])
				sum += data[i];
		}

	}

	ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) 
	{
		ListNode* p1=pHead1;
		ListNode* p2=pHead2;

		while(p1!=p2)
		{
			p1=(p1==NULL)?pHead2:p1->next;
			p2=(p2==NULL)?pHead1:p2->next;
		}

		return p1;
	}

	int GetNumberOfK(vector<int> data ,int k) 
	{
		int size = data.size();
		int count = 0;
		for (auto iter = data.begin(); iter != data.end(); ++iter)
		{
			if (k == *iter)
				count++;
			else if (k != *iter&&count != 0)
				break;
		}
		return count;
	}

	//求二叉树深度
	int TreeDepth(TreeNode* pRoot)
	{
		if (pRoot == NULL)
			return 0;
		int leftCount = TreeDepth(pRoot->left);
		int rightCount = TreeDepth(pRoot->right);

		return leftCount >= rightCount ? ++leftCount : ++rightCount;
	}

	int leftDepth = 0, rightDepth = 0;
	//判断是否为平衡二叉树
	bool IsBalanced_Solution(TreeNode* pRoot) 
	{
		int depth = 0;
		return IsBalanced_Solution(pRoot, depth);
	}

	bool IsBalanced_Solution(TreeNode* pRoot, int& Depth)
	{
		if (pRoot == NULL)
		{
			return true;
		}

		int tmp = Depth;
		bool lrRes = IsBalanced_Solution(pRoot->left, Depth) && IsBalanced_Solution(pRoot->right, tmp);
		if (!lrRes)return false;
		if (abs(Depth - tmp) > 1)return false;

		//实际不需要比较节点数值的大小
		bool left = true, right = true;
		if (pRoot->left && pRoot->left->val > pRoot->val)
			left = false;
		if (pRoot->right && pRoot->right->val < pRoot->val)
			right = false;

		Depth = Depth > tmp ? ++Depth : ++tmp;

		return left && right;
	}

	void FindNumsAppearOnce(vector<int> data,int* num1,int *num2) 
	{
		if (data.size() < 2)return;

		int resulrOR = 0;
		for (int i = 0; i < data.size(); i++)
		{
			resulrOR ^= data[i];
		}

		unsigned int indexOf1 = FindFirstBitIs1(resulrOR);

		*num1 = *num2 = 0;
		for (int j = 0; j < (int)data.size(); j++)
		{
			if (IsBit1(data[j], indexOf1))
				*num1 ^= data[j];
			else
				*num2 ^= data[j];
		}
	}

	//查找第一个为1的位数
	unsigned int FindFirstBitIs1(int num)
	{
		int indexBit = 0;
		while (((num & 1) == 0) && (indexBit < 8 * sizeof(int)))
		{
			num = num >> 1;
			indexBit++;
		}

		return indexBit;
	}

	bool IsBit1(int num, unsigned int indexBit)
	{
		num = num >> indexBit;
		return (num & 1);
	}

	vector<vector<int> > FindContinuousSequence(int sum) 
	{
		int maxLength = sqrt(sum * 2);
		vector<vector<int>> result;

		for (int i = 2; i < maxLength; i++)
		{
			vector<int> tmp;
			if ((2 * sum) % i == 0)
			{
				int centerNum = sum / i;
				for (int j = 0; j < i; j++)
				{
					tmp.push_back(centerNum - i / 2 + j);
				}
			}

			if (tmp.size() > 0)
				result.push_back(tmp);
		}
	}

	vector<int> FindNumbersWithSum(vector<int> array, int sum) 
	{
		vector<int> result;
		result.resize(2);
		int product = INT_MAX;
		int mid = 0;

		for (int i = 0; i < array.size(); ++i)
		{
			if (array[i] > sum / 2)
			{
				mid = i;
				break;
			}
		}

		for (int i = 0; i < mid - 1; ++i)
		{
			for (int j = mid; j < array.size(); ++j)
			{
				if (array[i] + array[j] == sum)
				{
					if (array[i] * array[j] < product)
					{
						result[0] = array[i];
						result[1] = array[j];
						product = array[i] * array[j];
					}
					break;
				}
			}
		}

		if (product == INT_MAX)
			return vector<int>();
		return result;
	}

	string LeftRotateString(string str, int n) 
	{
		int strLen = str.size();
		if (strLen == 0)return string();
		int left = n % strLen;

		while (left)
		{
			str.push_back(str[0]);
			str.erase(0,1);

			left--;
		}

		return str;
	}

	string ReverseSentence(string str) 
	{
		if (str.size() == 0)
			return string();
		string retStr;

		if (str.find(' ') > str.size())
			return str;
		
		int strLen = str.size();
		int i = 0;
		int j = strLen - 1;
		int left = 0, right = strLen - 1;
		int insertPoint = 0;

		while (i <= j)
		{
			if (str[i] == ' ' && str[j] == ' ')
			{
				retStr.insert(insertPoint, str.substr(j + 1, right-j+1)+' ');
				insertPoint += (right - j);
				retStr.insert(insertPoint+1, str.substr(left, i-left));
				insertPoint++;
				i++; j--;

				left = i; right = j;
			}

			if (str[i] != ' ')
				i++;

			if (str[j] != ' ')
				j--;
		}

		if (right >= left)
			retStr.insert(insertPoint, str.substr(left, right-left+1) + ' ');

		return retStr;
	}

	bool IsContinuous( vector<int> numbers ) 
	{
		vector<int> tmpNumbers;
		int size = numbers.size();
		int min = 13;
		int max = 0;
		int zeroCount = 0;

		for (int i = 0; i < size; ++i)
		{
			if (numbers[i] > max)
				max = numbers[i];
			if (numbers[i] < min && numbers[i] != 0)
				min = numbers[i];

			if (numbers[i] == 0)
				zeroCount++;
			else
			{
				for (int j = 0; j < tmpNumbers.size(); ++j)
				{
					if (numbers[i] == tmpNumbers[j])return false;
				}
			}
			
			tmpNumbers.push_back(numbers[i]);
		}

		int inmutableNum = size - zeroCount;
		if (max - min + 1 - inmutableNum <= zeroCount)
			return true;
		else 
			return false;
	}

	ListNode* deleteDuplication(ListNode* pHead)
	{
		if (pHead == NULL)return NULL;
		if (pHead->next == NULL)return pHead;
		int deleteVal = pHead->val - 1;
		ListNode* tmpNode = pHead;
		ListNode* pretmpNode = NULL;
		ListNode* frontNode = pHead;
		pHead = pHead->next;
		
		while (pHead)
		{
			if (tmpNode && pHead->val == tmpNode->val)
			{
				deleteVal = pHead->val;
				pHead = tmpNode;
			}

			if (pHead->val == deleteVal)
			{	
				if (pretmpNode == NULL)
				{
					//删除节点
					tmpNode = NULL;
					ListNode* tmp = pHead->next;
					delete pHead;
					pHead = tmp;
					frontNode = pHead;
					continue;
				}
				else
				{
					tmpNode = pretmpNode;
					pretmpNode->next = pHead->next;
					ListNode* tmp = pHead->next;
					delete pHead;
					pHead = tmp;
					continue;
				}
			}
			pretmpNode = tmpNode;
			tmpNode = pHead;
			pHead = pHead->next;
		}
		return frontNode;
	}

	//下面是递归方法
	ListNode* deleteDuplication_Recursive(ListNode* pHead)
	{
		if (pHead == NULL)
			return NULL;
		if (pHead != NULL && pHead->next == NULL)
			return pHead;

		ListNode* current;

		if (pHead->next->val == pHead->val) 
		{
			current = pHead->next->next;
			while (current != NULL && current->val == pHead->val)
				current = current->next;
			return deleteDuplication_Recursive(current);
		}
		else 
		{
			current = pHead->next;
			pHead->next = deleteDuplication_Recursive(current);
			return pHead;
		}
	}

	TreeLinkNode* GlobalNode;
	TreeLinkNode* GetNext(TreeLinkNode* pNode)
	{
		if (pNode == NULL)return NULL;
		GlobalNode = pNode;
		//找到根节点
		TreeLinkNode* rootNode = pNode;
		while (rootNode->next)
			rootNode = rootNode->next;
		
		TreeLinkNode* preNode = NULL;
		return TreeTraversing(rootNode, preNode);
	}

	TreeLinkNode* TreeTraversing(TreeLinkNode* pRoot, TreeLinkNode*& preNode)
	{
		if (pRoot == NULL)return NULL;

		//下面是中序遍历
		TreeLinkNode* left = TreeTraversing(pRoot->left, preNode);
		if (left != NULL)return left;
		if (preNode && preNode == GlobalNode)
			return pRoot;
		preNode = pRoot;
		TreeLinkNode* right = TreeTraversing(pRoot->right, preNode);
		if (right != NULL)return right;
		return NULL;
	}

	//这是通过判断的方法，
	TreeLinkNode* GetNext_1(TreeLinkNode* pNode)
	{
		if (pNode == NULL)
			return NULL;
		if (pNode->right != NULL)
		{
			//1、 如果该节点存在右子树就寻找右子树最左边的节点
			pNode = pNode->right;
			while (pNode->left != NULL)
				pNode = pNode->left;
			return pNode;
		}
		while (pNode->next != NULL)
		{
			TreeLinkNode *proot = pNode->next;
			if (proot->left == pNode)
				return proot;
			pNode = pNode->next;
		}
		return NULL;
	}

	bool isSymmetrical(TreeNode* pRoot)
	{
		if (pRoot == NULL)return true;

		return isSymmetricalImpl(pRoot->left, pRoot->right);
	}

	bool isSymmetricalImpl(TreeNode* pRootLeft, TreeNode* pRootRight)
	{
		if (pRootLeft == NULL && pRootRight == NULL)return true;
		if (!(pRootLeft && pRootRight))return false;
		bool res = false;
		if (pRootLeft->val == pRootRight->val)res = true;

		bool left = isSymmetricalImpl(pRootLeft->left, pRootRight->right);
		bool right = isSymmetricalImpl(pRootLeft->right, pRootRight->left);

		return res && left && right;
	}

	// 二叉树Z字形打印
	vector<vector<int> > Print(TreeNode* pRoot) 
	{
		// 不动态分配空间
		/*vector<vector<int>> res;
		if (pRoot == NULL)return res;

		stack<TreeNode*> nodes;
		res.push_back(vector<int>{pRoot->val});
		nodes.push(pRoot);
		bool bL2R = false;

		while (nodes.size() > 0)
		{
			vector<int> tmp;
			stack<TreeNode*> tmpNodes;
			while (nodes.size() > 0)
			{
				TreeNode* popNode = nodes.top();
				if (bL2R)
				{
					if (popNode->left) { tmp.push_back(popNode->left->val); tmpNodes.push(popNode->left); }
					if (popNode->right) { tmp.push_back(popNode->right->val); tmpNodes.push(popNode->right);}
				}
				else
				{
					if (popNode->right) { tmp.push_back(popNode->right->val); tmpNodes.push(popNode->right); }
					if (popNode->left) { tmp.push_back(popNode->left->val); tmpNodes.push(popNode->left); }
				}
			nodes.pop();
			}
			if (!tmp.empty())res.push_back(tmp);
			nodes = tmpNodes;
			bL2R = !bL2R;
		}

		return res;*/

		// 动态分配空间
		vector<vector<int>> res;
		if (pRoot == NULL)return res;

		stack<TreeNode*>* nodes = new stack<TreeNode*>;
		stack<TreeNode*>* tmpNodes = new stack<TreeNode*>;
		res.push_back(vector<int>{pRoot->val});
		nodes->push(pRoot);
		bool bL2R = false;

		while (nodes->size() > 0)
		{
			vector<int> tmp;
			while (nodes->size() > 0)
			{
				TreeNode* popNode = nodes->top();
				if (bL2R)
				{
					if (popNode->left) { tmp.push_back(popNode->left->val); tmpNodes->push(popNode->left); }
					if (popNode->right) { tmp.push_back(popNode->right->val); tmpNodes->push(popNode->right); }
				}
				else
				{
					if (popNode->right) { tmp.push_back(popNode->right->val); tmpNodes->push(popNode->right); }
					if (popNode->left) { tmp.push_back(popNode->left->val); tmpNodes->push(popNode->left); }
				}
				nodes->pop();
			}
			if (!tmp.empty())res.push_back(tmp);
			swap(nodes, tmpNodes);
			bL2R = !bL2R;
		}
		delete nodes;
		delete tmpNodes;
		return res;
	}

	// 二叉树打印成多行
	vector<vector<int> > Print_1(TreeNode* pRoot) 
	{
		// 与上面不同的是，这次需要队列
		vector<vector<int>> res;
		if (pRoot == NULL)return res;

		queue<TreeNode*>* nodes = new queue<TreeNode*>;
		queue<TreeNode*>* tmpNodes = new queue<TreeNode*>;
		res.push_back(vector<int>{pRoot->val});
		nodes->push(pRoot);

		while (nodes->size() > 0)
		{
			vector<int> tmp;
			//stack<TreeNode*> tmpNodes;
			while (nodes->size() > 0)
			{
				TreeNode* popNode = nodes->front();
				
				if (popNode->left) { tmp.push_back(popNode->left->val); tmpNodes->push(popNode->left); }
				if (popNode->right) { tmp.push_back(popNode->right->val); tmpNodes->push(popNode->right); }
				
				nodes->pop();
			}
			if (!tmp.empty())res.push_back(tmp);
			swap(nodes, tmpNodes);
		}
		delete nodes;
		delete tmpNodes;
		return res;
	}

	// 序列化二叉树
	char* Serialize(TreeNode *root) 
	{
		char* tmp = new char[100];
		char tmp1[] = "adasd";
	}

	// 反序列化二叉树
	TreeNode* Deserialize(char *str)
	{

	}

	int pathLen;

	bool hasPath(char* matrix, int rows, int cols, char* str)
	{
		pathLen = rows * cols;
	}

	bool hasPathImpl(char* matrix, int curIndex, char* str, vector<int> passed)
	{
		if (*str == '/0')
			return true;

		//if((curIndex-1)%)
	}

	int movingCount(int threshold, int rows, int cols)
	{

	}

public:
	vector<vector<int>> Temp;
};

bool ConvertStringToInteger(const char* szString, int* pInterger)
{
	string str(szString);
	if (str.size() == 0)return false;

	int res = 0, digits = 1;  
	int length = str.length();
	for (int i = length - 1; i >= 0; --i)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			res += (str[i] - '0')*digits;
			digits *= 10;
		}
		else
		{
			if (str[i] != '-'&&str[i] != '+') //首字母可以判断正负
				return false;
			if (i == 0 && str[i] == '-')
				res = -res;

		}
	}
	*pInterger = res;
	return true;
}

//int GetPrivateProfileString(char* lpAppName,char* lpKeyName,string lpDefault,vector<string>& lpReturnedString, int nSize,string lpFileName)
//{
//	IniInst* ini = FindIniFromFile(lpFileName);   //ini文件类
//
//	if (ini == nullptr) //未成功找到
//	{
//		ini = FindIniFromRoot(lpFileName);
//	}
//
//	if (!ini)return 0x2;
//
//	if (lpAppName == nullptr)
//	{
//		int sectionCount = ini->getSectionCount();
//
//		for (int i = 0; i < sectionCount; ++i)
//		{
//			IniSection section = ini->getSection(i);
//			for (auto it : section)
//			{
//				if (!it.isValid())return 0x2;
//				lpReturnedString.push_back(it.getValue());
//			}
//		}
//	}
//	else
//	{
//		if (lpKeyName != nullptr)
//		{
//			IniSection section = ini->getSection(lpKeyName);
//			for (auto it : section)
//			{
//				if (!it.isValid())return 0x2;
//				lpReturnedString.push_back(it.getValue());
//			}
//		}
//		else
//		{
//			IniSection section = ini->getSection(lpDefault);
//			for (auto it : section)
//			{
//				if (!it.isValid())return 0x2;
//				lpReturnedString.push_back(it.getValue());
//			}
//		}
//	}
//
//	if (lpKeyName == nullptr&&lpAppName == nullptr&&lpReturnedString.size() > nSize)
//		return nSize - 1;
//	if ((lpKeyName == nullptr || lpAppName == nullptr) && lpReturnedString.size() > nSize)
//		return nSize - 2;
//
//	return lpReturnedString.size() - 1;
//}

int main()
{
	Solution A;
	/*vector<int> list = { 3,7,5,10,13,16,15,9};

	bool Result = A.VerifySquenceOfBST(list);

	if (Result)
		cout << "Yes";
	else
		cout << "No";*/

	TreeNode* root = new TreeNode(10);
	root->left = new TreeNode(7);
	root->left->left = new struct TreeNode(5);
	root->left->left->right = new struct TreeNode(6);
	//root->left->left->right->left = new struct TreeNode(3);
	root->left->right = new struct TreeNode(9);
	root->right = new struct TreeNode(20);
	root->right->left = new struct TreeNode(15);
	root->right->right = new TreeNode(21);

	//cout << A.TreeDepth(root) << endl;

	if (A.IsBalanced_Solution(root))
		cout << "yes" << endl;
	else
		cout << "no" << endl;
	/*cout << A.FindPath(root, 13).size() << endl;

	for (auto iter = A.Temp.begin(); iter != A.Temp.end(); iter++)
	{
		for (auto iter1 = (*iter).begin(); iter1 != (*iter).end(); iter1++)
		{
			cout << (*iter1);
		}

		cout << endl;
	}*/

	//vector<int> numArray(9);
	////numArray = { 1,1,3,1,1,1,5,4,2 };
	////cout << A.MoreThanHalfNum_Solution(numArray);
	////numArray.insert(numArray.end(), 5);
	//numArray.push_back(2);
	//for (auto iter : numArray)
	//{
	//	cout << iter << "__";
	//}

	vector<int> numList = { 6,-3,-2,7,-15,1,2,2 };
	vector<int> numList1 = { 2,3,5,6,9,10,15 };
	/*vector<int> result = A.GetLeastNumbers_Solution(numList, 8);
	for (auto iter : result)
	{
		cout << iter << "_";
	}*/
	//cout << A.FindGreatestSumOfSubArray(numList);
	//cout << A.GetUglyNumber_Solution(9);
	/*string str = "abcbafc";
	char tmp = 'a' + 10;
	cout << A.FirstNotRepeatingChar(str)<< endl;*/
	string str = "man. handsome very a am i";
	vector<int> cardNum = { 1,2,3,4,6,0,0 };

	cout << A.FindNumbersWithSum(numList1, 12)[0] << endl;
	cout << A.FindNumbersWithSum(numList1, 12)[1] << endl;

	cout << str << endl;
	cout << A.ReverseSentence(str) << endl;

	cout << str.substr(6, 2) << endl;

	if (A.IsContinuous(cardNum))
		cout << "YES" << endl;
	else
		cout << "NO" << endl;

	TreeLinkNode* LinkRoot = new TreeLinkNode(8);
	LinkRoot->left = new struct TreeLinkNode(6);
	LinkRoot->left->next = LinkRoot;
	LinkRoot->left->left = new struct TreeLinkNode(5);
	LinkRoot->left->left->next = LinkRoot->left;
	LinkRoot->left->right = new struct TreeLinkNode(7);
	LinkRoot->left->right->next = LinkRoot->left;
	LinkRoot->right = new struct TreeLinkNode(10);
	LinkRoot->right->next = LinkRoot;
	LinkRoot->right->left = new struct TreeLinkNode(9);
	LinkRoot->right->left->next = LinkRoot->right;
	LinkRoot->right->right = new struct TreeLinkNode(11);
	LinkRoot->right->right->next = LinkRoot->right;

	//A.GlobalNode = LinkRoot->left->left;
	TreeLinkNode* preNode;
	cout << A.GetNext_1(LinkRoot->left->right)->val << endl;

	/*vector<int> intvec{ 1,2,3,4 };
	for (auto iter = intvec.begin(); iter != intvec.end(); ++iter)
	{
		cout << *iter << endl;
	}*/

	vector<vector<int>> vec;

	
	/*char buffer[5];
	sprintf_s(buffer, "%u", 245614);
	cout << buffer << endl;*/

	char str1[] = "welcomehh";
	cout << sizeof(str1) << endl;
	enum x_enum {x1,x2,x3=10,x4,x5}x;
	cout << x1;
	system("pause");
	return 0;
}