#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 987654321

int graph[7][7] = {
    {0, 5, 1, 0, 0, 0, 0},
    {5, 0, 0, 1, 0, 3, 3},
    {1, 0, 0, 2, 0, 0, 0},
    {0, 1, 2, 0, 5, 3, 0},
    {0, 0, 0, 5, 0, 0, 0},
    {0, 3, 0, 3, 0, 0, 2},
    {0, 3, 0, 0, 0, 2, 0},
};
int distance[7][7];
int path[7][7];

int min(int num1, int num2){
    return num2 > num1 ? num1 : num2;
}

// 플로이드 알고리즘
void floyd(){
    for(int i=0; i<7; i++)
        for(int j=0; j<7; j++)
            if(i != j)
                distance[i][j] = min(graph[i][j], graph[i][0] + graph[0][j]);
            else
                distance[i][j] = 0;
    
    for(int k=0; k<7; k++)
        for(int i=0; i<7; i++)
            for(int j=0; j<7; j++){
                if(distance[i][j] > distance[i][k] + distance[k][j]){
                    distance[i][j] = distance[i][k] + distance[k][j];
                    path[i][j] = k;
                }
            }
}

void reconstruct(int src, int target){
    if(path[src][target] == INF)
        printf("%d ", src);
    else{
        reconstruct(src, path[src][target]);
        reconstruct(path[src][target], target);  
    }
}

int main() {
    for(int i=0; i<7; i++)
        for(int j=0; j<7; j++)
            path[i][j] = INF;
    
    for(int i=0; i<7; i++)
        for(int j=0; j<7; j++)
            if(graph[i][j] == 0)
                graph[i][j] = INF;
                
    floyd();
    
    printf("====== Shortest path for all vertices ======\n");
    for(int i=0; i<7; i++){
        for(int j=0; j<7; j++){
            printf("%d ", distance[i][j]);
        }
        printf("\n");
    }
    
    printf("\n");
    printf("Shortest path for 0 to 1 : ");
    reconstruct(0, 1); printf("%d", 1);
    printf("\n");
      
	  return 0;
}
