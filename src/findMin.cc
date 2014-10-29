/*
 Find Minimum in Rotated Sorted Array
 Suppose a sorted array is rotated at some pivot unknown to you beforehand.

 (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

 Find the minimum element.

 You may assume no duplicate exists in the array.
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
//	bool isMin(vector<int>& num, int idx) {
//		return num[idx] < num[idx - 1] && num[idx] < num[idx + 1];
//	}
//	int findMin(vector<int> &num) {
//		int start = 0;
//		int end = num.size() - 1;
//		while (start <= end) {
//			int mid = start + (end - start) / 2;
//			cout << start << ' ' << mid << ' ' << end << endl;
//			if (isMin(num, mid))
//				return num[mid];
////			else if (isMin(num, start))
////				return num[start];
////			else if (isMin(num, end))
////				return num[end];
//			else if (num[start] <= num[mid]) {
//				start = mid + 1;
//			} else {
//				end = mid - 1;
//			}
//		}
//		return -1;
//	}

	int findMin(vector<int> &num) {
		int n = num.size();
		int start = 0, end = n - 1;
		while (num[start] > num[end]) {
			int mid = (start + end) >> 1;
			if (num[start] <= num[mid])
				start = mid + 1;
			else if (num[mid] < num[end])
				end = mid;
		}
		return num[start];
	}
};

int main(int argc, char **argv) {
	vector<int> num = { 4, 5, 6, 7, 0, 1, 2 };
	cout << Solution().findMin(num);

	return 0;
}

