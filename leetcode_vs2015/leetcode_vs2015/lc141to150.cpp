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
		//����ָ���������л���һ����֤2��
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
		//���뻷��ΪA������ָ���ཻ��ΪB��ԭ��ΪO AO=a AB=b
		//��B->A�ľ���Ϊa ��Ϊ��ָ������ָ�������������B�ػ���B�ľ���Ϊa+b������ָ��ľ�����ͬ������A->B�ľ���Ϊb
		//�������ཻ�Ժ��ԭ���ٸ��ָ����ཻ���ָ�룬��������ǰ���ڶ����ཻ���Ϊ�뻷����
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
		//�����汾�����������ʱ��ı�˳��DLR�ĳ�DRL������reverse֮��ͳ�ΪLRD����
		//˳�㸴ϰһ�µ�����������������ѵ�ǰ�ڵ�������ҽڵ���ջ���ĵ�ǰ�ڵ�Ϊ��ڵ㣬Ϊ��ʱջ��Ԫ�������ջ
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
			}//temp�����Ǵ�������ǰһ��ָ��
			if (temp == begin && work->val < temp->val) {//work����С���Ǹ�
				end->next = work->next;
				work->next = begin;
				begin = work;
				work = end->next;
			}
			else if (temp == end) {  //�嵽ĩβ
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
			slowpre = slow;   //��ָ��ǰһ����Ϊ��ǰ��ϵ�
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
				//����
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