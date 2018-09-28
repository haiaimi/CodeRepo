#include <iostream>
#include <string>
#include <vector>
#include <minwindef.h>

using namespace std;

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
};

int main()
{
	return 0;
}