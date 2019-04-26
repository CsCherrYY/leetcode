#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
class Solution {
public:
	vector<int> simple_select_sort(vector<int>&nums) {
		//��ѡ������ÿ��ѭ���ҳ�һ�������С��ֵ��Ȼ�󽻻�λ��
		//ʱ�临�Ӷ�O(n^2)���Ҳ��ȶ�����
		if (nums.size()<=1) {
			return nums;
		}
		int maxv;
		for (int i = 0; i < nums.size(); ++i) {
			maxv = i;
			for (int j = i; j < nums.size(); ++j) {
				if (nums[j] > nums[maxv]) {
					maxv = j;
				}
			}
			swap(nums[maxv], nums[i]);
		}
		return nums;
	}
	vector<int> bobble_sort(vector<int>&nums) {
		//ð������ͨ�����ڵĽ���ʹ��һ��ѭ�������С����ֵð����
		//O(n^2)���ȶ�����
		if (nums.size()<=1) {
			return nums;
		}
		for (int i = 0; i < nums.size() - 2; ++i) {
			for (int j = nums.size() - 1; j >= i + 1; --j) {
				if (nums[j] > nums[j - 1]) {
					swap(nums[j], nums[j - 1]);
				}
			}
		}
		return nums;
	}
	vector<int> insert_sort(vector<int>&nums) {
		//��������ÿ��ȡ��һ������������������
		//ʱ�临�Ӷ�O(n^2)���ȶ�����
		if (nums.size() <= 1) {
			return nums;
		}
		for (int i = 1; i < nums.size(); ++i) {
			//0~i-1���������Ժ�ð��һ��
			for (int j = i; j >= 1; --j) {
				if (nums[j] > nums[j - 1]) {
					swap(nums[j], nums[j - 1]);
				}
			}
		}
		return nums;
	}
	vector<int> merge_sort(vector<int>&nums) {
		//�鲢���򣬶��֣��ݹ�����������ٺϲ�
		//ʱ�临�Ӷ�O(nlogn)
		if (nums.size() <= 1) {
			return nums;
		}
		sort_merge(nums, 0, nums.size() - 1);
		return nums;
	}
	void sort_merge(vector<int>&nums, int left, int right) {
		if (right - left == 0) {
			return;
		}
		if (right - left == 1) {
			if (nums[left] < nums[right]) {
				swap(nums[left], nums[right]);
			}
			return;
		}
		int mid = left + (right - left) / 2;
		sort_merge(nums, left, mid);
		sort_merge(nums, mid + 1, right);
		sort_merged(nums, left, mid + 1, right);
		return;
	}
	void sort_merged(vector<int>&nums, int start1, int start2,int end) {
		vector<int>temp;
		int work1 = start1;
		int work2 = start2;
		while (work1 < start2&&work2 <= end) {
			if (nums[work1] > nums[work2]) {
				temp.push_back(nums[work1]);
				work1++;
			}
			else {
				temp.push_back(nums[work2]);
				work2++;
			}
		}
		if (work1 == start2) {
			while (work2 <= end) {
				temp.push_back(nums[work2]);
				work2++;
			}
		}
		else if (work2 > end) {
			while (work1 < start2) {
				temp.push_back(nums[work1]);
				work1++;
			}
		}
		for (int i = 0; i < temp.size(); ++i) {
			nums[i + start1] = temp[i];
		}
		return;
	}
	vector<int> quick_sort(vector<int>&nums) {
		//�������򣬰�ѡ���Ԫ�طֳɴ��ں�С�������֣��ٵݹ�
		//O(nlogn)�Ĳ��ȶ�����
		if (nums.size() <= 1) {
			return nums;
		}
		quick(nums, 0, nums.size() - 1);
		return nums;
	}
	void quick(vector<int>&nums, int left, int right) {
		if (left >= right) {
			return;
		}
		if (left + 1 == right) {
			if (nums[left] < nums[right]) {
				swap(nums[left], nums[right]);
			}
			return;
		}
		int loc = findloc(nums, left, right);
		quick(nums, 0, loc - 1);
		quick(nums, loc + 1, right);
		return;
	}
	int findloc(vector<int>&nums,int left,int right) {  //nums.size()>=3
		int ret = 0;
		int pilot = nums[left];
		int work_l = left + 1;
		int work_r = right;
		while (work_l < work_r) {
			while (nums[work_l] >= pilot&& work_l < work_r) {
				work_l++;
			}
			while (nums[work_r] <= pilot && work_l < work_r) {
				work_r--;
			}
			if (work_l != work_r) {
				swap(nums[work_l], nums[work_r]);
			}
		}
		if(work_l == work_r) {
			if (nums[work_l] >= pilot) {
				swap(nums[left], nums[work_l]);
				ret = work_l;
			}
			else {
				swap(nums[left], nums[work_l - 1]);
				ret = work_l - 1;
			}
		}
		return ret;
	}
	vector<int> heap_sort(vector<int>&nums) {
		//������O(nlogn)
		vector<int>res;
		//���һ����Ҷ�ӽڵ�n=nums.size()/2-1
		//��ĳ���ڵ���˵������2n+1���Һ���2n+2
		int length = nums.size();
		while (length) {
			for (int i = length / 2 - 1; i >= 0; --i) {
				if (nums[i] < nums[i * 2 + 1]) {
					swap(nums[i], nums[i * 2 + 1]);
				}
				if ((i * 2 + 2 < length) && nums[i] < nums[i * 2 + 2]) {
					swap(nums[i], nums[i * 2 + 2]);
				}
			}
			res.push_back(nums[0]);
			swap(nums[0], nums[length - 1]);
			length--;
		}
		return res;
	}
};
int main() {
	Solution solu;
	/*vector<int>test = { 8,6,3,6,1,4,5,9,1,3,5,2,6,2,8,4 };
	vector<int>res_select = solu.simple_select_sort(test);
	vector<int>res_bobble = solu.bobble_sort(test);
	vector<int>res_insert = solu.insert_sort(test);
	vector<int>res_merge = solu.merge_sort(test);
	vector<int>res_quick = solu.quick_sort(test);
	vector<int>res_heap = solu.heap_sort(test);*/

	int k = 0;
	return 0;
}