#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
	int minDistance(string word1, string word2) {
		//problem 72
		//dp[i][j] ��ʾstr1[0:i]��str2[0:j]��mindist
		if (!word1.length) {
			return word2.length();
		}
		if (!word2.length()) {
			return word1.length();
		}
		vector<vector<int>>dp(word1.length(), vector<int>(word2.length(), 0));
	}
};
int main() {
	return 0;
}