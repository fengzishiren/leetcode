/*
Maximum Product Subarray

Find the contiguous subarray within an array (containing at least one number) which has the largest product.

For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6.
 */

#include <iostream>
/**
 *
 *
 * Find the contiguous subarray within an array (containing at least one number) which has the largest product.
 *
 * For example, given the array [2,3,-2,4],
 * the contiguous subarray [2,3] has the largest product = 6.
 *
 */
/*
 * 思路：暴力循环
 * 对于每一个数，算出和它连续的后面数字的乘积
 *
 *
 *
 *
 */
int maxProduct(int A[], int n) {
	int max = 0;
	for (int i = 0; i < n; i++) {
		int x = A[i];
		if (i + 1 < n)
			for (int j = i + 1; j < n; j++) {
				x *= A[j];
				if (x > max) {
					max = x;
				}
			}
		else if (x > max) {
			max = x;
		}
	}
	return max;
}
/*
 * 动态规划：
 * 具体解法如下：
 * 假设数组为a[]，直接利用动归来求解，考虑到可能存在负数的情况，我们用Max来表示以a结尾的最大连续子串的乘积值，用Min表示以a结尾的最小的子串的乘积值，那么状态转移方程为：
 *
 *  Max=max{a, Max[i-1]*a, Min[i-1]*a};
 *  Min=min{a, Max[i-1]*a, Min[i-1]*a};
 *
 *  初始状态为Max[1]=Min[1]=a[1]。
 *
 */
int maxProduct1(int A[], int n) {
	int *maxA = new int[n];
	int *minA = new int[n];
	int value = maxA[0] = minA[0] = A[0];
	for (int i = 1; i < n; ++i) {
		//求 A[i], maxA[i-1]*A[i], minA[i-1]*A[i]的最大值
		maxA[i] = std::max(std::max(A[i], maxA[i - 1] * A[i]),
				minA[i - 1] * A[i]);
		minA[i] = std::min(std::min(A[i], maxA[i - 1] * A[i]),
				minA[i - 1] * A[i]);
		value = std::max(maxA[i], value);
	}
	delete[] maxA;
	delete[] minA;
	return value;
}


/*
LeetCode Online:

Maximum Product Subarray My Submissions Question Solution
Besides keeping track of the largest product, we also need to keep track of the smallest product. Why? The smallest product, which is the largest in the negative sense could become the maximum when being multiplied by a negative number.

Let us denote that:

f(k) = Largest product subarray, from index 0 up to k.
Similarly,

g(k) = Smallest product subarray, from index 0 up to k.
Then,

f(k) = max( f(k-1) * A[k], A[k], g(k-1) * A[k] )
g(k) = min( g(k-1) * A[k], A[k], f(k-1) * A[k] )
There we have a dynamic programming formula. Using two arrays of size n, we could deduce the final answer as f(n-1). Since we only need to access its previous elements at each step, two variables are sufficient.

public int maxProduct(int[] A) {
   assert A.length > 0;
   int max = A[0], min = A[0], maxAns = A[0];
   for (int i = 1; i < A.length; i++) {
      int mx = max, mn = min;
      max = Math.max(Math.max(A[i], mx * A[i]), mn * A[i]);
      min = Math.min(Math.min(A[i], mx * A[i]), mn * A[i]);
      maxAns = Math.max(max, maxAns);
   }
   return maxAns;
}
 */
int maxProduct2(int A[], int n) {
	int max = A[0], min = A[0], maxAns = A[0];
	for (int i = 1; i < n; ++i) {
	 int mx = max, mn = min;
	 max = std::max(std::max(A[i], mx * A[i]), mn * A[i]);
	 min = std::min(std::min(A[i], mx * A[i]), mn * A[i]);
	 maxAns = std::max(max, maxAns);
	}
	return maxAns;
}

int _main() {
	int A[] = { 2, 3, -2, 4 };
	std::cout << maxProduct(A, 4) << std::endl;
	return 0;
}
