#include<iostream>
#include<string>
#include<vector>
using namespace std;
class Solution {
public:
	void reverseWords(string &s) {
		//�����ַ���������ǰ����ߺ����������Ŀո񣬵��Ƿ�ת����ַ����ܰ�����
		//����������ʼ��ж���Ŀո񣬽���ת�󵥴ʼ�Ŀո���ٵ�ֻ��һ����
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