#include <iostream>
#include <string>
#include <vector>
#include <minwindef.h>
#include <algorithm>
#include <synchapi.h>
#include <stack>
#include <map>
#include <unordered_map>

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
	//求最长有效括号匹配 https://leetcode-cn.com/problems/longest-valid-parentheses/
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

	//最长子序和 https://leetcode-cn.com/problems/maximum-subarray/
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

	//求不同路径数，从网格左上角到右小角的路径数 https://leetcode-cn.com/problems/unique-paths/
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

	//求不同路径数，从网格左上角到右小角的路径数（遇到障碍需要绕过），障碍处为1 https://leetcode-cn.com/problems/unique-paths-ii/
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

	//求网格中最短路径（左上到右下）https://leetcode-cn.com/problems/minimum-path-sum/
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

	//解码方法  https://leetcode-cn.com/problems/decode-ways/
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

	//不同的二叉搜索树II https://leetcode-cn.com/problems/unique-binary-search-trees-ii/
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

	//无重复字符的最长字串 https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/
	//动态规划
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

	//两个排序数组的中位数 https://leetcode-cn.com/problems/median-of-two-sorted-arrays/
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

	//最长回文子串 https://leetcode-cn.com/problems/longest-palindromic-substring/
	//常规暴力解法 leetcode超时
	string longestPalindrome(string s) {
		if (s.length() == 1)return s;
		string revStr = s;
		string ret;
		using std::reverse;   //防止下面调用与类成员函数发生冲突
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

	//动态规划法
	//有两种情况，1、中间为单个字符 2、中间为2个字符
	string longestPalindrome_dp(string s)
	{
		int maxlen = 0;
		string ret;
		for (int i = 1; i < s.length(); ++i)
		{
			int left, right, curlen;
			//中间为1个字符的情况
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

			//中间为两个字符
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

	//Z字形变换 https://leetcode-cn.com/problems/zigzag-conversion/
	//寻找其中的变化规律即可
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

	//反转整数 https://leetcode-cn.com/problems/reverse-integer/
	int reverse(int x) {
		int tmp = abs(x);
		int res = 0;
		while (tmp)
		{
			int tmp2 = tmp % 10;
			if (res > (0x7fffffff - tmp2) / 10)return 0;   //此处可以改进更精确，如下
			//if (res > INT_MAX / 10 || (res == INT_MAX / 10 && tmp2 > 7)) return 0;//正数情况
			//if (res < INT_MIN / 10 || (res == INT_MIN / 10 && tmp2 < -8)) return 0;//负数情况
			res = res * 10 + tmp2;
			tmp /= 10;
		}

		if (x < 0)res = -res;
		return res;
	}

	//字符串转整数 (atoi) https://leetcode-cn.com/problems/string-to-integer-atoi/
	//这个函数没有考虑到e的表示法
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

	//回文数 https://leetcode-cn.com/problems/palindrome-number/
	//下面的方法是通过翻转数字来比较
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

	//下面是转换成字符串比较
	bool isPalindrome_1(int x) {
		if (x < 0)return false;

		string num = to_string(x), tmp = num;
		using std::reverse;
		reverse(tmp.begin(), tmp.end());

		return num == tmp;
	}

	//盛水最多的容器 https://leetcode-cn.com/problems/container-with-most-water/description/
	//可以用暴力法O(n2)，最佳方法的双指针方法，O(n)
	int maxArea(vector<int>& height) {
		int l = 0, r = height.size() - 1;  //左右两个指针
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

	//整数转罗马数字 https://leetcode-cn.com/problems/integer-to-roman/
	//由于输入数字小于3999所以就进行每一位的处理，没有使用循环
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

	//罗马数字转整数 https://leetcode-cn.com/problems/roman-to-integer/
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

	//最长公共前缀 https://leetcode-cn.com/problems/longest-common-prefix/
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

	//三数之和 https://leetcode-cn.com/problems/3sum/
	//leetcode 3000个元素的用例超时
	vector<vector<int>> threeSum(vector<int>& nums) {
		sort(nums.begin(), nums.end());  //对数组进行排序
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
					break;
				}

			if (tmp + nums[r] < 0)
			{ 
				int lt = l; l++;
				while (l < nums.size() && nums[l] == nums[lt]) { l++; lt++; };
				if (l < r)r = nums.size() - 1;
				continue; 
			}
			else if (tmp + nums[r] >= 0)
			{ 
				int rt = r; r--;
				while (r < nums.size() && nums[r] == nums[rt]) { r--; rt--; };
			}
		}
		return res;
	}

	//下面的方法就是使用基准值
	vector<vector<int>> threeSum_1(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		vector<vector<int>> res;
		vector<int> n(3, 0);

		for (int i = 0; i < nums.size() - 2; ++i)
		{
			int l = i + 1, r = nums.size() - 1;
			int tmp = -nums[i];
			while (l < r)
			{
				if (nums[l] + nums[r] == tmp)
				{
					n[0] = -tmp; n[1] = nums[l]; n[2] = nums[r];
					res.push_back(n);
					cout << "[" << n[0] << " ," << n[1] << " ," << n[2] << "]" << endl;
					l++;
					while (l < r && nums[l - 1] == nums[l])l++;
					r--;   //基准值未改变，左边的值改变，右边的值也要改变
				}
				else if (nums[l] + nums[r] < tmp)
				{
					l++;
					while (l < r && nums[l - 1] == nums[l])l++;
				}
				else
					r--;
			}
			while (i + 1 < nums.size() - 2 && nums[i] == nums[i + 1])i++;
		}
		return res;
	}

	//最接近的三数之和 https://leetcode-cn.com/problems/3sum-closest/
	int threeSumClosest(vector<int>& nums, int target) {
		sort(nums.begin(), nums.end());
		int min = INT_MAX;
		int res;

		for (int i = 0; i < nums.size() - 2; ++i)
		{
			int l = i + 1, r = nums.size() - 1;
			int p = nums[i] - target;
			while (r > l)
			{
				int tmp = p + nums[l] + nums[r];
				if (abs(tmp) < 1)return target;
				if (abs(tmp) < min) { min = abs(tmp); res = tmp + target; }
				if (tmp < 0)
				{
					int lt = l; l++;
					while (l >= 0 && nums[lt] == nums[l]) { lt++; l++; }
				}
				else
				{
					int rt = r; r--;
					while (r < nums.size() && nums[rt] == nums[r]) { rt--; r--; }
				}
			}
		}
		return res;
	}

	//电话号码的字母组合 https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number/
	//递归方法
	vector<string> letterCombinations(string digits) {
		if (digits.length() == 0) return vector<string>();

		vector<char> cs;
		int index = digits[0] - '2';

		switch (digits[0])
		{
		case '2':cs = { 'a','b','c' }; break;
		case '3':cs = { 'd','e','f' }; break;
		case '4':cs = { 'g','h','i' }; break;
		case '5':cs = { 'j','k','l' }; break;
		case '6':cs = { 'm','n','o' }; break;
		case '7':cs = { 'p','q','r','s' }; break;
		case '8':cs = { 't','u','v' }; break;
		case '9':cs = { 'w','x','y','z' }; break;
		}

		vector<string> res;
		for (int i = 0; i < cs.size(); ++i)
		{
			vector<string> tmp = letterCombinations(digits.substr(1));
			if (tmp.size() == 0)tmp = { "" };
			for (auto &it : tmp)
				it = cs[i] + it;
			res.insert(res.end(), tmp.begin(), tmp.end());
		}

		return res;
	}

	//四数之和 https://leetcode-cn.com/problems/4sum/
	vector<vector<int>> fourSum(vector<int>& nums, int target) {
		sort(nums.begin(), nums.end());
		vector<vector<int>> res;
		if (nums.size() < 4)return res;
		vector<int> n(4);

		for (int i = 0; i < nums.size() - 3; ++i)
		{
			for (int j = i + 1; j < nums.size() - 2; ++j)
			{
				int l = j + 1, r = nums.size() - 1;
				int sumt = target - nums[i] - nums[j];
				while (l < r)
				{
					if (nums[l] + nums[r] == sumt)
					{
						n[0] = nums[i]; n[1] = nums[j]; n[2] = nums[l]; n[3] = nums[r];
						res.push_back(n);

						l++;
						while (l < r&&nums[l - 1] == nums[l])l++;
						r--;
					}
					else if (nums[l] + nums[r] < sumt)
					{
						l++;
						while (l < r&&nums[l - 1] == nums[l])l++;
					}
					else
						r--;
				}

				while (j < nums.size() - 2 && nums[j] == nums[j + 1])j++;   
			}
			while (i < nums.size() - 3 && nums[i] == nums[i + 1])i++;     //这里也需要忽略相同数
		}

		return res;
	}

	//删除链表的倒数第N个结点 https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list/
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		if (head == NULL)return NULL;
		ListNode* front = head;
		ListNode* back = head;
		int i = n;
		while (i)
		{
			back = back->next;
			i--;
		}
		if (back == NULL)  return head->next; 

		while (back->next)
		{
			back = back->next;
			front = front->next;
		}

		ListNode* tmp = front->next;
		front->next = tmp->next;
		delete tmp;

		return head;
	}

	//有效的括号 https://leetcode-cn.com/problems/valid-parentheses/
	//利用栈的特性解决该问题
	bool isValid(string s) {
		int len = s.length();
		if (!len)return true;

		stack<char> strs;
		for (int i = 0; i < len; ++i)
		{
			if (!strs.empty() && ((strs.top() == '('&&s[i] == ')') || (strs.top() == '{'&&s[i] == '}') || (strs.top() == '['&&s[i] == ']')))
				strs.pop();
			else
				strs.push(s[i]);
		}
		if (strs.empty())return true;
		return false;
	}

	//括号生成 https://leetcode-cn.com/problems/generate-parentheses/description/
	//使用递归回溯的方法
	vector<string> generateParenthesis(int n) {
		vector<string> res;
		if (n == 0)return res;

		dfs(0, 0, "", res, n);
		return res;
	}

	void dfs(int l, int r, string buffer, vector<string>& res, int n) {
		if (l == n && r == n)
			res.push_back(buffer);

		if (l < n)
			dfs(l + 1, r, buffer + "(", res, n);
		if (r < l)
			dfs(l, r + 1, buffer + ")", res, n);
	}

	//合并k个排序链表 https://leetcode-cn.com/problems/merge-k-sorted-lists/submissions/
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		if (lists.size() == 0)return NULL;
		ListNode* first = NULL, *tmpfirst = NULL;
		while (lists.size())
		{
			int minindex = -1, min = INT_MAX;
			for (int i = 0; i < lists.size(); ++i)
			{
				if (lists[i] == NULL) { lists.erase(lists.begin() + i); --i; continue; }
				if (min > lists[i]->val) { minindex = i; min = lists[i]->val; }
			}
			if (minindex < 0)continue;
			if (first == NULL)first = lists[minindex];
			if (tmpfirst == NULL) { tmpfirst = lists[minindex]; }
			else { tmpfirst->next = lists[minindex]; tmpfirst = tmpfirst->next; }
			lists[minindex] = lists[minindex]->next;
		}

		return first;
	}

	//两两交换链表中的节点 https://leetcode-cn.com/problems/swap-nodes-in-pairs/submissions/
	ListNode* swapPairs(ListNode* head) {
		if (head == NULL) return NULL;
		ListNode *left = NULL, *mid = NULL, *first = head->next;
		if (first == NULL)return head;

		while (head)
		{
			if (head->next)
			{
				if (head->next->next)mid = head->next->next;
				head->next->next = head;
				if (left)left->next = head->next;
				head->next = NULL;
			}
			else if (!head->next&&left)left->next = head;

			left = head;
			head = mid;
			mid = NULL;
		}
		return first;
	}

	//k个一组翻转链表 https://leetcode-cn.com/problems/reverse-nodes-in-k-group/submissions/
	//方法略复杂
	ListNode* reverseKGroup(ListNode* head, int k) {
		if (head == NULL)return NULL;
		ListNode* t = head;
		ListNode* left = head, *first = head, *res = head, *pre = NULL;
		head = head->next;

		int nodeCounts = 0;
		while (t) { nodeCounts++; t = t->next; }  //计算链表节点个数

		//分组翻转链表
		for (int j = 0; j < nodeCounts / k; ++j)
		{
			for (int i = 0; i < k - 1; ++i)
			{
				if (head == NULL)break;
				ListNode* tmp = head->next;
				head->next = left;
				left = head;
				if (pre)pre->next = head;  //用于连接下一组
				head = tmp;
				first->next = head;
			}
			//准备下一组翻转
			if (j == 0)res = left;
			pre = first;
			first = head;
			left = head;
			if (head)head = head->next;
		}

		return res;
	}

	//删除排序数组中的重复项 https://leetcode-cn.com/problems/remove-duplicates-from-sorted-array/submissions/
	int removeDuplicates(vector<int>& nums) {
		if (nums.size() <= 1)return nums.size();
		int pre = nums[0];
		for (int i = 1; i < nums.size(); ++i)
		{
			if (nums[i] == pre)
			{
				nums.erase(nums.begin() + i);
				i--;
			}
			else
				pre = nums[i];
		}
		return nums.size();
	}

	//方法二 双指针法（快慢指针），把不同的元素往前放
	int removeDuplicates(vector<int>& nums) {
		if (nums.size() == 0)return 0;
		int i = 0;
		for (int j = 1; j < nums.size(); ++j)
		{
			if (nums[j] != nums[i])
			{
				i++;
				nums[i] = nums[j];
			}
		}
		return i + 1;
	}

	//移除元素 https://leetcode-cn.com/problems/remove-element/submissions/
	//双指针方法（左右开始），O(n)复杂度
	int removeElement(vector<int>& nums, int val) {
		if (nums.size() == 0)return 0;
		int l = 0, r = nums.size() - 1;
		while (l <= r)
		{
			if (nums[l] == val)
			{
				if (nums[r] != val)
				{
					nums[l] = nums[r];
					r--; l++;
				}
				else
					r--;
			}
			else
				l++;
		}

		return l;
	}

	//实现strStr() https://leetcode-cn.com/problems/implement-strstr/submissions/
	//使用了最简单的方法
	int strStr(string haystack, string needle) {
		if (needle.length() == 0)return 0;
		int last = haystack.length() - needle.length() + 1;

		for (int i = 0; i < last; ++i)
		{
			int tmp = i;
			for (int j = 0; j < needle.length(); ++j)
			{
				if (haystack[tmp] == needle[j])
					if (j == needle.length() - 1)return i;
					else { tmp++; continue; }
				else
					break;
			}
		}

		return -1;
	}

	//两数相除 https://leetcode-cn.com/problems/divide-two-integers/submissions/
	//实现的比较复杂
	int divide(int dividend, int divisor) {
		if (dividend == 0)return 0;
		int res = 0;
		int tmpres = 1;
		bool a = dividend > 0 ? true : false;
		bool b = divisor > 0 ? true : false;
		//最值都一一列出单独解决
		if (divisor == INT_MAX)
		{
			if (dividend == INT_MAX)return 1;
			if (dividend == INT_MIN)return -1;
			return 0;
		}

		if (divisor == INT_MIN)if (dividend == INT_MIN)return 1; else return 0;
		int absdd = abs(dividend), absdr = abs(divisor);
		if (dividend == INT_MIN)
		{
			absdd = INT_MAX;
			absdd -= (absdr - 1);
			res++;
		}
		int tmpdr = absdr;
		while (absdd >= absdr)
		{
			absdd -= tmpdr;
			res += tmpres;

			if (absdd >= abs(tmpdr + tmpdr))
			{
				tmpdr = tmpdr + tmpdr;
				tmpres = tmpres + tmpres;
			}
			else
			{
				tmpdr = absdr;
				tmpres = 1;
			}
			if (!(a^b) && INT_MAX - res < tmpres)return INT_MAX;
			if (a^b&&INT_MAX - res + 1 < tmpres)return INT_MIN;
		}

		if (a^b)res = -res;

		return res;
	}

	//位操作解决
	int divide_bit(int dividend, int divisor) {
		//转换成long long类型可以避免溢出问题
		if (divisor == 0 || (dividend == INT_MIN && divisor == -1)) return INT_MAX;
		long long m = abs((long long)dividend), n = abs((long long)divisor), res = 0;
		int sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1;    //判断结果正负
		if (n == 1) return sign == 1 ? m : -m;

		//思想与上面的方法一样，只不过这里使用位操作来实现倍数增加
		//同样就是要避免逐个相加，这样如果除数大就会造成多次循环
		while (m >= n) {
			long long t = n, p = 1;
			while (m >= (t << 1)) {
				t <<= 1;
				p <<= 1;  //
			}
			res += p;
			m -= t;  //处理剩余的
		}
		return sign == 1 ? res : -res;
	}

	//搜索旋转排序数组 https://leetcode-cn.com/problems/search-in-rotated-sorted-array/submissions/
	int search(vector<int>& nums, int target) {
		int l = 0, r = nums.size() - 1;
		if (nums.size() == 1)
			if (nums[0] == target)return 0;
			else return -1;
		int len = nums.size();
		while (l < r)
		{
			if (nums[l] == target)return l;
			if (nums[r] == target)return r;
			if (r - l == 1)return -1;
			int c = (l + r) / 2;

			//就是分情况考虑，在左边的情况和在右边的情况
			if (nums[l] >= target && nums[c] >= target && nums[l] > nums[c]) { r = c; continue; }
			if (nums[l] <= target && nums[c] <= target && nums[l] > nums[c]) { r = c; continue; }
			if (nums[l] <= target && nums[c] >= target) { r = c; continue; }

			if (nums[r] >= target) { l = c; continue; }
			if (nums[r] <= target && nums[c] <= target) { l = c; continue; }

			return -1;
		}
		return -1;
	}

	//在排序数组中查找元素的第一个和最后一个位置（log(n)复杂度）  https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/
	vector<int> res;
	vector<int> searchRange(vector<int>& nums, int target) {
		int l = 0, r = nums.size() - 1;
		res = vector<int>(2, -1);

		searchRangeImpl(nums, target, 0, r);
		return res;
	}

	void searchRangeImpl(vector<int>& nums, int target, int left, int right)
	{
		if (left > right)return;
		int mid = (left + right) / 2;

		if (nums[mid] == target)
		{
			if (mid == 0 || nums[mid - 1] < target)
			{
				res[0] = mid;
				searchRangeImpl(nums, target, mid + 1, right);
			}
			if (mid == nums.size() - 1 || nums[mid + 1] > target)
			{
				res[1] = mid;
				searchRangeImpl(nums, target, left, mid - 1);
			}

			searchRangeImpl(nums, target, left, mid - 1);
			searchRangeImpl(nums, target, mid + 1, right);
			return;
		}
		else if (nums[mid] > target)searchRangeImpl(nums, target, left, mid - 1);
		else searchRangeImpl(nums, target, mid + 1, right);
		return;
	}

	//与所有单词相关联的字串 https://leetcode-cn.com/problems/substring-with-concatenation-of-all-words/
	//下面的方法是使用哈希表
	vector<int> findSubstring(string s, vector<string>& words)
	{
		vector<int> res;
		if (s.empty() || words.empty()) return res;
		int n = words.size(), m = words[0].size();
		unordered_map<string, int> m1;
		for (auto &a : words) ++m1[a];

		for (int i = 0; i <= (int)s.size() - n * m; ++i) 
		{
			unordered_map<string, int> m2;   //辅助哈希表
			int j = 0;
			for (j = 0; j < n; ++j) 
			{
				string t = s.substr(i + j * m, m);
				if (m1.find(t) == m1.end()) break;
				++m2[t];
				if (m2[t] > m1[t]) break;
			}

			if (j == n) res.push_back(i);
		}
		return res;
		
	}
	//方法二，使用动态规划
	vector<int> findSubstring_1(string s, vector<string>& words) {
		vector<int>re;
		if (s.empty() || words.empty()) return re;
		int n = words[0].size(), length1 = s.size(), length2 = words.size();
		map<string, int> aa;
		for (auto x : words) ++aa[x];

		for (int i = 0; i < n; ++i) {
			int l = i, r = i;      //  l指向滑动窗口最左边的单词的起始点， r指向滑动窗口最右边的单词的起始点
			map<string, int> bb;
			while (r + n <= s.size()) {
				if (aa.count(s.substr(r, n))) {      //有效单词
					string wd = s.substr(r, n);
					++bb[wd];
					r += n;
					if (bb[wd] < aa[wd]) continue;    // 当前单词个数小于目标单词个数，r右移，添加最右端单词(continue,跳到下一次循环自动执行)

					//下面的就涉及到动态规划
					while (bb[wd] > aa[wd]) {       //当前单词个数大于目标单词个数，删除最左端单词，l右移
						if (--bb[s.substr(l, n)] == 0)
							bb.erase(s.substr(l, n));
						l += n;
					}    //这里一定要注意用while循环（而不是if），直到当前单词个数等于目标单词个数


					if (bb[wd] == aa[wd] && r - l == length2 * n) {  //当前单词个数等于目标单词个数，比较目前单词总数与目标单词总数是否相等，
						//如果不相等：r右移，添加最右端单词(跳到下一次循环自动执行)。如果相等：删除最左端单词，l右移；r右移，添加最右端单词(跳到下一次循环自动执行)。
						re.push_back(l);
						if (--bb[s.substr(l, n)] == 0)
							bb.erase(s.substr(l, n));
						l += n;
					}
				}
				else {  //如果单词无效，则l,r跳到下一个单词处重新开始计数
					bb.clear();
					r += n;
					l = r;
				}
			}
		}
		return re;
	}

	//下一个排列 https://leetcode-cn.com/problems/next-permutation/
	void nextPermutation(vector<int>& nums) {
		int len = nums.size();
		int i = 0;
		for (i = len - 2; i >= 0; --i)
		{
			int tmp = i, min = INT_MAX;
			for (int j = i + 1; j < len; ++j)
			{
				if (nums[i] < nums[j])
				{
					if (nums[j] - nums[i] < min)
					{
						min = nums[j] - nums[i];
						tmp = j;
					}
				}
			}
			if (i != tmp)
			{
				swap(nums[i], nums[tmp]);
				sort(nums.begin() + i + 1, nums.end());     //对后面的数进行排序
				return;
			}
		}

		sort(nums.begin(), nums.end());
	}

	//方法二，直接进行排序处理，效率较高
	void nextPermutation_1(vector<int>& nums){
		int len = nums.size();
		int i = 0;

		for (int i = len - 2; i >= 0; --i)
		{
			int tmp = nums[i];
			for (int j = i + 1; j < len; ++j)
			{
				if (tmp >= nums[j])
				{
					swap(nums[j - 1], nums[j]);
				}
				else
				{
					tmp = nums[j];
					nums.erase(nums.begin() + j);
					nums.insert(nums.begin() + i, tmp);
					return;
				}
			}
		}
	}

	//搜索插入位置 https://leetcode-cn.com/problems/search-insert-position/
	//直接迭代查找
	int searchInsert(vector<int>& nums, int target) {
		if (nums.size() == 0)return 0;

		for (int i = 0; i < nums.size(); ++i)
		{
			if (nums[i] == target)return i;
			if (nums[i] > target)return i;
		}
		return nums.size();
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

	//3000个数，超时
	vector<int> nums = { 82597,-9243,62390,83030,-97960,-26521,-61011,83390,-38677,12333,75987,46091,83794,19355,-71037,-6242,-28801,324,1202,-90885,
						-2989,-95597,-34333,35528,5680,89093,-90606,50360,-29393,-27012,53313,65213,99818,-82405,-41661,-3333,-51952,72135,-1523,26377,
						74685,96992,92263,15929,5467,-99555,-43348,-41689,-60383,-3990,32165,65265,-72973,-58372,12741,-48568,-46596,72419,-1859,34153,
						62937,81310,-61823,-96770,-54944,8845,-91184,24208,-29078,31495,65258,14198,85395,70506,-40908,56740,-12228,-40072,32429,93001,68445,
						-73927,25731,-91859,-24150,10093,-60271,-81683,-18126,51055,48189,-6468,25057,81194,-58628,74042,66158,-14452,-49851,-43667,11092,39189,
						-17025,-79173,13606,83172,92647,-59741,19343,-26644,-57607,82908,-20655,1637,80060,98994,39331,-31274,-61523,91225,-72953,13211,-75116,-98421,
						-41571,-69074,99587,39345,42151,-2460,98236,15690,-52507,-95803,-48935,-46492,-45606,-79254,-99851,52533,73486,39948,-7240,71815,-585,-96252,90990,
						-93815,93340,-71848,58733,-14859,-83082,-75794,-82082,-24871,-15206,91207,-56469,-93618,67131,-8682,75719,87429,-98757,-7535,-24890,-94160,85003,
						33928,75538,97456,-66424,-60074,-8527,-28697,-22308,2246,-70134,-82319,-10184,87081,-34949,-28645,-47352,-83966,-60418,-15293,-53067,-25921,55172,
						75064,95859,48049,34311,-86931,-38586,33686,-36714,96922,76713,-22165,-80585,-34503,-44516,39217,-28457,47227,-94036,43457,24626,-87359,26898,-70819,
						30528,-32397,-69486,84912,-1187,-98986,-32958,4280,-79129,-65604,9344,58964,50584,71128,-55480,24986,15086,-62360,-42977,-49482,-77256,-36895,-74818,20,
						3063,-49426,28152,-97329,6086,86035,-88743,35241,44249,19927,-10660,89404,24179,-26621,-6511,57745,-28750,96340,-97160,-97822,-49979,52307,79462,94273,
						-24808,77104,9255,-83057,77655,21361,55956,-9096,48599,-40490,-55107,2689,29608,20497,66834,-34678,23553,-81400,-66630,-96321,-34499,-12957,-20564,
						25610,-4322,-58462,20801,53700,71527,24669,-54534,57879,-3221,33636,3900,97832,-27688,-98715,5992,24520,-55401,-57613,-69926,57377,-77610,20123,
						52174,860,60429,-91994,-62403,-6218,-90610,-37263,-15052,62069,-96465,44254,89892,-3406,19121,-41842,-87783,-64125,-56120,73904,-22797,-58118,
						-4866,5356,75318,46119,21276,-19246,-9241,-97425,57333,-15802,93149,25689,-5532,95716,39209,-87672,-29470,-16324,-15331,27632,-39454,56530,-16000,
						29853,46475,78242,-46602,83192,-73440,-15816,50964,-36601,89758,38375,-40007,-36675,-94030,67576,46811,-64919,45595,76530,40398,35845,41791,67697,-30439,-82944,63115,
						33447,-36046,-50122,-34789,43003,-78947,-38763,-89210,32756,-20389,-31358,-90526,-81607,88741,86643,98422,47389,-75189,13091,95993,-15501,94260,-25584,-1483,-67261,
						-70753,25160,89614,-90620,-48542,83889,-12388,-9642,-37043,-67663,28794,-8801,13621,12241,55379,84290,21692,-95906,-85617,-17341,-63767,80183,-4942,
						-51478,30997,-13658,8838,17452,-82869,-39897,68449,31964,98158,-49489,62283,-62209,-92792,-59342,55146,-38533,20496,62667,62593,36095,-12470,5453,
						-50451,74716,-17902,3302,-16760,-71642,-34819,96459,-72860,21638,47342,-69897,-40180,44466,76496,84659,13848,-91600,-90887,-63742,-2156,-84981,
						-99280,94326,-33854,92029,-50811,98711,-36459,-75555,79110,-88164,-97397,-84217,97457,64387,30513,-53190,-83215,252,2344,-27177,-92945,-89010,
						82662,-11670,86069,53417,42702,97082,3695,-14530,-46334,17910,77999,28009,-12374,15498,-46941,97088,-35030,95040,92095,-59469,-24761,46491,
						67357,-66658,37446,-65130,-50416,99197,30925,27308,54122,-44719,12582,-99525,-38446,-69050,-22352,94757,-56062,33684,-40199,-46399,96842,
						-50881,-22380,-65021,40582,53623,-76034,77018,-97074,-84838,-22953,-74205,79715,-33920,-35794,-91369,73421,-82492,63680,-14915,-33295,37145,
						76852,-69442,60125,-74166,74308,-1900,-30195,-16267,-60781,-27760,5852,38917,25742,-3765,49097,-63541,98612,-92865,-30248,9612,-8798,53262,
						95781,-42278,-36529,7252,-27394,-5021,59178,80934,-48480,-75131,-54439,-19145,-48140,98457,-6601,-51616,-89730,78028,32083,-48904,16822,-81153,
						-8832,48720,-80728,-45133,-86647,-4259,-40453,2590,28613,50523,-4105,-27790,-74579,-17223,63721,33489,-47921,97628,-97691,-14782,-65644,18008,
						-93651,-71266,80990,-76732,-47104,35368,28632,59818,-86269,-89753,34557,-92230,-5933,-3487,-73557,-13174,-43981,-43630,-55171,30254,-83710,-99583,
						-13500,71787,5017,-25117,-78586,86941,-3251,-23867,-36315,75973,86272,-45575,77462,-98836,-10859,70168,-32971,-38739,-12761,93410,14014,-30706,
						-77356,-85965,-62316,63918,-59914,-64088,1591,-10957,38004,15129,-83602,-51791,34381,-89382,-26056,8942,5465,71458,-73805,-87445,-19921,-80784,
						69150,-34168,28301,-68955,18041,6059,82342,9947,39795,44047,-57313,48569,81936,-2863,-80932,32976,-86454,-84207,33033,32867,9104,-16580,-25727,
						80157,-70169,53741,86522,84651,68480,84018,61932,7332,-61322,-69663,76370,41206,12326,-34689,17016,82975,-23386,39417,72793,44774,-96259,3213,
						79952,29265,-61492,-49337,14162,65886,3342,-41622,-62659,-90402,-24751,88511,54739,-21383,-40161,-96610,-24944,-602,-76842,-21856,69964,43994,
						-15121,-85530,12718,13170,-13547,69222,62417,-75305,-81446,-38786,-52075,-23110,97681,-82800,-53178,11474,35857,94197,-58148,-23689,32506,92154,
						-64536,-73930,-77138,97446,-83459,70963,22452,68472,-3728,-25059,-49405,95129,-6167,12808,99918,30113,-12641,-26665,86362,-33505,50661,26714,
						33701,89012,-91540,40517,-12716,-57185,-87230,29914,-59560,13200,-72723,58272,23913,-45586,-96593,-26265,-2141,31087,81399,92511,-34049,20577,
						2803,26003,8940,42117,40887,-82715,38269,40969,-50022,72088,21291,-67280,-16523,90535,18669,94342,-39568,-88080,-99486,-20716,23108,-28037,
						63342,36863,-29420,-44016,75135,73415,16059,-4899,86893,43136,-7041,33483,-67612,25327,40830,6184,61805,4247,81119,-22854,-26104,-63466,63093,
						-63685,60369,51023,51644,-16350,74438,-83514,99083,10079,-58451,-79621,48471,67131,-86940,99093,11855,-22272,-67683,-44371,9541,18123,37766,
						-70922,80385,-57513,-76021,-47890,36154,72935,84387,-92681,-88303,-7810,59902,-90,-64704,-28396,-66403,8860,13343,33882,85680,7228,28160,
						-14003,54369,-58893,92606,-63492,-10101,64714,58486,29948,-44679,-22763,10151,-56695,4031,-18242,-36232,86168,-14263,9883,47124,47271,92761,
						-24958,-73263,-79661,-69147,-18874,29546,-92588,-85771,26451,-86650,-43306,-59094,-47492,-34821,-91763,-47670,33537,22843,67417,-759,92159,
						63075,94065,-26988,55276,65903,30414,-67129,-99508,-83092,-91493,-50426,14349,-83216,-76090,32742,-5306,-93310,-60750,-60620,-45484,-21108,
						-58341,-28048,-52803,69735,78906,81649,32565,-86804,-83202,-65688,-1760,89707,93322,-72750,84134,71900,-37720,19450,-78018,22001,-23604,26276,
						-21498,65892,-72117,-89834,-23867,55817,-77963,42518,93123,-83916,63260,-2243,-97108,85442,-36775,17984,-58810,99664,-19082,93075,-69329,87061,
						79713,16296,70996,13483,-74582,49900,-27669,-40562,1209,-20572,34660,83193,75579,7344,64925,88361,60969,3114,44611,-27445,53049,-16085,-92851,
						-53306,13859,-33532,86622,-75666,-18159,-98256,51875,-42251,-27977,-18080,23772,38160,41779,9147,94175,99905,-85755,62535,-88412,-52038,-68171,
						93255,-44684,-11242,-104,31796,62346,-54931,-55790,-70032,46221,56541,-91947,90592,93503,4071,20646,4856,-63598,15396,-50708,32138,-85164,38528,
						-89959,53852,57915,-42421,-88916,-75072,67030,-29066,49542,-71591,61708,-53985,-43051,28483,46991,-83216,80991,-46254,-48716,39356,-8270,-47763,
						-34410,874,-1186,-7049,28846,11276,21960,-13304,-11433,-4913,55754,79616,70423,-27523,64803,49277,14906,-97401,-92390,91075,70736,21971,-3303,
						55333,-93996,76538,54603,-75899,98801,46887,35041,48302,-52318,55439,24574,14079,-24889,83440,14961,34312,-89260,-22293,-81271,-2586,-71059,
						-10640,-93095,-5453,-70041,66543,74012,-11662,-52477,-37597,-70919,92971,-17452,-67306,-80418,7225,-89296,24296,86547,37154,-10696,74436,
						-63959,58860,33590,-88925,-97814,-83664,85484,-8385,-50879,57729,-74728,-87852,-15524,-91120,22062,28134,80917,32026,49707,-54252,-44319,
						-35139,13777,44660,85274,25043,58781,-89035,-76274,6364,-63625,72855,43242,-35033,12820,-27460,77372,-47578,-61162,-70758,-1343,-4159,64935,
						56024,-2151,43770,19758,-30186,-86040,24666,-62332,-67542,73180,-25821,-27826,-45504,-36858,-12041,20017,-24066,-56625,-52097,-47239,-90694,
						8959,7712,-14258,-5860,55349,61808,-4423,-93703,64681,-98641,-25222,46999,-83831,-54714,19997,-68477,66073,51801,-66491,52061,-52866,79907,
						-39736,-68331,68937,91464,98892,910,93501,31295,-85873,27036,-57340,50412,21,-2445,29471,71317,82093,-94823,-54458,-97410,39560,-7628,66452,
						39701,54029,37906,46773,58296,60370,-61090,85501,-86874,71443,-72702,-72047,14848,34102,77975,-66294,-36576,31349,52493,-70833,-80287,94435,
						39745,-98291,84524,-18942,10236,93448,50846,94023,-6939,47999,14740,30165,81048,84935,-19177,-13594,32289,62628,-90612,-542,-66627,64255,71199,
						-83841,-82943,-73885,8623,-67214,-9474,-35249,62254,-14087,-90969,21515,-83303,94377,-91619,19956,-98810,96727,-91939,29119,-85473,-82153,
						-69008,44850,74299,-76459,-86464,8315,-49912,-28665,59052,-69708,76024,-92738,50098,18683,-91438,18096,-19335,35659,91826,15779,-73070,67873,
						-12458,-71440,-46721,54856,97212,-81875,35805,36952,68498,81627,-34231,81712,27100,-9741,-82612,18766,-36392,2759,41728,69743,26825,48355,
						-17790,17165,56558,3295,-24375,55669,-16109,24079,73414,48990,-11931,-78214,90745,19878,35673,-15317,-89086,94675,-92513,88410,-93248,-19475,
						-74041,-19165,32329,-26266,-46828,-18747,45328,8990,-78219,-25874,-74801,-44956,-54577,-29756,-99822,-35731,-18348,-68915,-83518,-53451,95471,
						-2954,-13706,-8763,-21642,-37210,16814,-60070,-42743,27697,-36333,-42362,11576,85742,-82536,68767,-56103,-63012,71396,-78464,-68101,-15917,-11113,
						-3596,77626,-60191,-30585,-73584,6214,-84303,18403,23618,-15619,-89755,-59515,-59103,-74308,-63725,-29364,-52376,-96130,70894,-12609,50845,
						-2314,42264,-70825,64481,55752,4460,-68603,-88701,4713,-50441,-51333,-77907,97412,-66616,-49430,60489,-85262,-97621,-18980,44727,-69321,
						-57730,66287,-92566,-64427,-14270,11515,-92612,-87645,61557,24197,-81923,-39831,-10301,-23640,-76219,-68025,92761,-76493,68554,-77734,
						-95620,-11753,-51700,98234,-68544,-61838,29467,46603,-18221,-35441,74537,40327,-58293,75755,-57301,-7532,-94163,18179,-14388,-22258,
						-46417,-48285,18242,-77551,82620,250,-20060,-79568,-77259,82052,-98897,-75464,48773,-79040,-11293,45941,-67876,-69204,-46477,-46107,
						792,60546,-34573,-12879,-94562,20356,-48004,-62429,96242,40594,2099,99494,25724,-39394,-2388,-18563,-56510,-83570,-29214,3015,74454,
						74197,76678,-46597,60630,-76093,37578,-82045,-24077,62082,-87787,-74936,58687,12200,-98952,70155,-77370,21710,-84625,-60556,-84128,
						925,65474,-15741,-94619,88377,89334,44749,22002,-45750,-93081,-14600,-83447,46691,85040,-66447,-80085,56308,44310,24979,-29694,57991,
						4675,-71273,-44508,13615,-54710,23552,-78253,-34637,50497,68706,81543,-88408,-21405,6001,-33834,-21570,-46692,-25344,20310,71258,-97680,
						11721,59977,59247,-48949,98955,-50276,-80844,-27935,-76102,55858,-33492,40680,66691,-33188,8284,64893,-7528,6019,-85523,8434,-64366,
						-56663,26862,30008,-7611,-12179,-70076,21426,-11261,-36864,-61937,-59677,929,-21052,3848,-20888,-16065,98995,-32293,-86121,-54564,77831,
						68602,74977,31658,40699,29755,98424,80358,-69337,26339,13213,-46016,-18331,64713,-46883,-58451,-70024,-92393,-4088,70628,-51185,71164,
						-75791,-1636,-29102,-16929,-87650,-84589,-24229,-42137,-15653,94825,13042,88499,-47100,-90358,-7180,29754,-65727,-42659,-85560,-9037,
						-52459,20997,-47425,17318,21122,20472,-23037,65216,-63625,-7877,-91907,24100,-72516,22903,-85247,-8938,73878,54953,87480,-31466,-99524,
						35369,-78376,89984,-15982,94045,-7269,23319,-80456,-37653,-76756,2909,81936,54958,-12393,60560,-84664,-82413,66941,-26573,-97532,64460,
						18593,-85789,-38820,-92575,-43663,-89435,83272,-50585,13616,-71541,-53156,727,-27644,16538,34049,57745,34348,35009,16634,-18791,23271,
						-63844,95817,21781,16590,59669,15966,-6864,48050,-36143,97427,-59390,96931,78939,-1958,50777,43338,-51149,39235,-27054,-43492,67457,
						-83616,37179,10390,85818,2391,73635,87579,-49127,-81264,-79023,-81590,53554,-74972,-83940,-13726,-39095,29174,78072,76104,47778,25797,
						-29515,-6493,-92793,22481,-36197,-65560,42342,15750,97556,99634,-56048,-35688,13501,63969,-74291,50911,39225,93702,-3490,-59461,-30105,
						-46761,-80113,92906,-68487,50742,36152,-90240,-83631,24597,-50566,-15477,18470,77038,40223,-80364,-98676,70957,-63647,99537,13041,
						31679,86631,37633,-16866,13686,-71565,21652,-46053,-80578,-61382,68487,-6417,4656,20811,67013,-30868,-11219,46,74944,14627,56965,42275,
						-52480,52162,-84883,-52579,-90331,92792,42184,-73422,-58440,65308,-25069,5475,-57996,59557,-17561,2826,-56939,14996,-94855,-53707,
						99159,43645,-67719,-1331,21412,41704,31612,32622,1919,-69333,-69828,22422,-78842,57896,-17363,27979,-76897,35008,46482,-75289,65799,
						20057,7170,41326,-76069,90840,-81253,-50749,3649,-42315,45238,-33924,62101,96906,58884,-7617,-28689,-66578,62458,50876,-57553,6739,
						41014,-64040,-34916,37940,13048,-97478,-11318,-89440,-31933,-40357,-59737,-76718,-14104,-31774,28001,4103,41702,-25120,-31654,63085,
						-3642,84870,-83896,-76422,-61520,12900,88678,85547,33132,-88627,52820,63915,-27472,78867,-51439,33005,-23447,-3271,-39308,39726,
						-74260,-31874,-36893,93656,910,-98362,60450,-88048,99308,13947,83996,-90415,-35117,70858,-55332,-31721,97528,82982,-86218,6822,25227,
						36946,97077,-4257,-41526,56795,89870,75860,-70802,21779,14184,-16511,-89156,-31422,71470,69600,-78498,74079,-19410,40311,28501,26397,
						-67574,-32518,68510,38615,19355,-6088,-97159,-29255,-92523,3023,-42536,-88681,64255,41206,44119,52208,39522,-52108,91276,-70514,
						83436,63289,-79741,9623,99559,12642,85950,83735,-21156,-67208,98088,-7341,-27763,-30048,-44099,-14866,-45504,-91704,19369,13700,10481,
						-49344,-85686,33994,19672,36028,60842,66564,-24919,33950,-93616,-47430,-35391,-28279,56806,74690,39284,-96683,-7642,-75232,37657,
						-14531,-86870,-9274,-26173,98640,88652,64257,46457,37814,-19370,9337,-22556,-41525,39105,-28719,51611,-93252,98044,-90996,21710,
						-47605,-64259,-32727,53611,-31918,-3555,33316,-66472,21274,-37731,-2919,15016,48779,-88868,1897,41728,46344,-89667,37848,68092,
						-44011,85354,-43776,38739,-31423,-66330,65167,-22016,59405,34328,-60042,87660,-67698,-59174,-1408,-46809,-43485,-88807,-60489,
						13974,22319,55836,-62995,-37375,-4185,32687,-36551,-75237,58280,26942,-73756,71756,78775,-40573,14367,-71622,-77338,24112,23414,
						-7679,-51721,87492,85066,-21612,57045,10673,-96836,52461,-62218,-9310,65862,-22748,89906,-96987,-98698,26956,
						-43428,46141,47456,28095,55952,67323,-36455,-60202,-43302,-82932,42020,77036,10142,60406,70331,63836,58850,
						-66752,52109,21395,-10238,-98647,-41962,27778,69060,98535,-28680,-52263,-56679,66103,-42426,27203,80021,10153,
						58678,36398,63112,34911,20515,62082,-15659,-40785,27054,43767,-20289,65838,-6954,-60228,-72226,52236,-35464,25209,
						-15462,-79617,-41668,-84083,62404,-69062,18913,46545,20757,13805,24717,-18461,-47009,-25779,68834,64824,34473,39576,
						31570,14861,-15114,-41233,95509,68232,67846,84902,-83060,17642,-18422,73688,77671,-26930,64484,-99637,73875,6428,21034,
						-73471,19664,-68031,15922,-27028,48137,54955,-82793,-41144,-10218,-24921,-28299,-2288,68518,-54452,15686,-41814,66165,-72207,
						-61986,80020,50544,-99500,16244,78998,40989,14525,-56061,-24692,-94790,21111,37296,-90794,72100,70550,-31757,17708,-74290,61910,
						78039,-78629,-25033,73172,-91953,10052,64502,99585,-1741,90324,-73723,68942,28149,30218,24422,16659,10710,-62594,94249,96588,46192,
						34251,73500,-65995,-81168,41412,-98724,-63710,-54696,-52407,19746,45869,27821,-94866,-76705,-13417,-61995,-71560,43450,67384,-8838,
						-80293,-28937,23330,-89694,-40586,46918,80429,-5475,78013,25309,-34162,37236,-77577,86744,26281,-29033,-91813,35347,13033,-13631,
						-24459,3325,-71078,-75359,81311,19700,47678,-74680,-84113,45192,35502,37675,19553,76522,-51098,-18211,89717,4508,-82946,27749,85995,
						89912,-53678,-64727,-14778,32075,-63412,-40524,86440,-2707,-36821,63850,-30883,67294,-99468,-23708,34932,34386,98899,29239,-23385,
						5897,54882,98660,49098,70275,17718,88533,52161,63340,50061,-89457,19491,-99156,24873,-17008,64610,-55543,50495,17056,-10400,
						-56678,-29073,-42960,-76418,98562,-88104,-96255,10159,-90724,54011,12052,45871,-90933,-69420,67039,37202,78051,-52197,-40278,
						-58425,65414,-23394,-1415,6912,-53447,7352,17307,-78147,63727,98905,55412,-57658,-32884,-44878,22755,39730,3638,35111,39777,74193,38736,-11829,
						-61188,-92757,55946,-71232,-63032,-83947,39147,-96684,-99233,25131,-32197,24406,-55428,-61941,25874,-69453,64483,-19644,-68441,12783,87338,
						-48676,66451,-447,-61590,50932,-11270,29035,65698,-63544,10029,80499,-9461,86368,91365,-81810,-71914,-52056,-13782,44240,-30093,-2437,24007,
						67581,-17365,-69164,-8420,-69289,-29370,48010,90439,13141,69243,50668,39328,61731,78266,-81313,17921,-38196,55261,9948,-24970,75712,-72106,
						28696,7461,31621,61047,51476,56512,11839,-96916,-82739,28924,-99927,58449,37280,69357,11219,-32119,-62050,-48745,-83486,-52376,42668,82659,
						68882,38773,46269,-96005,97630,25009,-2951,-67811,99801,81587,-79793,-18547,-83086,69512,33127,-92145,-88497,47703,59527,1909,88785,-88882,
						69188,-46131,-5589,-15086,36255,-53238,-33009,82664,53901,35939,-42946,-25571,33298,69291,53199,74746,-40127,-39050,91033,51717,-98048,87240,
						36172,65453,-94425,-63694,-30027,59004,88660,3649,-20267,-52565,-67321,34037,4320,91515,-56753,60115,27134,68617,-61395,-26503,-98929,-8849,
						-63318,10709,-16151,61905,-95785,5262,23670,-25277,90206,-19391,45735,37208,-31992,-92450,18516,-90452,-58870,-58602,93383,14333,17994,82411,
						-54126,-32576,35440,-60526,-78764,-25069,-9022,-394,92186,-38057,55328,-61569,67780,77169,19546,-92664,-94948,44484,-13439,83529,27518,-48333,
						72998,38342,-90553,-98578,-76906,81515,-16464,78439,92529,35225,-39968,-10130,-7845,-32245,-74955,-74996,67731,-13897,-82493,33407,93619,
						59560,-24404,-57553,19486,-45341,34098,-24978,-33612,79058,71847,76713,-95422,6421,-96075,-59130,-28976,-16922,-62203,69970,68331,21874,40551,
						89650,51908,58181,66480,-68177,34323,-3046,-49656,-59758,43564,-10960,-30796,15473,-20216,46085,-85355,41515,-30669,-87498,57711,56067,63199,
						-83805,62042,91213,-14606,4394,-562,74913,10406,96810,-61595,32564,31640,-9732,42058,98052,-7908,-72330,1558,-80301,34878,32900,3939,-8824,
						88316,20937,21566,-3218,-66080,-31620,86859,54289,90476,-42889,-15016,-18838,75456,30159,-67101,42328,-92703,85850,-5475,23470,-80806,68206,
						17764,88235,46421,-41578,74005,-81142,80545,20868,-1560,64017,83784,68863,-97516,-13016,-72223,79630,-55692,82255,88467,28007,-34686,-69049,
						-41677,88535,-8217,68060,-51280,28971,49088,49235,26905,-81117,-44888,40623,74337,-24662,97476,79542,-72082,-35093,98175,-61761,-68169,59697,
						-62542,-72965,59883,-64026,-37656,-92392,-12113,-73495,98258,68379,-21545,64607,-70957,-92254,-97460,-63436,-8853,-19357,-51965,-76582,12687,
						-49712,45413,-60043,33496,31539,-57347,41837,67280,-68813,52088,-13155,-86430,-15239,-45030,96041,18749,-23992,46048,35243,-79450,85425,-58524,
						88781,-39454,53073,-48864,-82289,39086,82540,-11555,25014,-5431,-39585,-89526,2705,31953,-81611,36985,-56022,68684,-27101,11422,64655,-26965,
						-63081,-13840,-91003,-78147,-8966,41488,1988,99021,-61575,-47060,65260,-23844,-21781,-91865,-19607,44808,2890,63692,-88663,-58272,15970,-65195,
						-45416,-48444,-78226,-65332,-24568,42833,-1806,-71595,80002,-52250,30952,48452,-90106,31015,-22073,62339,63318,78391,28699,77900,-4026,-76870,
						-45943,33665,9174,-84360,-22684,-16832,-67949,-38077,-38987,-32847,51443,-53580,-13505,9344,-92337,26585,70458,-52764,-67471,-68411,-1119,
						-2072,-93476,67981,40887,-89304,-12235,41488,1454,5355,-34855,-72080,24514,-58305,3340,34331,8731,77451,-64983,-57876,82874,62481,-32754,
						-39902,22451,-79095,-23904,78409,-7418,7791 };

										
	//sort(nums.begin(), nums.end());
	
	int num = 1;
	int num2 = 1;
	num2 *= ++num;
	//num2 = num++;
	cout << num2 << endl;
	vector<string> strs = { "afaf","sgsdgsg","sgsdgs" };
	
	for (auto &it : strs)
	{
		char a = 'b';
		it += a;
	}

	for (auto it : strs)
		cout << it << endl;
	//string str = "abcdefg";
	//reverse(str.begin(), str.end());

	char a[10], *p = a;
	
	stack<int> st;
	
	system("pause");

	return 0;
};