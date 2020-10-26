/*
Q. Find the binomial coefficient nCr via dynamic programming.
Prepare memoization table, and everything required for dynamic programming.
*/

#include<stdio.h>
#include<stdlib.h>

int** makeMemoTable(int N){
	int **memo = (int **)calloc(N, sizeof(int*));
	int n, r;
	for(n = 0; n < N; n++) {
		memo[n] = (int *)calloc(N, sizeof(int));
	}
	
	for(n = 0; n < N; n++) {
		memo[n][n] = 1;
	}

	for(n = 1; n < N; n++){
		for(r = 1; r < n; r++){
			memo[n][r] = memo[n-1][r-1] + memo[n-1][r];
		}
	}
	for(n = 2; n < N; n++){
		for(r = 2; r < N; r++){
			printf("%d\t", memo[n][r]);
		}
		printf("\n");
	}
	return memo;
}

int findBino(int N, int R){
	int **memo;
	memo = makeMemoTable(N+2); 
	return memo[N][R];
}

int main(){
	int n, r, val;
	printf("Value of n: \n");
	scanf("%d", &n);
	printf("Value of r: \n");
	scanf("%d", &r);
	printf("\n");
	val = findBino(n+1, r+1);
	if(val == 0) printf("Binomial coefficient doesn't exist!");
	else printf("%dC%d: %d\n", n, r, val);
	return 0;
}
