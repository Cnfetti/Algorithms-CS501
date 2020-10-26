/*
Q. Implement the 0-1 Knapsack problem using dynamic programming approach.
*/

#include<stdio.h> 

int max(int a, int b){
	return (a > b)? a:b;
} 

int knapSack(int W, int *wt, int *val, int n) { 
	int i, w; 
	int K[n+1][W+1]; 
	for (i = 0; i <= n; i++){ 
		for (w = 0; w <= W; w++){ 
			if (i==0 || w==0) 
				K[i][w] = 0; 
			else if (wt[i-1] <= w) 
				K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]], K[i-1][w]); 
			else
				K[i][w] = K[i-1][w]; 
		} 
	} 
	return K[n][W]; 
}

int main() {
	int i, n, w;
	printf("Enter the number of items: ");
	scanf("%d", &n);
	printf("Enter the weight of knapsack: ");
	scanf("%d", &w);
	int *val, *weight;
	val = (int *)calloc(n, sizeof(int));
	weight = (int *)calloc(n, sizeof(int));
	for(i = 0; i < n; i++){
		printf("Enter value of item %d: ",i);
		scanf("%d", &val[i]);
		printf("Enter weight of item %d: ",i);
		scanf("%d", &weight[i]);
	}
	int x;
	x = knapSack(w, weight, val, n);
	printf("%d ", x);
	return 0;
}
	
