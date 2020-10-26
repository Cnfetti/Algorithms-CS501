/*
Q. Implement the problem of job sequencing when profits and deadlines are given using greedy method.
*/

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

void printArrMod(int *arr, int n){
	int i;
	printf("\n[");
	for(i = 0; i < n; i++){
		if(arr[i] == -1) break;
		printf("%d\t", arr[i]+1);
	}
	printf("]\n");
}

void printArr(int *arr, int n){
	int i;
	printf("\n[");
	for(i = 0; i < n; i++) printf("%d\t", arr[i]);
	printf("]\n");
}

int sumOfArr(int *arr, int n){
	int i, sum = 0;
	for(i = 0; i < n; i++) sum = sum + arr[i];
	return sum;
}

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void createHeapDesc(int *arr1, int *arr2, int* arr3, int n){
	int i;
	for(i = 1; i < n; i++){
		int child = i;
		while(child != 0){
			int parent = (child-1)/2;
			if(arr1[parent] < arr1[child]) break;
			swap(&(arr1[parent]), &(arr1[child]));
			swap(&(arr2[parent]), &(arr2[child]));
			swap(&(arr3[parent]), &(arr3[child]));
			child = parent;
		}
	}
}

void createHeapAsc(int *arr1, int *arr2, int *arr3, int n){
	int i;
	for(i = 1; i < n; i++){
		int child = i;
		while(child != 0){
			int parent = (child-1)/2;
			if(arr1[parent] > arr1[child]) break;
			swap(&(arr1[parent]), &(arr1[child]));
			swap(&(arr2[parent]), &(arr2[child]));
			swap(&(arr3[parent]), &(arr3[child]));
			child = parent;
		}
	}
}

void deleteHeapDesc(int *arr1, int *arr2, int* arr3, int n){
	int i;
	for(i = n-1; i >= 1; i--){
		swap(&(arr1[0]), &(arr1[i]));
		swap(&(arr2[0]), &(arr2[i]));
		swap(&(arr3[0]), &(arr3[i]));
		createHeapDesc(arr1, arr2, arr3, i);
	}
}

void deleteHeapAsc(int *arr1, int *arr2, int* arr3, int n){
	int i;
	for(i = n-1; i >= 1; i--){
		swap(&(arr1[0]), &(arr1[i]));
		swap(&(arr2[0]), &(arr2[i]));
		swap(&(arr3[0]), &(arr3[i]));
		createHeapAsc(arr1, arr2, arr3, i);
	}
}

void heapSortDesc2D(int* arr1, int* arr2, int* arr3, int n){
	createHeapDesc(arr1, arr2, arr3, n);
	deleteHeapDesc(arr1, arr2, arr3, n);
}

void heapSortAsc2D(int* arr1, int* arr2, int *arr3, int n){
	createHeapAsc(arr1, arr2, arr3, n);
	deleteHeapAsc(arr1, arr2, arr3, n);
}

int* jobSeqDeadlineProfitWise(int n, int* prof, int* deadline, int* taskNo){
	int i, j, count = 0;
	int *jobArr;
	jobArr = (int *)calloc(n, sizeof(int));
	int *jobArrProf;
	jobArrProf = (int *)calloc(n, sizeof(int));
	for(i = 0; i < n; i++){
		jobArr[i] = -1;
	}
	heapSortDesc2D(prof, deadline, taskNo, n);
	for(i = 0; i < n-1; i++){
		if(prof[i] == prof[i+1] && deadline[i] > deadline[i+1]){
			swap(&deadline[i], &deadline[i+1]);
			swap(&taskNo[i], &taskNo[i+1]);
		}
	}
	i = 0; j = 0;
	while(j != n){
		if(deadline[j] > count){
			jobArr[i] = taskNo[j];
			jobArrProf[i] = prof[j];
			count++;
			i++;
		}
		j++;
	}
	printf("Job sequence PR:");
	printArrMod(jobArr, n);
	printf("\n");
	printf("Job sequence profit PR:");
	printArr(jobArrProf, n);
	printf("\n");
	return jobArrProf;
}

int* jobSeqDeadlineDlWise(int n, int* prof, int* deadline, int* taskNo){
	int i, j, count = 0;
	int *jobArr;
	jobArr = (int *)calloc(n, sizeof(int));
	int *jobArrProf;
	jobArrProf = (int *)calloc(n, sizeof(int));
	for(i = 0; i < n; i++){
		jobArr[i] = -1;
	}
	heapSortAsc2D(deadline, prof, taskNo, n);
	for(i = 0; i < n-1; i++){
		if(deadline[i] == deadline[i+1] && prof[i] < prof[i+1]){
			swap(&prof[i], &prof[i+1]);
			swap(&taskNo[i], &taskNo[i+1]);
		}
	}
	i = 0; j = 0;
	while(j != n){
		if(deadline[j] > count){
			jobArr[i] = taskNo[j];
			jobArrProf[i] = prof[j];
			count++;
			i++;
		}
		j++;
	}
	printf("Job sequence DL: ");
	printArrMod(jobArr, n);
	printf("\n");
	printf("Job sequence profit DL: \n");
	printArr(jobArrProf, n);
	printf("\n");
	return jobArrProf;
}

void jobSeqDeadline(int n, int* prof, int* dline, int* taskNo){
	int* arrP;
	arrP = (int *)calloc(n, sizeof(int));
	int* arrD;
	int arrPsum = 0, arrDsum = 0;
	arrD = (int *)calloc(n, sizeof(int));
	arrP = jobSeqDeadlineProfitWise(n, prof, dline, taskNo);
	arrD = jobSeqDeadlineDlWise(n, prof, dline, taskNo);
	arrPsum = sumOfArr(arrP, n);
	arrDsum = sumOfArr(arrD, n);
	printf("Profit if sorted profit-wise: %d\n", arrPsum);
	printf("Profit if sorted deadline-wise: %d\n", arrDsum);
	if(arrPsum > arrDsum){
		printf("\nSorting with decreasing profit gives better result!\n");
	}
	else if(arrPsum < arrDsum){
		printf("\nSorting with decreasing deadline gives better result!\n");
	}
}

int main(){
	int i, n;
	printf("Enter the number of jobs: ");
	scanf("%d", &n);
	int *prof, *dline, *taskNo;
	prof = (int *)calloc(n, sizeof(int));
	dline = (int *)calloc(n, sizeof(int));
	taskNo = (int *)calloc(n, sizeof(int));
	for(i = 0; i < n; i++){
		printf("Enter profit for job %d: ",i);
		scanf("%d", &prof[i]);
		printf("Enter deadline for job %d: ",i);
		scanf("%d", &dline[i]);
		taskNo[i] = i;
	}
	jobSeqDeadline(n, prof, dline, taskNo);
	return 0;
}