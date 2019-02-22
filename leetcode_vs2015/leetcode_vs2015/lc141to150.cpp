#include<iostream>
#include<vector>
using namespace std;
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
class Solution {
public:
	bool hasCycle(ListNode *head) {
		//快慢指针相遇则有环，一定保证2倍
		ListNode *fast = head;
		ListNode *slow = head;
		if (!head) {
			return false;
		}
		while (slow) {
			if (!fast || !fast->next) {
				return false;
			}
			fast = fast->next->next;
			slow = slow->next;
			if (fast == slow) {
				return true;
			}
		}
		return false;
	}
	ListNode *detectCycle(ListNode *head) {
		//设入环点为A，快慢指针相交点为B，原点为O AO=a AB=b
		//则B->A的距离为a 因为快指针是慢指针的两倍，所以B沿环到B的距离为a+b，和慢指针的距离相同。所以A->B的距离为b
		//所以在相交以后从原点再搞个指针和相交点的指针，两个都往前，第二次相交点就为入环点了
		ListNode *fast = head;
		ListNode *slow = head;
		if (!head) {
			return NULL;
		}
		while (slow) {
			if (!fast || !fast->next) {
				break;
			}
			fast = fast->next->next;
			slow = slow->next;
			if (fast == slow) {
				break;
			}
		}
		if (!slow||!fast||!fast->next) {
			return NULL;
		}
		ListNode *third = head;
		while (third != slow && third) {
			third = third->next;
			slow = slow->next;
		}
		return third;
	}
	vector<int> preorderTraversal(TreeNode* root) {
		vector<int> temp;
		preorderTraversaltrace(root, temp);
		return temp;
	}
	void preorderTraversaltrace(TreeNode* root, vector<int>&temp) {
		if (!root) {
			return;
		}
		temp.push_back(root->val);
		preorderTraversaltrace(root->left, temp);
		preorderTraversaltrace(root->right, temp);
		return;
	}
	vector<int> postorderTraversal(TreeNode* root) {
		//迭代版本，先序遍历的时候改变顺序，DLR改成DRL，这样reverse之后就成为LRD后序
		//顺便复习一下迭代的树遍历：先序把当前节点输出，右节点入栈，改当前节点为左节点，为空时栈中元素逐个出栈
		vector<int>temp;
		vector<TreeNode*>tovisit;
		TreeNode*now = root;
		if (!root) {
			return temp;
		}
		while (now || !tovisit.empty()) {
			if (now) {
				temp.push_back(now->val);
				tovisit.push_back(now->left);
				now = now->right;
			}
			else {
				now = *(tovisit.begin() + (tovisit.size() - 1));
				tovisit.pop_back();
			}
		}
		reverse(temp.begin(), temp.end());
		return temp;
	}
};
int main() {
	return 0;
}