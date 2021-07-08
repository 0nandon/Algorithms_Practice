#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WATCHED 1
#define ON 2
#define OFF 0

int graph[1000][1000];
int count[1000];
int visited[1000];
int vertex, edge;
int cnt;

int gallery(int num, int isRoot){
    visited[num] = 1;
    int isWatched = 0;
    int ret, check = 0;
    
    for(int i=0; i<count[num]; i++){
        if(visited[graph[num][i]] == 1)
            continue;
        
        ret = gallery(graph[num][i], 0);

        if(ret == 2)
            check = 1;
        
        isWatched = isWatched || !ret;
    }
    
    if(isRoot && check != 1){
        cnt++;
        return -1;
    }
    else if(isWatched){
        cnt++;
        return ON;
    }
    else if(check)
        return WATCHED;
    
    return OFF;
}

void galleryAll(){
    for(int i=0; i<vertex; i++)
        if(visited[i] == -1)
            gallery(i, 1);
}

int main() {
    int caseNum;
    scanf("%d", &caseNum);
    int answer[caseNum];
    
    for(int i=0; i<caseNum; i++){
        memset(visited, -1, sizeof(visited));
        memset(graph, -1, sizeof(graph));
        memset(count, 0, sizeof(count));
        cnt = 0;
        
        scanf("%d%d", &vertex, &edge);
        for(int j=0; j<edge; j++){
            int num1, num2;
            scanf("%d%d", &num1, &num2);
            
            graph[num1][count[num1]++] = num2;
            graph[num2][count[num2]++] = num1;
        }
            
        galleryAll();
        answer[i] = cnt;
    }

    for(int i=0; i<caseNum; i++)
        printf("%d\n", answer[i]);

	return 0;
}
