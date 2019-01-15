#include<vector>
#include<algorithm>
#include<string>

using namespace std;
struct Interval {
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};
bool cmp(Interval a, Interval b) {
	return a.start < b.start;
}
class Solution {
public:
	vector<vector<string>> solveNQueens(int n) {
		vector<vector<string>> temp;
		string tempstr;
		int i, j;
		for (i = 0; i < n; i++) {
			tempstr += ".";
		}
		vector<string> table(n, tempstr);
		solver(temp, table, 0, n);
		return temp;
	}//递归回溯，有一个简单的想法是位运算
	void solver(vector<vector<string>>&res, vector<string> &temp, int now, int n) {
		if (now == n) {
			res.push_back(temp);
			return;
		}
		int i;
		for (i = 0; i < n; i++) {
			if (judge(temp, n, now, i)) {
				temp[now][i] = 'Q';
				solver(res, temp, now + 1, n);
				temp[now][i] = '.';
			}
		}
	}
	bool judge(vector<string> temp, int n, int loc_x, int loc_y) {
		int i, j;
		int count_row = 0;
		int count_array = 0;
		int count_x = 0;
		for (i = 0; i < n; i++) {
			if (temp[loc_x][i] == 'Q') {
				count_row++;
			}
			if (temp[i][loc_y] == 'Q') {
				count_array++;
			}
		}//检查一行/一列
		if (count_row >= 1 || count_array >= 1) {
			return false;
		}
		int step = 0;
		while ((loc_x - step) >= 0 && (loc_y - step) >= 0) {
			if (temp[loc_x - step][loc_y - step] == 'Q') {
				count_x++;
			}
			step++;
		}
		step = 0;
		while ((loc_x + step) < n && (loc_y - step) >= 0) {
			if (temp[loc_x + step][loc_y - step] == 'Q') {
				count_x++;
			}
			step++;
		}
		step = 0;
		while ((loc_x - step) >= 0 && (loc_y + step) < n) {
			if (temp[loc_x - step][loc_y + step] == 'Q') {
				count_x++;
			}
			step++;
		}
		step = 0;
		while ((loc_x + step) < n && (loc_y + step) < n) {
			if (temp[loc_x + step][loc_y + step] == 'Q') {
				count_x++;
			}
			step++;
		}
		if (count_x >= 1) {
			return false;
		}
		return true;
	}
	int totalNQueens(int n) {
		return solveNQueens(n).size();
	}
	int maxSubArray(vector<int>& nums) {
		if (nums.size() == 0) {
			return 0;
		}
		int i = 0;
		int max_sum = nums[0];
		for (i = 0; i < nums.size(); i++) {
if (nums[i] > max_sum) {
	max_sum = nums[i];
}
		}
		int now_sum = 0;
		i = 0;
		while (nums[i] < 0) {
			i++;
		}
		for (; i < nums.size(); i++) {
			if (now_sum + nums[i] > 0) {
				now_sum += nums[i];
			}
			else {
				now_sum = 0;
			}
			max_sum = max(max_sum, now_sum);
		}
		return max_sum;
	}
	bool canJumpdp(vector<int>& nums) {
		int len = nums.size();
		if (len <= 1) {
			return true;
		}
		int i, j;
		vector<bool> dp(len, false);
		dp[0] = true;
		for (i = 0; i < len; i++) {
			for (j = i; j <= i + nums[i]; j++) {
				dp[j] = dp[i];
			}
		}
		return dp[len - 1];
	}
	bool canJump(vector<int>& nums) {
		int len = nums.size();
		if (len <= 1) {
			return true;
		}
		int i;
		int target = len - 1;
		for (i = len - 2; i >= 0; i--) {
			if (nums[i] + i >= target) {
				target = i;
			}
		}
		if (target == 0) {
			return true;
		}
		return false;
	}//贪心法，能到达最后一个数的方法肯定能到达前面的数
	vector<Interval> merge(vector<Interval>& intervals) {
		sort(intervals.begin(), intervals.end(), cmp);
		if (intervals.size() <= 1) {
			return intervals;
		}
		int i;
		for (i = 0; i < intervals.size() - 1;) {
			if (intervals[i].end >= intervals[i + 1].start) {
				intervals[i].end = max(intervals[i + 1].end, intervals[i].end);
				intervals.erase(intervals.begin() + i + 1);
			}
			else {
				i++;
			}
		}
		return intervals;
	}
	vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
		intervals.push_back(newInterval);
		return merge(intervals);
	}
	int lengthOfLastWord(string s) {
		int len = s.length();
		if (len == 0) {
			return 0;
		}
		int local = s.rfind(' ');
		while (local == len - 1) {
			if (s == " ") {
				return 0;
			}
			s = s.substr(0, local);
			len--;
			local = s.rfind(' ');
		}
		//local = max(local, 0);
		return len - 1 - local;
	}
	vector<int> spiralOrder(vector<vector<int>>& matrix) {
		vector<int> temp;
		int size_m = matrix.size();
		if (!size_m) {
			return temp;
		}
		int size_n = matrix[0].size();
		if (!size_n) {
			return temp;
		}
		vector<vector<bool>> table(size_m,vector<bool>(size_n,false));
		int flag = 0;//0~3
		int step = 0;//0~m*n-1
		int step_max = size_m*size_n;
		int step_m = 0;
		int step_n = -1;
		while (step < step_max) {
			if (flag == 0) {  //右
				if (((step_n + 1) <= (size_n - 1)) && (!table[step_m][step_n + 1])) {
					step_n++;
					step++;
					temp.push_back(matrix[step_m][step_n]);
					table[step_m][step_n] = true;
				}
				else {
					flag = 1;
				}
			}
			else if (flag == 1) {   //下
				if (((step_m + 1) <= (size_m - 1)) && (!table[step_m + 1][step_n])) {
					step_m++;
					step++;
					temp.push_back(matrix[step_m][step_n]);
					table[step_m][step_n] = true;
				}
				else {
					flag = 2;
				}
			}
			else if (flag == 2) {   //左
				if (((step_n - 1) >= 0) && (!table[step_m][step_n - 1])) {
					step_n--;
					step++;
					temp.push_back(matrix[step_m][step_n]);
					table[step_m][step_n] = true;
				}
				else {
					flag = 3;
				}
			}
			else if (flag == 3) {   //上
				if (((step_m - 1) >= 0) && (!table[step_m - 1][step_n])) {
					step_m--;
					step++;
					temp.push_back(matrix[step_m][step_n]);
					table[step_m][step_n] = true;
				}
				else {
					flag = 0;
				}
			}
		}
		return temp;
	}
	vector<vector<int>> generateMatrix(int n) {
		vector<vector<int>> temp(n, vector<int>(n, 0));
		if (n == 0) {
			return temp;
		}
		else if (n == 1) {
			vector<int>temp0;
			temp0.push_back(1);
			temp.clear();
			temp.push_back(temp0);
			return temp;
		}
		vector<vector<bool>> table(n, vector<bool>(n, false));
		int flag = 0;//0~3
		int step = 0;//0~m*n-1
		int step_max = n*n;
		int step_m = 0;
		int step_n = -1;
		while (step < step_max) {
			if (flag == 0) {  //右
				if (((step_n + 1) <= (n - 1)) && (!table[step_m][step_n + 1])) {
					step_n++;
					step++;
					temp[step_m][step_n] = step;
					table[step_m][step_n] = true;
				}
				else {
					flag = 1;
				}
			}
			else if (flag == 1) {   //下
				if (((step_m + 1) <= (n - 1)) && (!table[step_m + 1][step_n])) {
					step_m++;
					step++;
					temp[step_m][step_n] = step;
					table[step_m][step_n] = true;
				}
				else {
					flag = 2;
				}
			}
			else if (flag == 2) {   //左
				if (((step_n - 1) >= 0) && (!table[step_m][step_n - 1])) {
					step_n--;
					step++;
					temp[step_m][step_n] = step;
					table[step_m][step_n] = true;
				}
				else {
					flag = 3;
				}
			}
			else if (flag == 3) {   //上
				if (((step_m - 1) >= 0) && (!table[step_m - 1][step_n])) {
					step_m--;
					step++;
					temp[step_m][step_n] = step;
					table[step_m][step_n] = true;
				}
				else {
					flag = 0;
				}
			}
		}
		return temp;
	}
	int fac(int n) {
		if (n == 0) {
			return 1;
		}
		int res = 1;
		for (int i = 1; i <= n; i++) {
			res *= i;
		}
		return res;
	}
	string getPermutation(int n, int k) {
		/*对每层来说分层点为fac(n-1)，分为n层
		该数除以fac(n-1)并向下取整，可以得到第一位的index
		ex:n=4 k=9 permutation=2314   
		fac(n-1)=fac(3)=6
		a[]={1,2,3,4}
		target=k-1=8
		8/6=1 --> a[1]=2（第一位）;
		a[]={1,3,4}
		8%6=2 
		fac(2)=2
		2/2=1  --> a[1]=3（第二位)
		a[]={1,4}
		2%2=0 
		fac(1)=1
		*/
		int target = k - 1;
		vector<int>temp(n, 0);
		int i, index, rest;
		int facn = n - 1;
		string result = "";
		for (i = 0; i < n; i++) {
			temp[i] = i + 1;
		}//赋值temp为1~n
		while (facn>=0) {
			index = target / fac(facn);
			result += to_string(temp[index]);
			temp.erase(temp.begin() + index);
			target = target%fac(facn);
			facn--;
		}
		return result;
	}
};

int main() {
	Solution solu;
	vector<int> solution54, nums;
	Interval inte1(1, 4);
	Interval inte2(4, 5);
	Interval inte3(8, 10);
	Interval inte4(15, 18);
	vector<Interval> solu56;
	vector<vector<int>> d2vec;
	vector<Interval> vecinte;
	string solution60;
	bool solution55;
	int solu58;
	int test = 60;
	switch (test)
	{
	case 54:
		d2vec = { { 1, 2, 3 },{ 4, 5, 6 },{ 7, 8, 9 } };
		d2vec = {};
		solution54 = solu.spiralOrder(d2vec);
		break;
	case 55:
		nums = { 2,3,1,1,4 };
		solution55 = solu.canJump(nums);
		break;
	case 56:
		vecinte.push_back(inte1);
		vecinte.push_back(inte2);
		//vecinte.push_back(inte3);
		//vecinte.push_back(inte4);
		solu56 = solu.merge(vecinte);
		break;
	case 58:
		solu58 = solu.lengthOfLastWord("a ");
		break;
	case 60:
		solution60 = solu.getPermutation(3, 3);
		break;
	default:
		break;
	}
}