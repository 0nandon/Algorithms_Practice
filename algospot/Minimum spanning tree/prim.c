#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NODENUM 7
#define MAXEDGE 21
#define INF 987654321

// adjacency metrics
int graph[NODENUM][NODENUM] = {
    {0, 5, 1, 0, 0, 0, 0}, // a
    {5, 0, 0, 1, 0, 3, 3}, // b
    {1, 0, 0, 4, 0, 0, 0}, // c
    {0, 1, 4, 0, 5, 3, 0}, // d
    {0, 0, 0, 5, 0, 0, 0}, // e
    {0, 3, 0, 3, 0, 0, 2}, // f
    {0, 3, 0, 0, 0, 2, 0}, // g
};

typedef struct node_t{
    int n1, n2;
    int distance;
}NODE;

NODE spanningTree[MAXEDGE];
int sLength = 0; // number of spanning tree's edges

int minWeight[NODENUM];
int parent[NODENUM];
int included[NODENUM];

void prim(int num){
    for(int i=0; i<NODENUM; i++)
        minWeight[i] = INF;
    memset(included, -1, sizeof(included));
    memset(parent, -1, sizeof(parent));
    
    int here = num;
    included[here] = 1;
    for(int i=0; i<NODENUM-1; i++){
        for(int there=0; there<NODENUM; there++){
            if(graph[here][there] == 0 || included[there] == 1)
                continue;
            
            if(minWeight[there] > graph[here][there]){
                minWeight[there] = graph[here][there];
                parent[there] = here;
            }
        }

        int minIndex = num;
        for(int j=0; j<NODENUM; j++){
            if(included[j] == 1)
                continue;
            
            minIndex = minWeight[minIndex] > minWeight[j] ? j : minIndex;
        }
 
        spanningTree[sLength].n1 = parent[minIndex];
        spanningTree[sLength].n2 = minIndex;
        spanningTree[sLength++].distance = minWeight[minIndex];
        included[minIndex] = 1;
        here = minIndex;
    }
    
    return;
}

int main(){
    prim(0);
    
    for(int i=0; i<sLength; i++)
        printf("%c %c\n", 'a' + spanningTree[i].n1, 'a' + spanningTree[i].n2);
     
    return 0;
}
