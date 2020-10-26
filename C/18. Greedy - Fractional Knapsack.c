#include<stdio.h>
#include<stdlib.h>

void printArr2(float *arr, int n){
	int i;
	printf("\n[");
	for(i = 0; i < n; i++) printf("%f ", arr[i]);
	printf("]\n");
}

int maxArr(float *arr, int n){
	int i, j = 0;
	float maxi = arr[0];
	for(i = 1; i < n; i++){
		if(maxi < arr[i]){
			maxi = arr[i];
			j = i;
		}
	}
	return j;
}

float* fractionalKnapsack(int n, float wos, float *val, float *weight){
	float *ratios;
	ratios = (float *)calloc(n, sizeof(float));
	int i;
	float wis;
	float *it;
	it = (float *)calloc(n, sizeof(float));
	float bw = wos;
	for(i = 0; i < n; i++){
		ratios[i] = val[i]/weight[i];
	}
	int maxIndex = maxArr(ratios, n);
	while(bw > weight[maxIndex]){
		it[maxIndex] = 1.0;
		ratios[maxIndex] = -10.0;
		bw = wos - weight[maxIndex];
		wos = bw;
		maxIndex = maxArr(ratios, n);
		if(maxIndex > n || maxIndex < 0) break;
	}
	maxIndex = maxArr(ratios, n);
	if(bw > 0 && bw < weight[maxIndex]){
		float x = bw/weight[maxIndex];
		it[maxIndex] = x;
	}
	return it;
}

int main(){
	int i, n, w;
	FILE *fp;
	fp = fopen("knap.txt", "r");
	if(fp == NULL){
		printf("File not found!");
		return 0;	
	}
	fscanf(fp, "%d", &n);
	fscanf(fp, "%d", &w);
	float *val, *weight;
	val = (float *)calloc(n, sizeof(float));
	weight = (float *)calloc(n, sizeof(float));
	for(i = 0; i < n; i++){
		fscanf(fp, "%f ", &val[i]);
	}
	for(i = 0; i < n; i++){
		fscanf(fp, "%f ", &weight[i]);
	}
	float *x;
	x = (float *)calloc(n, sizeof(float));
	x = fractionalKnapsack(n, w, val, weight);
	printArr2(x, n);
	float tv = 0.0;
	for(i = 0; i < n; i++) tv = tv + (x[i]*val[i]);
	printf("Total value: %f", tv);
	return 0;
}

/*
INSIDE THE FILE (knap.txt):
5 (Number of items)
20 (Weight of knapsack)
10 12 8 9 14 (Values)
15 17 10 11 20 (Weights)
*/