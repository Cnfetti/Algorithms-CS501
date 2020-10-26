/*
Q. Find out the max odd, min odd, max even and min even elements from an array using Divide & Conquer. Read inputs from a file.
*/

#include<stdio.h>
#include<stdlib.h>

//marr[0] = min odd, marr[1] = max odd, marr[2] = min even, marr[3] = max even.
//marr[0] is giving error so store it in marr[4].

int* findMinMaxArray(int arr[], int lb, int ub, int marr[]){
	if(ub > lb){
		int mid = (lb + ub)/2;
		printf("lb: %d and ub: %d\n", lb, ub);
		if(arr[mid] < marr[4] && arr[mid]%2 != 0) marr[4] = arr[mid];
		if(arr[mid] > marr[1] && arr[mid]%2 != 0) marr[1] = arr[mid];
		if(arr[mid] < marr[2] && arr[mid]%2 == 0) marr[2] = arr[mid];
		if(arr[mid] > marr[3] && arr[mid]%2 == 0) marr[3] = arr[mid];
		printf("%d\n",arr[mid]);
		marr = findMinMaxArray(arr, lb, mid, marr);
		marr = findMinMaxArray(arr, mid+1, ub, marr);
	}
	return marr;
}

int main(){
	int i,n;
	FILE *fp;
	fp = fopen("MaxMinData.txt", "r+");
	if(fp == NULL){
		printf("File not found!\n");
		return 0;
	}
	fscanf(fp, "%d ", &n);
	int arr[n];
	int* marr = (int *)calloc(5, sizeof(int));
	marr[0] = 0;
	marr[1] = marr[3] = -99999; 
	marr[2] = marr[4] = 99999;
	for(i = 0; i < n; i++){
		fscanf(fp, "%d ", &arr[i]);
	}
	for(i = 0; i < n; i++){
		printf("%d ", arr[i]);
	}
	marr = findMinMaxArray(arr, 0, 10, marr);
	printf("Minimum Odd: %d\n", marr[4]);
	printf("Maximum Odd: %d\n", marr[1]);
	printf("Minimum Even: %d\n", marr[2]);
	printf("Maximum Even: %d\n", marr[3]);
	return 0;
}

/*
INSIDE THE FILE:
10 (Number of elements)
2 6 5 4 7 10 21 3 8 1 (Array)
*/