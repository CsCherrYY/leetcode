#include<iostream>
#include<stack>
#include<vector>
using namespace std;
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

	}
};
int main() {
	Solution solu;
	bool solu331 = solu.isValidSerialization("9,3,4,#,#,1,#,#,2,#,6,#,#");
	return 0;
}