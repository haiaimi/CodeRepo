#include <iostream>
#include <string>
#include <vector>
#include <minwindef.h>
#include <algorithm>
#include <synchapi.h>

using namespace std;

//���������
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
	//�����Ч����ƥ�� https://leetcode-cn.com/problems/longest-valid-parentheses/
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

	//������ https://leetcode-cn.com/problems/maximum-subarray/
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

	//��ͬ·���������������Ͻǵ���С�ǵ�·���� https://leetcode-cn.com/problems/unique-paths/
	int uniquePaths(int m, int n)
	{
		//��̬�滮��
		//�ǵݹ�
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

		//�ݹ鷽��Ҳ����
	}

	//��ͬ·���������������Ͻǵ���С�ǵ�·�����������ϰ���Ҫ�ƹ������ϰ���Ϊ1 https://leetcode-cn.com/problems/unique-paths-ii/
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

	//�����������·�������ϵ����£�https://leetcode-cn.com/problems/minimum-path-sum/
	int minPathSum(vector<vector<int>>& grid) {
		//��̬�滮
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

	//���뷽��  https://leetcode-cn.com/problems/decode-ways/
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

	//��ͬ�Ķ���������II https://leetcode-cn.com/problems/unique-binary-search-trees-ii/
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

	//�����ַ��� https://leetcode-cn.com/problems/interleaving-string/
	//�ݹ鷨  leetcode��ʱ
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

	//������� https://leetcode-cn.com/problems/add-two-numbers/
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

	//���ظ��ַ�����ִ� https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/
	//��̬�滮
	int lengthOfLongestSubstring(string s) {
		int len = s.length();

		int l = 0, maxlen = 0;
		for (int i = 0; i < len; ++i)
		{
			for (int j = l; j < i; ++j)
			{
				if (s[i] == s[j])
				{
					l = j + 1;
					break;
				}
			}
			maxlen = max(maxlen, i - l + 1);
		}

		return maxlen;
	}

	//���������������λ�� https://leetcode-cn.com/problems/median-of-two-sorted-arrays/
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		int len = nums1.size() + nums2.size();
		int l = 0, r = 0, pre, cur;
		while (1)
		{
			if (l + r == 1 + len / 2)
			{
				if (len & 1)return (double)cur;
				else return ((double)cur + (double)pre) / 2;
			}
			if (l < nums1.size() && r < nums2.size())
				if (nums1[l] <= nums2[r]) { pre = cur; cur = nums1[l]; l++; continue; }
				else { pre = cur; cur = nums2[r]; r++; continue; }
			if (l < nums1.size() && r >= nums2.size()) { pre = cur; cur = nums1[l]; l++; continue; }
			if (l >= nums1.size() && r < nums2.size()) { pre = cur; cur = nums2[r]; r++; continue; }
		}
	}

	//������Ӵ� https://leetcode-cn.com/problems/longest-palindromic-substring/
	//���汩���ⷨ leetcode��ʱ
	string longestPalindrome(string s) {
		if (s.length() == 1)return s;
		string revStr = s;
		string ret;
		using std::reverse;   //��ֹ������������Ա����������ͻ
		reverse(revStr.begin(), revStr.end());

		int maxlen = 0, curlen = 0;

		for (int i = 0; i < s.length(); ++i)
		{
			int tmp = i, tmpj = -1;
			for (int j = 0; j < s.length(); ++j)
			{
				int tmp2 = tmp;
				if (tmp < s.length() && s[tmp] == revStr[j])
				{
					curlen++;
					tmp++;
				}
				if (j == (s.length() - 1)||tmp2 == (s.length() - 1) || s[tmp2] != revStr[j])
				{
					if (((j == s.length() - 1) || (tmp2 == s.length() - 1)) && s[tmp2]==revStr[j])j += 1;
					if (s.length() - j == i && curlen >= maxlen) { ret = s.substr(i, curlen < 1 ? 1 : curlen); maxlen = curlen; }
					curlen = 0;
					tmp = i;
					j = ++tmpj;
				}
			}
		}
		return ret;
	}

	//��̬�滮��
	//�����������1���м�Ϊ�����ַ� 2���м�Ϊ2���ַ�
	string longestPalindrome_dp(string s)
	{
		int maxlen = 0;
		string ret;
		for (int i = 1; i < s.length(); ++i)
		{
			int left, right, curlen;
			//�м�Ϊ1���ַ������
			left = i - 1;
			right = i + 1;
			while (left >= 0 && right < s.length() && s[left] == s[right])
			{
				left--; right++;
			}
			curlen = right - left - 1;
			if (curlen > maxlen)
			{
				ret = s.substr(left + 1, curlen);
				maxlen = curlen;
			}

			//�м�Ϊ�����ַ�
			if (s[i] == s[i - 1])
			{
				left = i - 2;
				right = i + 1;
				while (left >= 0 && right < s.length() && s[left] == s[right])
				{
					left--; right++;
				}
				curlen = right - left - 1;
				if (curlen > maxlen)
				{
					ret = s.substr(left + 1, curlen);
					maxlen = curlen;
				}
			}
		}
		return ret;
	}

	//Z���α任 https://leetcode-cn.com/problems/zigzag-conversion/
	//Ѱ�����еı仯���ɼ���
	string convert(string s, int numRows) {
		int pernum = 2 * numRows - 2;
		if (numRows <= 1)return s;

		string str;
		for (int i = 0; i < numRows; ++i)
		{
			for (int j = 0; j < s.length(); j += pernum)
			{
				if (j + i < s.length())
					str.push_back(s[j + i]);

				if (i != 0 && i != numRows - 1 && j + pernum - i < s.length())
					str.push_back(s[j + pernum - i]);
			}
		}
		return str;
	}

	//��ת���� https://leetcode-cn.com/problems/reverse-integer/
	int reverse(int x) {
		int tmp = abs(x);
		int res = 0;
		while (tmp)
		{
			int tmp2 = tmp % 10;
			if (res > (0x7fffffff - tmp2) / 10)return 0;   //�˴����ԸĽ�����ȷ������
			//if (res > INT_MAX / 10 || (res == INT_MAX / 10 && tmp2 > 7)) return 0;//�������
			//if (res < INT_MIN / 10 || (res == INT_MIN / 10 && tmp2 < -8)) return 0;//�������
			res = res * 10 + tmp2;
			tmp /= 10;
		}

		if (x < 0)res = -res;
		return res;
	}

	//�ַ���ת���� (atoi) https://leetcode-cn.com/problems/string-to-integer-atoi/
	//�������û�п��ǵ�e�ı�ʾ��
	int myAtoi(string str) {
		if (str.length() == 0)return 0;
		int p = 0;
		while (str[p] == ' ')
			p++;
		if (p == str.length())return 0;
		if (str[p] != '-'&&str[p] != '+' && (str[p]<'0' || str[p]>'9'))return 0;

		bool bPos = true;
		if (str[p] == '-') { bPos = false; p++; }
		if (str[p] == '+'&&bPos)p++;

		int num = 0;
		while (str[p] >= '0'&&str[p] <= '9')
		{
			int add = str[p] - '0';
			if (num > INT_MAX / 10 || (num == INT_MAX / 10 && add > 7))
				return bPos ? INT_MAX : INT_MIN;
			num = num * 10 + add;
			p++;
		}

		return bPos ? num : -num;
	}

	//������ https://leetcode-cn.com/problems/palindrome-number/
	//����ķ�����ͨ����ת�������Ƚ�
	bool isPalindrome(int x) {
		if (x < 0)return false;
		int tmp = x;
		int res = 0;
		while (tmp)
		{
			int tmp2 = tmp % 10;
			res = res * 10 + tmp2;
			tmp /= 10;
		}

		return res == x;
	}

	//������ת�����ַ����Ƚ�
	bool isPalindrome_1(int x) {
		if (x < 0)return false;

		string num = to_string(x), tmp = num;
		using std::reverse;
		reverse(tmp.begin(), tmp.end());

		return num == tmp;
	}

	//ʢˮ�������� https://leetcode-cn.com/problems/container-with-most-water/description/
	//�����ñ�����O(n2)����ѷ�����˫ָ�뷽����O(n)
	int maxArea(vector<int>& height) {
		int l = 0, r = height.size() - 1;  //��������ָ��
		int maxarea = 0;
		while (r > l)
		{
			int cur = min(height[l], height[r])*(r - l);
			maxarea = max(cur, maxarea);
			if (height[l] <= height[r])l++;
			else r--;
		}
		return maxarea;
	}

	//����ת�������� https://leetcode-cn.com/problems/integer-to-roman/
	//������������С��3999���Ծͽ���ÿһλ�Ĵ���û��ʹ��ѭ��
	string intToRoman(int num) {
		string res = "";

		int tmp = num / 1000;
		num = num % 1000;
		for (int i = 0; i < tmp; ++i)
			res.push_back('M');

		tmp = num / 100;
		num = num % 100;
		if (tmp == 4)res.append("CD");
		else if (tmp == 9)res.append("CM");
		else
		{
			if (tmp >= 5)res.push_back('D');
			for (int i = 0; i < tmp % 5; ++i)
				res.push_back('C');
		}

		tmp = num / 10;
		num = num % 10;
		if (tmp == 4)res.append("XL");
		else if (tmp == 9)res.append("XC");
		else
		{
			if (tmp >= 5)res.push_back('L');
			for (int i = 0; i < tmp % 5; ++i)
				res.push_back('X');
		}

		tmp = num;
		if (tmp == 4)res.append("IV");
		else if (tmp == 9)res.append("IX");
		else
		{
			if (tmp >= 5)res.push_back('V');
			for (int i = 0; i < tmp % 5; ++i)
				res.push_back('I');
		}

		return res;
	}

	//��������ת���� https://leetcode-cn.com/problems/roman-to-integer/
	int romanToInt(string s) {
		int len = s.length();
		int num = 0;

		for (int i = len - 1; i >= 0; --i)
		{
			if (s[i] == 'V')num += 5;
			if (s[i] == 'L')num += 50;
			if (s[i] == 'D')num += 500;

			if (s[i] == 'I')
				if (i + 1 < len && (s[i + 1] == 'X' || s[i + 1] == 'V'))
					num -= 1;
				else num += 1;
			if (s[i] == 'X')
				if (i + 1 < len && (s[i + 1] == 'L' || s[i + 1] == 'C'))
					num -= 10;
				else num += 10;
			if (s[i] == 'C')
				if (i + 1 < len && (s[i + 1] == 'D' || s[i + 1] == 'M'))
					num -= 100;
				else num += 100;

			if (s[i] == 'M')num += 1000;

		}
		return num;
	}

	//�����ǰ׺ https://leetcode-cn.com/problems/longest-common-prefix/
	string longestCommonPrefix(vector<string>& strs) {
		int strnum = strs.size();
		int pflen = 0;
		if (strnum == 0)return "";

		while (pflen < strs[0].length())
		{
			char tmp = strs[0][pflen];

			for (int i = 1; i < strnum; ++i)
			{
				if (strs[i][pflen] == tmp && pflen < strs[i].length())
					continue;
				else return strs[i].substr(0, pflen);
			}
			pflen++;
		}
		return strs[0].substr(0, pflen);
	}

	//����֮�� https://leetcode-cn.com/problems/3sum/
	vector<vector<int>> threeSum(vector<int>& nums) {
		sort(nums.begin(), nums.end());  //�������������
		int l = 0, r = nums.size() - 1;
		vector<vector<int>> res;
		vector<int> n(3, 0);
	
		while (r > l)
		{
			int tmp = nums[r] + nums[l];
			bool badded = false;
			for (int i = l + 1; i < r; ++i)
				if (nums[i] + tmp == 0)
				{
					n[0] = nums[l]; n[1] = nums[i]; n[2] = nums[r];
					cout << "[" << n[0] << " ," << n[1] << " ," << n[2] << "]" << endl;
					res.push_back(n);
					badded = true;
					break;
				}

			//if(tmp==0)while(nums[++l]==0);
			if (tmp <= 0) 
			{ 
				int lt = l; l++;
				while (nums[l] == nums[lt]) { l++; lt++; };
				if (badded)r = nums.size() - 1;
				continue; 
			}
			else 
			{ 
				int rt = r; r--;
				while (nums[r] == nums[rt]) { r--; rt--; };
				if(badded)l = 0; 
			}
		}
		return res;
	}
};

#pragma region BFBRT
const int N = 10005;

int a[N];

//��������
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

//Ѱ����λ������λ��
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

	//����ʣ��Ԫ��
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

//���л��ֹ���
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
	int p = FindMid(a, l, r);    //Ѱ����λ������λ��
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

	//cout << A.numDecodings("101") << endl;
	//cout << A.longestPalindrome_dp("ccc") << endl;

	vector<int> nums = { -4,-2,-2,-2,0,1,2,2,2,3,3,4,4,6,6 };
	A.threeSum(nums);
	string str = "cbba";
	str.append("NC");
	cout << str << endl;
	string str1 = str, str2 = str1;
	cout << str2 << endl;
	//cout << str.substr(1, 2) << endl;
	int num = 1;
	int num2 = 1;
	num2 *= ++num;
	//num2 = num++;
	cout << num2 << endl;
	//string str = "abcdefg";
	//reverse(str.begin(), str.end());
	cout << str<< endl;

	char a[10], *p = a;
	
	system("pause");

	return 0;
};