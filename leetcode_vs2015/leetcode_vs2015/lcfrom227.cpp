#include<iostream>
#include<stack>
#include<string>
#include<vector>
using namespace std;
class Solution {
public:
	int calculate(string s) {
		vector<char> ops;
		vector<int> nums;
		bool num = false;
		char tmpchar;
		int tempnum = 0;
		int num_left;
		int num_res = 0;
		for (int i = 0; i < s.size(); ++i) {
			tmpchar = s[i];
			if (tmpchar == ' ') {
				continue;
			}
			else if (tmpchar == '*' || tmpchar == '/') {
				num = false;
				nums.push_back(tempnum);
				ops.push_back(tmpchar);
			}
			else if (tmpchar == '+' || tmpchar == '-') {
				num = false;
				nums.push_back(tempnum);
				ops.push_back(tmpchar);
			}
			else {
				if (!num) {
					num = true;
					tempnum = tmpchar - '0';
				}
				else {
					tempnum = tempnum * 10 + tmpchar - '0';
				}
			}
		}
		if (num) {
			nums.push_back(tempnum);
		}
		return 1;
	}
};
int main() {
	Solution solu;
	int res = solu.calculate("31 + 5 / 2");
}