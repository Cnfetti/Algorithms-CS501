/*
Q. Implement Heap Sort. Read inputs from a file.
*/

#include<stdio.h>
#include<stdlib.h>

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void createHeap(int arr[], int n){
	int i;
	for(i = 1; i < n; i++){
		int child = i;
		while(child != 0){
			int parent = (child-1)/2;
			if(arr[parent] > arr[child]) break;
			swap(&(arr[parent]), &(arr[child]));
			child = parent;
		}
	}
}

void deleteHeap(int arr[], int n){
	int i;
	for(i = n-1; i >= 1; i--){
		swap(&(arr[0]), &(arr[i]));
		createHeap(arr, i);
	}
}

void heapsort(int arr[], int n){
	createHeap(arr, n);
	deleteHeap(arr, n);
}

int main(){
	int i, n;
	//int arr[];
	FILE *fp;
	fp = fopen("data", "r+");
	if(fp == NULL){
		printf("File not found!");
		return 0;	
	}
	fscanf(fp, "%d ", &n);
	int arr[n];
	for(i = 0; i < n; i++){
		fscanf(fp, "%d ", &arr[i]);	
	}
	for(i = 0; i < n; i++){
		printf("%d ", arr[i]);	
	}
	heapsort(arr, n);
	printf("\n");
	for(i = 0; i < n; i++){
		printf("%d ", arr[i]);
	}
	fclose(fp);
	fp = fopen("data", "a");
	for(i = 0; i < n; i++){
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