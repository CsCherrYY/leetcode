#include<iostream>
#include<map>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;
class Solution {
public:
	string getHint(string secret, string guess) {
		map<char, int>secmap, guemap;
		int bull = 0;
		for (int i = 0; i < secret.size(); ++i) {
			if (secret[i] == guess[i]) {
				++bull;
			}
			auto secit = secmap.find(secret[i]);
			if (secit == secmap.end()) {
				secmap.insert(pair<char, int>(secret[i], 1));
			}
			else {
				secmap[secret[i]]++;
			}
			auto gueit = guemap.find(guess[i]);
			if (gueit == guemap.end()) {
				guemap.insert(pair<char, int>(guess[i], 1));
			}
			else {
				guemap[guess[i]]++;
			}
		}
		int maxv = 0;
		for (auto s : secmap) {
			if (guemap.find(s.first) == guemap.end()) {
				continue;
			}
			maxv += min(guemap[s.first], s.second);
		}
		return to_string(bull) + "A" + to_string(maxv - bull) + "B";
	}
	int lengthOfLIS(vector<int>& nums) {
		if (!nums.size()) {
			return 0;
		}
		vector<int>dp(nums.size(), 1);
		int maxv = 1;
		for (int i = 1; i < nums.size(); ++i) {
			for (int j = 0; j < i; ++j) {
				if (nums[j] < nums[i]) {
					dp[i] = max(dp[i], dp[j] + 1);
				}
			}
			maxv = max(maxv, dp[i]);
		}
		return maxv;
	}
	map<int, int>dp309;
	int maxProfit(vector<int>& prices) {
		return maxProfitdp(prices, 0, prices.size() - 1);
	}
	int maxProfitdp(vector<int>& prices, int left, int maxlen) {
		if (left >= maxlen) {
			return 0;   //只有1个点无法卖了
		}  
		auto it = dp309.find(left);
		if (it != dp309.end()) {
			return it->second;
		}
		int profit = 0;
		int maxprofit = 0;
		//买left
		for (int i = left + 1; i <= maxlen; ++i) {
			//选择卖的日子
			profit = prices[i] - prices[left] + maxProfitdp(prices, i + 2, maxlen);
			maxprofit = max(maxprofit, profit);
		}
		//不买left
		profit = maxProfitdp(prices, left + 1, maxlen);
		maxprofit = max(maxprofit, profit);
		dp309.insert(pair<int, int>(left, maxprofit));
		return maxprofit;
	}
};
int main() {
	map<char, int>tmp;
	tmp.insert(pair<char, int>('a', 1));
	auto it = tmp.find('a');
	it->second++;
	int k = 0;
}