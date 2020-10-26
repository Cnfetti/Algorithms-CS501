#include<stdio.h>
#include<stdlib.h>

void jobsc(int *s, int *f, int n){
	int i, j;
	int *schedule = (int *)calloc(n, sizeof(int));
	schedule[0] = 1; //0 means won't do the job, 1 means to do.
	int lastJobDone = f[0];
	for(i = 1; i < n; i++){
		if(lastJobDone <= s[i]){
			schedule[i] = 1;
			lastJobDone = f[i];
		}
	}
	for(i = 0; i < n; i++){
		if(schedule[i] == 1) printf("Job %d\n", i+1);
	}
}


int main(){
	int i, n;
	int *s, *f;
	FILE *fp;
	fp = fopen("job.txt", "r");
	if(fp == NULL){
		printf("File not found!");
		return 0;	
	}
	fscanf(fp, "%d ", &n);
	s = (int *)calloc(n, sizeof(int));
	f = (int *)calloc(n, sizeof(int));
	for(i = 0; i < n; i++){
		fscanf(fp, "%d ", &s[i]);
	}
	for(i = 0; i < n; i++){
		fscanf(fp, "%d ", &f[i]);
	}
	jobsc(s, f, n);
}
/*
INSIDE FILE:
10 (Number of jobs)
3 4 5 6 7 8 9 10 11 12 (Their respective starting time)
5 7 8 10 11 12 13 14 15 16 (Their respective ending time)
*/