#include<iostream>
#include<map>
#include<algorithm>
#include<set>
#include<vector>
using namespace std;
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
class Trie {
public:
	/** Initialize your data structure here. */
	Trie() {

	}

	/** Inserts a word into the trie. */
	void insert(string word) {

	}

	/** Returns if the word is in the trie. */
	bool search(string word) {

	}

	/** Returns if there is any word in the trie that starts with the given prefix. */
	bool startsWith(string prefix) {

	}
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
			if (sum == 4) {   //4�ͽ���ѭ��
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
		ListNode *pre = start;   //��һ��ǰ�ڵ�
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
		//�������test̫�����ݹ���ݻ�ջ���
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
				else { //t�ù���sû�ù�
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
	map<int, int>dp213,dp2131;
	int rob(vector<int>& nums) {
		/*���1 2����ȡ ��ô�϶�С��1ȡ2��ȡ
		�������������1ȡ������2ȡ
		*/
		if (!nums.size()) {
			return 0;
		}
		if (nums.size() == 1) {
			return nums[0];
		}
		if (nums.size() == 2) {
			return max(nums[0], nums[1]);
		}
		int with1 = robdp_with1(nums, 0);
		int without1 = robdp_without1(nums, 0);
		return max(with1, without1);
	}
	int robdp_with1(vector<int>& nums, int left) {
		auto s = dp213.find(left);  //dp�洢��ʽ��pair<int1,int2> int1:left int2:maxvalue
		if (s != dp213.end()) {
			return s->second;
		}
		if (left >= nums.size()) {
			return 0;
		}
		if (left == nums.size() - 1) {
			return 0; //ֻ��ȡ�����
		}
		int temp3 = robdp_with1(nums, left + 1);  //1,2����ȡ 
		int temp1 = nums[left] + robdp_with1(nums, left + 2);   //ȡ��1
		int temp2;
		if (left + 1 != nums.size() - 1) {
			temp2 = nums[left + 1] + robdp_with1(nums, left + 3); //ȡ��2
		}
		else {
			temp2 = 0;
		}
		int res = max(temp1, temp2);
		res = max(res, temp3);
		dp213.insert(pair<int, int>(left, res));
		return res;
	}
	int robdp_without1(vector<int>& nums, int left) {
		auto s = dp2131.find(left);  //dp�洢��ʽ��pair<int1,int2> int1:left int2:maxvalue
		if (s != dp2131.end()) {
			return s->second;
		}
		if (left >= nums.size()) {
			return 0;
		}
		if (left == nums.size() - 1) {
			return nums[left]; //ֻ��ȡ�����
		}
		int temp1;
		int temp3 = robdp_without1(nums, left + 1);
		if (left) {
			temp1 = nums[left] + robdp_without1(nums, left + 2);   //ȡ��1
		}
		else {
			temp1 = 0;
		}
		int temp2 = nums[left + 1] + robdp_without1(nums, left + 3); //ȡ��2
		
		int res = max(temp1, temp2);
		res = max(res, temp3);
		dp2131.insert(pair<int, int>(left, res));
		return res;
	}
	int findKthLargest(vector<int>& nums, int k) {
		/*�ҵ�k����������
		���һ����Ҷ�ڵ�λ��k/2-1����ĳ���ڵ���˵������2*k+1 �Һ���2*k+2
		*/
		for (int i = 0; i < k; ++i) {
			adjust(nums, 0, nums.size() - i);
			swap(nums[0], nums[nums.size() - 1 - i]);
		}
		return nums[nums.size() - k];
	}
	void adjust(vector<int>&nums,int left, int right) {
		int start = right / 2 - 1;
		int bigger;
		for (int i = start; i >= left; --i) {
			bigger = i * 2 + 1;
			if (i * 2 + 2 <= right - 1) {
				if (nums[bigger + 1] >= nums[bigger]) {
					++bigger;
				}
			}
			if (nums[bigger] >= nums[i]) {
				swap(nums[bigger], nums[i]);
				//adjust(nums, bigger, right);
			}
		}
		return;
	}
};
int main() {
	Solution solu;
	vector<int>robs = { 1, 2, 3, 4, 5, 1, 2, 3, 4, 5 };
	vector<int>heap = { 3,2,3,1,2,4,5,5,6,4 };
	int test1 = solu.findKthLargest(heap, 4);
	int test = solu.rob(robs);
	return 0;
}