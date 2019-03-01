#include<vector>
#include<math.h>
#include<unordered_set>
#include<algorithm>
#include<set>
#include<queue>
using namespace std;
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class MyStack {
private:
	queue<int> myqueue;
public:
	/** 入队，如例：q.push(x); 将x 接到队列的末端。
	出队，如例：q.pop(); 弹出队列的第一个元素，注意，并不会返回被弹出元素的值。
	访问队首元素，如例：q.front()，即最早被压入队列的元素。
	访问队尾元素，如例：q.back()，即最后被压入队列的元素。
	判断队列空，如例：q.empty()，当队列空时，返回true。
	访问队列中的元素个数，如例：q.size()
	Initialize your data structure here. */
	MyStack() {

	}
	/** Push element x onto stack. */
	void push(int x) {
		int size = myqueue.size();
		myqueue.push(x);
		while (size) {
			myqueue.push(myqueue.front());
			myqueue.pop();
			--size;
		}
	}
	/** Removes the element on top of the stack and returns that element. */
	int pop() {
		int temp = myqueue.front();
		myqueue.pop();
		return temp;
	}
	/** Get the top element. */
	int top() {
		int temp = myqueue.front();
		return temp;
	}
	/** Returns whether the stack is empty. */
	bool empty() {
		return myqueue.size();
	}
};
class Solution {
public:
	vector<vector<int>> combinationSum3(int k, int n) {
		vector<vector<int>> temp;
		vector<int> ans;
		int left = 1;
		combinationSum3_trace(temp, left, k, n, ans);
		return temp;
	}
	void combinationSum3_trace(vector<vector<int>>& temp, int left, int k, int n, vector<int> ans) {
		if (!k) {    //k=0得出答案
			if (!n) {
				temp.push_back(ans);
			}
			return;
		}
		if (n < left || left > 9) {  //无解
			return;   
		}
		int i;
		for (i = left; i <= 9; ++i) {
			if (n - i >= 0) {
				ans.push_back(i);
				combinationSum3_trace(temp, i + 1, k - 1, n - i, ans);
				ans.pop_back();
			}
		}
		return;
	}
	bool containsDuplicate(vector<int>& nums) {
		unordered_set<int> table;
		for (int i = 0; i < nums.size(); ++i) {
			auto it = table.find(nums[i]);
			if (it == table.end()) {
				table.insert(nums[i]);
			}
			else {
				return true;
			}
		}
		return false;
	}
	bool containsNearbyDuplicate(vector<int>& nums, int k) {
		//table的size最大为k+1
		unordered_set<int> table;
		for (int i = 0; i < nums.size(); ++i) {
			if (table.size() > k) {
				auto del = table.find(nums[i - k - 1]);
				table.erase(del);
			}
			auto it = table.find(nums[i]);
			if (it == table.end()) {
				table.insert(nums[i]);
			}
			else {
				return true;
			}
		}
		return false;
	}
	bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
		//滑动窗口
		set<long long>table;
		long long llt = t;
		int i = 0;
		int size = nums.size();
		if (!size) {
			return false;
		}
		for (; i < size; ++i) {
			if (i > k) {
				table.erase(nums[i - k - 1]);
			}
			auto it = table.lower_bound(nums[i] - llt);
			if (it != table.end() && *it - nums[i] <= llt) {
				return true;
			}
			table.insert(nums[i]);
		}
		return false;
	}
	int maximalSquare(vector<vector<char>>& matrix) {
		//以i,j为右下角点，边长满足dp[i][j]=1+min(dp[i-1][j],dp[i][j-1],dp[i-1][j-1])
		int maxv = 0;
		int size_h = matrix.size();
		if (!size_h) {
			return 0;
		}
		int size_w = matrix[0].size();
		vector<vector<int>>dptable(size_h, vector<int>(size_w, 0));
		int w, h;
		int mintemp;
		for (w = 0; w < size_w; ++w) {
			if (matrix[0][w] == '1') {
				dptable[0][w] = 1;
				maxv = 1;
			}
		}
		for (h = 0; h < size_h; ++h) {
			if (matrix[h][0] == '1') {
				dptable[h][0] = 1;
				maxv = 1;
			}
		}
		for (h = 1; h < size_h; ++h) {
			for (w = 1; w < size_w; ++w) {
				if (matrix[h][w] == '1') {
					mintemp = min(dptable[h - 1][w], dptable[h][w - 1]);
					dptable[h][w] = 1 + min(mintemp, dptable[h - 1][w - 1]);
					maxv = max(maxv, dptable[h][w] * dptable[h][w]);
				}
			}
		}
		return maxv;
	}
	int countNodes(TreeNode* root) {
		if (!root) {
			return 0;
		}
		int left = getdepth(root->left);
		int right = getdepth(root->right);
		if (left == right) {  //在右边找
			return 1 + pow(2, left) - 1 + countNodes(root->right);
		}
		else {   //这里else里面其实判定右子数是笑了一层的完全二叉树
			return 1 + countNodes(root->left) + pow(2, right) - 1;
		}
	}
	int getdepth(TreeNode *root) {
		int len = 0;
		if (!root) {
			return len;
		}
		return 1 + getdepth(root->left);
	}
	int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
		if (E < A) {   //确保后一个在右边
			return computeArea(E, F, G, H, A, B, C, D);
		}
		int squarea = (C - A)*(D - B);
		int squareb = (G - E)*(H - F);
		int square;
		int lena = B - H;
		int lenb = D - F;
		int lenc = B - F;
		int lend = D - H;
		if (E >= C) {
			square = 0;//无重叠
		}
		else if (C >= G) {
			if (lena >= 0 && lenc >= 0 || lenb <= 0 && lend <= 0) {   //不相交
				square = 0;
			}
			else if (lenc <= 0 && lend >= 0) { //全部包含
				square = squareb;
			}
			else if (lenc >= 0 && lend <= 0) {
				square = (D - B)*(G - E);
			}
			else {
				square = (G - E)*min(abs(B - H), abs(D - F));
			}
		}
		else {
			if (lena >= 0 && lenc >= 0 || lenb <= 0 && lend <= 0) {   //不相交
				square = 0;
			}
			else if (lenc <= 0 && lend >= 0) {
				square = abs(C - E)*(H - F);
			}
			else if (lenc >= 0 && lend <= 0) {
				square = (C - E)*(D - B);
			}
			else {
				square = abs(C - E)*min(abs(B - H), abs(D - F));
			}
		}
		return squarea - square + squareb;
	}
	TreeNode* invertTree(TreeNode* root) {
		if (!root) {
			return root;
		}
		TreeNode *temp = root->left;
		root->left = invertTree(root->right);
		root->right = invertTree(temp);
		return root;
	}
};
int main() {
	Solution solu;
	vector<vector<int>> test216;
	int test222;
	test216 = solu.combinationSum3(3, 7);
	test222 = solu.computeArea(-2, -2, 2, 2, 1, -3, 3, 3);
	return 0;
}