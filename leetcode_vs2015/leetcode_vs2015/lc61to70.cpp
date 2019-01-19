#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
	ListNode* rotateRight(ListNode* head, int k) {
		if (!k || head == NULL) {
			return head;
		}
		ListNode *p = head;
		ListNode *q = head;
		ListNode *temp = head;
		int count = 0;
		while (count < k) {
			count++;
			q = q->next;
			if (q == NULL) {
				q = head;
			}
		}
		while (q->next != NULL) {
			p = p->next;
			q = q->next;
		}
		temp = (p->next) ? p->next : head;//ret
		p->next = NULL;
		q->next = head;
		return temp;
	}
	int uniquePaths(int m, int n) {
		vector<vector<int>>dp(m, vector<int>(n, 0));
		int i, j;
		for (i = 0; i < n; i++) {
			dp[0][i] = 1;
		}
		for (i = 0; i < m; i++) {
			dp[i][0] = 1;
		}
		for (i = 0; i < m; i++) {
			for (j = 0; j < n; j++) {
				if (dp[i][j] == 0) {
					dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
				}
			}
		}
		return dp[m - 1][n - 1];
	}
	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
		int m = obstacleGrid.size();
		if (m == 0) {
			return 0;
		}
		int n = obstacleGrid[0].size();
		vector<vector<int>>dp(m, vector<int>(n, 0));
		int i, j;
		int safe = 1;
		for (i = 0; i < n; i++) {
			if (obstacleGrid[0][i] == 1) {
				safe = 0;
			}
			dp[0][i] = safe;
		}
		safe = 1;
		for (i = 0; i < m; i++) {
			if (obstacleGrid[i][0] == 1) {
				safe = 0;
			}
			dp[i][0] = safe;
		}
		for (i = 1; i < m; i++) {
			for (j = 1; j < n; j++) {
				if (obstacleGrid[i][j] == 1) {
					dp[i][j] = 0;
				}
				else if (dp[i][j] == 0) {
					dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
				}
			}
		}
		return dp[m - 1][n - 1];
	}
	int minPathSum(vector<vector<int>>& grid) {
		int m = grid.size();
		if (m == 0) {
			return 0;
		}
		int n = grid[0].size();
		vector<vector<int>>dp(m, vector<int>(n, 0));
		int i, j;
		int startval = 0;
		for (i = 0; i < n; i++) {
			startval += grid[0][i];
			dp[0][i] = startval;
		}
		startval = 0;
		for (i = 0; i < m; i++) {
			startval += grid[i][0];
			dp[i][0] = startval;
		}
		for (i = 1; i < m; i++) {
			for (j = 1; j < n; j++) {
				dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
			}
		}
		return dp[m - 1][n - 1];
	}
	vector<int> plusOne(vector<int>& digits) {
		int size = digits.size();
		if (size == 0) {
			return digits;
		}
		int sign = 0;  //全进位
		int i;
		for (i = 0; i < size; i++) {
			if (digits[i] != 9) {
				sign = 1;
			}
		}
		if (sign == 0) {
			vector<int> temp(size + 1, 0);
			temp[0] = 1;
			return temp;
		}
		for (i = size - 1; i >= 0; i--) {
			if (digits[i] < 9) {
				digits[i] += 1;
				break;
			}
			else {
				digits[i] = 0;
			}
		}
		return digits;
	}
	string addBinary(string a, string b) {
		int len_a = a.length();
		int len_b = b.length();
		if (!len_a) {
			return b;
		}
		else if (!len_b) {
			return a;
		}
		if (len_a > len_b) {
			return addBinary(b, a); //保证a短
		}
		int i;
		int diff = len_b - len_a;
		int add = 0;
		string temp = b;
		for (i = len_a - 1; i >= 0; i--) {
			temp[i + diff] += (a[i] - '0');
		}
		for (i = len_b - 1; i >= 0; i--) {
			temp[i] += add;
			add = 0;
			if (temp[i] >= '2') {
				temp[i] = temp[i] - 2;
				add = 1;
			}
		}
		if (add) {
			temp.insert(0, "1");
		}
		return temp;
	}
	int mySqrt(int x) {  //x>=1
		if (x == 1 || x == 2 || x == 3) {
			return 1;
		}
		long long i = x;
		long long low = 1;
		long long high = x;
		long long temp, tempplus1;   //low和high也要用longlong
		while (1) {
			temp = i * i;
			tempplus1 = (i + 1)*(i + 1);
			if (temp <= x && tempplus1 > x) {
				return i;
			}
			else if (temp > x) {
				high = i + 1;
			}
			else if (tempplus1 <= x) {
				low = i;
			}
			i = (low + high) / 2;
		}
	}
	int climbStairs(int n) {
		vector<int>dp(n, 0);
		dp[0] = 1;  //1->1
		dp[1] = 2;  //2->2;
		int i;
		for (i = 2; i < n; i++) {
			dp[i] = dp[i - 1] + dp[i - 2];
		}
		return dp[n - 1];
	}
};
int main() {
	int test = 69;
	Solution solu;
	ListNode node1(1);
	ListNode *solu61;
	int solu69;
	switch (test)
	{
	case 61:
		solu61 = solu.rotateRight(&node1,1);
		break;
	case 69:
		solu69 = solu.mySqrt(2147395599);
		break;
	default:
		break;
	}
}