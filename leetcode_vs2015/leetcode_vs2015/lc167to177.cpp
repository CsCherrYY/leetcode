#include<vector>
#include<stack>
#include<map>
using namespace std;
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class BSTIterator {
public:
	//O(H)解法，不用一次遍历完全
	BSTIterator(TreeNode* root) {
		for (; root != nullptr; root = root->left) {
			stacks.push(root);
		}
	}
	/** @return the next smallest number */
	int next() {
		TreeNode* smallest = stacks.top();
		stacks.pop();
		int val = smallest->val;
		smallest = smallest->right;
		for (; smallest != nullptr; smallest = smallest->left) {
			stacks.push(smallest);
		}
		return val;
	}
	/** @return whether we have a next smallest number */
	bool hasNext() {
		return !stacks.empty();
	}
private:
	stack<TreeNode*> stacks;
};
class Solution {
public:
	vector<int> twoSum(vector<int>& numbers, int target) {
		vector<int> res;
		map<int, int> maps;
		int i;
		for (i = 0; i < numbers.size(); i++) {
			auto it = maps.find(numbers[i]);
			if (it == maps.end()) {
				maps.insert(pair<int, int>(target - numbers[i], i));
			}
			else {
				res.push_back(it->second + 1);

				res.push_back(i + 1);
			}
		}
		return res;
	}
	string convertToTitle(int n) {
		//10进制转26进制
		//A~Z
		int k;
		char ins;
		string temp;
		if (!n) {
			return temp;
		}
		while (n > 0) {
			n -= 1;
			k = n % 26;
			ins = 'A' + k;
			temp.insert(temp.begin(), ins);
			n = n / 26;
		}
		return temp;
	}
	int majorityElement(vector<int>& nums) {
		//摩尔投票法求众数
		if (!nums.size()) {
			return -1;
		}
		int temp = nums[0];
		int count = 1;
		for (int i = 1; i < nums.size(); ++i) {
			if (nums[i] == temp) {
				count++;
			}
			else {
				if (count == 0) {
					temp = nums[i];
					count = 1;
				}
				else {
					count--;
				}
			}
		}
		return temp;
	}
	int titleToNumber(string s) {
		if (s == "") {
			return 0;
		}
		int sum = 0;
		for (int i = 0; i < s.length(); ++i) {
			sum *= 26;
			sum += (s[i] - 'A' + 1);
		}
		return sum;
	}
	int trailingZeroes(int n) {
		//数因数中2和5的个数，又因为5的个数<<2的个数，所以数5
		int res = 0;
		while (n > 0) {
			res += n / 5;
			n /= 5;
		}
		return res;
	}
};
int main() {
	return 0;
}