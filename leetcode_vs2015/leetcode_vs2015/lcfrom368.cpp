#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<queue>
using namespace std;
struct comp {
	bool operator ()(pair<pair<int, int>, int>a, pair<pair<int, int>, int>b) {
		return a.second > b.second;
	}
};
class Solution {
public:
	vector<int> largestDivisibleSubset(vector<int>& nums) {
		vector<int>res;
		if (nums.size() == 0) {
			return res;
		}
		sort(nums.begin(), nums.end());
		//递推：能整除其中任何一个数，必定能整除最大的那个数
		int maxlen = 1;
		int maxi = 0;
		//第一次循环先算出那个最大的数，再退回去求解集
		vector<int>dp(nums.size(), 1);
		vector<int>last(nums.size(), 1);
		for (int i = 0; i < nums.size(); ++i) {
			last[i] = i;
		}
		for (int i = 1; i < nums.size(); ++i) {
			for (int j = 0; j < i; ++j) {
				if (nums[i] % nums[j] == 0) {
					if (dp[j] + 1 > dp[i]) {
						dp[i] = dp[j] + 1;
						last[i] = j;
					}
					if (dp[i] > maxlen) {
						maxlen = dp[i];
						maxi = i;
					}
				}
			}
		}
		while (maxlen) {
			res.insert(res.begin(), nums[maxi]);
			maxi = last[maxi];
			maxlen--;
		}
		return res;
	}
	int getSum(int a, int b) {
		if (a == 0) {
			return b;
		}
		if (b == 0) {
			return a;
		}
		int c = a^b;
		int carry = a&b;
		carry &= INT_MAX;
		carry = carry << 1;
		if (!carry) {
			return c;
		}
		return getSum(c, carry);
	}
	vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
		vector<pair<int, int>> res;
		if (!nums1.size() || !nums2.size()) {
			return res;
		}
		priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int> >, comp> pq;
		for (int i = 0; i < nums1.size(); ++i) {
			for (int j = 0; j < nums2.size(); ++j) {
				pq.push(make_pair(make_pair(nums1[i], nums2[j]), nums1[i] + nums2[j]));
			}
		}
		while (k && !pq.empty()) {
			res.push_back(pq.top().first);
			pq.pop();
			k--;
		}
		return res;
	}
	int getMoneyAmount(int n) {
		map<pair<int, int>, int>dp;
		int ret = getMoneyAmounttrace(1, n, dp);
		return ret;
	}
	int getMoneyAmounttrace(int left, int right, map<pair<int, int>, int>&dp) {
		if (right <= left) {
			return 0;
		}
		if (right - left == 1) {
			return left;
		}
		if (right - left == 2) {
			return (right + left) / 2;
		}
		if (auto ret = dp[make_pair(left, right)]) {
			return ret;
		}
		int maxv = (left + right)*(right - left) / 2;
		for (int i = left; i <= right; ++i) {
			maxv = min(maxv, i + max(getMoneyAmounttrace(left, i - 1, dp),getMoneyAmounttrace(i + 1, right, dp)));
		}
		dp[make_pair(left, right)] = maxv;
		return maxv;
	}
};
int main() {
	Solution solu;
	//vector<int>solu368 = solu.largestDivisibleSubset(vector<int>{4, 8, 10, 240});
	//int solu371 = solu.getSum(-1, 1);
	int solu375 = solu.getMoneyAmount(10);
	return 0;
}