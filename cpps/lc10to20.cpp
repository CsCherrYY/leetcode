#include<iostream>
#include<vector>
#include<algorithm>  //min max
#include<string>
#include<unordered_map>
#include<set>
#include<stack>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
	int maxArea(vector<int>& height) {
		int start = 0;
		int end = height.size()-1;
		int maxsqre = 0;
		while (end > start) {
			maxsqre = max(min(height[end], height[start])*(end - start),maxsqre);
			if (height[start] <= height[end]){
				start++;
			}
			else {
				end--;
			}
		}
		return maxsqre;
	}
	string intToRoman(int num) {
		string M[] = { "", "M", "MM", "MMM" };
		string C[] = { "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM" };
		string X[] = { "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC" };
		string I[] = { "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };
		return M[num / 1000] + C[(num % 1000) / 100] + X[(num % 100) / 10] + I[num % 10];
	}
	int romanToInt(string s) {
		unordered_map <char, int> T = { { 'I' , 1 },
								   { 'V' , 5 },
								   { 'X' , 10 },
								   { 'L' , 50 },
								   { 'C' , 100 },
								   { 'D' , 500 },
								   { 'M' , 1000 } };
		int res = 0;
		for (int i = 0; i < s.length(); i++) {
			if (i <= s.length() - 2) {
				if (T[s[i]] >= T[s[i + 1]]) {
					res += T[s[i]];
				}
				else {
					res -= T[s[i]];
				}
			}
			else {
				res += T[s[i]];
			}
		}
		return res;
	}
	string longestCommonPrefix(vector<string>& strs) {
		if (strs.size() == 0) {
			return "";
		}
		else {

			string nowstr = strs[0];
			int i, j;
			for (i = 1; i < strs.size(); i++) {
				for (j = 0; j < min(nowstr.length(), strs[i].length()); j++) {
					if (nowstr[j] != strs[i][j]) {
						break;
					}
				}
				nowstr = nowstr.substr(0,j);
			}
			return nowstr;
		}
	}
	vector<vector<int>> threeSum(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		vector<vector<int>> res;
		for (unsigned int i = 0; i < nums.size(); i++) {
			if ((i > 0) && (nums[i] == nums[i - 1]))
				continue;
			int l = i + 1, r = nums.size() - 1;
			while (l < r) {
				int s = nums[i] + nums[l] + nums[r];
				if (s > 0) r--;
				else if (s < 0) l++;
				else {
					res.push_back(vector<int> {nums[i], nums[l], nums[r]});
					while (nums[l] == nums[l + 1]) l++;
					while (nums[r] == nums[r - 1]) r--;
					l++; r--;
				}
			}
		}
		return res;
	}
	int threeSumClosest(vector<int>& nums, int target) {
		sort(nums.begin(), nums.end());
		int near,i,j,k,ans;
		near = nums[0] + nums[1] + nums[nums.size() - 1];
		for (i = 0; i < nums.size()-2; i++) {
			j = i + 1;
			k = nums.size() - 1;
			while (j < k) {
				ans = nums[i] + nums[j] + nums[k];
				//result = nums[i] + nums[j] + nums[k] - target;
				near = abs(ans- target)>=abs(near- target)?near:ans;
				if (ans-target < 0) {
					j++;
				}
				else {
					k--;
				}
			}
		}
		return near;
	}
	vector<string> letterCombinations(string digits) {
		vector<string> temp;
		vector<string> temp1;
		temp.push_back("");
		if (digits.length() == 0) {
			return temp1;
		}
		vector<string> table = { "abc","def","ghi","jkl","mno","pqrs","tuv","wxyz" };
		string nowstr;
		int i,j,k;
		for (i = 0; i < digits.length(); i++) {
			nowstr = table[digits[i] - '2'];
			temp1.clear();
			for (j = 0; j < nowstr.length(); j++) {
				for (k = 0; k < temp.size(); k++) {
					temp1.push_back(temp[k] + nowstr[j]);
				}
			}
			temp = temp1;
		}
		return temp;
	}
	vector<vector<int>> fourSum(vector<int>& nums, int target) {
		vector<vector<int>> temp;
		vector<int> tempvec,lastvec;
		sort(nums.begin(), nums.end());
		int i, j, k, l, test;
		if (nums.size() >= 4) {
			for (i = 0; i < nums.size() - 3; i++) {
				if (i > 0) {
					if (nums[i] == nums[i - 1]) {
						continue;
					}
				}
				for (j = i + 1; j < nums.size() - 2; j++) {
					if (j > i+1 && nums[j] == nums[j - 1]) {
						continue;
					}
					k = j + 1;
					l = nums.size() - 1;
					while (k < l) {
						test = nums[i] + nums[j] + nums[k] + nums[l] - target;
						if (test < 0) {
							k++;
						}
						else if (test > 0) {
							l--;
						}
						else {
							tempvec = { nums[i],nums[j],nums[k],nums[l] };
							if (lastvec != tempvec) {
								temp.push_back(tempvec);
							}
							lastvec = tempvec;
							while (nums[k + 1] == nums[k]) {
								k++;
							}
							while (nums[l - 1] == nums[l]) {
								l--;
							}
							k++;
							l--;
						}
					}
				}
			}
		}
		return temp;
	}
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		if (head == NULL) {
			return NULL;
		}
		ListNode *start, *end;
		start = head;
		end = head;
		int i;
		for (i = 0; i < n; i++) {
			end = end->next;
		}
		if (end == NULL) {    //ɾͷ
			return start->next;
		}
		else {
			while (end->next != NULL) {
				start = start->next;
				end = end->next;
			}
			start->next = start->next->next;
		}
		return head;
	}
	bool isValid(string s) {
		if (s.length() == 0) {
			return true;
		}
		if (s.length() % 2 == 1) {
			return false;
		}
		int i;
		stack<char> stacks;
		for (i = 0; i < s.length(); i++) {
			if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
				stacks.push(s[i]);
			}
			else if(!stacks.empty()){
				if (s[i] == ')'&&stacks.top()=='(') {
					stacks.pop();
				}
				else if (s[i] == ']'&&stacks.top() == '[') {
					stacks.pop();
				}
				else if (s[i] == '}'&&stacks.top() == '{') {
					stacks.pop();
				}
			}
		}
		if (stacks.empty()) {
			return true;
		}
		return false;
	}
};
int main(){
	Solution Solu;
	vector<int> vec;
	vector<vector <int>> solution15, solution18;
	ListNode *res;
	ListNode *l1 = new ListNode(1);
	ListNode *l2 = new ListNode(2);
	ListNode *l3 = new ListNode(3);
	ListNode *l4 = new ListNode(4);
	ListNode *l5 = new ListNode(5);
	vector<string> vecstr,solution17;
	int problem,solution11,solution13,solution16;
	string solution12,solution14;
	bool solution20;
	problem = 20;
	switch (problem)
	{
	case 11:
		vec.push_back(1);
		vec.push_back(8);
		vec.push_back(6);
		vec.push_back(2);
		vec.push_back(5);
		vec.push_back(4);
		vec.push_back(8);
		vec.push_back(3);
		vec.push_back(7);
		solution11 = Solu.maxArea(vec);
		break;
	case 12:
		solution12 = Solu.intToRoman(1994);
		break;
	case 13:
		solution13 = Solu.romanToInt("MCMXCIV");
		break;
	case 14:
		vecstr.push_back("flower");
		vecstr.push_back("flow");
		vecstr.push_back("flight");
		solution14 = Solu.longestCommonPrefix(vecstr);
		break;
	case 15:
		vec.push_back(-1);
		vec.push_back(0);
		vec.push_back(1);
		vec.push_back(2);
		vec.push_back(-1);
		vec.push_back(-4);
		solution15 = Solu.threeSum(vec);
		break;
	case 16:
		vec.push_back(-1);
		vec.push_back(2);
		vec.push_back(1);
		vec.push_back(-4);
		solution16 = Solu.threeSumClosest(vec,1);
		break;
	case 17:
		solution17 = Solu.letterCombinations("");
		break;
	case 18:
		vec.push_back(-1);
		vec.push_back(0);
		vec.push_back(1);
		vec.push_back(2);
		vec.push_back(-1);
		vec.push_back(-4);
		solution18 = Solu.fourSum(vec, -1);
		break;
	case 19:
		l1->next = l2;
		l2->next = l3;
		l3->next = l4;
		l4->next = l5;
		res = Solu.removeNthFromEnd(l1,2);
		break;
	case 20:
		solution20 = Solu.isValid("){");
		break;
	default:
		break;
	}
	return 0;
}
