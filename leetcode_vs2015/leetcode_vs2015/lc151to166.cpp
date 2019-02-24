#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
	void reverseWords(string &s) {
		//�����ַ���������ǰ����ߺ����������Ŀո񣬵��Ƿ�ת����ַ����ܰ�����
		//����������ʼ��ж���Ŀո񣬽���ת�󵥴ʼ�Ŀո���ٵ�ֻ��һ����
		//note:�����ö���ռ�ķ������Ƚ�����s���������ٽ�ÿ����������
		reverse(s.begin(), s.end());
		//string.erase(start,len) �Ƴ�start��len���ȵ�string
		//string.find_first_not_of(char)
		s.erase(0, s.find_first_not_of(' '));
		s += " ";//�ĳ� word+' '+word+' '����ʽ
		int i;
		int last_word = 0;
		int space = 0;
		for (i = 0; i < s.length();) {
			if (s[i] == ' ') {
				reverse(s.begin() + last_word, s.begin() + i);   //iָ��ո񣬾���word�ĺ�һ��ָ��
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
		s = s.substr(0, s.find_last_not_of(' ') + 1);  //��������пո�ȥ��
	}
	int maxProduct(vector<int>& nums) {
		/*
		1��һ�������ֵ * ��ǰ������ֵ
		2��һ������Сֵ * ��ǰ������ֵ
		3��ǰֵ
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
		//��Сֵ�϶������򲿷֣�����low��
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
			if (nums[mid] < nums[low]) {  //ǰ����������
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
	ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
		//Ѱ���ཻ�㣬O��1���ⷨ������ָ��������β����һ����ͷ���������н���ض��ڶ��������뽻��
		ListNode *worka = headA;
		ListNode *workb = headB;
		bool afin = false;
		bool bfin = false;
		while (worka != workb) {
			if (!worka) {
				if (!afin) {
					worka = headB;
					afin = true;
				}
				else {
					return NULL;
				}
			}
			else {
				worka = worka->next;
			}
			if (!workb) {
				if (!bfin) {
					workb = headA;
					bfin = true;
				}
				else {
					return NULL;
				}
			}
			else {
				workb = workb->next;
			}
		}
		return worka;
	}
	int findPeakElement(vector<int>& nums) {
		//�ϴ����һ�����ַ�ֵ
		//ע������ı߽��������������ж����Ľ���Ƿ������˵�ֵ
		int low = 1, high = nums.size() - 2;
		if (high < -1) return -1;    //size=0
		else if (high == -1)return 0;   //size=1
		else if (nums[low] < nums[low - 1]) return 0;   //�����俼�ǵ��˱߽�����
		else if (nums[high] < nums[high + 1]) return high + 1;
		else {
			while (low <= high) {
				int mid = (low + high) / 2;
				if (nums[mid] > nums[mid - 1] && nums[mid] > nums[mid + 1]) return mid;
				if (nums[mid] > nums[mid - 1]) low = mid + 1;
				else high = mid - 1;
			}
			return -1;
		}
	}
};
class MinStack {
public:
	/** initialize your data structure here. */
	//��Сջ��ÿ����ջ����Ԫ�أ�һ��Ԫ��ֵ��һ����Сֵ
	//��������ջ�����Դ洢���ٿռ�
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
				mins.push(x);  //ֻ�б�min��С����ҲҪ�������Ÿ���min
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