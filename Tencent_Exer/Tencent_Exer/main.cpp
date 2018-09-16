#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//int LCM(vector<int> nums, int max)
//{
//	int numCount = nums.size();
//	int multiCounts = 1;
//	int maxTmp = max;
//	while (maxTmp)
//	{
//		bool lcm = true;
//		for (int i = 0; i < numCount; ++i)
//		{
//			if (maxTmp%nums[i] != 0)
//			{
//				lcm = false;
//				break;
//			}
//		}
//		if (lcm)
//			return maxTmp;
//		multiCounts++;
//		maxTmp = max * multiCounts;
//	}
//	return 0;
//}

int fun(int tmp, int newNum)
{
	int max = tmp;
	if (tmp%newNum == 0)return tmp;
	int maxCount = 2;
	max *= maxCount;

	while (max)
	{
		if (max%newNum == 0)return max;
		maxCount++;
		max = maxCount * tmp;
	}
	return 0;
}


int LCM(int first, int last)
{
	int max = last;
	int size = last - first;
	int multiCount = 1;
	while (max)
	{
		bool lcm = true;
		for (int i = 0; i < size; ++i)
		{
			if (max % (first + i) != 0)
			{
				lcm = false;
				break;
			}
		}

		if (lcm)
			return max;
		multiCount++;
		max = last * multiCount;
	}
	return 0;
}

int main()
{
	int n = 0;
	cin >> n;
	
	/*vector<int> tmp;
	for (int i = 0; i < n; ++i)
		tmp.push_back(i);*/

	int ret = 0;
	int res = n+1;
	int num1 = LCM(1, n);
	for (int i = 2;; ++i)
	{
		res = fun(res, n + i);
		if (res%num1 == 0)
		{
			ret = n + i;
			break;
		}
	}

	cout << ret;

	///*vector<int> nums = { 4,5,6 };
	//cout << LCM(4,6);*/

	/*int t = 0;
	cin >> t;
	vector<vector<int>> nums(t, vector<int>(3));

	for (int i = 0; i < t; ++i)
	{
		cin >> nums[i][0] >> nums[i][1] >> nums[i][2];
	}
	
	cout << "YES" << endl;*/

	system("pause");
	return 0;
}