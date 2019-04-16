#include<iostream>
#include<stack>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include<string>
#include<queue>
#include<list>
using namespace std;
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class max_queue {  //做一个能取最大值的队列
public:
	queue<int>q;
	queue<int>maxq;
	max_queue() {}
	void push(int i) {

	}
};
class LRUCache {
private:
	int size;
	list<pair<int, int>> lis;
	unordered_map<int, list<pair<int, int>>::iterator>maps;
public:
	LRUCache(int capacity) {
		size = capacity;
	}

	int get(int key) {
		if (maps.find(key) != maps.end()) {
			int value = maps[key]->second;
			lis.splice(lis.begin(), lis ,maps[key]);
			return value;
		}
		return -1;
	}

	void put(int key, int value) {
		if (maps.find(key) != maps.end()) {
			maps[key]->second = value;
			get(key);
		}
		else {
			lis.emplace_front(key, value);
			maps[key] = lis.begin();
			if (lis.size() > size) {
				maps.erase(lis.back().first);
				lis.pop_back();
			}
		}
	}
};
class TrieNode{
public:
	bool isword;
	vector<TrieNode*>childs;
	TrieNode() {
		isword = false;
		childs = vector<TrieNode*>(26, nullptr);
	}
	~TrieNode() {
		for (auto ch : childs) {
			if (ch) {
				delete ch;
			}
		}
	}
};
class Solution {
public:
	int minDistance(string word1, string word2) {
		//problem 72
		//dp[i][j] 表示str1[0:i]和str2[0:j]的mindist
		if (!word1.length()) {
			return word2.length();
		}
		if (!word2.length()) {
			return word1.length();
		}
		vector<vector<int>>dp(word1.length() + 1, vector<int>(word2.length() + 1, 0));
		for (int i = 0; i <= word1.length(); i++) {
			dp[i][0] = i;
		}
		for (int i = 0; i <= word2.length(); i++) {
			dp[0][i] = i;
		}
		int minv;
		for (int i = 1; i <= word1.length(); i++) {
			for (int j = 1; j <= word2.length(); j++) {
				if (word1[i - 1] == word2[j - 1]) {
					dp[i][j] = dp[i - 1][j - 1];
				}
				else {
					minv = min(dp[i - 1][j], dp[i][j - 1]);
					minv = min(minv, dp[i - 1][j - 1]);
					dp[i][j] = minv + 1;
				}
			}
		}
		return dp[word1.length()][word2.length()];
	}
	int maxProfit_single(vector<int>& prices) {
		int ret = 0;
		vector<int>dp(prices.size(), 0);
		if (!prices.size()) {
			return 0;
		}
		for (int i = 0; i < prices.size(); i++) {
			if (i == 0) {
				dp[i] = prices[i];
			}
			else {
				dp[i] = min(dp[i - 1], prices[i]);
				ret = max(ret, prices[i] - dp[i - 1]);
			}
		}
		return ret;
	}
	int maxProfit(int k,vector<int>& prices) {
		if (k >= prices.size()-1) {
			int ret = 0;
			for (int i = 0; i < prices.size()-1; i++) {
				if (prices[i] < prices[i + 1]) {
					ret += prices[i + 1] - prices[i];
				}
			}
			return ret;
		}
		vector<vector<int>>dp(k + 1, vector<int>(prices.size(), 0));
		if (prices.size() <= 1) {
			return 0;
		}
		//dp[0][i]=0;
		int ret = 0;
		for (int i = 1; i <= k; i++) {
			int tmpmax = dp[i - 1][0] - prices[0];
			for (int j = 1; j < prices.size(); j++) {
				dp[i][j] = max(dp[i][j - 1], prices[j] + tmpmax);
				tmpmax = max(tmpmax, dp[i - 1][j] - prices[j]);   //这里记录，就不用再遍历一次
				ret = max(dp[i][j], ret);
			}
		}
		return ret;
	}
	int maxv = INT_MIN;
	int maxPathSum(TreeNode* root) {
		getmaxv(root);
		return maxv;
	}
	int getmaxv(TreeNode* root) {
		if (!root) {
			return 0;
		}
		int leftv = getmaxv(root->left);
		int rightv = getmaxv(root->right);  
		int case1 = root->val;
		int case2 = root->val + leftv;
		int case3 = root->val + rightv;
		int case4 = root->val + leftv + rightv;
		//第4种是不和上面的节点连接的
		int max_temp = max(max(case1, case2), max(case3, case4));
		maxv = max(maxv, max_temp);
		return max(max(case1, case2), max(case2, case3));
	}
	bool ishw(string s) {
		if (!s.length()) {
			return true;
		}
		int i = 0;
		int j = s.length() - 1;
		while (i < j) {
			if (s[i] != s[j]) {
				return false;
			}
			i++;
			j--;
		}
		return true;
	}
	int minCut(string s) {
		if (!s.length()) {
			return 0;
		}
		string temp = s;
		reverse(s.begin(), s.end());
		if (s == temp) {
			return 0;
		}
		for (int i = 0; i < s.length(); i++) {
			string temp1 = s.substr(0, i);
			string temp2 = s.substr(i);
			if (ishw(temp1) && ishw(temp2)) {
				return 1;
			}
		}
		vector<int>dp(s.length() + 1, 0);
		for (int i = 0; i < dp.size(); i++) {
			dp[i] = i;
		}
		dp[0] = -1;
		for (int i = 0; i < dp.size() - 1; i++) {
			for (int j = 0; j <= i; j++) {
				if (ishw(s.substr(j, i - j + 1))) {
					dp[i + 1] = min(dp[i + 1], dp[j] + 1);
				}
			}
		}
		return dp[s.length()];
	}
	vector<string> wordBreak(string s, vector<string>& wordDict) {
		vector<string> ret;
		string ans;
		unordered_map<string, string>dp;
		search(s, wordDict, ret, ans, dp);
		return ret;
	}
	void search(string s, vector<string>& wordDict, vector<string> &ret,string ans, unordered_map<string, string>&dp) {
		if (!s.length()) {
			ret.push_back(ans);
		}
		for (auto it : wordDict) {
			if (it == s.substr(0, it.length())) {
				string temp = ans + it;
				if (s.length() != it.length()) {
					temp += " ";
				}
				search(s.substr(it.length()), wordDict, ret, temp,dp);
			}
		}
	}
	int findMin(vector<int>& nums) {
		int low = 0;
		int high = nums.size() - 1;
		while (low < high) {
			int mid = low + (high - low) / 2;
			if (nums[mid] > nums[high]) {
				low = mid + 1;
			}
			else if (nums[mid] < nums[high]) {
				high = mid;
			}
			else {
				high--;
			}
		}
		return nums[low];
	}
	int maximumGap(vector<int>& nums) {
		if (nums.size() < 2) {
			return 0;
		}
		int maxv = nums[0];
		int minv = nums[0];
		for (int i = 1; i < nums.size(); i++) {
			if (nums[i] < minv) {
				minv = nums[i];
			}
			if (nums[i] > maxv) {
				maxv = nums[i];
			}
		}
		int buckets_diff = (maxv - minv) / (nums.size() - 1);
		if (buckets_diff*(nums.size() - 1) < (maxv - minv)) {
			buckets_diff += 1;
		}
		if (!buckets_diff) {
			return 0;
		}
		//在桶排序的情况下最大间隔只会出现在两个桶之间
		vector<bool>flag(nums.size(), false);
		vector<vector<int>>bucket(nums.size(), vector<int>(2, maxv + 1));  //minv maxv
		for (int i = 0; i < bucket.size(); i++) {
			bucket[i][1] = minv - 1;
		}
		for (int i = 0; i < nums.size(); i++) {
			int number = (nums[i] - minv) / buckets_diff;
			if (nums[i] < bucket[number][0]) {
				bucket[number][0] = nums[i];
				flag[number] = true;
			}
			if (nums[i] > bucket[number][1]) {
				bucket[number][1] = nums[i];
				flag[number] = true;
			}
		}
		int ret = 0;
		int last_flag = 0;
		for (int i = 1; i < bucket.size(); i++) {
			if (flag[i]) {
				ret = max(ret, bucket[i][0] - bucket[last_flag][1]);
				last_flag = i;
			}
		}
		return ret;
	}
	int calculateMinimumHP(vector<vector<int>>& dungeon) {
		if (!dungeon.size() || !dungeon[0].size()) {
			return 0;
		}
		int rows = dungeon.size();
		int columns = dungeon[0].size();
		vector<vector<int>>dp(rows, vector<int>(columns, 1)); //dp[i][j] represents the min hp of (i,j) back to begin
		//to solve the minv of 0,0
		int temp;
		for (int i = rows - 1; i >= 0; i--) {
			for (int j = columns - 1; j >= 0; j--) {
				if (i == rows - 1 && j == columns - 1) {
					temp = 1 - dungeon[i][j];
					dp[i][j] = (temp) < 1 ? 1 : temp;
				}
				else if (i != rows - 1 && j != columns - 1) {
					temp = min(dp[i + 1][j], dp[i][j + 1]) - dungeon[i][j];
					dp[i][j] = (temp) < 1 ? 1 : temp;
				}
				else if (i == rows - 1) {
					temp = dp[i][j + 1] - dungeon[i][j];
					dp[i][j] = (temp) < 1 ? 1 : temp;
				}
				else {
					temp = dp[i + 1][j] - dungeon[i][j];
					dp[i][j] = (temp) < 1 ? 1 : temp;
				}
			}
		}
		return dp[0][0];
	}
	bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
		//拓扑排序
		vector<int>course(numCourses, 0);
		queue<int>tp;
		int finish = 0;
		for (auto pre : prerequisites) {
			course[pre.first]++;           //[1,0] 0->1
		}
		for (int i = 0; i < course.size(); i++) {
			if (course[i] == 0) {
				tp.push(i);
			}
		}
		while (!tp.empty()) {
			for (auto pre : prerequisites) {
				if (pre.second == tp.front()) {
					course[pre.first]--;
					if (!course[pre.first]) {
						tp.push(pre.first);
					}
				}
			}
			tp.pop();
			finish++;
		}
		if (finish == numCourses) {
			return true;
		}
		return false;
	}
	vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
		vector<int>ret;
		vector<int>course(numCourses, 0);
		queue<int>tp;
		int finish = 0;
		for (auto pre : prerequisites) {
			course[pre.first]++;           //[1,0] 0->1
		}
		for (int i = 0; i < course.size(); i++) {
			if (course[i] == 0) {
				tp.push(i);
			}
		}
		while (!tp.empty()) {
			for (auto pre : prerequisites) {
				if (pre.second == tp.front()) {
					course[pre.first]--;
					if (!course[pre.first]) {
						tp.push(pre.first);
					}
				}
			}
			ret.push_back(tp.front());
			tp.pop();
			finish++;
		}
		if (finish == numCourses) {
			return ret;
		}
		ret.clear();
		return ret;
	}
	TrieNode*Trieroot = new TrieNode();
	void addword(string word, TrieNode*root) {
		TrieNode*work = root;
		for (auto ch : word) {
			if (!work->childs[ch - 'a']) {
				work->childs[ch - 'a'] = new TrieNode();
			}
			work = work->childs[ch - 'a'];
		}
		work->isword = true;
		return;
	}
	vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
		vector<string>ret;
		if (!board.size() || !board[0].size()) {
			return ret;
		}
		for (auto word : words) {
			addword(word, Trieroot);
		}
		vector<vector<bool>>flag(board.size(), vector<bool>(board[0].size(), false));
		for (int i = 0; i < board.size(); i++) {
			for (int j = 0; j < board[0].size(); j++) {
				if (Trieroot->childs[board[i][j] - 'a']) {
					flag[i][j] = true;
					string res;
					res += board[i][j];
					DFS_word(board, flag, res, Trieroot->childs[board[i][j] - 'a'], i, j, ret);
					flag[i][j] = false;
				}
			}
		}
		return ret;
	}
	void DFS_word(vector<vector<char>>& board, vector<vector<bool>>&flag, string res, TrieNode* work, int i, int j, vector<string>&ret) {
		if (work->isword) {
			ret.push_back(res);
			work->isword = false;  //防止重复
		}
		if (i - 1 >= 0 && !flag[i - 1][j] && work->childs[board[i - 1][j] - 'a']) {
			flag[i - 1][j] = true;
			DFS_word(board, flag, res + board[i - 1][j], work->childs[board[i - 1][j] - 'a'], i - 1, j, ret);
			flag[i - 1][j] = false;
		}
		if (i + 1 <= board.size() - 1 && !flag[i + 1][j] && work->childs[board[i + 1][j] - 'a']) {
			flag[i + 1][j] = true;
			DFS_word(board, flag, res + board[i + 1][j], work->childs[board[i + 1][j] - 'a'], i + 1, j, ret);
			flag[i + 1][j] = false;
		}
		if (j - 1 >= 0 && !flag[i][j - 1] && work->childs[board[i][j - 1] - 'a']) {
			flag[i][j - 1] = true;
			DFS_word(board, flag, res + board[i][j - 1], work->childs[board[i][j - 1] - 'a'], i, j - 1, ret);
			flag[i][j - 1] = false;
		}
		if (j + 1 <= board[0].size() - 1 && !flag[i][j + 1] && work->childs[board[i][j + 1] - 'a']) {
			flag[i][j + 1] = true;
			DFS_word(board, flag, res + board[i][j + 1], work->childs[board[i][j + 1] - 'a'], i, j + 1, ret);
			flag[i][j + 1] = false;
		}
		return;
	}
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		if (!nums.size()) {
			return nums;
		}
		vector<int>ret;
		for (int i = 0; i < k; i++) {
			
		}
		return ret;
	}
	void searchop(vector<string>&res, string num, int target, long long val,long long last,string ans) {
		if (!num.size()) {
			if (val == target) {
				res.push_back(ans);
			}
			return;
		}
		for (int i = 1; i <= num.size(); i++) {
			string current = num.substr(0, i);
			if (current.size() > 1 && current[0] == '0') {
				return;
			}
			string next = num.substr(i);
			if (!ans.length()) {
				searchop(res, next, target, stoll(current), stoll(current), current);
			}
			else {
				searchop(res, next, target, stoll(current) + val, stoll(current), ans + "+" + current);
				searchop(res, next, target, -stoll(current) + val, -stoll(current), ans + "-" + current);
				searchop(res, next, target, (val - last) + (last*stoll(current)), (last*stoll(current)), ans + "*" + current);
			}
		}
	}
	vector<string> addOperators(string num, int target) {
		vector<string>res;
		searchop(res, num, target, 0, 0,  "");
		return res;
	}
	bool isvalidkh(string s) {
		int cnt = 0;
		for (auto it : s) {
			if (it == '(') {
				cnt++;
			}
			else if (it == ')') {
				if (cnt) {
					cnt--;
				}
				else {
					return false;
				}
			}
		}
		if (cnt) {
			return false;
		}
		return true;
	}
	void delkh(unordered_set<string> &res, int left, int right, string s, int offset) {
		if (!left && !right) {
			if (isvalidkh(s)) {
				//res.push_back(s);
				res.insert(s);
			}
			return;
		}
		if (offset == s.length()) {
			return;
		}
		if (left) {
			if (s[offset] == '(') {
				string temp = s.substr(0, offset) + ((offset == s.length() - 1) ? "" : s.substr(offset + 1));
				delkh(res, left - 1, right, temp, offset);
			}
		}
		if (right) {
			if (s[offset] == ')') {
				string temp = s.substr(0, offset) + ((offset == s.length() - 1) ? "" : s.substr(offset + 1));
				delkh(res, left, right - 1, temp, offset);
			}
		}
		delkh(res, left, right, s, offset + 1);
	}
	vector<string> removeInvalidParentheses(string s) {
		//先计算出需要remove的括号的数量左和右，再递归
		int left = 0;
		int right = 0;
		for (int i = 0; i < s.length(); i++) {
			if (s[i] == '(') {
				left++;
			}
			else if (s[i] == ')') {
				if (left) {
					left--;
				}
				else {
					right++;
				}
			}
		}
		vector<string> res;
		unordered_set<string>res_set;
		delkh(res_set, left, right, s, 0);
		res.assign(res_set.begin(), res_set.end());
		return res;
	}
	vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {

	}
};
int main() {
	Solution solu;
	vector<string> ret = solu.addOperators("105", 5);
	return 0;
	
}