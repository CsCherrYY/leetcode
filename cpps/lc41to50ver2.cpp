#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;

class Solution {
public:
	bool isMatch(string s, string p) {
		int len_s = s.length();
		int len_p = p.length();
		vector<vector<bool>> dp(len_s + 1, vector<bool>(len_p + 1, false));
		dp[0][0] = true;
		int i, j;
		for (j = 1; j < len_p + 1; j++) {
			if (p[j - 1] == '*') {
				dp[0][j] = dp[0][j - 1];    //一开始的*
			}
		}
		for (i = 1; i < len_s + 1; i++) {
			for (j = 1; j < len_p + 1; j++) {
				if (p[j-1] == '?') {
					dp[i][j] = dp[i - 1][j - 1];
				}
				else if (p[j - 1] == '*') {
					dp[i][j] = (dp[i - 1][j - 1] | dp[i][j - 1] | dp[i - 1][j]);
					//1、视为空 dp[i][j]=dp[i][j-1]
					//2、视为单个 dp[i][j]=dp[i-1][j-1]
					//3、视为多个 dp[i][j]=dp[i-1][j]
				}
				else {
					if (p[j - 1] == s[i - 1]) {
						dp[i][j] = dp[i - 1][j - 1];
					}
				}
			}
			
		}
		bool ans = dp[len_s][len_p];
		return ans;
	}
	int jump(vector<int>& nums) {
		//最优子结构：到终点前的每一步都是最优的
		/*int sz = nums.size();
		vector<int>dp(sz, sz);
		dp[0] = 0;
		int i, j;
		for (i = 0; i < sz; i++) {
			for (j = 0; j <= nums[i]; j++) {
				if ((i + j) <= sz - 1) {
					dp[i + j] = min(dp[i + j], dp[i] + 1);
				}
			}
		}
		return dp[sz - 1];*/
		//这题DP是n^2(950ms) 贪心法n(12ms)
		int start = 0;
		int far = 0;
		int jumps = 0;
		int i;
		for (i = 0; i < nums.size(); i++) {
			far = max(far, i + nums[i]);
			if (i == start) {
				jumps++;
				start = far;
			}
		}
		return jumps;
	}
	void rotate(vector<vector<int>>& matrix) {
		int n = matrix.size();
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < i; j++)
			{
				swap(matrix[i][j], matrix[j][i]);
			}
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n / 2; j++)
			{
				swap(matrix[i][j], matrix[i][n - j - 1]);
			}
		}
		return;
	}  //先转置后镜像对称
	vector<vector<string>> groupAnagrams(vector<string>& strs) {
		map<char,int>maptable;
		map <map< char, int >, vector<string >> tb;
		map <map< char, int >, vector<string >>::iterator it;
		int i, j, k;
		vector<string>temp;
		vector<vector<string>> tempvec;
		for (i = 0; i < strs.size(); i++) {
			maptable.clear();
			for (j = 0; j < strs[i].length(); j++) {
				if (maptable.find(strs[i][j]) == maptable.end()) {         // map的find 用法
					maptable.insert(pair<char, int>(strs[i][j], 1));
				}
				else {
					maptable[strs[i][j]] += 1;
				}
			}
			if (tb.find(maptable) == tb.end()) {
				temp.clear();
				temp.push_back(strs[i]);
				tb.insert(pair<map< char, int >, vector<string >>(maptable, temp));
			}
			else {
				tb[maptable].push_back(strs[i]);
			}
		}
		for (it=tb.begin(); it != tb.end(); it++) {
			tempvec.push_back(it->second);
		}
		return tempvec;
	}
	double myPow(double x, int n) {
		if (n == 0) {
			return 1;
		}
		int minflag = 0;
		if (n == INT_MIN) {
			minflag = 1;
			n = INT_MAX;
		}
		int absn = abs(n);//min_int?
		vector<int> binary;
		while (absn > 0) {
			binary.push_back(absn % 2);
			absn /= 2;
		}
		int i;
		double res = 1;
		double temp = x;
		for (i = 0; i < binary.size(); i++) {
			if (binary[i] == 1) {
				res *= temp;
			}
			temp *= temp;
		}
		if (n > 0 && !minflag) {
			return res;
		}
		else {
			if (minflag) {
				res /= x;
			}
			return 1/res;
		}
	}
};

int main()
{
	Solution Solu;
	vector<int> temp;
	vector<string> vec;
	vector<vector<string>> solu49;
	int test = 50;
	double solu50;
	bool solu44;
	int solu45;
	switch (test) {
	case 44:
		solu44 = Solu.isMatch("adceb", "*a*b");
		break;
	case 45:
		temp = { 2,3,1,1,4 };
		solu45 = Solu.jump(temp);
		break;
	case 49:
		vec = { "eat", "tea", "tan", "ate", "nat", "bat" };
		solu49 = Solu.groupAnagrams(vec);
		break;
	case 50:
		solu50 = Solu.myPow(2.00000, 10);
		break;
	}
}
