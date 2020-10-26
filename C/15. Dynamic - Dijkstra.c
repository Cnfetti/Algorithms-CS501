#include <stdio.h> 
#include <stdlib.h>
#define INT_MAX 32767

int** create2DMat(int row, int col) {
	int **a;
	a = (int **)calloc(row, sizeof(int*));
	int i, j;
	for(i = 0; i < row; i++) {
		a[i] = (int *)calloc(col, sizeof(int));
	}
	return a;
}

int** enterWeightMat(int row, int col, int **weight) {
	int i, j;
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			printf("Enter arr[%d][%d] (0 for infinity): ", i, j);
			scanf("%d", &weight[i][j]);
		}
	}
	return weight;
}

void printSquareMat(int **arr, int n){
	int i, j;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			printf("%d\t",arr[i][j]);
		}
		printf("\n");
	}
}

int minDistance(int *dist, int *visited, int n) {
	int min = INT_MAX;
	int v, min_index;
	for (v = 0; v < n; v++){
		if (visited[v] == 0 && dist[v] <= min) 
			min = dist[v], min_index = v; 
	}
	return min_index; 
} 

int printSolution(int *dist, int n) {
	int i;
	printf("Vertex \t\t Distance from Source\n"); 
	for (i = 0; i < n; i++) 
		printf("%d \t\t %d\n", i+1, dist[i]); 
} 

void dijkstra(int **weight, int src, int n){ 
	int i, count;
	src--;
	int *visited;
	visited = (int *)calloc(n, sizeof(int));
	int *dist;
	dist = (int *)calloc(n, sizeof(int));  
	for (i = 0; i < n; i++){
		dist[i] = INT_MAX;
		visited[i] = 0; 
	}
	dist[src] = 0; 
	for (count = 0; count < n - 1; count++) {
		int v;
		int u = minDistance(dist, visited, n); 
		visited[u] = 1;  
		for (v = 0; v < n; v++){
			if(visited[v] == 0 && weight[u][v] != 0 && dist[u] != INT_MAX && dist[u] + weight[u][v] < dist[v]){
				dist[v] = dist[u] + weight[u][v];
			}
		}
	}
	printSolution(dist, n); 
}

/*
int main(){
	int i, n, source;
	printf("Enter number of vertices on graph: ");
	scanf("%d", &n);
	int **weight = create2DMat(n, n);
	int *dis = (int *)calloc(n, sizeof(int));
	printf("Weight Matrix Input: \n");
	weight = enterWeightMat(n, n, weight);
	printf("Weight Matrix: \n");
	printSquareMat(weight, n);
	printf("\nSource Vertex: ");
	scanf("%d", &source);
	dijkstra(weight, source, n); 
    return 0; 
}
*/

int main() {
	int i, j, n, source;
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
	printf("\nWeight Matrix: \n");
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			printf("%d\t", graph[i][j]);
		}
		printf("\n");	
	}	
	printf("\nSource Vertex: ");
	scanf("%d", &source);
	dijkstra(graph, source, n); 
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