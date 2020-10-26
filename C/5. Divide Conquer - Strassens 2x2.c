/*
Q. Multiply two 2x2 matrices using Strassen's method of matrix multiplication.
*/

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

void enterArray(int arr[2][2], int n){
	int i, j;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			printf("Enter arr[%d][%d]: ", i, j);
			scanf("%d", &arr[i][j]);
		}
	}
}

int* addTwoD_Array(int a[2][2], int b[2][2], int aplusb[2][2]){
	int i, j;
	for(i = 0; i < 2; i++){
		for(j = 0; j < 2; j++){
			aplusb[i][j] = a[i][j] + b[i][j];
		}
	}
	return *aplusb;
}

void calculateStrassenOne(int a00, int a01, int a10, int a11, int b00, int b01, int b10, int b11, int res[7]){
	res[0] = (a00 + a11)*(b00 + b11);
	res[1] = b00*(a10 + a11);
	res[2] = a00*(b01 - b11);
	res[3] = a11*(b10 - b00);
	res[4] = b11*(a00 + a01);
	res[5] = (a10 - a00)*(b00 + b01);
	res[6] = (a01 - a11)*(b11 + b10);
}

void calculateStrassenTwo(int res[7], int ab[2][2]){
	ab[0][0] = res[0] + res[3] - res[4] + res[6];
	ab[0][1] = res[2] + res[4];
	ab[1][0] = res[1] + res[3];
	ab[1][1] = res[0] + res[2] - res[1] + res[5];
}

void strassen(int arr1[2][2], int arr2[2][2]){
	int i, j, len1, len2;
	int res1[7];
	int prod[2][2];	
	calculateStrassenOne(arr1[0][0], arr1[0][1], arr1[1][0], arr1[1][1], arr2[0][0], arr2[0][1], arr2[1][0], arr2[1][1], res1);
	calculateStrassenTwo(res1, prod);
	for(i = 0; i < 2; i++){
		for(j = 0; j < 2; j++){
			printf("%d ",prod[i][j]);
		}
		printf("\n");
	}
}

int main() {
	int arr1[2][2], arr2[2][2], prod_arr[2][2];
	enterArray(arr1, 2);
	enterArray(arr2, 2);
	strassen(arr1, arr2);
}
	
