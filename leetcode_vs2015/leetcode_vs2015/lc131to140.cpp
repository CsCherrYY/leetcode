#include<vector>
#include<map>
#include<algorithm>
using namespace std;
class Solution {
public:
	int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
		int i, size, sum, numi;
		size = gas.size();
		vector<int>rest(2 * size, 0);
		sum = 0;
		for (i = 0; i < size; i++) {
			rest[i] = gas[i] - cost[i];
			rest[i + size] = rest[i];
			sum += rest[i];
		}
		if (sum < 0) {
			return -1;
		}
		sum = numi = 0;
		for (i = 0; i < size * 2; i++) {
			sum += rest[i];
			numi++;
			if (sum < 0) {
				sum = 0;
				numi = 0;
				continue;
			}
			if (numi == size) {
				return i - size + 1;
			}
		}
		return -1;
	}
	int candy(vector<int>& ratings) {
		int size = ratings.size();
		vector<int>candys(size, 1);
		int i;
		for (i = 0; i < size - 1; i++) {
			if (ratings[i] < ratings[i + 1]) {
				candys[i + 1] = candys[i] + 1;
			}
		}
		for (i = size - 1; i >= 1; i--) {
			if (ratings[i] < ratings[i - 1]) {
				candys[i - 1] = max(candys[i] + 1, candys[i - 1]);  //�ڶ���ɨ������ʱ����ܱ���ͱȺ������ˣ�����ȡmax
			}
		}
		int sum = 0;
		for (i = 0; i < size; i++) {
			sum += candys[i];
		}
		return sum;
	}
	int singleNumber1(vector<int>& nums) {
		int numb=nums[0];
		for (int i = 1; i < nums.size(); i++) {
			numb ^= nums[i];   //ͬ�����Ϊ0  a^a^b=b a^a^a^b=a^b
		}
		return numb;
	}
	bool wordBreak(string s, vector<string>& wordDict) {
		map<string, bool>dptable;
		return wordBreakdp(s, wordDict, dptable);
    }
	bool wordBreakdp(string s, vector<string>& wordDict, map<string, bool>&dptable) {
		if (s.length() == 0) {
			return true;
		}
		auto temp = dptable.find(s);
		if (temp != dptable.end()) {
			return temp->second;
		}
		bool result = false;
		int i, word_len;
		string tempstr;
		for (i = 0; i < wordDict.size(); i++) {
			word_len = wordDict[i].length();
			if (s.length() >= word_len) {
				tempstr = s.substr(0, word_len);
				if (tempstr == wordDict[i]) {
					result |= wordBreakdp(s.substr(word_len, s.length() - word_len), wordDict, dptable);
				}
			}
		}
		dptable.insert(pair<string, bool>(s, result));
		return result;
	}
};
int main() {
	Solution solu;
	int test = 134;
	int solu134;
	vector<int>gas = { 1,2,3,4,5 };
	vector<int>cost = { 3,4,5,1,2 };
	switch (test)
	{
	default:
		break;
	case 134:
		solu134 = solu.canCompleteCircuit(gas, cost);
		break;
	}
	return 0;
}