#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct edge{
    int g1, g2;
    int distance;
}EDGE;

EDGE edge[1000];
int reachable[100][100];
int distance[100];
int g, w;

// 플로이드 알고리즘
void calReachable(){
    for(int i=0; i<g; i++)
        for(int j=0; j<g; j++)
            if(i != j)
                reachable[i][j] = reachable[i][j] || (reachable[i][0] && reachable[0][j]);
            else
                reachable[i][j] = 1;
    
    for(int k=0; k<g; k++)
        for(int i=0; i<g; i++)
            for(int j=0; j<g; j++)
                reachable[i][j] = reachable[i][j] || (reachable[i][k] && reachable[k][j]);
}

int bellmanFord(int start){
    for(int i=0; i<g; i++)
        distance[i] = INF;
    distance[start] = 0;
    
    int here, there;
    int cnt = 0;
    for(int i=0; i<g; i++){
        for(int j=0; j<w; j++){
            here = edge[j].g1;
            there = edge[j].g2;
            
            if(distance[there] > distance[here] + edge[j].distance){
                distance[there] = distance[here] + edge[j].distance;
                
                if(i == g-1)
                    return there;
            }
            else
                cnt++;
        }
        
        if(cnt == w)
            return -1;
        cnt = 0;
    }
}

void changeWeight(){
    for(int i=0; i<w; i++)
        edge[i].distance *= -1;
}

void checkGraph(int cycle, int firstOrSecond){
    if(cycle != -1 && (reachable[0][cycle] && reachable[cycle][1]))
        printf("INFINITY");
    else if(firstOrSecond == 0)
        printf("%d", distance[1]);
    else
        printf("%d", -distance[1]);
    
    if(firstOrSecond == 0)
        printf(" ");
    else
        printf("\n");
}

int main() {
    int caseNum;
    scanf("%d", &caseNum);
    
    
    for(int i=0; i<caseNum; i++){
        scanf("%d%d", &g, &w);
        
        memset(reachable, 0, sizeof(reachable));
        
        int cycle = 0, min, max;
        for(int j=0; j<w; j++){
            scanf("%d%d%d", &edge[j].g1, &edge[j].g2, &edge[j].distance);
            reachable[edge[j].g1][edge[j].g2] = 1;
        }
        
        calReachable();
        if(!reachable[0][1])
            printf("UNREACHABLE\n");
        else{
            cycle = bellmanFord(0);
            checkGraph(cycle, 0);
            changeWeight();
            cycle = bellmanFord(0);
            checkGraph(cycle, 1);
        }
    }
      
    return 0;
}
