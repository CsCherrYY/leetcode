#include<iostream>
#include<vector>
#include<stack>
#include<unordered_map>
#include<algorithm>
using namespace std;
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
	int lastRemaining(int n) {
		//nÎªÆæÊý
		if (n == 1) {
			return 1;
		}
		else {
			return 2 * (1 + n / 2 - lastRemaining(n / 2));
		}
	}
	bool isSubsequence(string s, string t) {
		if (!s.length()) {
			return true;
		}
		if (!t.length()) {
			return false;
		}
		int points = 0;
		int pointt = 0;
		while (points < s.length()) {
			while (t[pointt] != s[points]) {
				pointt++;
				if (pointt == t.length()) {
					return false;
				}
			}
			points++;
			if (points == s.length()) {
				return false;
			}
			pointt++;
			if (pointt == t.length()) {
				return false;
			}
		}
		return true;
	}
	string decodeString(string s) {

	}
	int maxRotateFunction(vector<int>& A) {
		int sum = 0, F = 0;
		for (int i = 0; i < A.size(); ++i) {
			sum += A[i];
			F += i * A[i];
		}
		int max = F;
		for (int i = A.size() - 1; i > 0; --i) {
			F += (sum - A.size() * A[i]);
			if (max < F)
				max = F;
		}
		return max;
	}
	unordered_map<int, int>dp;
	int integerReplacement(int n) {
		if (n == 1) {
			return 0;
		}
		if (dp.count(n) != 0) {
			return dp[n];
		}
		int ints;
		if ((n & 1) == 0) {
			ints = 1 + integerReplacement(n >> 1);
		}
		else {
			ints = 1 + min(integerReplacement(n + 1), integerReplacement(n - 1));
		}
		dp.insert(make_pair(n, ints));
		return ints;
	}
	int sumOfLeftLeaves(TreeNode* root) {
		if (!root) {
			return 0;
		}
		if (!root->left) {
			return sumOfLeftLeaves(root->right);
		}
		if (!root->left->left && !root->left->right) {
			return root->left->val + sumOfLeftLeaves(root->right);
		}
		else {
			return sumOfLeftLeaves(root->left)+ sumOfLeftLeaves(root->right);
		}
	}
	vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
		auto comp = [](const pair<int, int>& p1, const pair<int, int>& p2)
		{ return p1.first > p2.first || (p1.first == p2.first && p1.second < p2.second); };
		sort(people.begin(), people.end(), comp);
		vector<pair<int, int>> res;
		for (auto& p : people) {
			res.insert(res.begin() + p.second, p);
		}
		return res;
	}
	int longestPalindrome(string s) {
		unordered_map<char, int>table;
		for (auto it : s) {
			table[it]++;
		}
		int res = 0;
		bool one = false;
		for (auto it : table) {
			int temp = it.second % 2;
			if (temp == 0) {
				res += it.second;
			}
			else if (it.second > 1) {
				res += it.second - 1;
			}
			if (!one && (temp == 1)) {
				res++;
				one = true;
			}
		}
		return res;
	}
};
int main() {
	Solution solu;
	return 0;
}