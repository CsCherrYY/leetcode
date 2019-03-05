#include<iostream>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;
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
};
int main() {
	return 0;
}