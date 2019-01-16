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
};
int main() {
	int test = 61;
	Solution solu;
	ListNode node1(1);
	ListNode *solu61;
	switch (test)
	{
	case 61:
		solu61 = solu.rotateRight(&node1,1);
		break;
	default:
		break;
	}
}