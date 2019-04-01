#include<iostream>
#include<stack>
#include<algorithm>
#include<unordered_map>
#include<vector>
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
using namespace std;
class Solution {
public:
	int minDistance(string word1, string word2) {
		//problem 72
		//dp[i][j] 表示str1[0:i]和str2[0:j]的mindist
		if (!word1.length()) {
			return word2.length();
		}
		if (!word2.length()) {
			return word1.length();
		}
		vector<vector<int>>dp(word1.length() + 1, vector<int>(word2.length() + 1, 0));
		for (int i = 0; i <= word1.length(); i++) {
			dp[i][0] = i;
		}
		for (int i = 0; i <= word2.length(); i++) {
			dp[0][i] = i;
		}
		int minv;
		for (int i = 1; i <= word1.length(); i++) {
			for (int j = 1; j <= word2.length(); j++) {
				if (word1[i - 1] == word2[j - 1]) {
					dp[i][j] = dp[i - 1][j - 1];
				}
				else {
					minv = min(dp[i - 1][j], dp[i][j - 1]);
					minv = min(minv, dp[i - 1][j - 1]);
					dp[i][j] = minv + 1;
				}
			}
		}
		return dp[word1.length()][word2.length()];
	}
	int maxProfit_single(vector<int>& prices) {
		int ret = 0;
		vector<int>dp(prices.size(), 0);
		if (!prices.size()) {
			return 0;
		}
		for (int i = 0; i < prices.size(); i++) {
			if (i == 0) {
				dp[i] = prices[i];
			}
			else {
				dp[i] = min(dp[i - 1], prices[i]);
				ret = max(ret, prices[i] - dp[i - 1]);
			}
		}
		return ret;
	}
	int maxProfit(int k,vector<int>& prices) {
		if (k >= prices.size()-1) {
			int ret = 0;
			for (int i = 0; i < prices.size()-1; i++) {
				if (prices[i] < prices[i + 1]) {
					ret += prices[i + 1] - prices[i];
				}
			}
			return ret;
		}
		vector<vector<int>>dp(k + 1, vector<int>(prices.size(), 0));
		if (prices.size() <= 1) {
			return 0;
		}
		//dp[0][i]=0;
		int ret = 0;
		for (int i = 1; i <= k; i++) {
			int tmpmax = dp[i - 1][0] - prices[0];
			for (int j = 1; j < prices.size(); j++) {
				dp[i][j] = max(dp[i][j - 1], prices[j] + tmpmax);
				tmpmax = max(tmpmax, dp[i - 1][j] - prices[j]);   //这里记录，就不用再遍历一次
				ret = max(dp[i][j], ret);
			}
		}
		return ret;
	}
	int maxv = INT_MIN;
	int maxPathSum(TreeNode* root) {
		getmaxv(root);
		return maxv;
	}
	int getmaxv(TreeNode* root) {
		if (!root) {
			return 0;
		}
		int leftv = getmaxv(root->left);
		int rightv = getmaxv(root->right);  
		int case1 = root->val;
		int case2 = root->val + leftv;
		int case3 = root->val + rightv;
		int case4 = root->val + leftv + rightv;
		//第4种是不和上面的节点连接的
		int max_temp = max(max(case1, case2), max(case3, case4));
		maxv = max(maxv, max_temp);
		return max(max(case1, case2), max(case2, case3));
	}
	bool ishw(string s) {
		if (!s.length()) {
			return true;
		}
		int i = 0;
		int j = s.length() - 1;
		while (i < j) {
			if (s[i] != s[j]) {
				return false;
			}
			i++;
			j--;
		}
		return true;
	}
	int minCut(string s) {
		if (!s.length()) {
			return 0;
		}
		string temp = s;
		reverse(s.begin(), s.end());
		if (s == temp) {
			return 0;
		}
		for (int i = 0; i < s.length(); i++) {
			string temp1 = s.substr(0, i);
			string temp2 = s.substr(i);
			if (ishw(temp1) && ishw(temp2)) {
				return 1;
			}
		}
		vector<int>dp(s.length() + 1, 0);
		for (int i = 0; i < dp.size(); i++) {
			dp[i] = i;
		}
		dp[0] = -1;
		for (int i = 0; i < dp.size() - 1; i++) {
			for (int j = 0; j <= i; j++) {
				if (ishw(s.substr(j, i - j + 1))) {
					dp[i + 1] = min(dp[i + 1], dp[j] + 1);
				}
			}
		}
		return dp[s.length()];
	}
	vector<string> wordBreak(string s, vector<string>& wordDict) {
		vector<string> ret;
		string ans;
		unordered_map<string, string>dp;
		search(s, wordDict, ret, ans, dp);
		return ret;
	}
	void search(string s, vector<string>& wordDict, vector<string> &ret,string ans, unordered_map<string, string>&dp) {
		if (!s.length()) {
			ret.push_back(ans);
		}
		for (auto it : wordDict) {
			if (it == s.substr(0, it.length())) {
				string temp = ans + it;
				if (s.length() != it.length()) {
					temp += " ";
				}
				search(s.substr(it.length()), wordDict, ret, temp);
			}
		}
	}
};
int main() {
	Solution solu;
	return 0;
}