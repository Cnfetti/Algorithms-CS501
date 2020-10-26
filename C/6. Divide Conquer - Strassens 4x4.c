/*
Q. Multiply two 4x4 matrices using Strassen's method of matrix multiplication.
*/

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

int** enterArray(int row, int col) {
	int **a;
	a = (int **)calloc(row, sizeof(int*));
	int i, j;
	for(i = 0; i < row; i++) {
		a[i] = (int *)calloc(col, sizeof(int));
		for(j = 0; j < col; j++) {
			printf("Enter arr[%d][%d]: ", i, j);
			scanf("%d", &a[i][j]);
		}
	}
	return a;
}

int** makeZeroArray(int row, int col) {
	int **a;
	a = (int **)calloc(row, sizeof(int*));
	int i, j;
	for(i = 0; i < row; i++) {
		a[i] = (int *)calloc(col, sizeof(int));
		for(j = 0; j < col; j++) {
			a[i][j] = 0;
		}
	}
	return a;
}

int** addMat(int **a, int **b){
	int **aplusb;
	aplusb = (int **)calloc(2, sizeof(int*));
	int i, j;
	for(i = 0; i < 2; i++) {
		aplusb[i] = (int *)calloc(2, sizeof(int));
	}
	for(i = 0; i < 2; i++){
		for(j = 0; j < 2; j++){
			aplusb[i][j] = a[i][j] + b[i][j];
		}
	}
	return aplusb;
}

int** subMat(int **a, int **b){
	int **aminusb;
	aminusb = (int **)calloc(2, sizeof(int*));
	int i, j;
	for(i = 0; i < 2; i++) {
		aminusb[i] = (int *)calloc(2, sizeof(int));
	}
	for(i = 0; i < 2; i++){
		for(j = 0; j < 2; j++){
			aminusb[i][j] = a[i][j] - b[i][j];
		}
	}
	return aminusb;
}

void print2DMat(int **arr){
	int i, j;
	for(i = 0; i < 2; i++){
		for(j = 0; j < 2; j++){
			printf("%d ",arr[i][j]);
		}
		printf("\n");
	}
}

/*
int* calculateStrassenOne(int a[2][2], int b[2][2]){
	int res[7];
	res[0] = (a[0][0] + a[1][1])*(b[0][0] + b[1][1]);
	res[1] = b[0][0]*(a[1][0] + a[1][1]);
	res[2] = a[0][0]*(b[0][1] - b[1][1]);
	res[3] = a[1][1]*(b[1][0] - b[0][0]);
	res[4] = b[1][1]*(a[0][0] + a[0][1]);
	res[5] = (a[1][0] - a[0][0])*(b[0][0] + b[0][1]);
	res[6] = (a[0][1] - a[1][1])*(b[1][1] + b[1][0]);
	return res;
}
*/

void calculateStrassenOne(int a00, int a01, int a10, int a11, int b00, int b01, int b10, int b11, int *res){
	res[0] = (a00 + a11)*(b00 + b11);
	res[1] = b00*(a10 + a11);
	res[2] = a00*(b01 - b11);
	res[3] = a11*(b10 - b00);
	res[4] = b11*(a00 + a01);
	res[5] = (a10 - a00)*(b00 + b01);
	res[6] = (a01 - a11)*(b11 + b10);
}
//To calculate the p, q, r, s, t, u, v for Strassens.
//a00 = arr1[0][0], b01 = arr2[0][1].
//p, q, r, s, t, u, v = arr[0], [1], [2], [3], [4], [5], [6].

void calculateStrassenTwo(int *res, int **ab){
	ab[0][0] = res[0] + res[3] - res[4] + res[6];
	ab[0][1] = res[2] + res[4];
	ab[1][0] = res[1] + res[3];
	ab[1][1] = res[0] + res[2] - res[1] + res[5];
}
//To calculate the final product matrix.

int** strassenTwo(int **arr1, int **arr2, int **prod){
	int i, j, len1, len2;
	int res1[7];	
	calculateStrassenOne(arr1[0][0], arr1[0][1], arr1[1][0], arr1[1][1], arr2[0][0], arr2[0][1], arr2[1][0], arr2[1][1], res1);
	calculateStrassenTwo(res1, prod);
	return prod;
}
//Strassens for 2x2 matrix.

/*
void breakMatrixFour(int arr[4][4], int arr_00[2][2], int arr_01[2][2], int arr_10[2][2], int arr_11[2][2]){
	arr_00[0][0] = arr[0][0];
	arr_00[0][1] = arr[0][1];
	arr_00[1][0] = arr[1][0];
	arr_00[1][1] = arr[1][1];

	arr_01[0][0] = arr[0][2];
	arr_01[0][1] = arr[0][3];
	arr_01[1][0] = arr[1][2];
	arr_01[1][1] = arr[1][3];
	
	arr_10[0][0] = arr[2][0];
	arr_10[0][1] = arr[2][1];
	arr_10[1][0] = arr[3][0];
	arr_10[1][1] = arr[3][1];
	
	arr_11[0][0] = arr[2][2];
	arr_11[0][1] = arr[2][3];
	arr_11[1][0] = arr[3][2];
	arr_11[1][1] = arr[3][3];
}
*/

void breakMatrixFour(int **arr, int **arr_00, int **arr_01, int **arr_10, int **arr_11){
	int i = 0, j = 0;
	
	for(i = 0; i < 2; i++){
		for(j = 0; j < 2; j++){
			arr_00[i][j] = arr[i][j];
		}
	}
	
	for(i = 0; i < 2; i++){
		for(j = 0; j < 2; j++){
			arr_01[i][j] = arr[i][j+2];
		}
	}
	
	for(i = 0; i < 2; i++){
		for(j = 0; j < 2; j++){
			arr_10[i][j] = arr[i+2][j];
		}
	}
	
	for(i = 0; i < 2; i++){
		for(j = 0; j < 2; j++){
			arr_11[i][j] = arr[i+2][j+2];
		}
	}
}
/*
To break a 4x4 matrix into four 2x2 ones:
arr00	arr01
arr10	arr11
Where arr00, arr01, arr10, arr11 are 2x2.
*/

void strassenFour(int **arr1, int **arr2){
	int i, j;
	int **temp1 = makeZeroArray(2, 2), **temp2 = makeZeroArray(2, 2), **temp3 = makeZeroArray(2, 2);
	int **p = makeZeroArray(2, 2), **q = makeZeroArray(2, 2), **r = makeZeroArray(2, 2), **s = makeZeroArray(2, 2);
    int **t = makeZeroArray(2, 2), **u = makeZeroArray(2, 2), **v = makeZeroArray(2, 2);
	int **prod00 = makeZeroArray(2, 2), **prod01 = makeZeroArray(2, 2), **prod10 = makeZeroArray(2, 2), **prod11 = makeZeroArray(2, 2);
	int **arr1_00 = makeZeroArray(2, 2), **arr1_01 = makeZeroArray(2, 2), **arr1_10 = makeZeroArray(2, 2), **arr1_11 = makeZeroArray(2, 2);
	int **arr2_00 = makeZeroArray(2, 2), **arr2_01 = makeZeroArray(2, 2), **arr2_10 = makeZeroArray(2, 2), **arr2_11 = makeZeroArray(2, 2);

	breakMatrixFour(arr1, arr1_00, arr1_01, arr1_10, arr1_11);
	breakMatrixFour(arr2, arr2_00, arr2_01, arr2_10, arr2_11);

	p = strassenTwo(addMat(arr1_00, arr1_11), addMat(arr2_00, arr2_11), p);
	q = strassenTwo(arr2_00, addMat(arr1_10, arr1_11), q);
	r = strassenTwo(arr1_00, subMat(arr2_01, arr2_11), r);
	s = strassenTwo(arr1_11, subMat(arr2_10, arr2_00), s);
	t = strassenTwo(arr2_11, addMat(arr1_00, arr1_01), t);
	u = strassenTwo(subMat(arr1_10, arr1_00), addMat(arr2_00, arr2_01), u);
	v = strassenTwo(subMat(arr1_01, arr1_11), addMat(arr2_11, arr2_10), v);
	
	prod00 = subMat(addMat(p, addMat(s, v)), t);
	prod01 = addMat(r, t);
	prod10 = addMat(q, s);
	prod11 = subMat(addMat(p, addMat(r, u)), q);
	
	printf("\nResult matrix: \n");
	
	//print2DMat(prod00); printf("\n");
	//print2DMat(prod01); printf("\n");
	//print2DMat(prod10); printf("\n");
	//print2DMat(prod11); printf("\n");
	
	printf("%d\t%d\t%d\t%d\t\n", prod00[0][0], prod00[0][1], prod01[0][0], prod01[0][1]);
	printf("%d\t%d\t%d\t%d\t\n", prod00[1][0], prod00[1][1], prod01[1][0], prod01[1][1]);
	printf("%d\t%d\t%d\t%d\t\n", prod10[0][0], prod10[0][1], prod11[0][0], prod11[0][1]);
	printf("%d\t%d\t%d\t%d\t\n", prod10[1][0], prod10[1][1], prod11[1][0], prod11[1][1]);
	
		
}

int main() {
	int dim;
	printf("Enter 1 for 2x2, 2 for 4x4: ");
	scanf("%d", &dim);
	switch(dim){
	case 1:{
		int **arr1, **arr2, **prod_arr;
		printf("Matrix 1: \n");
		arr1 = enterArray(2, 2);
		printf("Matrix 2: \n");
		arr2 = enterArray(2, 2);
		strassenTwo(arr1, arr2, prod_arr);
		break;
	}
	case 2:{
		int **arr1, **arr2, **prod_arr;
		printf("Matrix 1: \n");
		arr1 = enterArray(4, 4);
		printf("Matrix 2: \n");
		arr2 = enterArray(4, 4);
		strassenFour(arr1, arr2);
		break;
	}
	default: break;
	}
}
	
