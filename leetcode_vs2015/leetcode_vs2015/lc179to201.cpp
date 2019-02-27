#include<vector>
#include<map>
#include<algorithm>
#include<string>
using namespace std;
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
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
	vector<string> findRepeatedDnaSequences(string s) {
		vector<string>result;
		map<string, int> table;
		if (s.length() < 10) {
			return result;
		}
		int i;
		string temp;
		for (i = 0; i <= s.length() - 10; ++i) {
			temp = s.substr(i, 10);
			auto s = table.find(temp);
			if (s == table.end()) {
				table.insert(pair<string, int>(temp, 1));
			}
			else {
				table[temp]++;
			}
		}
		map<string, int>::iterator k;
		for (auto t : table) {
			if (t.second > 1) {
				result.push_back(t.first);
			}
		}
		return result;
	}
	void rotate(vector<int>& nums, int k) {
		//方法1：右移1步k次
		//方法2：数组分成两部分,分别rotate在rotate，这种最快
		if (nums.size() <= 1) {
			return;
		}
		if (nums.size() < k) {
			k %= nums.size();
		}
		int method = 2;
		switch (method)
		{
		case 1:
			for (int i = 0; i < k; i++) {
				rotateone(nums);
			}
			break;
		case 2:
			reversecs(nums, 0, nums.size() - k - 1);
			reversecs(nums, nums.size() - k, nums.size() - 1);
			reversecs(nums, 0, nums.size() - 1);
			break;
		default:
			break;
		}
		return;
	}
	void reversecs(vector<int>& nums, int left, int right) {
		reverse(nums.begin() + left, nums.begin() + right + 1);
		return;
	}
	void rotateone(vector<int>& nums) {
		if (nums.size() <= 1) {
			return;
		}
		int temp = nums[nums.size() - 1];
		nums.pop_back();
		nums.insert(nums.begin(), temp);
		return;
	}
	uint32_t reverseBits(uint32_t n) {
		uint32_t temp = 0;
		for (int i = 0; i < 32; ++i) {
			temp += n & 1;          //n%2  ===== n&1
			n = n >> 1;
			temp = temp << 1;
		}
		return temp;
	}
	int hammingWeight(uint32_t n) {
		int ans = 0;
		while (n)
		{
			ans += n % 2;
			n >>= 1;
		}
		return ans;
	}
	map<int, int>dp198;
	int rob(vector<int>& nums) {
		/*如果1 2都不取 那么肯定小于1取2不取
		所以两种情况，1取，或者2取
		*/
		if (!nums.size()) {
			return 0;
		}
		if (nums.size() == 1) {
			return nums[0];
		}
		if (nums.size() == 2) {
			return max(nums[0], nums[1]);
		}
		return robdp(nums, 0);
	}
	int robdp(vector<int>& nums, int left) {
		auto s = dp198.find(left);  //dp存储格式：pair<int1,int2> int1:left int2:maxvalue
		if (s != dp198.end()) {
			return s->second;
		}
		if (left >= nums.size()) {
			return 0;
		}
		if (left == nums.size() - 1) {
			return nums[nums.size() - 1]; //只能取这个了
		}
		int temp1 = nums[left] + robdp(nums, left + 2);   //取了1
		int temp2 = nums[left + 1] + robdp(nums, left + 3); //取了2
		int res = max(temp1, temp2);
		dp198.insert(pair<int, int>(left, res));
		return res;
	}
	vector<int> rightSideView(TreeNode* root) {
		//二叉树的右视图->层次遍历
		int next = 0;
		int number = 1;
		vector<TreeNode*>queues;
		vector<int>result;
		if (!root) {
			return result;
		}
		queues.push_back(root);
		TreeNode*work = root;
		while (!queues.empty()) {
			work = queues[0];
			if (work->left) {
				++next;
				queues.push_back(work->left);
			}
			if (work->right) {
				++next;
				queues.push_back(work->right);
			}
			--number;
			if (number == 0) {
				result.push_back(work->val);
				number = next;
				next = 0;
			}
			queues.erase(queues.begin());
		}
		return result;
	}
	int numIslands(vector<vector<char>>& grid) {
		//BFS for graph
		int size_h = grid.size();
		if (!size_h) {
			return 0;
		}
		int size_w = grid[0].size();
		if (!size_w) {
			return 0;
		}
		int island = 0;
		vector<vector<bool>> tf(size_h, vector<bool>(size_w, false));
		for (int i = 0; i < size_h; ++i) {
			for (int j = 0; j < size_w; ++j) {
				if (tf[i][j] == false&&grid[i][j]=='1') {
					travel(grid, tf, i, j);
					island++;
				}
			}
		}
		return island;
	}
	void travel(vector<vector<char>>& grid, vector<vector<bool>>& tf, int i, int j) {
		int size_h = grid.size();
		int size_w = grid[0].size();
		if (i < 0 || i >= size_h) {
			return;
		}
		if (j < 0 || j >= size_w) {
			return;
		}
		if (tf[i][j] == true || grid[i][j] == '0') {
			return;
		}
		tf[i][j] = true;
		travel(grid, tf, i - 1, j);
		travel(grid, tf, i + 1, j);
		travel(grid, tf, i, j - 1);
		travel(grid, tf, i, j + 1);
		return;
	}
	int rangeBitwiseAnd(int m, int n) {
		//k为偶数的时候 k&k+1=k ---> 只要m不等于n 最后一位等于0 继续递归下一位
		if (!m) {
			return 0;
		}
		if (m != n) {
			return rangeBitwiseAnd(m >> 1, n >> 1) << 1;
		}
		else {
			return (rangeBitwiseAnd(m >> 1, n >> 1) << 1) + m % 2;
		}
	}
};
int main() {
	Solution solu;
	vector<int>test155 = { 824,938,1399,5607,6973,5703,9609,4398,8247 };
	int test201;
	int test = 201;
	switch (test)
	{
	case 155:
		solu.fastsort(test155);
		break;
	case 201:
		test201 = solu.rangeBitwiseAnd(5, 7);
		break;
	default:
		break;
	}
	int i = 1;
}