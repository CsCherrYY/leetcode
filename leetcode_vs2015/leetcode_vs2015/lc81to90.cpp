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
	bool search(vector<int>& nums, int target) {
		//������o(logn)
		int size = nums.size();
		if (size < 1) {
			return false;
		}
		int low = 0;
		int high = size - 1;
		int mid;
		while (low <= high) {
			mid = (low + high) / 2;
			if (nums[mid] == target) {
				return true;
			}
			// if ǰ��� num[low]>=num[high]>=num[mid]  ���� num[mid]>=num[low]>=num[high]
			if ((nums[low] == nums[mid]) && (nums[mid] == nums[high])) {
				low++;
				high--;
			}
			else if (nums[mid] >= nums[low]) {   //�ֽ���ں���  ���������˼���33�е㲻һ����Ҫ���һ��
				if ((nums[low] <= target) && (nums[mid] > target)) {
					high = mid - 1;
				}
				else {
					low = mid + 1;
				}
			}
			else {
				if ((nums[mid] < target) && (nums[high] >= target)) {
					low = mid + 1;
				}
				else {
					high = mid - 1;
				}
			}
		}
		return false;
	}
	ListNode* deleteDuplicates_mid(ListNode* head) {
		if (!head || !(head->next)) {
			return head;
		}
		ListNode *newnode = new ListNode(0);
		newnode->next = head;
		ListNode* pre = newnode;
		ListNode* end = newnode->next;
		int step = 0;
		while (end&&end->next != NULL) {
			while (end->next&&end->val == end->next->val) {
				step++;
				end = end->next;
			}//end��ͬ���������һ��ָ��
			if (step > 0) {
				pre->next = end->next;
				end = end->next;
				step = 0;
			}
			else {
				pre = end;
				end = end->next;
			}
		}
		return newnode->next;
	}
	ListNode* deleteDuplicates(ListNode* head) {
		if (!head || !(head->next)) {
			return head;
		}
		ListNode *pre = head;
		ListNode *work = head->next;
		while (work != NULL) {
			if (pre->val == work->val) {
				pre->next = work->next;
				work = work->next;
			}
			else {
				pre = work;
				work = work->next;
			}
		}
		return head;
	}
	int largestRectangleArea(vector<int>& heights) {
		//��ؼ���һ��˼�룬���������Ĳ��ֲ����ܳ�Ϊ�����ε��յ�
		vector<int> index;
		heights.push_back(0); //С���ɣ�����߽�����
		int i, indexnew, h, maxsqre;
		maxsqre = 0;
		for (i = 0; i < heights.size(); i++) {
			while (!index.empty() && heights[index.back()] >= heights[i]) {
				h = heights[index.back()];
				index.pop_back();
				indexnew = index.size() > 0 ? index.back() : -1;
				maxsqre = max(maxsqre, h*(i - indexnew - 1));
			}
			index.push_back(i);
		}
		return maxsqre;
	}
};
int main() {
	int test = 82;
	Solution solu;
	ListNode *newnode = new ListNode(1);
	ListNode *newnode1 = new ListNode(1);
	ListNode *solu82;
	newnode->next = newnode1;
	bool solu81;
	switch (test)
	{
	case 81:
		//solu81 = solu.search({ 2,5,6,0,0,1,2 }, 0);
		break;
	case 82:
		solu82 = solu.deleteDuplicates_mid(newnode);
		break;
	default:
		break;
	}
	return 0;
}