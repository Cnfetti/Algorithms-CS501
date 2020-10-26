/*
Q. Find the minimum number of scalar multiplications needed for chain of matrix whose sequences are <5, 10, 3, 12, 5, 50, 6> using dynamic programming.
*/

#include<stdio.h>
#include<stdlib.h>

int findMinArr(int *arr, int n){
	int i;
	int min = 32000;
	for(i = 0; i < n; i++){
		if(arr[i] < min) min = arr[i];	
	}
	return min;
}

int** makeMemoTable(int *d, int size){
	int **memo = (int **)calloc(size, sizeof(int*));
	int i, j, k, l, i1;
	int min[50];
	for(i = 0; i < size; i++){
		memo[i] = (int *) calloc(size, sizeof(int));
	}
	for(i = size-2; i >= 1; i--){
		for(j = i+1; j < size; j++){
			for(k = i, l = 0; k <= j-1; k++){
				min[l++] = memo[i][k] + memo[k+1][j] + d[i-1]*d[k]*d[j];
				printf("(A%d to A%d) and (A%d to A%d): ", i, k, k+1, j);
				printf("%d + %d + (%d*%d*%d) = %d\n", memo[i][k], memo[k+1][j], d[i-1], d[k], d[j], min[l-1]);
			}
			memo[i][j] = findMinArr(min, l);
			printf("memo[%d][%d] = %d\n\n", i, j, memo[i][j]);
		}
	}	
	return memo;
}

int main(){
	int d[] = {5, 10, 3, 12, 5, 50, 6};
	//int d[] = {5, 2, 3, 4, 6, 7, 8};
	int i, j;
	int **memo;
	int n = sizeof(d) / sizeof(d[0]);
	memo = makeMemoTable(d, n);
	printf("\nLowest number of multiplications: %d\n", memo[1][n-1]);
	for(i = 1; i < n; i++){
		for(j = 1; j < n; j++){
			printf("%d\t", memo[i][j]);		
		} printf("\n");		
	}
	return 0;
}
