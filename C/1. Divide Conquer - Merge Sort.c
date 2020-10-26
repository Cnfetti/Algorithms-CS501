/*
Q. Implement Merge Sort using Divide & Conquer approach. Read inputs from a file.
*/

#include<stdio.h>
#include<stdlib.h>

void merge(int arr[], int lb, int ub){
	int mid, i, j, k, temp[(ub-lb)+1];
	if(lb < ub){
		mid = (lb + ub)/2;
		merge(arr, lb, mid);
		merge(arr, mid+1, ub);
		for(i = lb, j = mid + 1, k = 0; i <= mid && j <= ub; ){
			if(arr[i] < arr[j])
				temp[k++] = arr[i++];
			else if(arr[i] > arr[j])
				temp[k++] = arr[j++];
		}
		while (i <= mid)
			temp[k++] = arr[i++];
		while (j <= ub)
			temp[k++] = arr[j++];
		for(i = lb, j = 0; i <= ub ; i++, j++) arr[i] = temp[j];
	}
}


int main(){
	int i;
	int arr[10];
	FILE *fp;
	fp = fopen("data", "r");
	if(fp == NULL){
		printf("File not found!");
		return 0;	
	}
	for(i = 0; i < 10; i++){
		fscanf(fp, "%d ", &arr[i]);	
	}
	for(i = 0; i < 10; i++){
		printf("%d ", arr[i]);	
	}
	merge(arr, 0, 9);
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
2 6 5 4 7 10 21 3 8 100 (Array of fixed size 10 to be sorted)
*/