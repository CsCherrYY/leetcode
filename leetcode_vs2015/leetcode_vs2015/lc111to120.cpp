#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
struct TreeLinkNode {
	TreeLinkNode *left;
	TreeLinkNode *right;
	TreeLinkNode *next;
};
class Solution {
public:
	int minDepth(TreeNode* root) {
		if (!root) {
			return 0;
		}
		int left = minDepth(root->left);
		int right = minDepth(root->right);
		if (!root->left) {       //右边是空的就取左边，最小深度的定义要到叶子节点
			return 1 + right;
		}
		if (!root->right) {
			return 1 + left;
		}
		return 1 + min(left, right);
	}
	bool hasPathSum(TreeNode* root, int sum) {
		if (!root) {
			return false;
		}
		if (!root->left && !root->right) {   //确定是叶子节点
			if (root->val == sum) {
				return true;
			}
		}
		bool left = hasPathSum(root->left, sum - root->val);
		bool right = hasPathSum(root->right, sum - root->val);
		if (!root->left) {
			return right;
		}
		if (!root->right) {
			return left;
		}
		return left || right;
	}
	vector<vector<int>> pathSum(TreeNode* root, int sum) {
		vector<vector<int>> res;
		vector<int>temp;
		pathSumtrace(root, sum, res, temp);
		return res;
	}
	void pathSumtrace(TreeNode* root, int sum, vector<vector<int>>& res, vector<int>temp) {
		if (!root) {
			return;
		}
		if (!root->left && !root->right) {   //确定是叶子节点
			if (root->val == sum) {
				temp.push_back(root->val);
				res.push_back(temp);
				return;
			}
		}
		if (!root->left) {
			temp.push_back(root->val);
			pathSumtrace(root->right, sum - root->val, res, temp);
			return;
		}
		if (!root->right) {
			temp.push_back(root->val);
			pathSumtrace(root->left, sum - root->val, res, temp);
			return;
		}
		temp.push_back(root->val);
		pathSumtrace(root->right, sum - root->val, res, temp);
		pathSumtrace(root->left, sum - root->val, res, temp);
		return;
	}
	void flatten(TreeNode* root) {
		if (!root) {
			return;
		}
		flatten(root->left);
		flatten(root->right);
		TreeNode* newnode = root->left;
		if (!newnode) {
			return;
		}
		while (newnode&&newnode->right) {
			newnode = newnode->right;
		}
		newnode->right = root->right;
		root->right = root->left;
		root->left = NULL;
		return;
	}
	int numDistinct(string s, string t) {
		//dp[i][j]表示s中前i个和t中前j个的组合个数
		int size_s = s.size();
		int size_t = t.size();
		vector<vector<int>>dp(size_s + 1, vector<int>(size_t + 1, 0));
		int i, j;
		for (i = 0; i <= size_s; ++i) {
			dp[i][0] = 1;
		}
		for (i = 1; i <= size_s; i++) {
			for (j = 1; j <= size_t; j++) {
				dp[i][j] = dp[i - 1][j];   //目前这个s可以不取 个数就和之前一位是一样的
				if (s[i-1] == t[j-1]) {               //那如果这个s也可以取，条件是s要等于t的最后一个 那条件就和t也不取最后一位一样
					dp[i][j] += dp[i - 1][j - 1];
				}
			}
		}
		return dp[size_s][size_t];
	}
	void connect(TreeLinkNode *root) {
		if (root == NULL) {
			return;
		}
		TreeLinkNode *node = NULL;
		if (root->left) {
			if (root->right) {
				root->left->next = root->right;
			}
			else {
				node = root->next;
				while (node) {
					if (node->left) {
						root->left->next = node->left;
						break;
					}
					if (node->right) {
						root->left->next = node->right;
						break;
					}
					node = node->next;
				}
			}
		}
		if (root->right) {
			node = root->next;
			while (node) {
				if (node->left) {
					root->right->next = node->left;
					break;
				}
				if (node->right) {
					root->right->next = node->right;
					break;
				}
				node = node->next;
			}
		}
		connect(root->right);  //先右子树？因为调左子树的话连不到右边
		connect(root->left);
	}
	vector<vector<int>> generate(int numRows) {
		vector<int>temp, last;
		vector<vector<int>> res;
		if (numRows == 0) {
			return res;
		}
		temp = { 1 };
		res.push_back(temp);
		if (numRows == 1) {
			return res;
		}
		temp = { 1,1 };
		res.push_back(temp);
		if (numRows == 2) {
			return res;
		}
		int i, j;
		last = temp;
		for (i = 3; i <= numRows; i++) {
			temp.clear();
			for (j = 0; j < i; j++) {
				if (j == 0||j == i - 1) {
					temp.push_back(1);
				}
				else {
					temp.push_back(last[j - 1] + last[j]);
				}
			}
			res.push_back(temp);
			last.assign(temp.begin(),temp.end());
		}
		return res;
	}
	vector<int> getRow(int rowIndex) {
		rowIndex = rowIndex + 1;
		vector<int> temp(rowIndex,1);
		vector<int> last;
		if (rowIndex == 1 || rowIndex == 2) {
			return temp;
		}
		int i, j;
		for (i = 3; i <= rowIndex; i++) {
			last = temp;
			for (j = 1; j < i - 1; j++) {
				temp[j] = last[j] + last[j - 1];
			}
		}
		return temp;
	}
	int minimumTotal(vector<vector<int>>& triangle) {
		int size = triangle.size();
		if (size == 0) {
			return 0;
		}
		vector<int>dp(size + 1, 0);
		vector<int>temp;
		int i, j;
		for (i = size - 1; i >= 0; --i) {
			temp = triangle[i];
			for (j = 0; j < temp.size(); j++) {
				dp[j] = min(dp[j], dp[j + 1]) + temp[j];
			}
		}
		return dp[0];
	}
};
int main() {
	vector<vector<int>> solu118;
	Solution solu;
	int test = 118;
	switch (test)
	{
	case 118:
		solu118 = solu.generate(5);
		break;
	default:
		break;
	}
	return 0;
}