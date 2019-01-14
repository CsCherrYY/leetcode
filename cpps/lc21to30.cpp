#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<unordered_set>
#include<set>
#include<unordered_map>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		if (l1 == NULL){
			return l2;
		}
		else if (l2 == NULL) {
			return l1;
		}
		ListNode *news=new ListNode(0);
		news->val = (l1->val >= l2->val) ? l2->val : l1->val;
		news->next = (l1->val >= l2->val) ? mergeTwoLists(l1, l2->next) : mergeTwoLists(l1->next, l2);
		return news;
	}
	vector<string> generateParenthesis(int n) {
		vector<string> temp;
		genstr(temp, "", n, 0);
		return temp;
	}
	void genstr(vector<string> &temp, string tempstr, int left, int right) {   //这个&
		if (left > 0) {
			genstr(temp, tempstr + "(", left - 1, right + 1);
		}
		if (right > 0) {
			genstr(temp, tempstr + ")", left, right - 1);
		}
		if (left == 0 && right == 0) {
			temp.push_back(tempstr);
		}
	}
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		int i, minloc = 0;
		int min = pow(2, 30);
		if (lists.empty()) {
			return NULL;
		}
		for (i = 0; i < lists.size(); i++) {
			if (lists[i] == NULL) {
				lists.erase(lists.begin() + i);
				i--;
			}
			else if (lists[i]->val < min) {
				minloc = i;
				min = lists[i]->val;
			}
		}
		if (lists[minloc] != NULL) {
			if (lists[minloc]->next == NULL) {
				lists.erase(lists.begin() + minloc);
			}
			else {
				lists[minloc] = lists[minloc]->next;
			}
			ListNode *news = new ListNode(min);
			news->next = mergeKLists(lists);
			return news;
		}
		return NULL;
	}
	ListNode* reverseKGroup(ListNode* head, int k) {
		if (head == NULL) {
			return NULL;
		}
		if (k == 1) {
			return head;
		}
		ListNode* endnode = head;
		ListNode* part_begin;
		ListNode* part_end;
		ListNode* start = new ListNode(0);
		start->next = head;
		ListNode* startnode = start;
		int n = 1;
		int i;
		while (endnode->next != NULL) {
			endnode = endnode->next;
			n++;
		}
		while (n >= k) {
			part_begin = start->next;
			part_end = part_begin;
			for (i = 0; i < k-1; i++) {            //这段的交换思想
				start->next = part_end->next;
				part_end->next = part_end->next->next;
				start->next->next = part_begin;
				part_begin = start->next;
			}
			n -= k;
			start = part_end;
		}
		return startnode->next;
	}
	ListNode* swapPairs(ListNode* head) {
		if (head == NULL) {
			return NULL;
		}
		return reverseKGroup(head, 2);
	}
	string longestPalindrome(string s) {
		if (s.empty()) {
			return "";
		}
		else if (s.length() == 1) {
			return s;
		}
		short len = s.length();
		int i, j;
		vector<vector<short>> table(len, vector<short>(len)); //创建含有len个第二个参数拷贝的vector
		vector<vector<short>> start(len, vector<short>(len)); //创建含有len个第二个参数拷贝的vector
		for (j = 0; j < len; j++) {
			table[j][j] = 1;
			start[j][j] = j;
			for (i = j - 1; i >= 0; i--) {
				if (s[i] == s[j]) {
					if (j - i == 1) {
						table[i][j] = 2;
						start[i][j] = i;
					}
					else if (start[i + 1][j - 1] == i + 1 && table[i + 1][j - 1]==j-1-i){  //动归的迭代形式
						table[i][j] = table[i + 1][j - 1] + 2;
						start[i][j] = i;
					}
					else {
						table[i][j] = max(table[i][j - 1], table[i + 1][j]);
						start[i][j] = table[i][j - 1] > table[i + 1][j] ? start[i][j - 1] : start[i + 1][j];
					}
				}
				else {
					table[i][j] = max(table[i][j - 1], table[i + 1][j]);
					start[i][j] = table[i][j - 1] > table[i + 1][j] ? start[i][j - 1] : start[i + 1][j];
				}
			}
		}
		string ans = s.substr(start[0][len - 1], table[0][len - 1]);
		return ans;
	}
	bool isMatch(string s, string p) {
		int s_len = s.length();
		int p_len = p.length();
		vector<vector<bool>> dptable(s_len+1, vector<bool>(p_len+1, false));
		//table[i][j]表示s(0:i)到p(0:j)是否匹配
		dptable[0][0] = true;//加一个
		int i, j;
		for (j = 0; j < p_len; j++) {
			if (p[j] == '*') {
				dptable[0][j + 1] = dptable[0][j - 1];
			}
		}
		for (i = 0; i < s_len; i++) {
			for (j = 0; j < p_len; j++) {
				if (p[j] =='.') {
					dptable[i + 1][j + 1] = dptable[i][j];
				}
				if (p[j] == s[i]) {
					dptable[i + 1][j + 1] = dptable[i][j];
				}
				if (p[j] == '*') {
					if (p[j - 1] != s[i] && p[j-1]!='.') {
						dptable[i + 1][j + 1] = dptable[i + 1][j - 1];
					}
					else {
						dptable[i + 1][j + 1] = (dptable[i + 1][j - 1] || dptable[i + 1][j] || dptable[i][j + 1]);
					}
				}
			}
		}
		return dptable[s_len][p_len];
	}
	int removeDuplicates(vector<int>& nums) {
		set<int> settemp;
		int i;
		for (i = 0; i < nums.size(); i++) {
			settemp.insert(nums[i]);
		}
		nums.assign(settemp.begin(), settemp.end());  //vector的一个赋值方法
		return settemp.size();
	}
	int removeElement(vector<int>& nums, int val) {
		int i;
		for (i = 0; i < nums.size();) {
			if (nums[i] == val) {
				nums.erase(nums.begin()+i);
			}
			else {
				i++;
			}
		}
		return nums.size();
	}
	int strStr(string haystack, string needle) {
		string::size_type position;
		if (position = haystack.find(needle) != string::npos) {   //find函数的返回值
			return position;
		}
		return -1;
	}
	int divide(int dividend, int divisor) {
		//without using multiplication, division and mod operator
		//return 2^31 − 1 when the division result overflows.
		if (!divisor || (dividend == INT_MIN && divisor == -1))
			return INT_MAX;
		int sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1;
		long long dvd = labs(dividend);
		long long dvs = labs(divisor);
		int res = 0;
		while (dvd >= dvs) {
			long long temp = dvs, multiple = 1;
			while (dvd >= (temp << 1)) {   //这里加速直接搞2^n
				temp <<= 1;
				multiple <<= 1;
			}
			dvd -= temp;
			res += multiple;
		}
		return sign == 1 ? res : -res;
	}
	vector<int> findSubstring(string s, vector<string>& words) {
		vector<vector<int>> start;
		vector<int> temp;
		unordered_map<string, int> table;
		unordered_map<string, int> now;
		int i;
		for (i = 0; i < words.size(); i++) {
			if (words[i] == "") {                  //""
				return temp;
			}
			else if (table.find(words[i]) == table.end()) {    //查找失败
				table.insert(pair<string, int>(words[i],1));
			}
			else {
				table[words[i]]++;
			}
		}
		if (!words.size()) {
			return temp;
		}
		int size_word = words[0].length();
		string strtemp;
		int j,k;
		for (i = 0; i < s.length() - size_word*words.size()+1; i++) {
			strtemp = s.substr(i, size_word*words.size());
			now.clear();
			for (j = 0; j < strtemp.length(); j += size_word) {
				string tofind = strtemp.substr(j, size_word);
				if (table.find(tofind) == table.end()) {
					break;
				}
				else if(now.find(tofind) != now.end()){
					now[tofind]++;
					if (now[tofind] > table[tofind]) {
						break;
					}
				}
				else {
					now.insert(pair<string, int>(tofind, 1));
				}
			}
			if (j == strtemp.length()) {
				temp.push_back(i);
			}
		}
		return temp;
	}
};

int main() {
	int solution=30;
	string solution5;
	vector<string> solution22;
	vector<string> vec;
	vector<int> solution30;
	ListNode l1(1);
	ListNode l2(1);
	ListNode *l3;
	Solution Solu;
	bool solution10;
	int solution29;
	switch (solution)
	{
	case 5:
		solution5 = Solu.longestPalindrome("adbbdca");
		break;
	case 10:
		solution10 = Solu.isMatch("ab", ".*");
		break;
	case 21:
		l3 = Solu.mergeTwoLists(&l1, &l2);
		break;
	case 22:
		solution22 = Solu.generateParenthesis(3);
		break;
	case 29:
		solution29 = Solu.divide(2147483647, 2);
		break;
	case 30:
		vec.push_back("word");
		vec.push_back("good");
		vec.push_back("best");
		vec.push_back("word");
		solution30 = Solu.findSubstring("wordgoodgoodgoodbestword", vec);
		break;
	default:
		break;
	}
}