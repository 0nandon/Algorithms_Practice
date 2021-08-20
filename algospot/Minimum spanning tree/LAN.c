#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAXN 500
#define INF 987654321

int N, M;
double graph[MAXN][MAXN]; 

typedef struct node_t{
    int x, y;
}NODE;
NODE node[MAXN];

double minWeight[MAXN];
int included[MAXN];

void calDistance(){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(graph[i][j] == 0)
                continue;
            
            double dx = pow(node[i].x - node[j].x, 2);
            double dy = pow(node[i].y - node[j].y, 2);
            graph[i][j] = sqrt(dx+dy);
            graph[j][i] = sqrt(dx+dy);
        }
    }
}

double prim(int num){
    for(int i=0; i<N; i++)
        minWeight[i] = INF;
    memset(included, -1, sizeof(included));
    
    double ret = 0;
    int here = num;
    included[here] = 1;
    for(int i=0; i<N-1; i++){
        for(int there=0; there<N; there++){
            if(graph[here][there] == -1 || included[there] == 1)
                continue;
            
            if(minWeight[there] > graph[here][there])
                minWeight[there] = graph[here][there];
        }

        int minIndex = num;
        for(int j=0; j<N; j++){
            if(included[j] == 1)
                continue;
            
            minIndex = minWeight[minIndex] > minWeight[j] ? j : minIndex;
        }
 
        ret += minWeight[minIndex];
        included[minIndex] = 1;
        here = minIndex;
    }
    
    return ret;
}

int main(){
    int caseNum;
    scanf("%d", &caseNum);
    
    for(int i=0; i<caseNum; i++){
        scanf("%d%d", &N, &M);
        
        for(int a=0; a<N; a++){
            for(int b=0; b<N; b++){
                graph[a][b] = INF;
                graph[b][a] = INF;
            }
        }
        
        for(int j=0; j<N; j++)
            scanf("%d", &node[j].x);
        
        for(int j=0; j<N; j++)
            scanf("%d", &node[j].y);
        
        for(int j=0; j<M; j++){
            int n1, n2;
            scanf("%d%d", &n1, &n2);   
            graph[n1][n2] = 0.0;
            graph[n2][n1] = 0.0;
        }
        
        calDistance();
        double ret = prim(0);
        printf("%.9lf\n", ret);
    }
     
    return 0;
}
