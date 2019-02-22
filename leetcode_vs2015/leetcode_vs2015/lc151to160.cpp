#include<iostream>
#include<string>
#include<vector>
using namespace std;
class Solution {
public:
	void reverseWords(string &s) {
		//输入字符串可以在前面或者后面包含多余的空格，但是反转后的字符不能包括。
		//如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。
		vector<string>words;
		if (s == "") {
			return;
		}
		char* work_s = &s[0];
		char* work_e = &s[s.length() - 1];
		int start = 0;
		int end = s.length();
		while (*work_s == ' ') {
			work_s++;
			start++;
		}
		while (*work_e == ' ') {
			work_e--;
			end--;
		}
		string s_new = s.substr(start, end - start);

	}
};
int main() {
	return 0;
}