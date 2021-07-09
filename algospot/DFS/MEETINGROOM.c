#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int start;
    int end;
    int isTrue;
}NODE;

NODE meetings[400];
int discovered[400];
int stack[400];
int graph[400][400];
int roomNum, count, stackCount;

int sccId[400];
int sccCount;

int isOverlap(int num1, int num2){
    return (meetings[num1].end <= meetings[num2].start) || (meetings[num2].end <= meetings[num1].start);
}

void makeImplicationGraph(){
    for(int i=0; i<roomNum; i++){
        graph[4*i+1][4*i+2] = 1;
        graph[4*i+3][4*i] = 1; 
    }
    
    for(int i=0; i<roomNum; i++){
        for(int j=i+1; j<roomNum; j++){
            if(!isOverlap(4*i, 4*j)){
                graph[4*i][4*j+1] = 1;
                graph[4*j][4*i+1] = 1;
            }
            if(!isOverlap(4*i, 4*j+2)){
                graph[4*i][4*j+3] = 1;
                graph[4*j+2][4*i+1] = 1;
            }
            if(!isOverlap(4*i+2, 4*j)){
                graph[4*i+2][4*j+1] = 1;
                graph[4*j][4*i+3] = 1;
            }
            if(!isOverlap(4*i+2, 4*j+2)){
                graph[4*i+2][4*j+3] = 1;
                graph[4*j+2][4*i+3] = 1;
            }
        }
    }
}

int scc(int here){
    discovered[here] = count++;
    stack[stackCount++] = here;
    int min = discovered[here];
    
    for(int there=0; there<roomNum*4; there++){
        if(graph[here][there] == 1){
            if(discovered[there] == -1){
                int ret = scc(there);
                min = min > ret ? ret : min;
            }else if(sccId[there] == -1)
                min = min > discovered[there] ? discovered[there] : min;
        }
    }
    
    if(min == discovered[here]){
        while(1){
            int top = stack[stackCount-1];
            sccId[top] = sccCount;
            stack[stackCount-1] = -1;
            stackCount--;
            
            if(top == here)
                break;
        }
        sccCount++;
    }
    
    return min;
}

void tarjanSCC(){
    for(int i=0; i<roomNum*4; i++)
        if(discovered[i] == -1)
            scc(i);
}

int satSolve(){
    for(int i=0; i<roomNum*2; i++)
        if(sccId[2*i] == sccId[2*i+1])
            return -1;
    
    while(1){
        if(sccCount == 0)
            break;
        
        int ret[400]; int retCount = 0;
        for(int i=0; i<roomNum*4; i++)
            if(sccId[i] == sccCount-1)
                ret[retCount++] = i;
        
        int check = 0;
        for(int i=0; i<retCount; i++){
            if(meetings[ret[i]].isTrue == 1){
                check = 1;
                break;
            }
        }
        
        for(int i=0; i<retCount; i++){
            meetings[ret[i]].isTrue = check;
                
            if(ret[i]%2 == 1)
                meetings[ret[i]-1].isTrue = !check;
            else
                meetings[ret[i]+1].isTrue = !check;
        }
        
        sccCount--;
    }
}

int main() {
    int caseNum;
    scanf("%d", &caseNum);
    
    for(int i=0; i<caseNum; i++){
        scanf("%d", &roomNum);
        memset(stack, -1, sizeof(stack));
        memset(discovered, -1, sizeof(discovered));
        memset(graph, -1, sizeof(graph));
        memset(sccId, -1, sizeof(sccId));
        sccCount = 0; count = 0; stackCount = 0;
        
        int cnt = 0;
        for(int j=0; j<roomNum*2; j++){
            int num1, num2;
            scanf("%d%d", &num1, &num2);
            
            for(int a=0; a<2; a++){
                meetings[cnt].start = num1;
                meetings[cnt].end = num2;
                meetings[cnt++].isTrue = -1;
            }
        }
        
        makeImplicationGraph();
        tarjanSCC();
        int check = satSolve();
        
        if(check == -1)
            printf("IMPOSSIBLE\n");
        else{
            printf("POSSIBLE\n");
            for(int j=0; j<roomNum; j++){
                if(meetings[4*j].isTrue)
                    printf("%d %d\n", meetings[4*j].start, meetings[4*j].end);
                else
                    printf("%d %d\n", meetings[4*j+2].start, meetings[4*j+2].end);
            }
        }
    }

    return 0;
}
