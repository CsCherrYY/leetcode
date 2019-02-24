#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
class Solution {
public:
	void reverseWords(string &s) {
		//输入字符串可以在前面或者后面包含多余的空格，但是反转后的字符不能包括。
		//如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。
		//note:不适用额外空间的方法：先将整个s整体逆序，再将每个单词逆序
		reverse(s.begin(), s.end());
		//string.erase(start,len) 移除start起len长度的string
		//string.find_first_not_of(char)
		s.erase(0, s.find_first_not_of(' '));
		s += " ";//改成 word+' '+word+' '的形式
		int i;
		int last_word = 0;
		int space = 0;
		for (i = 0; i < s.length();) {
			if (s[i] == ' ') {
				reverse(s.begin() + last_word, s.begin() + i);   //i指向空格，就是word的后一个指针
				space = i;
				while (s[space] == ' '&&space < s.length()) {
					space++;
				}
				if (space > i) {
					s.erase(i, space - i - 1);
				}
				i++;
				last_word = i;
			}
			else {
				i++;
			}
		}
		s = s.substr(0, s.find_last_not_of(' ') + 1);  //后面的所有空格去掉
	}
	int maxProduct(vector<int>& nums) {
		/*
		1上一步的最大值 * 当前（正）值
		2上一步的最小值 * 当前（负）值
		3当前值
		*/
		if (nums.size() == 1)
			return nums[0];
		int len = nums.size();
		vector<int> dp_max(len, 0);
		vector<int> dp_min(len, 0);
		int max_value = INT_MIN;
		for (int i = 0; i < len; i++)
		{
			if (i == 0)
			{
				dp_max[i] = nums[i];
				dp_min[i] = nums[i];
			}
			else
			{
				dp_max[i] = max(dp_max[i - 1] * nums[i], max(dp_min[i - 1] * nums[i], nums[i]));
				dp_min[i] = min(dp_max[i - 1] * nums[i], min(dp_min[i - 1] * nums[i], nums[i]));
			}
			max_value = max(max_value, dp_max[i]);
		}
		return max_value;
	}
	int findMin(vector<int>& nums) {
		//最小值肯定在无序部分，或者low点
		int low = 0;
		int high = nums.size() - 1;
		int mid = (high + low) / 2;
		if (nums.size() == 1) {
			return nums[0];
		}
		else if (nums.size() == 2) {
			return min(nums[0], nums[1]);
		}
		while (low <= high) {
			mid = (high + low) / 2;
			if (mid == 0) {
				if (nums[mid] < nums[mid + 1]) {
					return nums[mid];
				}
			}
			else if (mid == nums.size() - 1) {
				if (nums[mid] < nums[mid - 1]) {
					return nums[mid];
				}
			}
			else {
				if (nums[mid] < nums[mid - 1] && nums[mid] < nums[mid + 1]) {
					return nums[mid];
				}
			}
			if (nums[mid] < nums[low]) {  //前半段是无序的
				high = mid - 1;
			}
			else if(nums[mid]>nums[high]){
				low = mid + 1;
			}
			else {
				return nums[low];
			}
		}
		return nums[low];
	}
};
class MinStack {
public:
	/** initialize your data structure here. */
	//最小栈：每次入栈两个元素，一个元素值，一个最小值
	//或用两个栈，可以存储更少空间
	stack<int> nums;
	stack<int> mins;
	MinStack() {
		
	}
	void push(int x) {
		nums.push(x);
		if (mins.empty()) {
			mins.push(x);
		}
		else {
			if (x <= mins.top()) {
				mins.push(x);  //只有比min的小（等也要！！）才更新min
			}
		}
	}
	void pop() {
		if (mins.empty() || nums.empty()) {
			return;
		}
		if (mins.top() == nums.top()) {
			mins.pop();
			nums.pop();
		}
		else {
			nums.pop();
		}
	}
	int top() {
		if (nums.empty()) {
			return -1;
		}
		return nums.top();
	}
	int getMin() {
		if (mins.empty()) {
			return -1;
		}
		return mins.top();
	}
};
int main() {
	int test = 153;
	int solu153;
	vector<int> test153 = { 4,5,6,7,0,1,2 };
	Solution solu;
	switch (test)
	{
	case 153:
		solu153 = solu.findMin(test153);
		break;
	default:
		break;
	}
	return 0;
}