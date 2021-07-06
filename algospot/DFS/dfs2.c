#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int finished[7];
int discovered[7];
int graph[7][7] = {
    {0, 1, 0, 0, 1, 1, 1},
    {0, 0, 1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 1},
    {0, 0, 0, 1, 0, 0, 0}
};
int cnt;

void dfs2(int num){
    discovered[num] = ++cnt;  // discovered를 visited 배열로 대체
    
    for(int i=0; i<7; i++){
        if(graph[num][i] == 1){
            if(discovered[i] == 0){
                printf("%d-%d : tree edge\n", num, i);
                dfs2(i);
            }
            else if(discovered[num] < discovered[i])
                printf("%d-%d : forward edge\n", num, i);
            else if(finished[i] == 0)
                printf("%d-%d : backward edge\n", num, i);
            else
                printf("%d-%d : cross edge\n", num, i);
        }
    }
    
    finished[num] = 1;  // dfs2가 끝났는지 안끝났는지 체크
}

void dfsAll(){
    for(int i=0; i<7; i++)
        if(discovered[i] == 0)
            dfs2(i);
}

int main() {
    memset(finished, 0, sizeof(finished));
    memset(discovered, 0, sizeof(discovered));
    cnt = 0;
    
    dfsAll();

    return 0;
}
