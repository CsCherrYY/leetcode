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
};
int main() {
	return 0;
}