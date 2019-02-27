#include<iostream>
#include<map>
#include<set>
using namespace std;
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
	bool isHappy(int n) {
		int temp = n;
		int sum = 0;
		while (1) {
			while (temp) {
				sum += (temp % 10)*(temp % 10);
				temp /= 10;
			}
			if (sum == 4) {   //4就进入循环
				return false;
			}
			if (sum == 1) {
				return true;
			}
			temp = sum;
			sum = 0;
		}
	}
	ListNode* removeElements(ListNode* head, int val) {
		if (!head) {
			return head;
		}
		ListNode *start = new ListNode(0);
		start->next = head;
		ListNode *pre = start;   //设一个前节点
		ListNode *work = head;
		while (work) {
			if (work->val == val) {
				pre->next = work->next;
				work = work->next;
				continue;
			}
			pre = pre->next;
			work = work->next;
		}
		return start->next;
	}
	bool isIsomorphic(string s, string t) {
		//这题后面test太长，递归回溯会栈溢出
		map<char, char>st;
		set<char>set_t;
		int len = s.length();
		if (!len) {
			return true;
		}
		char char_s;
		char char_t;
		for (int i = 0; i < len; ++i) {
			char_s = s[i];
			char_t = t[i];
			auto it_st = st.find(char_s);
			auto it_t = set_t.find(char_t);
			if (it_st == st.end()) {
				if (it_t == set_t.end()) {
					st.insert(pair<char, char>(char_s, char_t));
					set_t.insert(char_t);
					continue;
				}
				else { //t用过了s没用过
					return false;
				}
			}
			else {
				if (it_st->second == char_t) {
					continue;
				}
				else {
					return false;
				}
			}
		}
		return true;
	}
	ListNode* reverseList(ListNode* head) {
		if (!head) {
			return head;
		}
		ListNode *start = new ListNode(0);
		start->next = head;
		ListNode *work = head;
		ListNode *beg = head;
		ListNode *pre = start;
		while (work) {
			pre->next = work->next;
			work->next = pre->next->next;
			pre->next->next = beg;
			beg = pre->next;
		}
		return start->next;
	}

};
int main() {
	return 0;
}