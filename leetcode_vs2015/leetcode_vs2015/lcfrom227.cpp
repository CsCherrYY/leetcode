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
	TreeNode* lowestCommonAncestor_search(TreeNode* root, TreeNode* p, TreeNode* q) {
		//判断节点左右
		if (p->val > q->val) {
			return lowestCommonAncestor(root, q, p);
		}
		if (root->val == p->val || root->val == q->val) {
			return root;
		}
		if ((root->val) > (p->val)&&(root->val) < (q->val)) {
			return root;
		}
		if ((root->val) > (p->val) && (root->val) > (q->val)) {
			return lowestCommonAncestor(root->left, p, q);
		}
		if ((root->val) < (p->val) && (root->val) < (q->val)) {
			return lowestCommonAncestor(root->right, p, q);
		}
		return nullptr;
	}
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (root == p || root == q || !root) {
			return root;
		}
		TreeNode *left = lowestCommonAncestor(root->left, p, q);
		TreeNode *right = lowestCommonAncestor(root->right, p, q);
		if (left&&right) {
			return root;
		}
		else if (left) {
			return left;
		}
		else if (right) {
			return right;
		}
		else {
			return nullptr;
		}
	}
	void deleteNode(ListNode* node) {
		//请编写一个函数，使其可以删除某个链表中给定的（非末尾）节点，你将只被给定要求被删除的节点。
		ListNode *work = node->next;
		while (1) {
			node->val = work->val;
			work = work->next;
			if (!work) {
				node->next = NULL;
				return;
			}
			node = node->next;
		}
	}
	vector<int> productExceptSelf(vector<int>& nums) {
		//说明: 请不要使用除法，且在 O(n) 时间复杂度内完成此题。
		//进阶：常数空间复杂度
		int size = nums.size();
		vector<int> out(size, 1);
		vector<int> right(size, 1);
		//左右
		for (int i = 1; i < size; ++i) {
			out[i] = out[i - 1] * nums[i - 1];
		}
		for (int i = size - 2; i >= 0; --i) {
			right[i] = right[i + 1] * nums[i + 1];
		}
		for (int i = 0; i < size; ++i) {
			out[i] = out[i] * right[i];
		}
		return out;
	}
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		int size_h = matrix.size();
		if (!size_h) {
			return false;
		}
		int size_w = matrix[0].size();
		int i = size_h - 1;
		int j = 0;
		while (i>=0&&j<=size_w-1) {
			if (matrix[i][j] == target) {
				return true;
			}
			else if (matrix[i][j] > target) {
				--i;
			}
			else {
				++j;
			}
		}
		return false;
	}
	vector<int> diffWaysToCompute(string input) {
		vector<int>res;
		for (int i = 0; i < input.size(); ++i) {
			char c = input[i];
			if (c == '+' || c == '-' || c == '*') {
				vector<int>res1 = diffWaysToCompute(input.substr(0, i));
				vector<int>res2 = diffWaysToCompute(input.substr(i + 1));
				for (auto s : res1) {
					for (auto t : res2) {
						if (c == '+') {
							res.push_back(s + t);
						}
						else if (c == '-') {
							res.push_back(s - t);
						}
						else if (c == '*') {
							res.push_back(s * t);
						}
					}
				}
			}
		}
		if (res.empty()) {
			res.push_back(stoi(input));
		}
		return res;
	}
	bool isAnagram(string s, string t) {
		vector<int> vecs(26, 0);
		vector<int> vect(26, 0);
		for (auto c : s) {
			++vecs[c - 'a'];
		}
		for (auto c : t) {
			++vect[c - 'a'];
		}
		for (int i = 0; i < 26; ++i) {
			if (vecs[i] != vect[i]) {
				return false;
			}
		}
		return true;
	}
	vector<string> binaryTreePaths(TreeNode* root) {
		vector<string> res;
		string now;
		binaryTreePaths_trace(root, res, now);
		return res;
	}
	void binaryTreePaths_trace(TreeNode* root, vector<string>& res, string now) {
		if (!root) {
			return;
		}
		now += to_string(root->val);
		if (!root->left && !root->right) {
			res.push_back(now);
			return;
		}
		now += "->";
		binaryTreePaths_trace(root->left, res, now);
		binaryTreePaths_trace(root->right, res, now);
		return;
	}
	int addDigits(int num) {
		//你可以不使用循环或者递归，且在 O(1) 时间复杂度内解决这个问题吗
		//简单的实现
		int temp = 0;
		int i;
		while (1) {
			while (num) {
				i = num % 10;
				num /= 10;
				temp += i;
			}
			if (temp < 10) {
				return temp;
			}
			num = temp;
		}
	}
	vector<int> singleNumber(vector<int>& nums) {
		vector<int> res;
		int temp = 0;
		for (auto s : nums) {
			temp ^= s;
		}
		int k = 0;
		int last;
		while (temp) {
			last = temp % 2;
			temp = temp >> 1;
			if (!k) {
				k = 1;
			}
			else {
				k = k << 1;
			}
			if (last) {
				break;
			}
		}
		int a = 0;
		int b = 0;
		for (auto s : nums) {
			auto l = s&k;
			if (l == 0) {
				a ^= s;
			}
			else {
				b ^= s;
			}
		}
		res.push_back(a);
		res.push_back(b);
		return res;
	}
};
int main() {
	Solution solu;
	vector<int>test260;
	//int res = solu.calculate("31 + 5 / 2");
	//test229 = solu.majorityElement(vector<int>{1, 2, 2, 3, 2, 1, 1, 3});
	test260 = solu.singleNumber(vector<int>{1, 2, 1, 3, 2, 5});
	return 0;
}