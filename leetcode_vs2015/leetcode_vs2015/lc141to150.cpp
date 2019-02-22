#include<iostream>
#include<vector>
#include<string>
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
	ListNode* insertionSortList(ListNode* head) {
		if (!head) {
			return head;
		}
		ListNode* begin = head;
		ListNode* end = head;
		ListNode* work = head->next;
		ListNode* temp = begin;
		while (work) {
			temp = begin;
			while (temp->val < work->val&&temp->next->val < work->val) {
				temp = temp->next;
			}//temp现在是待插入点的前一个指针
			if (temp == begin && work->val < temp->val) {//work是最小的那个
				end->next = work->next;
				work->next = begin;
				begin = work;
				work = end->next;
			}
			else if (temp == end) {  //插到末尾
				end = work;
				work = end->next;
			}
			else {
				end->next = work->next;
				work->next = temp->next;
				temp->next = work;
				work = end->next;
			}
		}
		return begin;
	}
	ListNode* sortList(ListNode* head) {
		if (!head || !head->next) {
			return head;
		}
		ListNode *fast = head;
		ListNode *slow = head;
		ListNode *slowpre = NULL;
		while (fast&&fast->next) {
			slowpre = slow;   //慢指针前一个，为了前后断掉
			fast = fast->next->next;
			slow = slow->next;
		}
		if (slowpre) {
			slowpre->next = NULL;
		}
		ListNode *l = sortList(head);
		ListNode *r = sortList(slow);
		return Merge(l, r);
	}
	ListNode* Merge(ListNode* left, ListNode* right) {
		ListNode *start = new ListNode(0);
		ListNode *work = start;
		while (left&&right) {
			if (left->val <= right->val) {
				work->next = left;
				left = left->next;
				work = work->next;
			}
			else {
				work->next = right;
				right = right->next;
				work = work->next;
			}
		}
		if (left) {
			work->next = left;
		}
		else if (right) {
			work->next = right;
		}
		return start->next;
	}
	int evalRPN(vector<string>& tokens) {
		vector<string>ops;
		vector<string>nums;
		int i, num1, num2, result;
		for (i = 0; i < tokens.size(); i++) {
			if (tokens[i] != "+"&&tokens[i] != "-"&&tokens[i] != "*"&&tokens[i] != "/") {
				//数字
				nums.push_back(tokens[i]);
			}
			else {
				//op
				num2 = stoi(*(nums.begin() + (nums.size() - 1)));
				num1 = stoi(*(nums.begin() + (nums.size() - 2)));
				nums.pop_back();
				nums.pop_back();
				if (tokens[i] == "+") {
					result = num1 + num2;
				}
				else if (tokens[i] == "-") {
					result = num1 - num2;
				}
				else if (tokens[i] == "*") {
					result = num1 * num2;
				}
				else {
					result = num1 / num2;
				}
				nums.push_back(to_string(result));
			}
		}
		return stoi(*nums.begin());
	}
};
int main() {
	Solution solu;
	int test = 148;
	ListNode *solu148 = new ListNode(0);
	ListNode *node1 = new ListNode(4);
	ListNode *node2 = new ListNode(2);
	ListNode *node3 = new ListNode(1);
	ListNode *node4 = new ListNode(3);
	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	switch (test)
	{
	case 148:
		solu148 = solu.sortList(node1);
		break;
	default:
		break;
	}
	return 0;
}