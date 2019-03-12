#include<iostream>
#include<stack>
#include<set>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
	bool isValidSerialization(string preorder) {
		if (preorder == "#") {
			return true;
		}
		stack<bool> chars;
		chars.push(true);
		vector<string> strs;
		string temp;
		for (auto it : preorder) {
			if (it == ',') {
				strs.push_back(temp);
				temp.clear();
			}
			else {
				temp += it;
			}
		}
		strs.push_back(temp);
		for (auto it : strs) {
			if (it != "#") {
				if (chars.empty()) {
					return false;
				}
				chars.pop();
				chars.push(true);
				chars.push(true);
			}
			else {
				if (chars.empty()) {
					return false;
				}
				chars.pop();
			}
		}
		if (chars.empty()) {
			return true;
		}
		return false;
	}
	vector<string> findItinerary(vector<pair<string, string>> tickets) {
		//矩阵建图
		set<string> airs;
		vector<string> res;
		for (auto t : tickets) {
			airs.insert(t.first);
			airs.insert(t.second);
		}
		int size = airs.size();
		map<string, int>maps;
		auto it = airs.begin();
		for (int i = 0; i < size; ++i) {
			maps.insert(pair<string, int>(*it, i));
			it++;
		}
		vector<vector<bool>>table(size, vector<bool>(size, false));
		for (auto t : tickets) {
			table[maps[t.first]][maps[t.second]] = true;
		}
		//深度遍历
		res = DFS(maps, table,tickets.size());
		return res;
	}
	vector<string> DFS(map<string, int> &maps, vector<vector<bool>> &table,int size0) {
		int now;
		for (auto t : maps) {
			if (t.first == "JFK") {
				now = t.second;
				break;
			}
		}
		vector<string> res;
		vector<int>resint;
		map<int,int>visit;
		//visit.insert(make_pair(now, 1));
		vector<int>temp(maps.size(), 0);
		DFSwork(size0,table, temp, resint, visit, now);
		resint.insert(resint.begin(), now);
		map<int,string>rev;
		for (auto it : maps) {
			rev.insert(make_pair(it.second, it.first));
		}
		for (auto it : resint) {
			res.push_back(rev[it]);
		}
		return res;
	}
	void DFSwork(int size0,vector<vector<bool>> &table, vector<int>&temp, vector<int> &res,map<int,int>&visit, int now) {
		if (visit.size()== size0) {
			return;
		}
		for (int i = temp[now]; i < temp.size(); ++i) {
			if (table[now][i] == true) {   //now->i 一条线路
				temp[now] = i;  //更新temp
				visit.insert(make_pair(now, i));//visit i
				res.push_back(i);
				DFSwork(size0,table, temp, res, visit, i);  //更新now
				if (visit.size() == size0) {
					return;
				}
				res.pop_back();
				auto it = visit.find(now);
				visit.erase(it);
			}
		}
	}
	bool increasingTriplet(vector<int>& nums) {
		//递增的三元子序列
		//if i>=j  i无用
		//if i<j  
		if (nums.size() < 3) {
			return false;
		}
		int num1, num2, num3, point;
		point = 0;
		for (int i = 0; i < nums.size(); ++i) {
			if (point == 0) {
				num1 = nums[i];
				point = 1;
			}
			else if (point == 1) {
				if (num1 >= nums[i]) {
					num1 = nums[i];
				}
				else {
					num2 = nums[i];
					point = 2;
				}
			}
			else if(point==2){   //point==2
				if (num2 < nums[i]) {
					return true;
				}
				else if (nums[i] == num2) {
					continue;
				}
				else if (nums[i]<num2&&nums[i]>num1) {
					num2 = nums[i];
				}
				else if (nums[i] <= num1) {
					num3 = nums[i];
					point = 3;
				}
			}
			else {
				if (nums[i] > num2) {
					return true;
				}
				else if (nums[i] == num2) {
					point = 2;
				}
				else if (nums[i] >= num3) {
					num1 = num3;
					num2 = nums[i];
					point = 2;
				}
				else if (nums[i] < num3) {
					num3 = nums[i];
				}
			}
		}
		return false;
	}
	int rob(TreeNode* root) {
		map<TreeNode*, int>truedp,falsedp;
		if (!root) {
			return 0;
		}
		int tmpt = robdp(root->left, true, truedp, falsedp) + robdp(root->right, true, truedp, falsedp);
		int tmpf= robdp(root->left, false, truedp, falsedp) + robdp(root->right, false, truedp, falsedp);
		return max(root->val + tmpf, tmpt);
	}
	int robdp(TreeNode* root, bool sign, map<TreeNode*, int>&truedp, map<TreeNode*, int>&falsedp) {
		if (!root) {
			return 0;
		}
		if (sign) {
			auto it = truedp.find(root);
			if (it != truedp.end()) {
				return it->second;
			}
		}
		else {
			auto it = falsedp.find(root);
			if (it != falsedp.end()) {
				return it->second;
			}
		}
		int maxv;
		int tmpt = robdp(root->left, true, truedp, falsedp) + robdp(root->right, true, truedp, falsedp);
		int tmpf = robdp(root->left, false, truedp, falsedp) + robdp(root->right, false, truedp, falsedp);
		if (sign) {
			maxv = max(tmpf + root->val, tmpt);
			truedp.insert(make_pair(root, maxv));
		}
		else {
			maxv = max(tmpf , tmpt);
			falsedp.insert(make_pair(root, maxv));
		}
		return maxv;
	}
	vector<int> countBits(int num) {
		vector<int> res;
		res.push_back(0);
		for (int i = 1; i <= num; i++) {
			if (i % 2 == 0) {
				res.push_back(res[i / 2]);
			}
			else {
				res.push_back(res[i / 2] + 1);
			}
		}
		return res;
	}
	bool isPowerOfFour(int num) {
		if (num < 0 || num & (num - 1)) {//check(is or not) a power of 2.
			return false;
		}
		return num & 0x55555555;//check 1 on odd bits
	}
};
int main() {
	Solution solu;
	bool solu331 = solu.isValidSerialization("9,3,4,#,#,1,#,#,2,#,6,#,#");
	//vector<string>temp = solu.findItinerary(vector<pair<string, string>>{make_pair("JFK", "SFO"), make_pair("JFK", "ATL"), make_pair("SFO", "ATL"), make_pair("ATL", "JFK"), make_pair("ATL", "SFO")});
	bool solu334 = solu.increasingTriplet(vector<int>{1, 2, 3, 4, 5});
	return 0;
}