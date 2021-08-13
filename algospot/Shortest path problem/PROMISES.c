#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 987654321

int v, m, n;
int graph[200][200];

int min(int num1, int num2){
    return num1 > num2 ? num2 : num1;
}

// 플로이드 알고리즘
void floyd(){
    for(int i=0; i<v; i++)
        for(int j=0; j<v; j++)
            if(i != j)
                graph[i][j] = min(graph[i][j], graph[i][0] + graph[0][j]);
            else
                graph[i][j] = 0;
    
    for(int k=0; k<v; k++)
        for(int i=0; i<v; i++)
            for(int j=0; j<v; j++)
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
}
                                     
int promises(int a, int b, int c){
    if(graph[a][b] <= c)
        return 1;
    
    for(int i=0; i<v; i++){
        for(int j=0; j<v; j++){
            graph[i][j] = min(
                graph[i][j],
                min(graph[i][a] + graph[b][j] + c,
                    graph[i][b] + graph[a][j] + c)
            );
        }
    }
    
    return 0;
}

int main(){
    int caseNum, answer;
    scanf("%d", &caseNum);
    
    for(int i=0; i<caseNum; i++){
        scanf("%d%d%d", &v, &m, &n);
        
        answer = 0;
        for(int j=0; j<v; j++)
            for(int k=0; k<v; k++)
                graph[j][k] = INF;
        
        int num1, num2, distance;
        for(int j=0; j<m; j++){
            scanf("%d%d%d", &num1, &num2, &distance);
            
            if(distance >= graph[num1][num2])
                continue;
            
            graph[num1][num2] = distance;
            graph[num2][num1] = distance;
        }
        
        floyd();
        
        for(int j=0; j<n; j++){
            scanf("%d%d%d", &num1, &num2, &distance);
            
            answer += promises(num1, num2, distance);
        }
        
        printf("%d\n", answer);
    }
    
	return 0;
}
