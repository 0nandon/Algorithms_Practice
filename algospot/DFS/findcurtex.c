#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int discovered[8];
int graph[8][8] = {
    {0, 1, 0, 0, 0, 0, 0, 0},
    {1, 0, 1, 1, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 0},
    {0, 1, 1, 0, 1, 1, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 1, 1, 0, 0, 1, 1},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0}
};
int cnt;

int findCurtex(int num){
    int child = 0, isCurtex = 0, isRoot = 0;
    int ret;
    
    discovered[num] = cnt++;  // discovered를 visited 배열로 대체
    int min = discovered[num];
    
    if(cnt == 1)
        isRoot = 1;
    
    for(int i=0; i<8; i++){
        if(graph[num][i] == 1){
            if(discovered[i] == -1){
                child++;
                graph[num][i]--;
                graph[i][num]--;
            
                ret = findCurtex(i);
    
                isCurtex = isCurtex || (discovered[num] <= ret);
                min = min > ret ? ret : min;
            }
            else
                min = min > discovered[i] ? discovered[i] : min;
        }
    }
    
    if(!isRoot && isCurtex)
        printf("%d ", num);
    else if(isCurtex && child > 1)
        printf("%d ", num);
    
    return min;
}

void findAll(){
    for(int i=0; i<8; i++)
        if(discovered[i] == -1)
            findCurtex(i);
}

int main() {
    memset(discovered, -1, sizeof(discovered));
    cnt = 0;

    findAll();

    return 0;
}
