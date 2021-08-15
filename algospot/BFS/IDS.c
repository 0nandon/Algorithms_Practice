#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 987654321

int graph[9][9] = {
    {0, 1, 0, 1, 1, 0, 0, 1, 0},
    {1, 0, 1, 1, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 1, 1, 0, 0},
    {1, 1, 0, 0, 0, 0, 1, 0, 0},
    {1, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 1, 0, 1, 0, 0, 0, 0},
    {0, 0, 1, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0},
};
int distance[9];
int step = 0;

void dfs(int here, int now){
    if(now > step)
        return;
    
    for(int there=0; there<9; there++){
        if(graph[here][there] == 0)
            continue;
        
        dfs(there, now+1);
    }
    
    distance[here] = distance[here] > now ? now : distance[here];
}


int ids(int src, int target){
    for(int i=0; i<9; i++)
        distance[i] = INF;
    
    while(distance[target] == INF){
        step++;
        dfs(src, 0);
    }
    
    return distance[target];
}

int main(){
    printf("%d", ids(0, 8));
    
    return 0;
}
