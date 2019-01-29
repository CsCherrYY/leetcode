#include<iostream>
#include<string>
#include<vector>
#include<map>
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
using namespace std;
class Solution {
public:
	int numDecodings(string s) {
		map<string, int> maps;
		return numDecodingsdp(s, maps);
	}
	int numDecodingsdp(string s, map<string, int>& maps) {
		int len = s.length();
		if (len == 0) {
			return 0;
		}
		else if (len == 1 && s[0] == '0') {
			return 0;
		}
		else if (len == 1) {
			return 1;
		}
		if (maps.find(s) != maps.end()) {
			return maps[s];   //查表
		}
		int i, count;
		count = 0;
		string left, right;
		left = s.substr(0, len - 1);
		right = s.substr(0, len - 2);
		if (s[len - 1] != '0') {
			count += numDecodingsdp(left, maps) == 0 ? 1 : numDecodingsdp(left, maps);
		}
		if (s[len - 2] < '2' || (s[len - 2] == '2'&&s[len - 1] <= '6')) {
			count += numDecodingsdp(right, maps) == 0 ? 1 : numDecodingsdp(right, maps);
		}
		maps.insert(pair<string, int>(s, count));
		return count;
	}
	ListNode* reverseBetween(ListNode* head, int m, int n) {
		if (m == n) {
			return head;
		}
		//三个指针p q r p指向逆序部分的前一个节点 q指向逆序部分的最后一个节点 r是待加入的新节点
		int i = 1;
		ListNode*start = new ListNode(0);
		start->next = head;
		ListNode*p = start;
		ListNode*q = start;
		ListNode*r = start;
		p = start;
		while (i < m) {
			p=p->next;
			i++;
		}
		q = p->next;
		int k;
		for (k = 0; k < n - m; k++) {
			r = q->next;
			q->next = r->next;
			r->next = p->next;
			p->next = r;
		}
		return start->next;
	}
	vector<int> inorderTraversal(TreeNode* root) {
		vector<int> temp;
		inorderTraversalcs(root, temp);
		return temp;
	}
	void inorderTraversalcs(TreeNode* root, vector<int>&temp) {
		if (root == NULL) {
			return;
		}
		inorderTraversalcs(root->left, temp);
		temp.push_back(root->val);
		inorderTraversalcs(root->right, temp);
		return;
	}
	vector<TreeNode*> generateTrees(int n) {
		vector<TreeNode*> temp;
		if (n == 0) {
			return temp;
		}
		return generateTreesdp(1, n);
	}
	vector<TreeNode*> generateTreesdp(int begin, int end)
	{
		vector<TreeNode*> res;
		if (begin > end)
		{
			res.push_back(NULL);
			return res;
		}
		int i, j, k;
		for (i = begin; i <= end; ++i)
		{
			vector<TreeNode*> left_trees = generateTreesdp(begin, i - 1); //用容器作为返回值，然后对容器遍历就可以
			vector<TreeNode*> right_trees = generateTreesdp(i + 1, end);
			for (j = 0; j < left_trees.size(); j++) {
				for (k = 0; k < right_trees.size(); k++) {
					TreeNode* root = new TreeNode(i);
					root->left = left_trees[j];
					root->right = right_trees[k];
					res.push_back(root);
				}
			}
		}
		return res;
	}
	int numTrees(int n) {
		if (n == 0) {
			return 1;
		}
		vector<int> dp(n + 1, 0);   //这个n+1非常重要
		dp[0] = 1;
		dp[1] = 1;
		int k = numTreesdp(n, dp);
		return k;
	}
	int numTreesdp(int n, vector<int>& dp) {
		if (dp[n] != 0) {
			return dp[n];
		}
		int i, total;
		total = 0;
		for (i = 0; i < n; i++) {
			total += numTreesdp(i, dp)*numTreesdp(n - 1 - i, dp);
		}
		dp[n] = total;
		return total;
	}
	bool isInterleave(string s1, string s2, string s3) {
		if (s1 == ""&&s2 == ""&&s3 == "") {
			return true;
		}
		int len1 = s1.length();
		int len2 = s2.length();
		int len3 = s3.length();
		if (len1 + len2 != len3) {
			return false;
		}
		vector<vector<bool>>dp(len1 + 1, vector<bool>(len2 + 1, false));
		int i = 0, j = 0, k = 0;
		dp[0][0] = true;
		while (i<len1&&s1[i] == s3[i]) {     //边界条件的初始化
			dp[i + 1][0] = true;
			i++;
		}
		while (j<len2&&s2[j] == s3[j]) {
			dp[0][j + 1] = true;
			j++;
		}
		//dp[i][j] s3[i+j]可以通过s1[i]和s2[j]表示
		for (i = 1; i <= len1; ++i) {
			for (j = 1; j <= len2; ++j) {
				if (s3[i + j - 1] == s1[i - 1]) {               //一般这种字符串dp，都要多一个存储空间，作为边界条件
					dp[i][j] = dp[i][j] || dp[i - 1][j];
				}
				if (s3[i + j - 1] == s2[j - 1]) {
					dp[i][j] = dp[i][j] || dp[i][j - 1];
				}
			}
		}
		return dp[len1][len2];
	}
	bool isValidBST(TreeNode* root) {
		//中序遍历为升序
		if (!root) {
			return true;
		}
		vector<int>temp;
		LDRtree(root, temp);
		int i;
		for (i = 0; i < temp.size() - 1; i++) {
			if (temp[i] >= temp[i + 1]) {
				return false;
			}
		}
		return true;
	}
	void LDRtree(TreeNode* root, vector<int>&temp) {
		if (!root) {
			return;
		}
		LDRtree(root->left, temp);
		temp.push_back(root->val);
		LDRtree(root->right, temp);
	}
	void LDRtreenode(TreeNode* root, vector<TreeNode*>&temp) {
		if (!root) {
			return;
		}
		LDRtreenode(root->left, temp);
		temp.push_back(root);
		LDRtreenode(root->right, temp);
	}
	void recoverTree(TreeNode* root) {
		if (!root) {
			return;
		}
		vector<TreeNode*>temp;
		LDRtreenode(root, temp); //node指针按中序排列好
		int i, j, k;
		int flagj = 0;
		int tempint;
		for (i = 0; i < temp.size(); i++) {
			if (i == 0) {
				if (temp[0]->val > temp[1]->val) {
					j = 0;
					flagj = 1;
				}
			}
			else if (i == temp.size() - 1) {
				if (temp[i]->val < temp[i - 1]->val) {
					k = i;
				}
			}
			else {
				if (temp[i]->val > temp[i - 1]->val&&temp[i]->val > temp[i + 1]->val&&!flagj) {
					j = i;  //注意，j应该取先的，k应该取后的，所以j不能被覆盖，k可以被覆盖
					flagj = 1;
				}
				else if (temp[i]->val < temp[i - 1]->val&&temp[i]->val < temp[i + 1]->val) {
					k = i;
				}
			}
		}
		swap(temp[j]->val, temp[k]->val);
		return;
	}
	bool isSameTree(TreeNode* p, TreeNode* q) {
		if (!p) {
			if (!q) {
				return true;
			}
			return false;
		}
		if (!q) {
			return false;
		}
		if (p->val != q->val) {
			return false;
		}
		return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
	}
};
int main() {
	int test = 99;
	TreeNode* tree146 = new TreeNode(146);
	TreeNode* tree71 = new TreeNode(71);
	TreeNode* treef13 = new TreeNode(-13);
	TreeNode* tree55 = new TreeNode(55);
	TreeNode* tree231 = new TreeNode(231);
	TreeNode* tree399 = new TreeNode(399);
	TreeNode* tree321 = new TreeNode(321);
	TreeNode* treef33 = new TreeNode(-33);
	tree146->left = tree71;
	tree146->right = treef13;
	tree71->left = tree55;
	tree55->left = tree321;
	tree321->left = treef33;
	treef13->left = tree231;
	treef13->right = tree399;
	ListNode* node1 = new ListNode(1);
	ListNode* node2 = new ListNode(2);
	ListNode* node3 = new ListNode(3);
	ListNode* node4 = new ListNode(4);
	ListNode* node5 = new ListNode(5);
	ListNode* solu92 = new ListNode(0);
	int solu96;
	bool solu97;
	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;
	vector<ListNode*> temp1;
	temp1.push_back(node1);
	temp1.push_back(node2);
	temp1.push_back(node3);
	swap(temp1[0]->val, temp1[1]->val);
	Solution solu;
	int solu91;
	switch (test)
	{
	case 91:
		solu91 = solu.numDecodings("226");
		break;
	case 92:
		solu92 = solu.reverseBetween(node1, 2, 4);
		break;
	case 96:
		solu96 = solu.numTrees(19);
		break;
	case 97:
		solu97 = solu.isInterleave("aabcc", "dbbca", "aadbbcbcac");
		break;
	case 99:
		solu.recoverTree(tree146);
		break;
	default:
		break;
	}
	return 0;
}