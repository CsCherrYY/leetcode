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
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
	bool isSymmetric(TreeNode* root) {
		if (!root) {
			return true;
		}
		return isSymmetriccs(root->left, root->right);
	}
	bool isSymmetriccs(TreeNode* left, TreeNode* right) {
		if (!left && !right) {
			return true;
		}
		else if (!left||!right) {
			return false;
		}
		if (left->val != right->val) {
			return false;
		}
		return isSymmetriccs(left->right, right->left) && isSymmetriccs(left->left, right->right);
	}
	vector<vector<int>> levelOrder(TreeNode* root) {
		vector<vector<int>> temp;
		vector<TreeNode*> nowlev;
		vector<int> nowlev_int;
		if (!root) {
			return temp;
		}
		int i, nowlev_size;
		nowlev.push_back(root);
		while (1) {
			nowlev_size = nowlev.size();
			if (!nowlev_size) {
				break;
			}
			nowlev_int.clear();
			for (i = 0; i < nowlev_size; i++) {
				if (nowlev[0]->left) {
					nowlev.push_back(nowlev[0]->left);
				}
				if (nowlev[0]->right) {
					nowlev.push_back(nowlev[0]->right);
				}
				nowlev_int.push_back(nowlev[0]->val);
				nowlev.erase(nowlev.begin());
			}
			temp.push_back(nowlev_int);
		}
		return temp;
	}
	vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
		vector<vector<int>> temp;
		vector<TreeNode*> nowlev;
		vector<int> nowlev_int;
		bool flag = true;
		if (!root) {
			return temp;
		}
		int i, nowlev_size;
		nowlev.push_back(root);
		while (1) {
			nowlev_size = nowlev.size();
			if (!nowlev_size) {
				break;
			}
			nowlev_int.clear();
			for (i = 0; i < nowlev_size; i++) {
				if (nowlev[0]->left) {
					nowlev.push_back(nowlev[0]->left);
				}
				if (nowlev[0]->right) {
					nowlev.push_back(nowlev[0]->right);
				}
				nowlev_int.push_back(nowlev[0]->val);
				nowlev.erase(nowlev.begin());
			}
			if (!flag) {
				reverse(nowlev_int.begin(), nowlev_int.end());
			}
			flag = !flag;
			temp.push_back(nowlev_int);
		}
		return temp;
	}
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		TreeNode* root = new TreeNode(0);
		int size = preorder.size();
		if (!size) {
			return NULL;
		}
		int tempval = preorder[0];
		root->val = tempval;
		vector<int>::iterator it = find(inorder.begin(), inorder.end(), tempval);
		vector<int>inorder_left, inorder_right, preorder_left, preorder_right;
		inorder_left.assign(inorder.begin(), it);
		inorder_right.assign(it + 1, inorder.end());
		preorder_left.assign(preorder.begin() + 1, preorder.begin() + (it - inorder.begin() + 1));
		preorder_right.assign(preorder.begin() + (it - inorder.begin() + 1), preorder.end());
		root->left = buildTree(preorder_left, inorder_left);
		root->right = buildTree(preorder_right, inorder_right);
		return root;
	}
	TreeNode* buildTreep(vector<int>& inorder, vector<int>& postorder) {
		TreeNode* root = new TreeNode(0);
		int size = inorder.size();
		if (!size) {
			return NULL;
		}
		int tempval = postorder[size - 1];
		root->val = tempval;
		vector<int>::iterator it = find(inorder.begin(), inorder.end(), tempval);
		vector<int>inorder_left, inorder_right, postorder_left, postorder_right;
		inorder_left.assign(inorder.begin(), it);
		inorder_right.assign(it + 1, inorder.end());
		postorder_left.assign(postorder.begin(), postorder.begin() + (it - inorder.begin()));
		postorder_right.assign(postorder.begin() + (it - inorder.begin()), postorder.end() - 1);
		root->left = buildTree(inorder_left, postorder_left);
		root->right = buildTree(inorder_right, postorder_right);
		return root;
	}
	vector<vector<int>> levelOrderBottom(TreeNode* root) {
		vector<vector<int>> temp;
		vector<TreeNode*> nowlev;
		vector<int> nowlev_int;
		if (!root) {
			return temp;
		}
		int i, nowlev_size;
		nowlev.push_back(root);
		while (1) {
			nowlev_size = nowlev.size();
			if (!nowlev_size) {
				break;
			}
			nowlev_int.clear();
			for (i = 0; i < nowlev_size; i++) {
				if (nowlev[0]->left) {
					nowlev.push_back(nowlev[0]->left);
				}
				if (nowlev[0]->right) {
					nowlev.push_back(nowlev[0]->right);
				}
				nowlev_int.push_back(nowlev[0]->val);
				nowlev.erase(nowlev.begin());
			}
			temp.push_back(nowlev_int);
		}
		reverse(temp.begin(), temp.end());
		return temp;
	}
	TreeNode* sortedArrayToBST(vector<int>& nums) {
		int size = nums.size();
		if (!size) {
			return NULL;
		}
		TreeNode* newnode = new TreeNode(0);
		int mid_loc = size / 2;
		vector<int> left, right;
		newnode->val = nums[mid_loc];
		left.assign(nums.begin(), nums.begin() + mid_loc);
		right.assign(nums.begin() + mid_loc + 1, nums.end());
		newnode->left = sortedArrayToBST(left);
		newnode->right = sortedArrayToBST(right);
		return newnode;
	}
	TreeNode* sortedListToBST(ListNode* head) {
		//快慢指针
		if (!head) {
			return NULL;
		}
		ListNode* fast = head;
		ListNode* slow = head;
		ListNode* slowback = head;
		int i = 0;
		while (fast&&fast->next) {
			if (i > 0) {
				slowback = slowback->next;
			}
			slow = slow->next;
			fast = fast->next->next;
			i = 1;
		}
		TreeNode* newnode = new TreeNode(0);
		newnode->val = slow->val;
		if (head->next) {            //这个判断很重要
			slowback->next = NULL;
			newnode->left = sortedListToBST(head);
			newnode->right = sortedListToBST(slow->next);
		}
		return newnode;
	}
	int treeheight(TreeNode* root) {
		if (!root) {
			return 0;
		}
		return 1 + max(treeheight(root->left), treeheight(root->right));
	}
	bool isBalanced(TreeNode* root) {
		if (!root) {
			return true;
		}
		int temp = abs(treeheight(root->left) - treeheight(root->right));
		if (temp > 1) {
			return false;
		}
		return isBalanced(root->left)&&isBalanced(root->right);
	}
};
int main() {
	int test = 109;
	ListNode* node1 = new ListNode(-10);
	ListNode* node2 = new ListNode(-3);
	ListNode* node3 = new ListNode(0);
	ListNode* node4 = new ListNode(5);
	ListNode* node5 = new ListNode(9);
	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;
	Solution solu;
	TreeNode* root = new TreeNode(0);
	vector<int> preorder, inorder, postorder;
	preorder = { 3,9,20,15,7 };
	inorder = { 9,3,15,20,7 };
	postorder = { 9,15,7,20,3 };
	switch (test)
	{
	case 105:
		root = solu.buildTree(preorder, inorder);
		break;
	case 109:
		root = solu.sortedListToBST(node1);
		break;
	default:
		break;
	}
	return 0;
}