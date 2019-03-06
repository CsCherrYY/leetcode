#include<iostream>
#include<set>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
bool isBadVersion(int version);
class Solution {
public:
	bool isUgly(int num) {
		if (num < 1) {
			return false;
		}
		if (num == 1) {
			return true;
		}
		while (num>=1) {
			if (num == 1) {
				return true;
			}
			else if (num % 2 == 0) {
				num /= 2;
			}
			else if (num % 3 == 0) {
				num /= 3;
			}
			else if (num % 5 == 0) {
				num /= 5;
			}
			else {
				return false;
			}
		}
		return false;
	}
	int nthUglyNumber(int n) {
		//generate ugly
		vector<int>uglynum(n, 1);
		vector<int>index(3, 0);   //2,3,5
		int a, b, c, temp;
		for (int i = 1; i < n; ++i) {
			a = uglynum[index[0]] * 2;
			b = uglynum[index[1]] * 3;
			c = uglynum[index[2]] * 5;
			temp = min(a, min(b, c));
			uglynum[i] = temp;
			if (temp == a) {
				++index[0];
			}
			if (temp == b) {
				++index[1];
			}
			if (temp == c) {
				++index[2];
			}
		}
		return uglynum[n - 1];
	}
	int missingNumber(vector<int>& nums) {
		//O(n)时间+O(n)空间，常规实现，O(1)空间解法
		long long sum = 0;
		for (auto s : nums) {
			sum += s;
		}
		return ((nums.size() + 1)*nums.size()) / 2 - sum;
	}
	int hIndexI(vector<int>& citations) {
		//o nlogn 排序+遍历
		if (citations.size() == 0) {
			return 0;
		}
		sort(citations.begin(), citations.end());
		int h = 0;
		for (int i = 0; i < citations.size(); ++i) {
			int htemp = min(citations[i], int(citations.size() - i));
			h = max(h, htemp);
		}
		return h;
	}
	int hIndex(vector<int>& citations) {
		//条件，数组有序，二分：
		int right = citations.size() - 1;
		int left = 0;
		int h = 0;
		int mid;
		while (left <= right) {
			mid = (left + right) / 2;
			if (citations[mid] > (citations.size() - mid)) {
				h = max(h, int(citations.size() - mid));
				right = mid - 1;
			}
			else {
				h = max(h, citations[mid]);
				left = mid + 1;
			}
		}
		return h;
	}
	int firstBadVersion(int n) {
		int left = 1;
		int right = n;
		int mid;
		while (left < right) {
			mid = (left + right) / 2;
			if (mid == n) {
				return mid;
			}
			else if (isBadVersion(mid) == true && isBadVersion(mid + 1) == false) {
				return mid + 1;
			}
			else if (isBadVersion(mid) == true) {
				left = mid + 1;
			}
			else if (isBadVersion(mid) == false) {
				right = mid - 1;
			}
		}
		return left;
	}
	int numSquares(int n) {
		map<int, int>dpsqrt;
		return numSquaresdp(n, dpsqrt);
	}
	int numSquaresdp(int n, map<int, int>&dpsqrt) {
		if (!n) {
			return 0;
		}
		else if (n == 1) {
			return 1;
		}
		auto it = dpsqrt.find(n);
		if (it != dpsqrt.end()) {
			return it->second;
		}
		int max = int(sqrt(n));
		int count = n;
		for (int i = max; i >= 1; --i) {
			count = min(count, 1 + numSquaresdp(n - pow(i, 2), dpsqrt));
		}
		dpsqrt.insert(pair<int, int>(n, count));
		return count;
	}
	void moveZeroes(vector<int>& nums) {
		int end = nums.size() - 1;
		int zero_pos = end;
		int i;
		while (zero_pos>=0) {
			while (zero_pos >= 0 && nums[zero_pos] ) {
				--zero_pos;
			}
			if (zero_pos < 0) {
				break;
			}
			for (i = zero_pos; i < end; ++i) {
				nums[i] = nums[i + 1];
			}
			nums[end] = 0;
			--zero_pos;
			--end;
		}
		return;
	}
	int findDuplicate(vector<int>& nums) {
		int fast = 0, slow = 0;
		while (1) {
			fast = nums[nums[fast]];
			slow = nums[slow];
			if (fast == slow) {
				fast = 0;
				while (fast != slow) {
					fast = nums[fast];
					slow = nums[slow];
				}
				return nums[slow];
			}
		}
	}
	bool wordPattern(string pattern, string str) {
		map<char, string> maps;
		set<string>val;
		string temp = str;
		int spacepos = 0;
		string word;
		int charpos = 0;
		while (1) {
			if (charpos == pattern.size()) {
				if (spacepos == -1) {
					return true;
				}
				else {
					return false;
				}
			}
			spacepos = temp.find(' ');
			if (spacepos == -1) {
				word = temp;
			}
			else {
				word = temp.substr(0, spacepos);
				temp = temp.substr(spacepos + 1);
			}
			auto it = maps.find(pattern[charpos]);
			if (it==maps.end()) {
				maps.insert(pair<char, string>(pattern[charpos], word));
				if (val.find(word) != val.end()) {
					return false;
				}
				val.insert(word);
				++charpos;
			}
			else if (it->second != word) {
				return false;
			}
			else {
				++charpos;
			}
		}
		return true;
	}
};
int main() {
	Solution solu;
	bool a = solu.wordPattern("abba", "dog dog dog dog");
	return 0;
}