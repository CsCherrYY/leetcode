#include<vector>
#include<algorithm>
#include<unordered_map>
#include<set>
using namespace std;
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
	bool search(vector<int>& nums, int target) {
		//二分搜o(logn)
		int size = nums.size();
		if (size < 1) {
			return false;
		}
		int low = 0;
		int high = size - 1;
		int mid;
		while (low <= high) {
			mid = (low + high) / 2;
			if (nums[mid] == target) {
				return true;
			}
			// if 前半段 num[low]>=num[high]>=num[mid]  后半段 num[mid]>=num[low]>=num[high]
			if ((nums[low] == nums[mid]) && (nums[mid] == nums[high])) {
				low++;
				high--;
			}
			else if (nums[mid] >= nums[low]) {   //分界点在后半段  这个做法的思想和33有点不一样，要理解一下
				if ((nums[low] <= target) && (nums[mid] > target)) {
					high = mid - 1;
				}
				else {
					low = mid + 1;
				}
			}
			else {
				if ((nums[mid] < target) && (nums[high] >= target)) {
					low = mid + 1;
				}
				else {
					high = mid - 1;
				}
			}
		}
		return false;
	}
	ListNode* deleteDuplicates_mid(ListNode* head) {
		if (!head || !(head->next)) {
			return head;
		}
		ListNode *newnode = new ListNode(0);
		newnode->next = head;
		ListNode* pre = newnode;
		ListNode* end = newnode->next;
		int step = 0;
		while (end&&end->next != NULL) {
			while (end->next&&end->val == end->next->val) {
				step++;
				end = end->next;
			}//end是同样数的最后一个指针
			if (step > 0) {
				pre->next = end->next;
				end = end->next;
				step = 0;
			}
			else {
				pre = end;
				end = end->next;
			}
		}
		return newnode->next;
	}
	ListNode* deleteDuplicates(ListNode* head) {
		if (!head || !(head->next)) {
			return head;
		}
		ListNode *pre = head;
		ListNode *work = head->next;
		while (work != NULL) {
			if (pre->val == work->val) {
				pre->next = work->next;
				work = work->next;
			}
			else {
				pre = work;
				work = work->next;
			}
		}
		return head;
	}
	int largestRectangleArea(vector<int>& heights) {
		//最关键的一个思想，连续递增的部分不可能成为最大矩形的终点
		vector<int> index;
		heights.push_back(0); //小技巧，解决边界条件
		int i, indexnew, h, maxsqre;
		maxsqre = 0;
		for (i = 0; i < heights.size(); i++) {
			while (!index.empty() && heights[index.back()] >= heights[i]) {
				h = heights[index.back()];
				index.pop_back();
				indexnew = index.size() > 0 ? index.back() : -1;
				maxsqre = max(maxsqre, h*(i - indexnew - 1));
			}
			index.push_back(i);
		}
		return maxsqre;
	}
	ListNode* partition(ListNode* head, int x) {
		ListNode *p = new ListNode(0);
		ListNode *q = new ListNode(0);
		ListNode *op = new ListNode(0);
		ListNode *startp = new ListNode(0);
		ListNode *startq = new ListNode(0);
		if (head == NULL||head->next==NULL) {
			return head;
		}
		op = head;
		startp = p;
		startq = q;
		while (op != NULL) {
			if (op->val < x) {
				p->next = op;
				p = p->next;
			}
			else {
				q->next = op;
				q = q->next;
			}
			op = op->next;
		}
		q->next = NULL;   //非常重要，否则返回一个循环了
		p->next = startq->next;
		return startp->next;
	}
	bool isScramble(string s1, string s2) {
		unordered_map<string, bool> maps;
		return isScramblecs(s1, s2, maps);   //用map做动态规划
	}
	bool isScramblecs(string s1, string s2, unordered_map<string, bool>& maps) {
		//最优子结构性质：存在一个划分点，在该点划分使得两个子串分别为扰乱字符串
		if (maps.find(s1 + " " + s2) != maps.end()) {
			return maps[s1 + " " + s2];
		}
		if (s1 == s2) {
			maps.insert(pair<string, int>(s1 + " " + s2, true));
			return true;
		}
		if (s1.length() != s2.length()) {
			maps.insert(pair<string, int>(s1 + " " + s2, false));
			return false;
		}
		int i;
		string temps1l, temps1r, temps2l, temps2r;
		for (i = 1; i < s1.length(); i++) {
			temps1l = s1.substr(0, i);
			temps1r = s1.substr(i, s1.length() - i);
			temps2l = s2.substr(0, i);
			temps2r = s2.substr(i, s2.length() - i);
			if (isScramblecs(temps1l, temps2l, maps) && isScramblecs(temps1r, temps2r, maps)) {
				maps.insert(pair<string, int>(s1 + " " + s2, true));
				return true;
			}
			temps2l = s2.substr(0, s2.length() - i);
			temps2r = s2.substr(s2.length() - i, i);
			if (isScramblecs(temps1l, temps2r, maps) && isScramblecs(temps1r, temps2l, maps)) {
				maps.insert(pair<string, int>(s1 + " " + s2, true));
				return true;
			}
		}
		maps.insert(pair<string, int>(s1 + " " + s2, false));
		return false;
	}
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		int tail = m + n - 1;
		m--;
		n--;
		while (m >= 0 && n >= 0)
		{
			if (nums1[m] >= nums2[n]) {
				nums1[tail] = nums1[m];
				tail--;
				m--;
			}
			else {
				nums1[tail] = nums2[n];
				tail--;
				n--;
			}
		}
		//nums2中剩余的前n个数复制到nums1
		while (n >= 0) {
			nums1[n] = nums2[n];
			n--;
		}
		return;
	}
	vector<int> grayCode(int n) {
		vector<int> temp;
		vector<int> temp_rev;
		temp.push_back(0);
		if (n == 0) {
			return temp;
		}
		int i, j;
		for (i = 1; i <= n; i++) {
			temp_rev = temp;
			reverse(temp_rev.begin(), temp_rev.end());    //格雷码的操作：reverse后加2^n 并append到原list 这样就可以保持原性质
			for (j = 0; j < temp_rev.size(); j++) {
				temp_rev[j] += pow(2, i - 1);
			}
			temp.insert(temp.end(), temp_rev.begin(), temp_rev.end());
		}
		return temp;
		//0: 0
		//1:0 1
		//2: 00 01 11 10
		//3: 000 001 011 010 110 111 101 100
		//
	}
	vector<vector<int>> subsetsWithDup(vector<int>& nums) {
		set<vector<int>> tempset;
		vector<vector<int>> temp;
		vector<int> nows;
		newsub(nums, tempset, 0, nows);
		int i;
		for (auto it = tempset.begin(); it != tempset.end(); it++) {
			temp.push_back(*it);                  //返回迭代器的引用 *it，非常重要
		}
		return temp;
	}
	void newsub(vector<int> nums, set<vector<int>>& tempset,int nowloc,vector<int>nows) {
		if (nowloc == nums.size()) {
			sort(nows.begin(), nows.end());
			tempset.insert(nows);
			return;
		}
		newsub(nums, tempset, nowloc + 1, nows);
		nows.push_back(nums[nowloc]);
		newsub(nums, tempset, nowloc + 1, nows);
	}
};
int main() {
	int test = 90;
	Solution solu;
	ListNode *newnode = new ListNode(1);
	ListNode *newnode1 = new ListNode(4);
	ListNode *newnode2 = new ListNode(3);
	ListNode *newnode3 = new ListNode(2);
	ListNode *newnode4 = new ListNode(5);
	ListNode *newnode5 = new ListNode(2);
	ListNode *solu82;
	bool solu87;
	ListNode *solu86;
	vector<vector<int>> solu90;
	newnode->next = newnode1;
	newnode1->next = newnode2;
	newnode2->next = newnode3;
	newnode3->next = newnode4;
	newnode4->next = newnode5;
	vector<int> nums1 = { 1,2,2 };
	vector<int> nums2 = { 2 };
	//newnode5->next = newnode6;
	bool solu81;
	switch (test)
	{
	case 81:
		//solu81 = solu.search({ 2,5,6,0,0,1,2 }, 0);
		break;
	case 82:
		solu82 = solu.deleteDuplicates_mid(newnode);
		break;
	case 86:
		solu86 = solu.partition(newnode,3);
		break;
	case 87:
		solu87 = solu.isScramble("abcdefghijklmnopq", "efghijklmnopqcadb");
		break;
	case 88:
		solu.merge(nums1, 1, nums2, 1);
		break;
	case 90:
		solu90 = solu.subsetsWithDup(nums1);
		break;
	default:
		break;
	}
	return 0;
}