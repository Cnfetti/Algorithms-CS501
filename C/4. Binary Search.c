/*
Q. Implement Binary Search. Read inputs from a file. Sort the elements using Quick Sort.
*/

#include <stdio.h>
#include <stdlib.h>

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

int binaryS(int arr[], int lb, int ub, int key){
	while(lb <= ub){	
		int mid = (lb + ub)/2;
		if(key == arr[mid]){
			return mid;
		}
		else if(key < arr[mid]){
			return binaryS(arr, lb, mid-1, key);
		}
		else if(key > arr[mid]){
			return binaryS(arr, mid+1, ub, key);	
		}
	}
	return -1;	
}

int main(){
	int i, n, key, place;
	FILE *fp;
	fp = fopen("bsdata", "r");	
	if(fp == NULL){
		printf("File not found!");
		return 0;
	}
	fscanf(fp, "%d ", &n);
	int arr[n];
	for(i = 0; i < 11; i++){
		fscanf(fp, "%d ", &arr[i]);	
	}
	for(i = 0; i < 11; i++){
		printf("%d ", arr[i]);	
	}
	printf("Enter element to be searched: ");
	scanf("%d", &key);
	place = binaryS(arr, 0, 10, key);
	if(place == -1){
		printf("Element not found! \n");
		return 0;
	}
	printf("Pos: %d \n", place);
	
	fclose(fp);
	return 0;
}

/*
INSIDE THE FILE (bsdata):
10 (Number of elements)
2 6 5 4 7 10 21 3 8 100 (Array to be sorted)
*/
