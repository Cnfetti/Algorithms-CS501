/*
Q. Implement the 15 puzzle problem using Branch and Bound Technique. Read input from a file (0 is empty state). Say, a typical input is:
1	2	3	4
5	0	7	8
9	6	11	12
13	10	14	15
Goal State:
1	2	3	4
5	6	7	8
9	10	11	12
13	14	15	0
Output:
Down, Down, Right, Right.
Scope Of Improvement: This code reads board from the file as 4x4 2D array and then maps everything from 2D array with index [0][0], [0][1], [0][2]... [3][3] so on to a linear indexing 1, 2, 3... 16. It would be better if we can just take the input as a 1D array itself and avoid the unnecessary mapping problem. Time complexity, however, will be same as it has to go through 16 indices in either cases.
*/

#include<stdio.h>
#include<stdlib.h>

int getElement(int **board, int x){ //Returns element at xth pos. x = 1 to 16.
	int i, j, count = 1;
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			if(count == x) return board[i][j];
			count++;
		}
	}
}

int printBoard(int **board){
	int i, j;
	printf("\nGame Board (0 means empty state): \n");
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			printf("%d\t", board[i][j]);
		}
		printf("\n");	
	}
}

int** writeElement(int **board, int m, int x){ //Writes m at position x. x = 1 to 16.
	int i, j, count = 1;
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			if(count == x){
				board[i][j] = m;
				return board;
			}
			count++;
		}
	}
}

int findArrSum(int *arr, int x){
	int i, sum = 0;
	for(i = 0; i < x; i++){
		sum = sum + arr[i];
	}
	return sum;
}

int getMinArrIndexForGx(int *arr, int x){
	int i, m = 99999, index;
	for(i = 0; i < x; i++){
		if(arr[i] < m){
			m = arr[i];
			index = i;
		}
	}
	return index;
}

int getPos(int **board, int x){ //Positions: 1 to 16.
	int i, j, pos = 1;
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			if(board[i][j] == x) return pos;
			pos++;
		}
	}
}

int getLess(int **board, int i){
	int j, lessval = 0;
	for(j = 1; j < i; j++){
		if(getPos(board,j) > getPos(board, i)) lessval++;
	}
	return lessval;
}

int getLessForEmptyState(int **board){
	int j, lessval = 0;
	for(j = 1; j < 16; j++){
		if(getPos(board,j) > getPos(board, 0)) lessval++;
	}
	return lessval;
}

int calculateGx(int **board){
	int i, gx = 0, pos = 1;
	for(i = 1; i < 16; i++){
		if(getPos(board, i) != pos) gx++;
		pos++;
	}
	return gx;
}

int isGoalReachable(int **board){
	int i, p, x, less[16];
	p = getPos(board, 0);
	if((p == 2)||(p == 4)||(p == 5)||(p == 7)||(p == 10)||(p == 12)||(p == 13)||(p == 15)) x = 1;
	else x = 0;
	printf("X: %d\n", x);
	less[0] = getLessForEmptyState(board);
	printf("Less[0]: %d\n", less[0]);
	for(i = 1; i < 16; i++){
		less[i] = getLess(board, i);
		printf("Less[%d]: %d\n",i, less[i]);
	}
	int sum = findArrSum(less, 16);
	printf("Sum: %d\n", sum + x);
	if((sum + x)%2 == 0) return 1; //Means solvable as sum is even.
	else return 0; //Means not solvable as sum is odd.
}

int moveEmptySpace(int **board, int dir){
	//Dir = 0 means move up, 1 = down, 2 = left, 3 = right.
	//Return 1 means move unsuccessful. Return 0 means successful.
	int es_pos, temp;
	es_pos = getPos(board, 0);
	if(dir == 0){
		if(es_pos <= 4) return 1;
		temp = getElement(board, es_pos - 4);
		board = writeElement(board, 0, es_pos - 4);
		board = writeElement(board, temp, es_pos);
	}
	else if(dir == 1){
		if(es_pos >= 13) return 1;
		temp = getElement(board, es_pos + 4);
		board = writeElement(board, 0, es_pos + 4);
		board = writeElement(board, temp, es_pos);
	}
	else if(dir == 2){
		if((es_pos - 1) %4 == 0) return 1;
		temp = getElement(board, es_pos - 1);
		board = writeElement(board, 0, es_pos - 1);
		board = writeElement(board, temp, es_pos);
	}
	else if(dir == 3){
		if(es_pos %4 == 0) return 1;
		temp = getElement(board, es_pos + 1);
		board = writeElement(board, 0, es_pos + 1);
		board = writeElement(board, temp, es_pos);
	}
	return 0;
}

void play(int **board){
	int gxarray[4], i, move_chosen, isBoardChanged;
	//gxarr[0] will store g(x) when empty state is moved up, gxarr[1] when moved down, gxarr[3] when moved left, gxarr[4] when moved right.
	if(isGoalReachable(board) == 0){
		printf("Goal state cannot be reached!");
		return;
	}
	while(1){
		for(i = 0; i < 4; i++){
			isBoardChanged = moveEmptySpace(board, i);
			if(isBoardChanged == 1) gxarray[i] = 10000;
			//Means move unsuccessful. gxarray = 10000 to prevent infinite looping.
			else gxarray[i] = calculateGx(board);
			printf("G(x)[%d] = %d\n", i, gxarray[i]);
			if(gxarray[i] == 0){
				if(i == 0) printf("Empty state is moved up. Goal Reached!\n");
				else if(i == 1) printf("Empty state is moved down. Goal Reached!\n");
				else if(i == 2) printf("Empty state is moved left. Goal Reached!\n");
				else if(i == 3) printf("Empty state is moved right. Goal Reached!\n");
				printBoard(board);
				return;
			}
			if(i == 0 && isBoardChanged == 0) moveEmptySpace(board, 1);
			//If moved up, re-adjust and move it down so that we get the original board back for our next move (iteration).
			//If board is not changed, i.e. isBoardChanged == 1, then no need to re-adjust board.
			if(i == 1 && isBoardChanged == 0) moveEmptySpace(board, 0);
			if(i == 2 && isBoardChanged == 0) moveEmptySpace(board, 3);
			if(i == 3 && isBoardChanged == 0) moveEmptySpace(board, 2);
		}
		move_chosen = getMinArrIndexForGx(gxarray, 4);
		if(move_chosen == 0){
			printf("Empty state is moved up\n");
			moveEmptySpace(board, move_chosen);
		}
		else if(move_chosen == 1){
			printf("Empty state is moved down\n");
			moveEmptySpace(board, move_chosen);
		}
		else if(move_chosen == 2){
			printf("Empty state is moved left\n");
			moveEmptySpace(board, move_chosen);
		}
		else if(move_chosen == 3){
			printf("Empty state is moved right\n");
			moveEmptySpace(board, move_chosen);
		}
		printBoard(board);
	}
}

int main() {
	int i, j, n;
	FILE *fp;
	fp = fopen("15puz.txt", "r");
	if(fp == NULL){
		printf("File not found!");
		return 0;	
	}
	int **board = (int **)calloc(4, sizeof(int*));
	for(i = 0; i < 4; i++){
		board[i] = (int *)calloc(4, sizeof(int));
		for(j = 0; j < 4; j++){
			fscanf(fp, "%d\t", &board[i][j]);
		}
	}
	printBoard(board);
	play(board);
	return 0;
}
