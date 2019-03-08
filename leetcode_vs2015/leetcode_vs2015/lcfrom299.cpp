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
	vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
		//先找叶子节点，再按次序删掉，反复（逆向BFS）
		vector<int> res;
		if (!n) {
			return res;
		}
		map<int, int>nodes;
		for (auto s : edges) {
			auto t = nodes.find(s.first);
			if (t == nodes.end()) {
				nodes.insert(pair<int, int>(s.first, 1));
			}
			else {
				++t->second;
			}
			t = nodes.find(s.second);
			if (t == nodes.end()) {
				nodes.insert(pair<int, int>(s.second, 1));
			}
			else {
				++t->second;
			}
		}
		vector<int>outs;
		for (auto r : nodes) {
			if (r.second == 1) {
				outs.push_back(r.first);
			}
		}
		while (n > 2) {
			n -= outs.size();
			for (auto y : outs) {
				
			}
		}
	}
	int nthSuperUglyNumber(int n, vector<int>& primes) {
		vector<int>res(n, 1);
		int size = primes.size();
		if (n == 1) {
			return 1;
		}
		vector<int>points(size, 0);
		vector<int>tempv(size, 0);
		int minv = INT_MAX;
		int minl = 0;
		int temp;
		for (int i = 1; i < n; ++i) {
			minv = INT_MAX;
			for (int j = 0; j < size; ++j) {
				temp = res[points[j]] * primes[j];
				tempv[j] = temp;
				if (temp <= minv) {
					minv = temp;
					minl = j;
				}
			}
			res[i] = minv;
			for (int k = 0; k < size;++k) {
				if (tempv[k] == minv) {
					points[k]++;
				}
			}
		}
		return res[n - 1];
	}
	int maxProduct(vector<string>& words) {
		int maxl = 0;
		if (!words.size()) {
			return maxl;
		}
		vector<int> hash(words.size(), 0);  //32位对应26个英文字母
		for (int i = 0; i < words.size(); ++i) {
			for (int j = 0; j < words[i].length(); ++j) {
				int shift = words[i][j] - 'a';
				hash[i] = hash[i] | (1 << shift);
			}
		}
		for (int i = 0; i < hash.size(); ++i) {
			for (int j = i + 1; j < hash.size(); ++j) {
				int temp = hash[i] & hash[j];
				if (temp == 0) {
					maxl = max(maxl, int(words[i].length()*words[j].length()));
				}
			}
		}
		return maxl;
	}
	
	int coinChange(vector<int>& coins, int amount) {
		if (!amount) {
			return 0;
		}
		vector<int>dp(amount + 1, amount + 1);
		dp[0] = 0;
		for (int i = 1; i <= amount; ++i) {
			for (auto j : coins) {
				if (i - j >= 0) {
					dp[i] = min(dp[i], dp[i - j] + 1);
				}
			}
		}
		return (dp[amount] == amount + 1) ? -1 : dp[amount];
	}
};
int main() {
	Solution solu;
	//int solu313 = solu.nthSuperUglyNumber(12, vector<int>{2, 7, 13, 19});
	//int solu318 = solu.maxProduct(vector<string>{"abcw", "baz", "foo", "bar", "xtfn", "abcdef"});
	int solu322 = solu.coinChange(vector<int>{186, 419, 83, 408}, 6249);
	int k = 0;
}