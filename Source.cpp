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
int maxCrossingSum(int arr[], int l, int m, int h, int& z, int& r,int &counter, vector<int> &lVec,
	vector<int> &rVec, vector<int> &sumVec)
{
	// Include elements on left of mid.
	int sum = 0;
	int left_sum = INT_MIN;
	for (int i = m; i >= l; i--) {
		counter++;
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
		counter++;
		if (sum > right_sum) 
		{
			right_sum = sum;
			r = m + (i-m);
		}
	}

	lVec.push_back(z);
	rVec.push_back(r);
	sumVec.push_back(right_sum + left_sum);

	return max(left_sum + right_sum, left_sum, right_sum); //this gives the next function the "slice of the array
	//to parse"
}

// Returns sum of maximum sum subarray in aa[l..h]
int maxSubArraySum(int arr[], int l, int h, int &z, int &r, int& counter, vector<int>& lVec,
	vector<int>& rVec, vector<int>& sumVec)
{
	// Base Case: Only one element
	if (l == h)
		return arr[l];

	int m = (l + h) / 2;

	return max(maxSubArraySum(arr, l, m, z, r,counter, lVec,rVec,sumVec),
		maxSubArraySum(arr, m + 1, h, z, r, counter, lVec, rVec, sumVec),
		maxCrossingSum(arr, l, m, h, z, r, counter, lVec, rVec, sumVec));
}

/*Driver program to test maxSubArraySum*/
int main()
{
	vector<int> lVec, rVec, sumVec;
	int counter = 0;
	int arr[] = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
	int z = 0;
	int r = 0;

	int n = sizeof(arr) / sizeof(arr[0]);
	int max_sum = maxSubArraySum(arr, 0, n - 1, z, r,counter,lVec,rVec,sumVec);

	for (int i = 0; i < rVec.size(); i++)
	{
		if (sumVec[i] == max_sum)
		{
			cout << "L index: " << lVec[i] << " R index: " << rVec[i] << " counter: " << counter << endl;
		}
	}

	printf("Maximum contiguous sum is %d\n", max_sum);
	getchar();


	return 0;
}
