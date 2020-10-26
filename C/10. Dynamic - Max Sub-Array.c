/*
Q. The Maximum Sub-array Sum problem is to find the sub-array (A sub-array of the array A [0 … N-1] is A[i…j] where 0 ≤ i ≤ j < N ) for which the sum of its elements is maximum. For example, given an array {12, -13, -5, 25, -20, 30, 10}, the maximum sub-array sum is 45 for sub-array {25, -20, 30, 10}.
Find the subarray from an array which gives the maximum sum, using dynamic programming. The subarray elements should be contiguous. Prepare memoization table, and everything required for dynamic programming.
*/

#include<stdio.h>
#include<stdlib.h>

int** makeMemoTable(int *arr, int size){
	int **memo = (int **)calloc(size, sizeof(int*));
	int i, j;
	for(i = 0; i < size; i++) {
		memo[i] = (int *)calloc(size, sizeof(int));
		memo[i][i] = arr[i];
	}
	for(i = 0; i < size; i++){
		for(j = i+1; j < size; j++){
			memo[i][j] = memo[i][j-1] + arr[j];
		}
	}
	return memo;
}

int findMax(int **memo, int size){
	int i, j;
	int max = -2000;
	for(i = 0; i < size; i++){
		for(j = i+1; j < size; j++){
			if(memo[i][j] > max){
				max = memo[i][j];
				printf("Max subarray starting index: %d, ending index: %d\n", i, j);
			}
		}
	}
	return max;
}

int main(){
	int a[7] = {12, -13, -5, 25, -20, 30, 10};
	int **m;
	int max;
	m = makeMemoTable(a, 7);
	max = findMax(m, 7);
	printf("Max sum: %d", max);
	return 0;
}