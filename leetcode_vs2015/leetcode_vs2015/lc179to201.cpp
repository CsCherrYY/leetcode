#include<vector>
#include<algorithm>
#include<string>
using namespace std;
class Solution {
public:
	bool largeequal(int a, int b) {
		bool set = 1;
		if (!set) {
			return a >= b;
		}
		else {
			if (!a || !b) {
				return a >= b;   //考虑0的话，输入是非负数，直接返回大等于
			}
			vector<int>numa, numb, temp;
			while (a > 0) {
				numa.push_back(a % 10);
				a /= 10;
			}
			while (b > 0) {
				numb.push_back(b % 10);
				b /= 10;
			}
			temp = numb;
			numb.insert(numb.begin(), numa.begin(), numa.end());
			numa.insert(numa.begin(), temp.begin(), temp.end());
			int tempa, tempb;
			while (numa.size() || numb.size()) {
				if (!numa.empty()) {
					tempa = numa[numa.size() - 1];
					numa.pop_back();
				}
				if (!numb.empty()) {
					tempb = numb[numb.size() - 1];
					numb.pop_back();
				}
				if (tempa > tempb) {
					return true;
				}
				else if (tempa < tempb) {
					return false;
				}
			}
			return true;
		}
	}
	bool lessequal(int a, int b) {
		bool set = 1;
		if (!set) {
			return a <= b;
		}
		else {
			if (!a || !b) {
				return a <= b;   //考虑0的话，输入是非负数，直接返回大等于
			}
			vector<int>numa, numb, temp;
			while (a > 0) {
				numa.push_back(a % 10);
				a /= 10;
			}
			while (b > 0) {
				numb.push_back(b % 10);
				b /= 10;
			}
			numb.insert(numb.begin(), numa.begin(), numa.end());
			numa.insert(numa.begin(), temp.begin(), temp.end());
			int tempa, tempb;
			while (numa.size() || numb.size()) {
				if (!numa.empty()) {
					tempa = numa[numa.size() - 1];
					numa.pop_back();
				}
				if (!numb.empty()) {
					tempb = numb[numb.size() - 1];
					numb.pop_back();
				}
				if (tempa < tempb) {
					return true;
				}
				else if (tempa > tempb) {
					return false;
				}
			}
			return true;
		}
	}
	void fastsort(vector<int>& nums) {
		fastsort_work(nums, 0, nums.size() - 1);
		return;
	}
	void fastsort_work(vector<int>& nums, int left, int right) {
		//双路快排
		if (right - left <= 0) {
			return;
		}
		if (right - left == 1) {
			//sort(nums.begin() + left, nums.begin() + right + 1);  //是否+1?
			if (lessequal(nums[left], nums[right])) {
				return;
			}
			swap(nums[left], nums[right]);
			return;
		}
		//哨兵位置0，一路1 一路size-1
		int i = left + 1;
		int j = right;
		while (i < j) {
			while (lessequal(nums[i], nums[left]) && i < j) {
				i++;
			}
			while (largeequal(nums[j],nums[left]) && i < j) {
				j--;               //右指针先动
			}
			swap(nums[i], nums[j]);
		}
		if (largeequal(nums[left],nums[i])) {
			swap(nums[left], nums[i]);   //直接交换即可
		}
		else {
			i--;
			swap(nums[left], nums[i]);  //若nums[i]>nums[left] 需要后退一步交换
		}
		fastsort_work(nums, left, i - 1);
		fastsort_work(nums, i + 1, right);
		return;
	}
	string largestNumber(vector<int>& nums) {
		//[9 30 95]当成[99 33 95]做个排序
		fastsort(nums);
		reverse(nums.begin(), nums.end());
		string res;
		for (int i = 0; i < nums.size(); ++i) {
			res += to_string(nums[i]);
			if (i == 0 && res == "0") {
				return res;
			}
		}
		return res;
	}
};
int main() {
	Solution solu;
	vector<int>test155 = { 824,938,1399,5607,6973,5703,9609,4398,8247 };
	int test = 155;
	switch (test)
	{
	case 155:
		solu.fastsort(test155);
		break;
	default:
		break;
	}
}