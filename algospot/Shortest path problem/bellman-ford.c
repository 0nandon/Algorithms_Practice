#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 987654321
#define VERTEXNUM 7

int graph[VERTEXNUM][VERTEXNUM] = {
    {0, 5, 1, 0, 0, 0, 0},
    {5, 0, 0, 1, 0, 3, 3},
    {1, 0, 0, 2, 0, 0, 0},
    {0, 1, 2, 0, 5, 3, 0},
    {0, 0, 0, 5, 0, 0, 0},
    {0, 3, 0, 3, 0, 0, 2},
    {0, 3, 0, 0, 0, 2, 0},
};

int circleGraph[VERTEXNUM][VERTEXNUM] = {
    {0, 5, 1, 0, 0, 0, 0},
    {5, 0, 0, -3, 0, 3, 3},
    {1, 0, 0, 2, 0, 0, 0},
    {0, -3, 2, 0, 5, 3, 0},
    {0, 0, 0, 5, 0, 0, 0},
    {0, 3, 0, 3, 0, 0, 2},
    {0, 3, 0, 0, 0, 2, 0},
};
int distance[VERTEXNUM];

int bellmanFord(int start){
    for(int i=0; i<VERTEXNUM; i++)
        distance[i] = INF;
    distance[0] = 0;
    
    int check = 1;
    for(int i=0; i<VERTEXNUM; i++){
        for(int j=0; j<VERTEXNUM; j++){
            for(int a=0; a<VERTEXNUM; a++){
                if(graph[j][a] == 0)
                    continue;
                
                if(distance[a] > distance[j] + graph[j][a]){
                    distance[a] = distance[j] + graph[j][a];
                    
                    if(i == VERTEXNUM-1)
                        check = -1;
                }
            }
        }     
    }
    
    if(check == -1)
        return -1;
    else
        return 1;
}

int main() {
    int check = bellmanFord(0);
    
    if(check == 1)
        for(int i = 0; i<VERTEXNUM; i++)
            printf("%d ", distance[i]);
    else
        printf("IMPOSSIBLE");
        
    return 0;
}
