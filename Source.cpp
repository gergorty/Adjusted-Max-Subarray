// A Divide and Conquer based program for maximum subarray
// sum problem
#include <limits.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// A utility function to find maximum of two integers
int max(int a, int b) { return (a > b) ? a : b; }

// A utility function to find maximum of three integers
int max(int a, int b, int c) { return max(max(a, b), c); }

// Find the maximum possible sum in arr[] auch that arr[m]
// is part of it
int maxCrossingSum(int arr[], int l, int m, int h, int& z, int& r)
{
	// Include elements on left of mid.
	int sum = 0;
	int left_sum = INT_MIN;
	for (int i = m; i >= l; i--) {
		sum = sum + arr[i];
		if (sum > left_sum) {
			
			left_sum = sum;
			z = i;	
		}
	}

	r = m;
	sum = 0;
	int right_sum = INT_MIN;
	for (int i = m + 1; i <= h; i++) {
		sum = sum + arr[i];
	
		if (sum > right_sum) 
		{
			right_sum = sum;
			r = m + (i-m);
		}
	}

	cout << setw(10) << left <<"index L: " << setw(5) << left << m - l 
		<< setw(10) << left << " left sum:  " << setw(5) << left << left_sum 
		<< setw(10) << left <<"   index R:  " << setw(5) << left <<r 
		<< setw(10) << left << " Right sum: " << setw(5) << left << right_sum 
		<< setw(10) << left << "   Totals:    " << setw(5) << left << right_sum + left_sum << endl;
	// Return sum of elements on left and right of mid
	// returning only left_sum + right_sum will fail for
	// [-2, 1]
	return max(left_sum + right_sum, left_sum, right_sum); //this gives the next function the "slice of the array
	//to parse"
}

// Returns sum of maximum sum subarray in aa[l..h]
int maxSubArraySum(int arr[], int l, int h, int &z, int &r)
{
	// Base Case: Only one element
	if (l == h)
		return arr[l];

	int m = (l + h) / 2;

	return max(maxSubArraySum(arr, l, m, z, r),
		maxSubArraySum(arr, m + 1, h, z, r),
		maxCrossingSum(arr, l, m, h, z, r));
}

/*Driver program to test maxSubArraySum*/
int main()
{
	int arr[] = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
	int z = 0;
	int r = 0;

	int n = sizeof(arr) / sizeof(arr[0]);
	int max_sum = maxSubArraySum(arr, 0, n - 1, z, r);
	printf("Maximum contiguous sum is %d\n", max_sum);
	getchar();


	return 0;
}
