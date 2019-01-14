#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
	int firstMissingPositive(vector<int>& nums) {
		int i;
		int len = nums.size();
		for (i = 0; i < len; i++) {
			//while (nums[i] > 0 && nums[i] <= len&&nums[i] != i + 1) 
			while (nums[i] > 0 && nums[i] <= len&&nums[i] != nums[nums[i]-1]) {
				swap(nums[i], nums[nums[i] - 1]);//新的条件比上面的条件还多了一个swap的两个不等
			}
		}
		for (i = 0; i < len; i++) {
			if (nums[i] != i + 1) {
				break;
			}
		}
		return i + 1;
	}
	int trap(vector<int>& height) {
		int n = height.size();
		vector<int> left(n), right(n);// left[i]表示i左边的最大值，right[i]表示i右边的最大值
		for (int i = 1; i < n; i++) {
			left[i] = max(left[i - 1], height[i - 1]);
		}
		for (int i = n - 2; i >= 0; i--) {
			right[i] = max(right[i + 1], height[i + 1]);
		}
		int water = 0;
		for (int i = 0; i < n; i++) {
			int level = min(left[i], right[i]);
			water += max(0, level - height[i]);
		}
		return water;
	}
	string multiply(string num1, string num2) {
		if (num1 == "0" || num2 == "0") {
			return "0";
		}
		int i, j;
		int len1 = num1.length();
		int len2 = num2.length();
		vector<vector<int>> temp(len2, vector<int>(len1 + len2, 0)); //ex:len1>len2
		int loop = 0;
		for (j = len2 - 1; j >= 0; j--) {   //         len2>=j>=0
			for (i = len1 - 1; i >= 0; i--) {
				temp[j][i+len2-loop] = (num1[i] - '0')*(num2[j] - '0');
			}
			loop++;
		}
		int sum = 0;
		int add = 0;
		vector<int>result(len1 + len2, 0);
		for (i = len1 + len2 - 1; i >= 0; i--) {
			for (j = 0; j < len2; j++) {
				sum += temp[j][i];
			}
			sum += add;
			add = sum / 10;
			result[i] = sum % 10;
			sum = 0;
		}
		string tempstr;
		i = 0;
		while (result[i] == 0) {
			i++;
		}
		for (; i < len1 + len2; i++) {
			tempstr += result[i] + '0';
		}
		return tempstr;
	}
	vector<vector<int>> permute(vector<int>& nums) {
		vector<vector<int>> temp;
		vector<int> now;
		if (nums.size() != 0) {
			permute_hs(temp, nums, now);
		}
		return temp;
	}
	void permute_hs(vector<vector<int>>&temp, vector<int>& nums, vector<int>& now) {
		if (nums.size()==0) {
			temp.push_back(now);
			return;
		}
		int i,tempint;
		for (i = 0; i < nums.size(); i++) {
			tempint = nums[i];
			now.push_back(tempint);
			nums.erase(nums.begin() + i);
			permute_hs(temp, nums, now);
			now.pop_back();
			nums.insert(nums.begin() + i, tempint);
		}
		return;
	}
	vector<vector<int>> permuteUnique(vector<int>& nums) {
		vector<vector<int>> temp;
		vector<int> now;
		if (nums.size() != 0) {
			permuteUnique_hs(temp, nums, now);
		}
		return temp;
	}
	void permuteUnique_hs(vector<vector<int>>&temp, vector<int>& nums, vector<int>& now) {
		if (nums.size() == 0) {
			if (find(temp.begin(), temp.end(), now) == temp.end()) {   
				temp.push_back(now);                                   
			}
			return;
		}
		//这样有点蠢，有个全排列的方法
		//用一个循环，让i和最左一个数交换，下一次递归回溯，就可以产生一个新的排列
		/*
		void perm(vector<int> nums, int left, int right) {
		if (left == right)
		ans.push_back(nums);
		else {
		for (int i = left; i <= right; i++) {
		if (i != left && nums[left] == nums[i]) continue;  # 去重
		swap(nums[left], nums[i]);
		perm(nums, left + 1, right);
		}
		}
		}
		*/
		int i, tempint;
		for (i = 0; i < nums.size(); i++) {
			tempint = nums[i];
			now.push_back(tempint);
			nums.erase(nums.begin() + i);
			permuteUnique_hs(temp, nums, now);
			now.pop_back();
			nums.insert(nums.begin() + i, tempint);
		}
		return;
	}
	void rotate(vector<vector<int>>& matrix) {

	}
};

int main() {
	Solution Solu;
	vector<int> vec;
	int test = 47;
	int solu41,solu42;
	string solu43;
	vector<vector<int>> solu46,solu47;
	switch (test)
	{
	case 41:
		vec = { 1,1 };
		solu41 = Solu.firstMissingPositive(vec);
		break;
	case 42:
		vec = { 0,1,0,2,1,0,1,3,2,1,2,1 };
		solu42 = Solu.trap(vec);
		break;
	case 43:
		solu43 = Solu.multiply("3456", "123");
		break;
	case 46:
		vec = { 1 };
		solu46 = Solu.permute(vec);
		break;
	case 47:
		vec = { 1,1,2 };
		solu47 = Solu.permuteUnique(vec);
		break;
	default:
		break;
	}
	return 0;
}