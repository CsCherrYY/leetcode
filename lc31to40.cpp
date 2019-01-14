#include<vector>
#include<algorithm>
#include<iostream>
#include<set>
#include<map>
#include<string>
#include<unordered_set>
//#include<iostream>
using namespace std;

class Solution {
public:
	void nextPermutation(vector<int>& nums) {            //按字典序排列
		//The replacement must be in-place and use only constant extra memory.
		if (nums.size() <= 1) {
			return;
		}
		int temp;
		int i, j;
		int maxlocj = -1;
		if (nums.size() == 2) {
			reverse(nums.begin(), nums.end());
			return;
		}
		for (j = 0; j < nums.size() - 1; j++) {
			if (nums.at(j + 1) > nums.at(j)) {         //找到满足num[j]<num[j+1]的最大值
				maxlocj = j;
			}
		}
		if (maxlocj == -1) {
			sort(nums.begin(), nums.end());              //字典序已经最大
			return;
		}
		j = maxlocj;
		i = j + 1;
		int min = nums.at(i);
		int minloc = i;
		for (; i < nums.size(); i++) {
			if (nums.at(i)<=min&&nums.at(i)>nums.at(j)) {
				min = nums.at(i);
				minloc = i;
			}
		}
		swap(nums.at(j), nums.at(minloc));
		reverse(nums.begin() + j + 1, nums.end());
		i = 1;
		return;
	}
	int longestValidParentheses(string s) {
		vector<int> dptable(s.length(), 0);
		if (s.length() <= 1) {
			return 0;
		}
		int i = 1;
		int maxlen = 0;
		if (s[1] == ')'&&s[0] == '(') {
			dptable[1] = 2;
			maxlen = 2;
			if (s.length() == 2) {
				return 2;
			}
			
		}
		for (i = 2; i < s.length(); i++) {
			if (s[i] == ')'&&s[i - 1] == '(') {
				dptable[i] = dptable[i - 2] + 2;
				maxlen = max(maxlen, dptable[i]);
			}
			else if (s[i] == ')'&&s[i - 1] == ')') {
				if (s[i - 1 - dptable[i - 1] + 1 - 1] == '(') {
					dptable[i] = dptable[i - 1] + 2 + dptable[i - 1 - dptable[i - 1] + 1 - 2];////可以把之前的连起来
					maxlen = max(maxlen, dptable[i]);
				}
			}
		}
		return maxlen;
	}
	int search(vector<int>& nums, int target) {
		int low = 0;
		int size_n = nums.size();
		if (size_n == 0) {
			return -1;
		}
		if (size_n == 1) {
			if (nums[0] == target) {
				return 0;
			}
		}
		int high = size_n - 1;
		int position;
		while (low < high) {                   //找到最小点
			position = (high + low) / 2;
			if (nums[position] > nums[high]) {
				low = position + 1;
			}
			else{
				high = position;
			}
		}
		int minloc = low;
		low = 0;
		high = size_n - 1;
		int realmid;
		while (low <= high) {                  //二分查找的边界问题
			position = (high + low) / 2;
			realmid = (position + minloc) % size_n;        //循环思想
			if (nums[realmid] == target) {
				return realmid;
			}
			else if (nums[realmid] > target) {
				high = position - 1;
			}
			else{
				low = position + 1;
			}
		}
		if (nums[low] == target) {
			return low;
		}
		return -1;
	}
	vector<int> searchRange(vector<int>& nums, int target) {
		vector<int> temp(2, -1);
		vector<int>::iterator iter = find(nums.begin(),nums.end(),target);
		if (iter == nums.end()) {
			return temp;
		}
		int start = distance(nums.begin(), iter);   //求距离
		temp[0] = start;
		int i;
		for (i = start; i < nums.size(); i++) {
			if (nums[i] != nums[start]) {
				break;
			}
		}
		temp[1] = i - 1;
		return temp;
	}
	int searchInsert(vector<int>& nums, int target) {
		if (nums.size() == 0) {
			return 0;
		}
		int i;
		for (i = 0; i < nums.size(); i++) {
			if (nums[i] >= target) {
				break;
			}
		}
		return i;
	}
	bool checkcolumn(vector<vector<char>> board, int x, int y) {
		set<char> tempset;
		for (int i = 0; i < 9; i++) {
			char tempchar = board[i][y];
			if (tempchar != '.') {
				if (tempset.find(tempchar) == tempset.end()) {
					tempset.insert(tempchar);
				}
				else {
					return false;
				}
			}
		}
		return true;
	}
	bool checkrow(vector<vector<char>> board, int x, int y) {
		set<char> tempset;
		for (int i = 0; i < 9; i++) {
			char tempchar = board[x][i];
			if (tempchar != '.') {
				if (tempset.find(tempchar) == tempset.end()) {
					tempset.insert(tempchar);
				}
				else {
					return false;
				}
			}
		}
		return true;
	}
	bool checksqrt(vector<vector<char>> board, int x, int y) {
		set<char> tempset;
		//int sqrt = (x / 3) * 3 + y / 3;
		int startx = (x / 3) * 3;
		int starty = (y / 3) * 3;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				char tempchar = board[startx + i][starty + j];
				if (tempchar != '.') {
					if (tempset.find(tempchar) == tempset.end()) {
						tempset.insert(tempchar);
					}
					else {
						return false;
					}
				}
			}

		}
		return true;
	}
	bool isValidSudoku(vector<vector<char>>& board) {
		int i, j;
		bool row[9][9] = { false };
		bool column[9][9] = { false };
		bool square[9][9] = { false };
		int nowchar;
		for (i = 0; i < 9; i++) {
			for (j = 0; j < 9; j++) {
				nowchar = board[i][j]-'1';
				if (board[i][j] != '.') {                  //行  i行j列
					if (!row[i][nowchar]&&!column[j][nowchar]&&!square[(i/3)*3+j/3][nowchar]){
						row[i][nowchar] = true;
						column[j][nowchar] = true;
						square[(i / 3) * 3 + j / 3][nowchar] = true;
					}
					else{
						return false;
					}
				}
			}
		}
		return true;
	}
	bool check(vector<vector<char>> &board, int i, int j, char val)            //插入i,j的位置时只需检测该位置是否合法
	{
		int row = i - i % 3, column = j - j % 3;
		for (int x = 0; x<9; x++) if (board[x][j] == val) return false;
		for (int y = 0; y<9; y++) if (board[i][y] == val) return false;
		for (int x = 0; x<3; x++)
			for (int y = 0; y<3; y++)
				if (board[row + x][column + y] == val) return false;
		return true;
	}
	bool solvesudoku(vector<vector<char>> &board, int i, int j)
	{
		if (i == 9) return true;
		if (j == 9) return solvesudoku(board, i + 1, 0);
		if (board[i][j] != '.') return solvesudoku(board, i, j + 1);  //初值合法，判断下一个位置，之后的所有数字都是经过判断得出

		for (char c = '1'; c <= '9'; c++)
		{
			if (check(board, i, j, c))
			{
				board[i][j] = c;
				if (solvesudoku(board, i, j + 1)) return true;
				board[i][j] = '.';  //回溯
			}
		}
		return false;
	}
	void solveSudoku(vector<vector<char>>& board) {
		solvesudoku(board, 0, 0);
	}
	string countAndSay(int n) {
		vector<pair<char, int>> vec;
		vector<pair<char, int>>::iterator itor;
		string temp = "1";
		int j;
		int vecloc = 0;
		char last;
		for (int i = 1; i < n; i++) {
			vec.clear();
			for (j = 0; j < temp.length(); j++) {
				if (j == 0) {
					vec.push_back(pair<char,int>(temp[j], 1));
					last = temp[j];
					vecloc = 0;
				}
				else if (temp[j] == last) {
					(vec[vecloc].second)++;
				}
				else {
					vec.push_back(pair<char, int>(temp[j], 1));          //push_back不能和迭代器同时使用？
					last = temp[j];
					vecloc++;
				}
			}
			temp = "";
			itor = vec.begin();
			while (itor != vec.end()) {
				temp += to_string(itor->second);
				temp += itor->first;
				itor++;
			}
		}
		return temp;
	}
	vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
		vector<vector<int>> temp2d;
		vector<int>now;
		combination(candidates, now, target, temp2d, 0);
		return temp2d;
	}
	void combination(vector<int>& candidates,vector<int>& now, int target,vector<vector<int>>& temp2d,int start) {
		if (target == 0) {
			temp2d.push_back(now);
			return;
		}
		int i, temp;
		for (i = start; i < candidates.size(); i++) {
			temp = target - candidates[i];
			if (temp >= 0) {
				now.push_back(candidates[i]);
				combination(candidates, now, temp, temp2d, i);         //回溯
				now.pop_back();
			}
		}
		return;
	}
	vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
		vector<vector<int>> temp2d;
		vector<int>now;
		sort(candidates.begin(), candidates.end());
		combination2(candidates, now, target, temp2d, -1);
		return temp2d;
	}
	void combination2(vector<int>& candidates, vector<int>& now, int target, vector<vector<int>>& temp2d, int start) {
		if (target == 0) {
			vector<vector<int>>::iterator it = find(temp2d.begin(), temp2d.end(), now);   //vector去重方法
			if (it == temp2d.end()) {
				temp2d.push_back(now);
				return;
			}
			return;
		}
		int i, temp;
		for (i = start + 1; i < candidates.size(); i++) {
			temp = target - candidates[i];
			if (temp >= 0) {
				now.push_back(candidates[i]);
				combination2(candidates, now, temp, temp2d, i);
				now.pop_back();
			}
		}
		return;
	}
};

int main() {
	vector<int> vec;
	vector<vector<char>> temp = { {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
	{'6', '.', '.', '1', '9', '5', '.', '.', '.'},
	{'.', '9', '8', '.', '.', '.', '.', '6', '.'},
	{'8', '.', '.', '.', '6', '.', '.', '.', '3'},
	{'4', '.', '.', '8', '.', '3', '.', '.', '1'},
	{'7', '.', '.', '.', '2', '.', '.', '.', '6'},
	{'.', '6', '.', '.', '.', '.', '2', '8', '.'},
	{'.', '.', '.', '4', '1', '9', '.', '.', '5'},
	{'.', '.', '.', '.', '8', '.', '.', '7', '9'} };
	Solution Solu;
	vector<vector<int>> solu39,solu40;
	int k = 0;
	int test = 40;
	switch (test)
	{
	case 31:
		vec.push_back(1);
		vec.push_back(5);
		vec.push_back(1);
		//vec.push_back(3);
		//vec.push_back(3);
		Solu.nextPermutation(vec);
		break;
	case 33:
		vec.push_back(4);
		vec.push_back(5);
		vec.push_back(6);
		vec.push_back(7);
		vec.push_back(0);
		vec.push_back(1);
		vec.push_back(2);
		cout<<Solu.search(vec, 0);
		break;
	case 37:
		Solu.solveSudoku(temp);
		k = 1;
		break;
	case 38:
		Solu.countAndSay(5);
		break;
	case 39:
		vec = { 2,3,6,7 };
		solu39 = Solu.combinationSum(vec,7);
		break;
	case 40:
		vec = { 10,1,2,7,6,1,5 };
		solu40 = Solu.combinationSum2(vec, 8);
		break;
	default:
		break;
	}
	return 0;
}