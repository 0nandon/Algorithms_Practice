#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int discovered[11];
int sccId[11];
int stack[11];
int graph[11][11] = {
    {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, // 0
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, // 1
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 2
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0}, // 3
    {0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0}, // 4
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, // 5
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, // 6
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0}, // 7
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 8
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, // 9
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, // 10
};
int sccCount, cnt, stackCnt;

int scc(int num){    
    discovered[num] = cnt++;
    stack[stackCnt++] = num;
    int min = discovered[num];
    
    for(int i=0; i<11; i++){
        if(graph[num][i] == 1){
            if(discovered[i] == -1){
                int ret = scc(i);
                min = min > ret ? ret : min;
            }else if(sccId[i] == -1)
                min = min > discovered[i] ? discovered[i] : min;
        }
    }
    
    if(min == discovered[num]){
        while(1){
            sccId[stack[stackCnt-1]] = sccCount;
            stackCnt--;
            if(stack[stackCnt] == num)
                break;

            stack[stackCnt] = -1;
        }
        stack[stackCnt] = -1;
        sccCount++;
    }
    
    return min;
}

void tarjanSCC(){
    for(int i=0; i<11; i++)
        if(discovered[i] == -1)
            scc(i);
}

int main() {
    memset(discovered, -1, sizeof(discovered));
    memset(sccId, -1, sizeof(sccId));
    memset(stack, -1, sizeof(stack));
    sccCount = 0;
    cnt = 0;
    stackCnt = 0;

    tarjanSCC();
    
    for(int i=0; i<11; i++)
        printf("%d ", sccId[i]);

    return 0;
}
