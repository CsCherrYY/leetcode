#include<vector>
#include<map>
using namespace std;
class Solution {
public:
	vector<int> twoSum(vector<int>& numbers, int target) {
		vector<int> res;
		map<int, int> maps;
		int i;
		for (i = 0; i < numbers.size(); i++) {
			auto it = maps.find(numbers[i]);
			if (it == maps.end()) {
				maps.insert(pair<int, int>(target - numbers[i], i));
			}
			else {
				res.push_back(it->second + 1);
				res.push_back(i + 1);
			}
		}
		return res;
	}
};
int main() {
	return 0;
}