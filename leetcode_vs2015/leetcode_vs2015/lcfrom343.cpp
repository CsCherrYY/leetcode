#include<iostream>
#include<set>
#include<vector>
#include<algorithm>
#include<queue>
#include<unordered_map>
#include<map>
using namespace std;
struct comp {
	bool operator()(pair<int,int> a, pair<int,int> b) {
		//默认最大堆
		return a.first < b.first;//最小堆，从小到大排序
	}
};
class Solution {
public:
	int integerBreak(int n) {
		//你可以假设 n 不小于 2 且不大于 58
		//i=0->1 i=1->2
		vector<int>dp(n + 1, -1);
		dp[0] = 1;
		dp[1] = 1;
		dp[2] = 1;
		int temp = 0;
		for (int i = 3; i <= n; ++i) {
			for (int j = 1; j <= i - 1; ++j) {
				dp[i] = max(dp[j] * dp[i - j], dp[i]);
				dp[i] = max(j*(i - j), dp[i]);
			}
		}
		return dp[n];
	}
	void reverseString(vector<char>& s) {
		int left = 0;
		int right = s.size() - 1;
		char temp;
		while (right > left) {
			temp = s[left];
			s[left] = s[right];
			s[right] = temp;
			++left;
			--right;
		}
		return;
	}
	vector<int> topKFrequent(vector<int>& nums, int k) {
		unordered_map<int, int> map;
		for (int num : nums) {
			map[num]++;
		}
		vector<int> res;
		priority_queue<pair<int, int>,vector<pair<int,int>>,comp> pq;
		for (auto it = map.begin(); it != map.end(); it++) {
			pq.push(make_pair(it->second, it->first));
			if (pq.size() > (int)map.size() - k) {
				res.push_back(pq.top().second);
				pq.pop();
			}
		}
		return res;
	}
	vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
		set<int> set1, set2;
		vector<int> vec;
		for (auto s : nums1) {
			set1.insert(s);
		}
		for (auto t : nums2) {
			if (set1.find(t)!=set1.end()) {
				set2.insert(t);
			}
		}
		vec.assign(set2.begin(), set2.end());
		return vec;
	}
	vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
		map<int, int> map1;
		vector<int>res;
		for (auto s : nums1) {
			map1[s]++;
		}
		for (auto s : nums2) {
			if (map1[s] > 0) {
				res.push_back(s);
				map1[s]--;
			}
		}
		return res;
	}
	int countNumbersWithUniqueDigits(int n) {
		//给定一个非负整数 n，计算各位数字都不同的数字 x 的个数，其中 0 ≤ x < 10^n。
		if (n == 0) {
			return 1;
		}
		if (n == 1) {
			return 10;
		}
		if (n > 10) {
			return 0;
		}
		int res = 9;
		int count = 1;
		for (int i = 9; i >= 0; --i) {
			res *= i;
			count++;
			if (count == n) {
				break;
			}
		}
		return res + countNumbersWithUniqueDigits(n - 1);
	}
	bool isPerfectSquare(int num) {
		if (num == 1) {
			return true;
		}
		int l = 0;
		int r = num;
		int mid;
		long long temp;
		while (l <= r) {
			mid = l + (r - l) / 2;
			temp = mid*mid;
			if (temp == num) {
				return true;
			}
			else if (temp > num) {
				r = mid - 1;
			}
			else {
				l = mid + 1;
			}
		}
		return false;
	}
};
int main() {
	Solution solu;
	bool solu367 = solu.isPerfectSquare(16);
	return 0;
}