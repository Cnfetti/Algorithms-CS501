#include<stdio.h>
#include<stdlib.h>
#define UNASSIGNED 0
#define N 9

int FindZeroLocation(int grid[N][N],int *row,int *col);
int isSafe(int grid[N][N], int row, int col, int num);

int SolveSudoku(int grid[N][N])
{
	int row=0,col=0;

	if (!FindZeroLocation(grid,&row,&col))    // If there is no unassigned location, we are done
        return 1; // success!

	for (int num = 1; num <= 9; num++)  // consider digits 1 to 9
	{
		if (isSafe(grid, row, col, num))    // if looks promising
		{
			grid[row][col] = num;   // make tentative assignment

			if (SolveSudoku(grid))  // return, if success, Success!
				return 1;

			grid[row][col] = UNASSIGNED;    // failure, unmake & try again
		}
	}
	return 0; // this triggers backtracking
}

int FindZeroLocation(int grid[N][N],int *row,int *col)  /* Searches the grid to find an entry that is still unassigned*/
{
	for (*row = 0;*row < 9;(*row)++)
		for (*col = 0;*col < 9;(*col)++)
			if (grid[*row][*col] == UNASSIGNED)
				return 1;
	return 0;
}

/* Returns a integer value which indicates whether an assigned entry
in the specified row matches the given number. */
int UsedInRow(int grid[N][N], int row, int num)
{
	for (int col = 0; col < 9; col++)
		if (grid[row][col] == num)
			return 1;
	return 0;
}

/* Returns a integer value which indicates whether an assigned entry
in the specified column matches the given number. */
int UsedInCol(int grid[N][N], int col, int num)
{
	for (int row = 0; row < N; row++)
		if (grid[row][col] == num)
			return 1;
	return 0;
}

/* Returns a integer value which indicates whether an assigned entry
within the specified 3x3 box matches the given number. */
int UsedInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num)
{
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (grid[row+boxStartRow][col+boxStartCol] == num)
				return 1;
	return 0;
}

int isSafe(int grid[N][N], int row, int col, int num)
{
	/* Check if 'num' is not already placed in current row,
	current column and current 3x3 box */
	return  !UsedInRow(grid, row, num) &&
            !UsedInCol(grid, col, num) &&
            !UsedInBox(grid, row - row%3 , col - col%3, num)&&
			grid[row][col]==UNASSIGNED;
}

void printGrid(int grid[9][9])  /*function to print grid */
{
    int i,j;
    printf("\t-------------------------\n");
    for(i=0;i<9;i++)
    {
        printf("\t");
        for(j=0;j<9;j++)
        {
            if(j==0)
                printf("| ");
            if(grid[i][j]==0)
                printf(". ");
            else
                printf("%d ",grid[i][j]);
            if((j+1)%3==0 )
                printf("| ");
        }
        if((i+1)%3==0 )
        printf("\n\t-------------------------");
        printf("\n");
    }
}

int main()
{
    FILE *fp = fopen("sudoku.txt","r");
    int i,j,x,solution=0;
    int grid[9][9];
    if(fp == NULL)
    {
        printf("NO ELEMENTS PRESENT IN THE LIST\n");
        exit(0);
    }
    for(i = 0; i<9; i++)
    {
        for(j=0; j<9; j++)
            fscanf(fp,"%d",&grid[i][j]);
    }
    fclose(fp);
    printf("The Entered Sudoku puzzle is: \n");
    printGrid(grid);
    printf("Press '1' to confirm and solve, or '0' to exit: ");
    scanf("%d",&x);
    if(x == 0)
        exit(0);
    else if(x == 1)
    {
        solution=SolveSudoku(grid);
        if(solution)
        {
            printf("\nThe Solved Sudoku is: \n\n");
            printGrid(grid);
        }
        else
            printf("\nNo Possible Solution!!\n\n");
    }
    return 0;
}

/*
Filename: sudoku.txt
Contents:
3 0 6 5 0 8 4 0 0
5 2 0 0 0 0 0 0 0
0 8 7 0 0 0 0 3 1
0 0 3 0 1 0 0 8 0
9 0 0 8 6 3 0 0 5
0 5 0 0 9 0 6 0 0
1 3 0 0 0 0 2 5 0
0 0 0 0 0 0 0 7 4
0 0 5 2 0 6 3 0 0
*/