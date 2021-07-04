#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char input[1000][21];
int num;
int dicNum;
int graph[26][26];
int visited[26];
int sorted[26];

void makeGraph(){
    for(int i=1; i<num; i++){
        int cnt = 0;
        while(input[i][cnt] == input[i-1][cnt]){
            if(input[i][cnt] == 0 || input[i-1][cnt] == 0)
                break;
            cnt++;
        }
        if(input[i][cnt] == 0 || input[i-1][cnt] == 0)
            continue;
        
        graph[input[i-1][cnt] - 'a'][input[i][cnt] - 'a'] = 1;
    }
}

int dfs(int i){
    visited[i] = 1;
    
    for(int j=0; j<26; j++)
        if(graph[i][j] == 1 && visited[j] == -1)
            dfs(j);
    
    sorted[dicNum++] = i + 'a';
}

void dfsAll(){
    for(int i=0; i<26; i++)
        if(visited[i] == -1)
            dfs(i);
    
    for(int i=0; i<dicNum; i++){
        for(int j=i+1; j<dicNum; j++){
            if(graph[sorted[i] - 'a'][sorted[j] - 'a'] == 1){
                printf("INVALID HYPOTHESIS");
                return;
            }
        }
    }
    
    for(int i=dicNum-1; i>-1; i--)
        printf("%c", sorted[i]);
}

int main() {
    int caseNum;
    scanf("%d", &caseNum);
    
    for(int i=0; i<caseNum; i++){
        scanf("%d", &num);
        memset(visited, -1, sizeof(visited));
        memset(graph, 0, sizeof(graph));
        memset(sorted, -1, sizeof(sorted));
        
        for(int j=0; j<num; j++)
            scanf("%s", input[j]);
        
        dicNum = 0;
        makeGraph();
        dfsAll();
        printf("\n");
    }

	return 0;
}