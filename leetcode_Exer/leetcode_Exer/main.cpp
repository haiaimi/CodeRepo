#include <iostream>
#include <string>
#include <vector>
#include <minwindef.h>

using namespace std;

//二叉树结点
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
	//求最长有效括号匹配
	int longestValidParentheses(string s) {
		int size = s.size();
		int counts = 0;
		vector<int> sign(size, 0);

		for (int i = 1; i < size; ++i)
		{
			for (int j = i - 1; j >= 0; --j)
			{
				if (s[j] == '('&&s[i] == ')')
				{
					int tmp = j < 1 ? 1 : j;

					if (sign[j] == 0)
					{
						sign[i] = max(sign[i - 1] + 1, sign[i - 1] + sign[tmp - 1] + 1);
						if (counts < sign[i])counts = sign[i];
						sign[j] = -1;
						break;
					}
				}
			}
		}

		return counts * 2;
	}

	//最长子序和
	int maxSubArray(vector<int>& nums) {
		int curMax = nums[0];
		int preSum = nums[0];

		for (int i = 1; i < nums.size(); ++i)
		{
			preSum = max(nums[i], nums[i] + preSum);
			curMax = max(preSum, curMax);
		}

		return curMax;

	}

	//求不同路径数，从网格左上角到右小角的路径数
	int uniquePaths(int m, int n)
	{
		//动态规划法
		//非递归
		vector<vector<int>> map(m, vector<int>(n, 0));
		map[0][0] = 1;
		int ways = 0;
		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if (i - 1 >= 0)
					map[i][j] += map[i - 1][j];
				if (j - 1 >= 0)
					map[i][j] += map[i][j - 1];
			}
		}

		return map[m - 1][n - 1];

		//递归方法也可以
	}

	//求不同路径数，从网格左上角到右小角的路径数（遇到障碍需要绕过），障碍处为1
	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
		int n = obstacleGrid[0].size();
		int m = obstacleGrid.size();
		vector<vector<int>> map(m, vector<int>(n, 0));
		map[0][0] = 1;

		if (obstacleGrid[0][0] == 1 || obstacleGrid[m - 1][n - 1] == 1)return 0;

		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if (obstacleGrid[i][j] != 1)
				{
					if (i - 1 >= 0)
						if (obstacleGrid[i - 1][j] != 1)
							map[i][j] += map[i - 1][j];

					if (j - 1 >= 0)
						if (obstacleGrid[i][j - 1] != 1)
							map[i][j] += map[i][j - 1];
				}
			}
		}

		return map[m - 1][n - 1];
	}

	//求网格中最短路径（左上到右下）
	int minPathSum(vector<vector<int>>& grid) {
		//动态规划
		int m = grid.size();
		int n = grid[0].size();
		vector<vector<int>> map(m, vector<int>(n, 0));
		map[0][0] = grid[0][0];

		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				int tmp1 = 0, tmp2 = 0;
				if (i - 1 >= 0)
					tmp1 = map[i - 1][j] + grid[i][j];
				if (j - 1 >= 0)
					tmp2 = map[i][j - 1] + grid[i][j];

				if (!(tmp1 || tmp2))map[i][j] = grid[i][j];
				else if ((tmp1 || tmp2) && !(tmp1&&tmp2))map[i][j] = tmp1 + tmp2;
				else map[i][j] = min(tmp1, tmp2);
			}
		}

		return map[m - 1][n - 1];
	}

	//获取编码的个数 详细题目 https://leetcode-cn.com/problems/decode-ways/
	int numDecodings(string s) {
		vector<int> allNum(s.length(), 0);
		vector<int> num(s.length(), 0);

		for (int i = 0; i < s.length(); ++i)
			allNum[i] = s[i] - '0';

		num[0] = allNum[0] ? 1 : 0;

		for (int i = 1; i < allNum.size(); ++i)
		{
			if (allNum[i] != 0)
				num[i] += num[i - 1];

			if (allNum[i - 1] * 10 + allNum[i] <= 26 && allNum[i - 1] * 10 + allNum[i] >= 10)
				if (i - 2 >= 0)
					num[i] += num[i - 2];
				else
					num[i] += 1;
		}

		return num.back();
	}

	//生成二叉树
	typedef vector<TreeNode*> Trees;
	vector<TreeNode*> generateTrees(int n) {
		if (n == 0)return Trees();
		return generateTreesImpl(1, n);
	}

	Trees generateTreesImpl(int start, int end)
	{
		if (start > end)return Trees(1, NULL);
		if (start == end)return Trees(1, new TreeNode(start));

		Trees tmp;
		for (int i = start; i <= end; ++i)
		{
			Trees left = generateTreesImpl(start, i - 1);
			Trees right = generateTreesImpl(i + 1, end);

			for (int j = 0; j < left.size(); ++j)
			{
				for (int k = 0; k < right.size(); ++k)
				{
					TreeNode* node = new TreeNode(i);
					node->left = left[j];
					node->right = right[k];
					tmp.push_back(node);
				}
			}
		}
		return tmp;
	}

	//交错字符串 https://leetcode-cn.com/problems/interleaving-string/
	//递归法  leetcode超时
	bool isInterleave_rec(string s1, string s2, string s3) {
		if (s1.length() + s2.length() != s3.length())return false;

		int l = 0, r = 0, c = 0;
		while (1)
		{
			cout << c << endl;
			if (c == s3.length())return true;
			if (s3[c] == s1[l] && s3[c] != s2[r])
			{
				l++; c++; continue;
			}
			if (s3[c] == s2[r] && s3[c] != s1[l])
			{
				r++; c++; continue;
			}
			if (s3[c] == s2[r] && s3[c] == s1[l])
			{
				return isInterleave_rec(s1.substr(l + 1), s2.substr(r), s3.substr(c + 1)) || isInterleave_rec(s1.substr(l), s2.substr(r + 1), s3.substr(c + 1));
			}

			return false;
		}
	}

	bool isInterleave(string s1, string s2, string s3)
	{

		return false;
	}

	//两数相加 https://leetcode-cn.com/problems/add-two-numbers/
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		bool bcarry = false;
		ListNode* ret = NULL, *tmp_node;

		while (l1 || l2)
		{
			int tmp = 0;
			if (l1 == NULL)
				tmp = bcarry ? l2->val + 1 : l2->val;
			else if (l2 == NULL)
				tmp = bcarry ? l1->val + 1 : l1->val;
			else
				tmp = bcarry ? l1->val + l2->val + 1 : l1->val + l2->val;
			bcarry = tmp / 10;
			if (ret == NULL) { ret = new ListNode(tmp % 10); tmp_node = ret; }
			else { ret->next = new ListNode(tmp % 10); ret = ret->next; }

			if (l1)l1 = l1->next;
			if (l2)l2 = l2->next;
		}

		if (bcarry)ret->next = new ListNode(1);
		return tmp_node;
	}
};

#pragma region BFBRT
const int N = 10005;

int a[N];

//插入排序
void InsertSort(int a[], int l, int r)
{
	for (int i = l + 1; i <= r; i++)
	{
		if (a[i - 1] > a[i])
		{
			int t = a[i];
			int j = i;
			while (j > l && a[j - 1] > t)
			{
				a[j] = a[j - 1];
				j--;
			}
			a[j] = t;
		}
	}
}

//寻找中位数的中位数
int FindMid(int a[], int l, int r)
{
	if (l == r) return l;
	int i = 0;
	int n = 0;
	for (i = l; i < r - 5; i += 5)
	{
		InsertSort(a, i, i + 4);
		n = i - l;
		swap(a[l + n / 5], a[i + 2]);
	}

	//处理剩余元素
	int num = r - i + 1;
	if (num > 0)
	{
		InsertSort(a, i, i + num - 1);
		n = i - l;
		swap(a[l + n / 5], a[i + num / 2]);
	}
	n /= 5;
	if (n == l) return l;
	return FindMid(a, l, l + n);
}

//进行划分过程
int Partion(int a[], int l, int r, int p)
{
	swap(a[p], a[l]);
	int i = l;
	int j = r;
	int pivot = a[l];
	while (i < j)
	{
		while (a[j] >= pivot && i < j)
			j--;
		a[i] = a[j];
		while (a[i] <= pivot && i < j)
			i++;
		a[j] = a[i];
	}
	a[i] = pivot;
	return i;
}

int BFPRT(int a[], int l, int r, int k)
{
	int p = FindMid(a, l, r);    //寻找中位数的中位数
	int i = Partion(a, l, r, p);

	int m = i - l + 1;
	if (m == k) return a[i];
	if (m > k) return BFPRT(a, l, i - 1, k);
	return BFPRT(a, i + 1, r, k - m);
}

#pragma endregion

int main()
{/*
	int n, k;
	scanf_s("%d", &n);
	for (int i = 0; i < n; i++)
		scanf_s("%d", &a[i]);

	scanf_s("%d", &k);
	printf_s("The %d th number is : %d\n", k, BFPRT(a, 0, n - 1, k));

	for (int i = 0; i < n; i++)
		printf_s("%d ", a[i]);

	puts("");*/
	
	Solution A;
	/*bool res = A.isInterleave_rec("bbbbbabbbbabaababaaaabbababbaaabbabbaaabaaaaababbbababbbbbabbbbababbabaabababbbaabababababbbaaababaa",
		"babaaaabbababbbabbbbaabaabbaabbbbaabaaabaababaaaabaaabbaaabaaaabaabaabbbbbbbbbbbabaaabbababbabbabaab",
		"babbbabbbaaabbababbbbababaabbabaabaaabbbbabbbaaabbbaaaaabbbbaabbaaabababbaaaaaabababbababaababbababbbababbbbaaaabaabbabbaaaaabbabbaaaabbbaabaaabaababaababbaaabbbbbabbbbaabbabaabbbbabaaabbababbabbabbab");

	if (res)cout << "true";
	else cout << "false";*/

	cout << A.numDecodings("101") << endl;

	string str = "abcdefg";
	cout << str.substr(7).length() << endl;
	system("pause");

	return 0;
}