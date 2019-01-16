#include<iostream>

using namespace std;

int main() {
	int k;
	int i = 0;
	int c = i + 1;
	int *p = &i;
	int test = 0;
	cout << i << endl;
	if (test == 0) {
		cout << (*++p) << endl;
	}
	else {
		cout << (*p++) << endl;
	}
	cout << (*p)+1 << endl;
	i = 1;
	system("pause");
	return 0;
}