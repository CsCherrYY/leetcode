#include<iostream>
#include<stack>
#include<algorithm>
#include<string>
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
class MyQueue {
private:
	stack<int>mystack;
	stack<int>mystack1;
public:
	/** Initialize your data structure here. */
	MyQueue() {
		
	}
	/** Push element x to the back of queue. */
	void push(int x) {
		int temp;
		while (!mystack.empty()) {
			temp = mystack.top();
			mystack1.push(temp);
			mystack.pop();
		}
		mystack.push(x);
		while (!mystack1.empty()) {
			temp = mystack1.top();
			mystack.push(temp);
			mystack1.pop();
		}
		return;
	}
	/** Removes the element from in front of queue and returns that element. */
	int pop() {
		int temp = mystack.top();
		mystack.pop();
		return temp;
	}
	/** Get the front element. */
	int peek() {
		return mystack.top();
	}
	/** Returns whether the queue is empty. */
	bool empty() {
		return mystack.empty();
	}
};
class Solution {
public:
	int calculate(string s) {
		vector<char> ops;
		vector<int> nums;
		bool num = false;
		char tmpchar;
		int tempnum = 0;
		int num_left;
		int num_res = 0;
		for (int i = 0; i < s.size(); ++i) {
			tmpchar = s[i];
			if (tmpchar == ' ') {
				continue;
			}
			else if (tmpchar == '*' || tmpchar == '/') {
				num = false;
				nums.push_back(tempnum);
				ops.push_back(tmpchar);
			}
			else if (tmpchar == '+' || tmpchar == '-') {
				num = false;
				nums.push_back(tempnum);
				ops.push_back(tmpchar);
			}
			else {
				if (!num) {
					num = true;
					tempnum = tmpchar - '0';
				}
				else {
					tempnum = tempnum * 10 + tmpchar - '0';
				}
			}
		}
		if (num) {
			nums.push_back(tempnum);
		}
		return 1;
	}
	vector<string> summaryRanges(vector<int>& nums) {
		vector<string> temp;
		bool zone = false;
		int start = 0;
		int last = 0;
		if (!nums.size()) {
			return temp;
		}
		for (int i = 0; i < nums.size(); ++i) {
			if (!zone) {
				last = nums[i];
				start = nums[i];
				zone = true;
			}
			else {
				if (nums[i] == last + 1) {
					last = nums[i];
				}
				else {
					if (start != last) {
						temp.push_back(to_string(start) + "->" + to_string(last));
					}
					else {
						temp.push_back(to_string(start));
					}
					start = nums[i];
					last = nums[i];
				}
			}
		}
		if (start != last) {
			temp.push_back(to_string(start) + "->" + to_string(last));
		}
		else {
			temp.push_back(to_string(start));
		}
		return temp;
	}
	vector<int> majorityElement(vector<int>& nums) {
		//求出现次数大于三分之一的数，这个数一定不超过2个
		vector<int> res;
		int num1 = 0;
		int num2 = 0;
		int count1 = 0;
		int count2 = 0;
		for (int i = 0; i < nums.size(); ++i) {
			if (nums[i] == num1) {
				++count1;
			}
			else if (nums[i] == num2) {
				++count2;
			}
			else if (!count2) {
				num2 = nums[i];
				count2 = 1;
			}
			else if (!count1) {
				num1 = nums[i];
				count1 = 1;
			}
			else {
				--count1;
				--count2;
			}
		}
		count1 = 0;
		count2 = 0;
		for (int j = 0; j < nums.size(); ++j) {
			if (nums[j] == num1) {
				++count1;
			}
			else if (nums[j] == num2) {
				++count2;
			}
		}
		if (count1 > nums.size() / 3) {
			res.push_back(count1);
		}
		if (count2 > nums.size() / 3) {
			res.push_back(count2);
		}
		sort(res.begin(), res.end());
		return res;
	}
	int kthSmallest(TreeNode* root, int k) {
		if (!root) {
			return -1;
		}
		vector<int>ret;
		inordertree(root, k, ret);
		return ret[k];
	}
	void inordertree(TreeNode* root, int k, vector<int>& ret) {
		if (!root) {
			return;
		}
		if (ret.size() == k) {
			return;
		}
		inordertree(root->left, k, ret);
		ret.push_back(root->val);
		inordertree(root->right, k, ret);
		return;
	}
	bool isPowerOfTwo(int n) {
		if (n <= 0) {
			return false;
		}
		//2的n次方的2进制只有1个1
		int k = 0;
		while (n) {
			k += n & 1;
			n = n >> 1;
		}
		return !(k == 1);
	}
	bool isPalindrome(ListNode* head) {
		if (!head) {
			return true;
		}
		ListNode* slow = head;
		ListNode* fast = head;
		while (fast) {
			slow = slow->next;
			fast = (fast->next) ? fast->next->next : fast->next;
		}
		ListNode *prev = nullptr;
		while (slow) {
			ListNode *news = slow->next;
			slow->next = prev;
			prev = slow;
			slow = news;
		}
		while (head&&prev) {
			if (head->val != prev->val) {
				return false;
			}
			head = head->next;
			prev = prev->next;
		}
		return true;
		//O(1)空间复杂度
	}
};
int main() {
	Solution solu;
	vector<int>test229;
	int res = solu.calculate("31 + 5 / 2");
	test229 = solu.majorityElement(vector<int>{1, 2, 2, 3, 2, 1, 1, 3});
	return 0;
}