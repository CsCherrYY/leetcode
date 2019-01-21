#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<unordered_map>
using namespace std;
class Solution {
public:
	string simplifyPath(string path) {
		vector<string> temp;
		vector<string> simple;
		int i;
		string temppath;
		string tempdir;
		bool sign = false;
		for (i = 0; i < path.length(); i++) {
			if (path[i] == '/') {   //那种斜杠无意义
				if (!tempdir.empty()) {
					temp.push_back(tempdir);
				}
				tempdir.clear();
			}
			else {
				tempdir += path[i];
			}
		}
		if (!tempdir.empty()) {
			temp.push_back(tempdir);        //这里注意一下 最后可能没有斜杠的
		} 
		for (i = 0; i < temp.size(); i++) {
			if (temp[i] == ".") {
				continue;
			}
			else if (temp[i] == "..") {
				if (!simple.empty()) {
					simple.erase(simple.begin() + simple.size() - 1);
				}
			}
			else {
				simple.push_back(temp[i]);
			}
		}
		for (i = 0; i < simple.size(); i++) {
			temppath += "/";
			temppath += simple[i];
		}
		return (temppath.empty()) ? "/" : temppath;
	}
	int minDistance(string word1, string word2) {  

	}  //这题不会，先自闭了
	void setZeroes(vector<vector<int>>& matrix) {
		int i, j; //O(mn):bool矩阵 O(m+n)：接起来存行列  常数：判断存储在第一行和第一列中
		int len_0 = matrix.size();
		int len_1 = matrix[0].size();
		bool firstline = false;
		bool firstcow = false;
		for (j = 0; j < len_1; j++) {  //第一行是否有0
			if (matrix[0][j] == 0) {
				firstline = true;
			}
		}
		for (i = 0; i < len_0; i++) {
			if (matrix[i][0] == 0) {
				firstcow = true;
			}
		}
		for (i = 1; i < len_0; i++) {
			for (j = 1; j < len_1; j++) {
				if (matrix[i][j] == 0) {
					matrix[i][0] = 0;
					matrix[0][j] = 0;
				}
			}
		}
		for (i = 1; i < len_0; i++) {
			if (matrix[i][0] == 0) {
				for (j = 1; j < len_1; j++) {
					matrix[i][j] = 0;
				}
			}
		}
		for (j = 1; j < len_1; j++) {
			if (matrix[0][j] == 0) {
				for (i = 1; i < len_0; i++) {
					matrix[i][j] = 0;
				}
			}
		}
		if (firstline) {
			for (j = 0; j < len_1; j++) {
				matrix[0][j] = 0;
			}
		}
		if (firstcow) {
			for (i = 0; i < len_0; i++) {
				matrix[i][0] = 0;
			}
		}
		return;
	}
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		int len_0 = matrix.size();
		if (!len_0) {
			return false;
		}
		int len_1 = matrix[0].size();
		if (!len_1) {
			return false;
		}
		int low = 0;
		int high = len_0 * len_1 - 1;
		int mid, midx, midy;
		while (low <= high) {
			mid = (low + high) / 2;
			midx = mid / len_1;
			midy = mid % len_1;
			if (matrix[midx][midy] == target) {
				return true;
			}
			else if (low == high) {
				return false;
			}
			else if (matrix[midx][midy] < target) {
				low = mid + 1; 
				/*二分查找的控制流：
				1、while条件low<=high 
				2、mid=(low+mid)/2 
				3、low=mid+1 
				4、high=mid-1*/
				continue;
			}
			else {
				high = mid - 1;
				continue;
			}
		}
	}
	void sortColors(vector<int>& nums) {
		int i = 0;  //三路快排思想
		int len = nums.size();
		int zero_tail = 0;
		int one_tail = 0;
		int two_head = len - 1;
		for (i = 0; i < len;) {
			if (nums[i] == 0) {
				swap(nums[i], nums[zero_tail]);
				zero_tail++;
				one_tail++;
			}
			else if (nums[i] == 2) {
				swap(nums[i], nums[two_head]);
				two_head--;
			}
			else {
				one_tail++;
				i++;
			}
			if (one_tail > two_head) {  //这里要用大于
				break;
			}
			i = one_tail;     //把当前指针点指向1的最后一个
		}
	}
	string minWindow(string s, string t) {
		string minstr, temp;
		minstr = s;
		vector<int>needt(128, 0);
		int left = 0;
		int right = 0;
		int i;
		int remain = t.length();
		for (i = 0; i < t.length(); i++) {
			needt[t[i]]++;
		}//记录t中每个单词的个数
		while (right<s.length()) {
			for (; right < s.length();right++) {
				if (!remain) {
					break;
				}
				needt[s[right]]--;
				if (needt[s[right]] >= 0) {
					remain--;          //存在有该字符
				}
			}
			if (minstr == s&&remain>0) {
				return "";
			}
			else if (remain > 0) {
				break;
			}
			for (; left < right; left++) {
				temp = s.substr(left, right-left);
				minstr = temp.length() >= minstr.length() ? minstr : temp;
				needt[s[left]]++;
				if (needt[s[left]] > 0) {
					left++;
					remain++;
					break;
				}
			}
		}
		return minstr;
	}
	vector<vector<int>> combine(int n, int k) {
		vector<vector<int>> temp;
		vector<int> nums,result;
		int i;
		for (i = 1; i <= n; i++) {
			nums.push_back(i);
		}
		combinecs(nums, k, temp, result);
		return temp;
	}
	void combinecs(vector<int> nums, int k, vector<vector<int>>& temp, vector<int>& result) {
		//组合 不能简单的回溯    nums 候选集合 k 剩余数字 result当前集合
		if (k == 0) {
			temp.push_back(result);
			return;
		}
		int i;
		int tempint;
		//int size0 = nums.size();
		for (i = 0; i < nums.size(); ) {  //erase了以后size减小了
			tempint = nums[i];
			result.push_back(tempint);
			nums.erase(nums.begin() + i);
			combinecs(nums, k - 1, temp, result);
			//nums.insert(nums.begin() + i, tempint);
			result.pop_back();
		}
	}
	vector<vector<int>> subsets(vector<int>& nums) {
		vector<vector<int>> temp;
		if (nums.size() == 0) {
			return temp;
		}
		vector<int> result;
		subsetcs(nums, nums.size(), temp, result);
		return temp;
		//对每个元素都可以选存在或不存在
	}
	void subsetcs(vector<int> nums, int k,vector<vector<int>>& temp,vector<int> result) {
		if (k == 0) {
			temp.push_back(result);
			return;
		}
		int i;
		int tempint;
		vector<int> result1 = result;
		for (i = 0; i < nums.size();) {
			tempint = nums[i];
			result.push_back(tempint);
			//result1不push
			nums.erase(nums.begin() + i);
			subsetcs(nums, k - 1, temp, result);  //递归回溯
			subsetcs(nums, k - 1, temp, result1);
			result.pop_back();
		}
	}
	bool exist(vector<vector<char>>& board, string word) {
		if (board.size() == 0) {
			return false;
		}
		if (board[0].size() == 0) {
			return false;
		}
		if (word.length() == 0) {
			return false;
		}
		int line = board.size();
		int arrays = board[0].size();
		int i, j;
		for (i = 0; i < line; i++) {
			for (j = 0; j < arrays; j++) {
				if (judge(board, i, j, word, 0)) {
					return true;
				}
			}
		}
		return false;
	}
	bool judge(vector<vector<char>>& board, int x, int y,string word,int size) {
		if (size == word.length()) {
			return true;
		}
		if (x<0 || x>board.size() - 1) {
			return false;
		}
		if (y<0 || y>board[0].size() - 1) {
			return false;
		}
		if (board[x][y] != word[size]) {
			return false;
		}
		char temp;
		temp = board[x][y];
		board[x][y] = 0;
		if (judge(board, x + 1, y, word, size + 1) ||
			judge(board, x - 1, y, word, size + 1) ||
			judge(board, x, y + 1, word, size + 1) ||
			judge(board, x, y - 1, word, size + 1)) {
			return true;   //左右探测
		}
		board[x][y] = temp;  //回溯
		return false;
	}
	int removeDuplicates(vector<int>& nums) {
		int size = nums.size();
		if (size <= 2) {
			return size;  //不用改了
		}
		int i, j, k;
		for (i = 0; i < nums.size() - 2;) {
			j = i + 1;
			k = i + 2;
			if (nums[i] == nums[j] && nums[j] == nums[k]) {
				nums.erase(nums.begin() + k);
			}
			else {
				i++;
			}
		}
		return nums.size();
	}
};
int main() {
	int test = 77;
	Solution solu;
	vector<vector<int>> solu77;
	string solu71, solu76;
	vector<vector<int>> int2d;
	vector<int>int1d;
	switch (test)
	{
	case 71:
		solu71 = solu.simplifyPath("/a//b////c/d//././/..");
		break;
	case 73:
		int2d = { {0,1,2,0},{3,4,5,2},{1,3,1,5} };
		solu.setZeroes(int2d);
		break;
	case 74:
		int2d = { {1,   3,  5,  7},{10, 11, 16, 20},{23, 30, 34, 50} };
		solu.searchMatrix(int2d, 13);
		break;
	case 75:
		int1d = { 2,0,2,1,1,0 };
		solu.sortColors(int1d);
		break;
	case 76:
		solu76 = solu.minWindow("acbdbaab","aabd");
		break;
	case 77:
		solu77 = solu.combine(4, 2);
		break;
	default:
		break;
	}
}