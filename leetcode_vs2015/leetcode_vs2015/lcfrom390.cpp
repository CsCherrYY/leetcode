#include<iostream>
using namespace std;
class Solution {
public:
	int lastRemaining(int n) {
		//nÎªÆæÊý
		if (n == 1) {
			return 1;
		}
		else {
			return 2 * (1 + n / 2 - lastRemaining(n / 2));
		}
	}
	bool isSubsequence(string s, string t) {
		if (!s.length()) {
			return true;
		}
		if (!t.length()) {
			return false;
		}
		int points = 0;
		int pointt = 0;
		while (points < s.length()) {
			while (t[pointt] != s[points]) {
				pointt++;
				if (pointt == t.length()) {
					return false;
				}
			}
			points++;
			if (points == s.length()) {
				return false;
			}
			pointt++;
			if (pointt == t.length()) {
				return false;
			}
		}
		return true;
	}
	string decodeString(string s) {

	}
};
int main() {
	return 0;
}