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
};

int main()
{
	return 0;
}