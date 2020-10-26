/*
Q. The Maximum Sub-array Sum problem is to find the sub-array (A sub-array of the array A [0 … N-1] is A[i…j] where 0 = i = j < N ) for which the sum of its elements is maximum. For example, given an array {12, -13, -5, 25, -20, 30, 10}, the maximum sub-array sum is 45 for sub-array {25, -20, 30, 10}.
Find the subarray from an array which gives the maximum sum, using Divide & Conquer. The subarray elements should be contiguous.
1. Divide the given array in two halves.
2. Return the maximum of the following:
a) Maximum sub-array sum in the left half (Make a recursive call).
b) Maximum sub-array sum in the right half (Make a recursive call).
c) Maximum subarray sum such that the subarray crosses the midpoint.
*/

#include<stdio.h>
#include<stdlib.h>

int maxAmongThree(int a, int b, int c){
	int x = (a > b)? a:b;
	return (x > c)? x:c;
}

int maxSubArr(int *arr, int lb, int ub){
	if(lb == ub) return arr[lb];
	int mid = (lb + ub)/2;
	return maxAmongThree(maxSubArr(arr, lb, mid), findMaxSum(arr, lb, mid, ub), maxSubArr(arr, mid+1, ub));
}

int findMaxSum(int *arr, int l, int m, int u){
	int i, s = 0, t1 = -32000, t2 = -32000;
	for(i = m; i >= l; i--){
		s = s + arr[i];
		if(s > t1) t1 = s;
	}
	s = 0;
	for(i = m+1; i <= u; i++){
		s = s + arr[i];
		if(s > t2) t2 = s;
	}
	return t1 + t2;
}

int main(){
	int a[7] = {12, -13, -5, 25, -20, 30, 10};
	int max;
	max = maxSubArr(a, 0, 6);
	printf("Max sum: %d", max);
	return 0;
}
