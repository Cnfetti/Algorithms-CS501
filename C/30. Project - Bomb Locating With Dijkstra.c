/*
Q. A scene in the film (Holiday: A Soldier Is Never Off Duty) stops a bomb blast from happening at different places by splitting a group of 12 men and killing the criminals by stopping them from triggering the bomb at 12 different places in Mumbai. Apply a design technique to find a solution to this problem.
Approach: The 12 bomb locations are treated as 12 vertices in a graph. We also have a source vertes, from where the men start their journey.
We need to find the shortest possible route to the bombs so that we can quickly kill the criminals and stop them from triggering the bomb.
So this is a problem of Single Source Shortest Path problem, where we find the shortest possible paths to all other vertices from a single source using either Dijkstra's algorithm or Bellman Ford's algorithm.
Say we find 12 sets of shortest paths for each of 12 vertices. Now, we need to deploy a man to each path. Suppose bomb 1's shortest path is along the vertices S-3-2-1 and bomb 2's is S-3-2 (Vertex 1 = place where bomb 1 is located. Vertex 2 = place where bomb 2 is located, and so on). Then we need to release three men in the S-3 edge, one to handle bomb 3 in vertex 3, one to handle bomb 2 in vertex 2 and one to handle bomb 1 in vertex 1.
Finally, we need to print the 12 shortest paths, and the total number of men to be deployed in each path.
We use Dijkstra's algorithm to solve this particular problem.
*/

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
			printf("%d ",arr[i][j]);
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

int printSolution(int *dist, int *parent, int n) {
	int i;
	printf("Vertex \t\t Distance from Source\n"); 
	for (i = 0; i < n; i++) 
		printf("%d \t\t %d\n", i+1, dist[i]);
	printf("Parent array:\n"); 
	printf("Vertex \t\t Parent\n");
	for (i = 0; i < n-1; i++) 
		printf("%d \t\t %d\n", i+1, parent[i]+1);  
}

void printPath(int *parent, int source, int n){
	int i, j;
	for(i = 0; i < n-1; i++){
		printf("Bomb %d is at vertex %d\n", i+1, i+1);
		if(parent[i] == source){
			printf("We go from vertex %d to vertex %d\n", source+1, i+1);
			printf("Bomb %d diffused!\n", i+1);
		}
		else{
			j = i;
			while(1){
				printf("We reach vertex %d from vertex %d\n", j+1, parent[j]+1);
				j = parent[j];
				if(parent[j] == source){
					printf("We reach vertex %d from vertex %d\n", j+1, parent[j]+1);
					printf("Bomb %d diffused!\n", i+1);
					break;
				}
			}
		}
	}
}

void dijkstra(int **weight, int src, int n){ 
	int i, count;
	src--;
	int *visited;
	visited = (int *)calloc(n, sizeof(int));
	int *dist;
	dist = (int *)calloc(n, sizeof(int));
	int *parent;
	parent = (int *)calloc(n, sizeof(int));
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
				parent[v] = u;
			}
		}
	}
	printSolution(dist, parent, n);
	printPath(parent, src, n);
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
13 (Number of vertices)
0 3 0 0 0 0 0 0 0 0 0 0 5
3 0 5 0 0 0 0 0 0 0 0 0 2
0 5 0 1 0 0 0 0 0 0 0 0 9
0 0 1 0 2 0 0 0 0 0 0 0 9
0 0 0 2 0 8 0 0 0 0 0 0 7
0 0 0 0 8 0 6 0 0 0 0 0 8
0 0 0 0 0 6 0 2 0 0 0 0 10
0 0 0 0 0 0 2 0 1 0 0 0 10
0 0 0 0 0 0 0 1 0 3 0 0 6
0 0 0 0 0 0 0 0 3 0 9 0 1
0 0 0 0 0 0 0 0 0 9 0 7 5
0 0 0 0 0 0 0 0 0 0 7 0 3
5 2 9 6 7 8 10 10 6 1 5 3 0
*/
