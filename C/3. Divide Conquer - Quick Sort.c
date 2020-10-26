/*
Q. Implement Quick Sort using Divide & Conquer approach. Read inputs from a file.
*/

#include<stdio.h>
#include<stdlib.h>

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void quickSort(int arr[], int lb, int ub){
	if(lb >= ub) return;
	int pivot = (lb + ub)/2;
	int i = lb, j = ub;
	while(i < j){
		while(arr[i] < arr[pivot]) i++;	
		while(arr[j] > arr[pivot]) j--;
		if(i == pivot) pivot = j;
		else if(j == pivot) pivot = i;
		swap(&arr[i], &arr[j]);
	}
	quickSort(arr, lb, pivot-1);
	quickSort(arr, pivot+1, ub);
}

int main(){
	int n, i;
	FILE *fp;
	fp = fopen("data", "r");
	if(fp == NULL){
		printf("File not found!");
		return 0;	
	}
	fscanf(fp, "%d", &n);
	int arr[n];
	for(i = 0; i < 10; i++){
		fscanf(fp, "%d ", &arr[i]);	
	}
	for(i = 0; i < 10; i++){
		printf("%d ", arr[i]);	
	}
	quickSort(arr, 0, 9);
	printf("\n");
	for(i = 0; i < 10; i++){
		printf("%d ", arr[i]);
	}
	fclose(fp);
	fp = fopen("data", "a");
	for(i = 0; i < 10; i++){
		fprintf(fp, "%d ", arr[i]);
	}
	printf("\n");
	fclose(fp);
	return 0;
}

/*
INSIDE THE FILE (data):
10 (Number of elements)
2 6 5 4 7 10 21 3 8 100 (Array to be sorted)
*/

