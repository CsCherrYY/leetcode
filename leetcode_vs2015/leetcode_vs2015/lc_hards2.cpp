#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_map>
#include<stack>
#include<unordered_set>
using namespace std;
class RandomizedSet {
private:
	vector<int>nums;
	unordered_map<int, int>table;
	int pos;
public:
	/** Initialize your data structure here. */
	RandomizedSet() {
		pos = 0;
	}

	/** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
	bool insert(int val) {
		if (table.find(val) != table.end()) {
			return false;
		}
		nums.push_back(val);
		table[val] = nums.size() - 1;
		return true;
	}

	/** Removes a value from the set. Returns true if the set contained the specified element. */
	bool remove(int val) {
		if (table.find(val) == table.end()) {
			return false;
		}
		if (!nums.size()) {
			return false;
		}
		int last = nums[nums.size() - 1];
		table[last] = table[val];
		nums[table[val]] = last;
		nums.pop_back();
		table.erase(val);
		return true;
	}

	/** Get a random element from the set. */
	int getRandom() {
		return nums[rand() % nums.size()];
	}
};
struct Interval {
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
	int search(vector<vector<int>>&dp, vector<int>& nums, int i, int j) {
		if (i > j) {
			return 0;
		}
		if (dp[i][j]) {
			return dp[i][j];
		}
		for (int k = i; k <= j; k++) {
			int left = search(dp, nums, i, k - 1);
			int right = search(dp, nums, k + 1, j);
			int mid = nums[i - 1] * nums[k] * nums[j + 1];
			dp[i][j] = max(dp[i][j], left + right + mid);
		}
		return dp[i][j];
	}
	int maxCoins(vector<int>& nums) {
		vector<vector<int>>dp(nums.size() + 2, vector<int>(nums.size() + 2, 0));
		nums.insert(nums.begin(), 1);
		nums.push_back(1);
		search(dp, nums, 1, nums.size() - 2);
		return dp[1][nums.size() - 2];
	}
	string removeDuplicateLetters(string s) {
		unordered_map<char, int>maps;
		unordered_set<char>hashtable;
		for (auto ch : s) {
			maps[ch]++;
		}
		string res = "0";
		for (auto ch : s) {
			maps[ch]--;
			if (hashtable.find(ch) != hashtable.end()) {
				continue;
			}
			while (ch < res[res.length() - 1] && maps[res[res.length() - 1]]) {
				//maps[res[res.length() - 1]]++;
				hashtable.erase(res[res.length() - 1]);
				res.pop_back();
			}
			res += ch;
			hashtable.insert(ch);
		}
		return res.substr(1, res.length() - 1);
	}
	static bool comp_pair(pair<int, int>a, pair<int, int>b) {
		return a.first == b.first ? a.second < b.second : a.first < b.first;
	}
	int maxEnvelopes(vector<pair<int, int>>& envelopes) {
		int size = envelopes.size();
		if (size == 0) {
			return 0;
		}
		if (size == 1) {
			return 1;
		}
		int maxv = 0;
		sort(envelopes.begin(), envelopes.end(), comp_pair);
		vector<int>dp(size, 1);
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < i; j++) {
				if (envelopes[i].first > envelopes[j].first&&envelopes[i].second > envelopes[j].second) {
					dp[i] = max(dp[i], dp[j] + 1);
					maxv = max(maxv, dp[i]);
				}
			}
		}
		return maxv;
	}
	int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
		//建立积分图，fig[i][j]为[0][0]到[i][j]之和
		if (!matrix.size() || !matrix[0].size()) {
			return 0;
		}
		vector<vector<int>>fig(matrix.size(), vector<int>(matrix[0].size(), 0));
		int max_sqre = -9999999;
		for (int i = 0; i < matrix.size(); i++) {
			for (int j = 0; j < matrix[i].size(); j++) {
				if (matrix[i][j] <= k) {
					max_sqre = max(max_sqre, matrix[i][j]);
				}
				if (i) {
					fig[i][j] += fig[i - 1][j];
				}
				if (j) {
					fig[i][j] += fig[i][j - 1];
				}
				if (i&&j) {
					fig[i][j] -= fig[i - 1][j - 1];
				}
				fig[i][j] += matrix[i][j];
			}
		}
		if (max_sqre == k) {
			return k;
		}
		int temp_sqre;
		for (int i = 0; i < matrix.size(); i++) {
			for (int j = 0; j < matrix[0].size(); j++) {
				//for every ij
				for (int m = 0; m <= i; m++) {
					for (int n = 0; n <= j; n++) {
						if (m&&n) {
							temp_sqre = fig[i][j] - fig[m - 1][j] - fig[i][n - 1] + fig[m - 1][n - 1];
						}
						else if (m) {
							temp_sqre = fig[i][j] - fig[m - 1][j];
						}
						else if (n) {
							temp_sqre = fig[i][j] - fig[i][n - 1];
						}
						else {
							temp_sqre = fig[i][j];
						}
						if (temp_sqre <= k && temp_sqre > max_sqre) {
							max_sqre = temp_sqre;
						}
					}
				}
			}
		}
		return max_sqre;
	}
	int gcd(int x, int y) {
		if (x == y) {
			return x;
		}
		if (x < y) {
			return gcd(y, x);
		}
		if (x%y == 0) {
			return y;
		}
		return gcd(x - y, y);
	}
	bool canMeasureWater(int x, int y, int z) {
		if (z > x + y) {
			return false;
		}
		if (x < y) {
			return canMeasureWater(y, x, z);
		}
		if (y == 0) {
			return z == y || z == x;
		}
		int temp = gcd(x, y);
		if (z%temp == 0) {
			return true;
		}
		return false;
	}
	int splitArray(vector<int>& nums, int m) {
		vector<vector<long long>>dp(nums.size(), vector<long long>(m, INT_MAX));
		long long sum = 0;
		for (int i = 0; i < nums.size(); i++) {
			sum += nums[i];
			dp[i][0] = sum;
		}
		for (int i = 1; i < nums.size(); i++) {
			for (int j = 1; j < min(m, i + 1); j++) {
				for (int k = i - 1; k >= j - 1; k--) {
					dp[i][j] = min(dp[i][j], max(dp[i][0] - dp[k][0], dp[k][j - 1]));
				}
			}
		}
		return dp[nums.size() - 1][m - 1];
	}
	string addStrings(string num1, string num2) {
		int loc1 = num1.length() - 1;
		int loc2 = num2.length() - 1;
		int carry = 0;
		string res;
		while (loc1 >= 0 || loc2 >= 0 || carry) {
			if (loc1 >= 0) {
				carry += (num1[loc1] - '0');
				loc1--;
			}
			if (loc2 >= 0) {
				carry += (num2[loc2] - '0');
				loc2--;
			}
			res.insert(res.begin(), '0' + (carry % 10));
			carry /= 10;
		}
		return res;
	}
	static bool comp_inte(Interval a, Interval b) {
		return a.start == b.start ? a.end < b.end : a.start < b.start;
	}
	int eraseOverlapIntervals(vector<Interval>& intervals) {
		if (!intervals.size()) {
			return 0;
		}
		sort(intervals.begin(), intervals.end(), comp_inte);
		vector<int>dp(intervals.size(), 1);
		for (int i = 0; i < intervals.size(); i++) {
			for (int j = 0; j < i; j++) {
				if (intervals[j].end <= intervals[i].start) {
					dp[i] = max(dp[i], dp[j] + 1);
				}
			}
		}
		return intervals.size() - dp[intervals.size() - 1];
	}
	static bool comp_arrow(const pair<int, int>a,const pair<int, int>b) {
		return a.second == b.second ? a.first < b.first : a.second < b.second;
	}
	int findMinArrowShots(vector<pair<int, int>>& points) {
		if (!points.size()) {
			return 0;
		}
		sort(points.begin(), points.end(), comp_arrow);
		int arrow = 0;
		int last_arrow = 0;
		for (int i = 0; i < points.size(); i++) {
			if (i == 0) {
				arrow++;
				last_arrow = points[i].second;
				continue;
			}
			if (points[i].first <= last_arrow) {
				continue;
			}
			else {
				arrow++;
				last_arrow = points[i].second;
			}
		}
		return arrow;
	}
	bool find132pattern(vector<int>& nums) {
		stack<int>temp;
		if (nums.size() < 3) {
			return false;
		}
		int minv = nums[0];
		for (int i = 0; i < nums.size(); i++) {
			if (temp.size() >= 2 && nums[i]<temp.top() && nums[i]>minv) {
				return true;
			}
			if (!temp.empty() && nums[i] > temp.top()) {
				temp.push(nums[i]);
			}
			minv = min(minv, nums[i]);
		}
		return false;
	}
};
int main() {
	Solution solu;
	//int res = solu.maxSumSubmatrix(vector<vector<int>>{{1, 0, 1}, { 0, -2, 3 }},2);
	int res = solu.findMinArrowShots(vector<pair<int, int>>{ {10, 16}, { 2, 8 }, { 1, 6 }, { 7, 12 }});
	bool j = solu.find132pattern(vector<int>{3, 1, 4, 2});
}