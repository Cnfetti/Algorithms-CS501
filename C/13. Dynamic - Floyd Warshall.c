#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define INF INT_MAX

void printSolution(int **graph, int V); 

void floydWarshall (int **graph, int V){
	int **dist = (int **)calloc(V, sizeof(int *)); 
	int i, j, k;
	for (i = 0; i < V; i++){
		dist[i] = (int *)calloc(V, sizeof(int *)); 
		for (j = 0; j < V; j++){
			dist[i][j] = graph[i][j];
		}
	}
	for (k = 0; k < V; k++){
		for (i = 0; i < V; i++){
			for (j = 0; j < V; j++){
				if (dist[i][k] + dist[k][j] < dist[i][j]) 
					dist[i][j] = dist[i][k] + dist[k][j]; 
			} 
		} 
	}
	printSolution(dist, V); 
} 

void printSolution(int **dist, int V){
	int i, j;
	printf ("\nThe following matrix shows the shortest distances between every pair of vertices \n"); 
	for (i = 0; i < V; i++){ 
		for (j = 0; j < V; j++){ 
			if (dist[i][j] == INF) 
				printf("%7s", "INF"); 
			else
				printf ("%7d\t", dist[i][j]); 
		} 
	printf("\n"); 
	} 
}

int main() {
	int i, j, n;
	FILE *fp;
	fp = fopen("graph.txt", "r");
	if(fp == NULL){
		printf("File not found!");
		return 0;	
	}
	fscanf(fp, "%d ", &n);
	int **graph = (int **)calloc(n, sizeof(int*));
	for(i = 0; i < n; i++){
		graph[i] = (int *)calloc(n, sizeof(int));
		for(j = 0; j < n; j++){
			fscanf(fp, "%d ", &graph[i][j]);
		}
	}
	printf("\nAdjacency Matrix: \n");
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			printf("%d\t", graph[i][j]);
		}
		printf("\n");	
	}	
	floydWarshall(graph, n); 
	return 0;
}

/*
INSIDE THE FILE (graph.txt):
4 (Number of vertices)
0 2 3 5 (Weight matrix)
1 0 6 7
0 0 0 4
2 0 5 0
*/