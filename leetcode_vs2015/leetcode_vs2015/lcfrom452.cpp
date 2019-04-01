#include<iostream>
#include<vector>
using namespace std;
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
	ListNode* reverse_list(ListNode* head) {
		if (!head) {
			return head;
		}
		ListNode *beg = head;
		ListNode *end = head;
		ListNode *temp = nullptr;
		while (beg->next) {
			temp = beg->next;
			beg->next = temp->next;
			temp->next = end;
			end = temp;
		}
		return end;
	}
	void reorderList(ListNode* head) {
		if (!head || !head->next) {
			return;
		}
		ListNode *fast = head;
		ListNode *slow = head;
		while (fast->next&&fast->next->next) {
			slow = slow->next;
			fast = fast->next->next;
		}
		ListNode *temp = slow->next;
		slow->next = nullptr;
		temp = reverse_list(temp);
		ListNode *work = head;
		while (work&&temp) {
			ListNode *temp_backorder = temp;
			temp = temp->next;
			ListNode *temp_inorder = work->next;
			temp_backorder->next = temp_inorder;
			work->next = temp_backorder;
			work = temp_inorder;
		}
	}
};
int main() {
	ListNode* node1 = new ListNode(1);
	ListNode* node2 = new ListNode(2);
	ListNode* node3 = new ListNode(3);
	node1->next = node2;
	node2->next = node3;
	Solution solu;
	ListNode *temp = solu.reverse_list(node1);
	return 0;
}