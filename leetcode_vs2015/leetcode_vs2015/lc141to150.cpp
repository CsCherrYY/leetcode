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
};
int main() {
	return 0;
}