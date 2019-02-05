#include<vector>
#include<algorithm>
#include<string>
#include<map>
#include<set>
//#include<hash_map>
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
using namespace std;
class Solution {
public:
	int maxProfitI(vector<int>& prices) {
		int i, size, min_temp;
		size = prices.size();
		vector<int>dp(size, 0);
		if (size<=1) {
			return 0;
		}
		min_temp = prices[0];
		for (i = 1; i < size; i++) {
			dp[i] = max(prices[i] - min_temp, dp[i - 1]);
			min_temp = min(prices[i], min_temp);
		}
		if (dp[size - 1] < 0) {
			return 0;
		}
		return dp[size - 1];
		//第i天的最大收益，两种情况，第一种利用该点，即dp[i]=a[i]-min{a[i-1]}
		//第二种不利用该点 dp[i]=dp[i-1]
	}
	int maxProfitII(vector<int>& prices) {
		//简单的一次遍历：将所有后一个大于前一个的差值相加
		int max = 0;
		int i;
		for (i = 1; i < prices.size(); i++) {
			if (prices[i] > prices[i - 1]) {
				max += prices[i] - prices[i - 1];
			}
		}
		return max;
	}
	bool isPalindrome(string s) {
		int len = s.length();
		if (len <= 1) {
			return true;
		}
		int start = 0;
		int end = len - 1;
		while (1) {
			if (end - start <= 0) {
				return true;
			}
			while (start < end) {    //这里要小于
				if (s[start] >= '0'&&s[start] <= '9') {
					break;
				}
				if (s[start] >= 'a'&&s[start] <= 'z') {
					break;
				}
				if (s[start] >= 'A'&&s[start] <= 'Z') {
					s[start] += 32;
					break;
				}
				start++;
			}
			while (start < end) {
				if (s[end] >= '0'&&s[end] <= '9') {
					break;
				}
				if (s[end] >= 'a'&&s[end] <= 'z') {
					break;
				}
				if (s[end] >= 'A'&&s[end] <= 'Z') {
					s[end] += 32;
					break;
				}
				end--;
			}
			if (s[start] == s[end]) {
				start++;
				end--;
				continue;
			}
			else {
				break;
			}
		}
		return false;
	}
	bool diffone(const string &a,const string &b) {//好习惯是不修改的对象作为const引用
		int count = 0;
		for (int i = 0; i < a.length(); i++) {
			if (a[i] != b[i]) {
				count++;
			}
		}
		return count == 1;
	}
	int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
		//你可以假设 beginWord 和 endWord 是非空的，且二者不相同
		//用图搜索，构建wordlist每个单词的邻接图
		if (find(wordList.begin(), wordList.end(), endWord) == wordList.end()) {
			return 0;
		}
		map<string, vector<string>> dict;//每个string对应可达string的表
		vector<string> temp;
		wordList.push_back(beginWord);
		int i, j;
		for (i = 0; i < wordList.size(); i++) {
			temp.clear();
			for (j = 0; j < wordList.size(); j++) {
				if (i != j) {
					if (diffone(wordList[i], wordList[j])) {
						temp.push_back(wordList[j]);
					}
				}
			}
			dict.insert(pair <string, vector<string>>(wordList[i], temp));
		}
		vector<pair<string, int>> queue;
		set<string> visit;
		queue.push_back(make_pair(beginWord, 1));
		visit.insert(beginWord);
		while (!queue.empty()) {
			string node = queue[0].first;
			int step = queue[0].second;
			queue.erase(queue.begin());
			if (node == endWord) {
				return step;
			}
			vector<string>neighbor = dict[node];
			auto it = neighbor.begin();
			while (it != neighbor.end()) {
				if (visit.find(*it) == visit.end()) {
					queue.push_back(make_pair(*it, step + 1));
					visit.insert(*it);
				}
				it++;
			}
		}
		return 0;
	}
	vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
		vector<vector<string>> res;  //这题结果过不了
		if (find(wordList.begin(), wordList.end(), endWord) == wordList.end()) {
			return res;
		}
		map<string, vector<string>> dict;//每个string对应可达string的表
		vector<string> temp;
		wordList.push_back(beginWord);
		int i, j;
		int len_min = wordList.size() + 2;
		for (i = 0; i < wordList.size(); i++) {
			temp.clear();
			for (j = 0; j < wordList.size(); j++) {
				if (i != j) {
					if (diffone(wordList[i], wordList[j])) {
						temp.push_back(wordList[j]);
					}
				}
			}
			dict.insert(pair <string, vector<string>>(wordList[i], temp));
		}
		vector<pair<string, vector<string>>> queue;
		set<string> visit;
		vector<string> tempstr;
		queue.push_back(make_pair(beginWord, tempstr));
		visit.insert(beginWord);
		while (!queue.empty()) {
			string node = queue[0].first;
			vector<string> step = queue[0].second;
			queue.erase(queue.begin());
			if (node == endWord) {
				if (step.size() <= len_min) {
					len_min = step.size();
					step.push_back(endWord);
					res.push_back(step);
				}
				continue;
			}
			vector<string>neighbor = dict[node];
			auto it = neighbor.begin();
			while (it != neighbor.end()) {
				vector<string>temp1 = step;
				temp1.push_back(node);
				if (find(step.begin(),step.end(),*it) == step.end()) {
					queue.push_back(make_pair(*it, temp1));
					visit.insert(*it);
				}
				it++;
			}
		}
		return res;
	}
	int longestConsecutive(vector<int>& nums) {
		map<int, int>maptable;
		int len, left, right;
		int maxlen = 0;
		for (int i = 0; i < nums.size(); i++) {
			if (maptable.find(nums[i]) == maptable.end()) {
				if (maptable.find(nums[i] - 1) == maptable.end()) {
					left = 0;
				}
				else {
					left = maptable[nums[i] - 1];
				}
				if (maptable.find(nums[i] + 1) == maptable.end()) {
					right = 0;
				}
				else {
					right = maptable[nums[i] + 1];
				}
				len = left + right + 1;          //延长区间，连接
				maptable[nums[i]] = len;
				maxlen = max(maxlen, len);
				maptable[nums[i] - left] = len;   //只需要更新区间端点的长度
				maptable[nums[i] + right] = len;
			}
		}
		return maxlen;
	}
	int sumNumbers(TreeNode* root) {
		int nowsum = 0;
		int temp = 0;
		sumNumberscs(root, temp, nowsum);
		return nowsum;
	}
	void sumNumberscs(TreeNode* root, int temp, int& nowsum) {
		if (!root) {
			nowsum += temp;
			return;
		}
		int newint = temp * 10 + root->val;
		if (root->left) {
			sumNumberscs(root->left, newint, nowsum);
		}
		if (root->right) {
			sumNumberscs(root->right, newint, nowsum);
		}
		if (!root->left && !root->right) {
			nowsum += newint;
		}
		return;
	}
	void solve(vector<vector<char>>& board) {
		//首先对边界上每一个'O'做深度优先搜索，将与其相连的所有'O'改为'-'。然后遍历矩阵，将矩阵中所有'O'改为'X',将矩阵中所有'-'变为'O'
		int len = board.size();
		if (!len) {
			return;
		}
		int wid = board[0].size();
		if (!wid) {
			return;
		}
		int i, j;
		for (i = 0; i < wid; i++) {
			dfs(board, 0, i);
			dfs(board, len - 1, i);
		}
		for (i = 0; i < len; i++) {
			dfs(board, i, 0);
			dfs(board, i, wid - 1);
		}
		for (i = 0; i < len; i++) {
			for (j = 0; j < wid; j++) {
				if (board[i][j] == 'O') {
					board[i][j] = 'X';
				}
				else if (board[i][j] == '-') {
					board[i][j] = 'O';
				}
			}
		}
		return;
	}
	void dfs(vector<vector<char>>& board, int i, int j) {
		int len = board.size();
		int wid = board[0].size();
		if (i < 0 || i >= len) {
			return;
		}
		if (j < 0 || j >= wid) {
			return;
		}
		if (board[i][j] != 'O') {
			return;
		}
		board[i][j] = '-';
		dfs(board, i - 1, j);
		dfs(board, i + 1, j);
		dfs(board, i, j - 1);
		dfs(board, i, j + 1);
		return;
	}
};
int main() {
	Solution solu;
	bool solu125;
	int solu127, solu128;
	vector<int> nums = { 100,4,200,1,3,2 };
	vector<string> wordList = { "hot","dot","dog","lot","log","cog" };
	int test = 128;
	vector<vector<string>> solu126;
	switch (test)
	{
	case 125:
		solu125 = solu.isPalindrome("A man, a plan, a canal : Panama");
		break;
	case 126:
		solu126 = solu.findLadders("hit", "cog", wordList);
		break;
	case 127:
		solu127 = solu.ladderLength("hit", "cog", wordList);
		break;
	case 128:
		solu128 = solu.longestConsecutive(nums);
		break;
	default:
		break;
	}
	return 0;
}