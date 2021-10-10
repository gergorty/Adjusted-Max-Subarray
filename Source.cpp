// A Divide and Conquer based program for maximum subarray
// sum problem
#include <limits.h>
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

// A utility function to find maximum of two integers
int max(int a, int b) { return (a > b) ? a : b; }

// A utility function to find maximum of three integers
int max(int a, int b, int c) { return max(max(a, b), c); }

// Find the maximum possible sum in arr[] auch that arr[m]
// is part of it
int maxCrossingSum(int arr[], int l, int m, int h)
{
	// Include elements on left of mid.
	int sum = 0;
	int left_sum = INT_MIN;
	for (int i = m; i >= l; i--) {
		sum = sum + arr[i];
		if (sum > left_sum)
			left_sum = sum;
	}

	// Include elements on right of mid
	sum = 0;
	int right_sum = INT_MIN;
	for (int i = m + 1; i <= h; i++) {
		sum = sum + arr[i];
		if (sum > right_sum)
			right_sum = sum;
	}


	// Return sum of elements on left and right of mid
	// returning only left_sum + right_sum will fail for
	// [-2, 1]
	return max(left_sum + right_sum, left_sum, right_sum);
}

// Returns sum of maximum sum subarray in aa[l..h]
int maxSubArraySum(int arr[], int l, int h, vector<int> &x)
{
	// Base Case: Only one element
	if (l == h)
		return arr[l];

	// Find middle point
	int m = (l + h) / 2;


	x.push_back(max(maxSubArraySum(arr, l, m, x), maxSubArraySum(arr, m + 1, h, x),
		maxCrossingSum(arr, l, m, h)));


	//l is the beginning of the whole array
	//m is the beginning point of the sum
	//h is the end of the whole array

	x.push_back(m+1); //left of the array
	x.push_back(l+1);
	x.push_back(h+1);

	/* Return maximum of following three possible cases
			a) Maximum subarray sum in left half
			b) Maximum subarray sum in right half
			c) Maximum subarray sum such that the subarray
	crosses the midpoint */
	return max(maxSubArraySum(arr, l, m, x),
		maxSubArraySum(arr, m + 1, h, x),
		maxCrossingSum(arr, l, m, h));
}

/*Driver program to test maxSubArraySum*/
int main()
{
	int arr[] = { -2, 3, -4, 5, 7, -6 };
	vector<int> memoize;
	int n = sizeof(arr) / sizeof(arr[0]);
	int max_sum = maxSubArraySum(arr, 0, n - 1, memoize);
	int z = sizeof(memoize) / sizeof(memoize[0]);
	printf("Maximum contiguous sum is %d\n", max_sum);
	getchar();


	return 0;
}
