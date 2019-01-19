#include<iostream>
#include<string>
#include<vector>
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

	}
};
int main() {
	int test = 71;
	Solution solu;
	string solu71;
	switch (test)
	{
	case 71:
		solu71 = solu.simplifyPath("/a//b////c/d//././/..");
		break;
	default:
		break;
	}
}