#include<iostream>
#include<vector>
#include<queue>
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
class Node {
public:
	int val;
	Node* prev;
	Node* next;
	Node* child;

	Node() {}

	Node(int _val, Node* _prev, Node* _next, Node* _child) {
		val = _val;
		prev = _prev;
		next = _next;
		child = _child;
	}
};
class Solution {
public:
	int lastRemaining(int n) {
		//n为奇数
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
	int numberOfArithmeticSlices(vector<int>& A) {
		if (A.size() < 3) {
			return 0;
		}
		vector<int>dp(A.size(), 0);
		int sum = 0;
		int diff = A[1] - A[0];
		for (int i = 2; i < A.size(); ++i) {
			if ((A[i] - A[i - 1]) == (A[i-1]-A[i-2])) {
				dp[i] = dp[i - 1] + 1;
				sum += dp[i];
			}
		}
		return sum;
	}
	bool canPartition(vector<int>& nums) {
		//求几个元素的和等于sum
		if (nums.size() <= 1) {
			return false;
		}
		int sum = 0;
		for (int i = 0; i < nums.size(); i++) {
			sum += nums[i];
		}
		if (sum & 1) {
			return false;
		}
		//找组合成为sum/2
		vector<vector<bool>>dp(nums.size(), vector<bool>(sum + 1, false));
		//dp[i,x]=dp[i-1,x-nums[i]]
		for (int i = 0; i < nums.size(); i++) {
			dp[i][nums[i]] = true;
		}
		for (int i = 0; i < nums.size(); i++) {
			dp[i][0] = true;
		}
		for (int i = 1; i < nums.size(); i++) {
			for (int j = 1; j <= sum; j++) {
				if (j - nums[i] >= 0) {
					dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i]];
				}
				else {
					dp[i][j] = dp[i - 1][j];
				}
			}
		}
		return dp[nums.size()-1][sum / 2];
	}
	vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
		vector<pair<int, int>>res;
		if (!matrix.size()) {
			return res;
		}
		if (!matrix[0].size()) {
			return res;
		}
		vector<vector<bool>>a(matrix.size(), vector<bool>(matrix[0].size(), false));
		vector<vector<bool>>b(matrix.size(), vector<bool>(matrix[0].size(), false));
		vector<vector<bool>>sa(matrix.size(), vector<bool>(matrix[0].size(), false));
		vector<vector<bool>>sb(matrix.size(), vector<bool>(matrix[0].size(), false));
		for (int i = 0; i < matrix.size(); i++) {
			a[i][0] = true;
			b[i][matrix[0].size() - 1] = true;
		}
		for (int i = 0; i < matrix[0].size(); i++) {
			a[0][i] = true;
			b[matrix.size() - 1][i] = true;
		}
		for (int i = 0; i < matrix.size(); i++) {
			for (int j = 0; j < matrix[0].size(); j++) {
				if (sa[i][j] == false && a[i][j] == true) {
					DFS(matrix, a, sa, i, j);
				}
				if (sb[i][j] == false && b[i][j] == true) {
					DFS(matrix, b, sb, i, j);
				}
			}
		}
		for (int i = 0; i < matrix.size(); i++) {
			for (int j = 0; j < matrix[0].size(); j++) {
				if (a[i][j] && b[i][j]) {
					res.push_back(make_pair(i, j));
				}
			}
		}
		return res;
	}
	void DFS(vector<vector<int>>& matrix, vector<vector<bool>>&table, vector<vector<bool>>&flag, int i, int j) {
		if (i < 0 || i >= matrix.size()) {
			return;
		}
		if (j < 0 || j >= matrix[0].size()) {
			return;
		}
		flag[i][j] = true;
		if (i > 0 && matrix[i][j] <= matrix[i - 1][j] && !flag[i-1][j]) {
			table[i - 1][j] = true;
			DFS(matrix, table, flag, i - 1, j);
		}
		if ((i < matrix.size() - 1) && (matrix[i][j] <= matrix[i + 1][j]) && !flag[i + 1][j]) {
			table[i + 1][j] = true;
			DFS(matrix, table, flag, i + 1, j);
		}
		if ((j > 0) && (matrix[i][j] <= matrix[i][j - 1]) && !flag[i][j-1]) {
			table[i][j - 1] = true;
			DFS(matrix, table, flag, i, j - 1);
		}
		if ((j < matrix[0].size() - 1) && (matrix[i][j] <= matrix[i][j + 1]) && !flag[i][j + 1]) {
			table[i][j + 1] = true;
			DFS(matrix, table, flag, i, j + 1);
		}
		return;
	}
	int characterReplacement(string s, int k) {
		if (!s.length()) {
			return 0;
		}
		int left = 0;
		int res = 0;
		int maxcount = 0;
		vector<int>count(26, 0);
		for (int i = 0; i < s.length(); i++) {
			count[s[i] - 'A']++;
			maxcount = max(maxcount, count[s[i] - 'A']);
			if (i - left + 1 - maxcount > k) {
				count[s[left] - 'A']--;
				left++;
			}
			res = max(res, i - left + 1);
		}
		return res;
	}
	Node* flatten(Node* head) {
		if (!head) {
			return head;
		}
		Node *temp = head;
		while (!temp->child) {
			if (!temp->next) {
				return head;
			}
			temp = temp->next;
		}
		Node*work1 = flatten(temp->next);
		Node*work2 = flatten(temp->child);
		temp->child = nullptr;
		temp->next = work2;
		work2->prev = temp;
		while (work2->next) {
			work2 = work2->next;
		}
		work2->next = work1;
		work1->prev = work2;
		return head;
	}
};
int main() {
	Solution solu;
	vector<vector<int>>test;
	test.push_back(vector<int>{1, 2, 2, 3, 5});
	test.push_back(vector<int>{3, 2, 3, 4, 4});
	test.push_back(vector<int>{2, 4, 5, 3, 1});
	test.push_back(vector<int>{6, 7, 1, 4, 5});
	test.push_back(vector<int>{5, 1, 1, 2, 4});
	vector<pair<int, int>> res = solu.pacificAtlantic(test);
	return 0;
}