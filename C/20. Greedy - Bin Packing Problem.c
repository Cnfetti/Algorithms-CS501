/*
Q. Implement bin-packing problem using the greedy approach. Include the following:
(1) Next Fit
(2) First Fit
(3) Best Fit
(4) First Fit Decreasing
(5) Best Fit Decreasing
(6) Full Bin
*/

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

void displayArr(int *arr, int n){
	int i;
	for(i = 0; i < n; i++){
		printf("%d ", arr[i]); 
	}
}

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

int arrSum(int *a, int n){
	int i, sum = 0;
	for(i = 0; i < n; i++) sum = sum + a[i];
	return sum;
}

void createHeap(int *arr, int n){
	int i;
	for(i = 1; i < n; i++){
		int child = i;
		while(child != 0){
			int parent = (child-1)/2;
			if(arr[parent] < arr[child]) break;
			swap(&(arr[parent]), &(arr[child]));
			child = parent;
		}
	}
}

void deleteHeap(int *arr, int n){
	int i;
	for(i = n-1; i >= 1; i--){
		swap(&(arr[0]), &(arr[i]));
		createHeap(arr, i);
	}
}

void heapsortDesc(int *arr, int n){
	createHeap(arr, n);
	deleteHeap(arr, n);
}

void nextFit(int* weight, int n, int binCapacity){
	int i, res = 0;
	int whichBin[n]; //whichBin[2] = 4 means 2nd item will go inside 4th Bin.
	int bin_rem = binCapacity;
	for(i = 0; i < n; i++) {
		if(weight[i] <= bin_rem) {
			bin_rem = bin_rem - weight[i];
			whichBin[i] = res;
		}
		else if(weight[i] > bin_rem) {
			res++;
			bin_rem = binCapacity - weight[i];
			whichBin[i] = res;
		}
	}
	for(i = 0; i < n; i++) printf("Item[%d] goes into: Bin[%d]\n", i, whichBin[i]);
	printf("Number of bins in next fit algorithm: %d\n\n", res+1);
}

void firstFit(int* weight, int n, int binCapacity){
	int i, j, res = 0;
	int whichBin[n];
	int bin_rem[n];
	for(i = 0; i < n; i++){
		bin_rem[i] = binCapacity; //bin_rem[4] = 6 means 4th bin has 6 capacity left.
	}
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++){
			if(weight[i] <= bin_rem[j]){
				bin_rem[j] = bin_rem[j] - weight[i];
				whichBin[i] = j;
				break;
			}
		}
	}
	for(i = 0; i < n; i++){
		printf("Item[%d] goes into: Bin[%d]\n", i, whichBin[i]);
		if(bin_rem[i] != binCapacity) res++;
	}
	printf("Number of bins in first fit algorithm: %d\n\n", res);
}

void bestFit(int *weight, int n, int binCapacity){
	int i, res = 0;
	int bin_rem[n];
	int whichBin[n];
	for(i = 0; i < n; i++){
		int j;
		int minSpaceLeft = binCapacity + 1, bin_index = 0;
		for(j = 0; j < res; j++){
			if(bin_rem[j] >= weight[i] && bin_rem[j] - weight[i] < minSpaceLeft){
				bin_index = j;
				minSpaceLeft = bin_rem[j] - weight[i];
				whichBin[i] = j;
			}
		}
		if(minSpaceLeft == binCapacity + 1){
			bin_rem[res] = binCapacity - weight[i];
			res++;
			whichBin[i] = res-1;
		}
		else{
			bin_rem[bin_index] = bin_rem[bin_index] - weight[i];
			whichBin[i] = bin_index;
		}
	}
	for(i = 0; i < n; i++) printf("Item[%d] goes into: Bin[%d]\n", i, whichBin[i]);
	printf("Number of bins in best fit algorithm: %d\n\n", res);
}

void fullBin(int *weight, int n, int binCapacity){
	int i = 0, j, res = 0;
	int bin_rem[n];
	int whichBin[n];
	for(i = 0; i < n; i++) whichBin[i] = -1;
	for(i = 0; i < n;){
		for(j = i+1; j < n; j++){
			printf("i = %d, arr[i] = %d, j = %d, arr[j] = %d\n", i, weight[i], j, weight[j]);
			if(weight[i] + weight[j] == binCapacity){
				if(whichBin[i] == -1) whichBin[i] = res;
				if(whichBin[j] == -1) whichBin[j] = res;
				weight[i] = weight[j] = 0;
				i++; j = i+1;
				res++;
			}
			else if(weight[i] + weight[j] < binCapacity){
				weight[i] = weight[i] + weight[j];
				if(whichBin[i] == -1) whichBin[i] = res;
				if(whichBin[j] == -1) whichBin[j] = res;
				weight[j] = 0;
			}
		}
		if(arrSum(weight, n) == 0) break;
	}
	for(i = 0; i < n; i++) printf("Item[%d] goes into: Bin[%d]\n", i, whichBin[i]);
	printf("Number of bins in full bin fit algorithm: %d\n\n", res);
}

int main(){
	int s[11] = {4, 8, 5, 1, 7, 6, 1, 4, 2, 2};
	int c;
	printf("(1) Next Fit\n(2) First Fit\n(3) Best Fit\n(4) First Fit Decreasing\n(5) Best Fit Decreasing\n(6) Full Bin\n");
	printf("Enter choice: ");
	scanf("%d", &c);
	switch(c){
		case 1: nextFit(s, 10, 10); break;
		case 2: firstFit(s, 10, 10); break;
		case 3: bestFit(s, 10, 10); break;
		case 4: heapsortDesc(s, 10); displayArr(s, 10); printf("\n"); firstFit(s, 10, 10); break;
		case 5: heapsortDesc(s, 10); displayArr(s, 10); printf("\n"); bestFit(s, 10, 10); break;
		case 6: heapsortDesc(s, 10); displayArr(s, 10); printf("\n"); fullBin(s, 10, 10); break;
		default: printf("Wrong choice! Enter again");
	}
	return 0;
}
