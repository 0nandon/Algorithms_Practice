#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DICS 12

// input
int hanoiNum;
int answer;

int distance[1<<(MAX_DICS*2)];

typedef struct node{
    int state;
    struct node * front;
    struct node * rear;
}NODE;

typedef struct queue{
    int count;
    struct node * front;
    struct node * rear;
}QUEUE;

NODE * createNode(int state){
    NODE * newNode;
    newNode = (NODE*)malloc(sizeof(NODE));
    
    // input data
    newNode->state = state;
    
    // link null
    newNode->front = NULL;
    newNode->rear = NULL;
    
    return newNode;
}

QUEUE * createQueue(){
    QUEUE * queue;
    queue = (QUEUE*)malloc(sizeof(QUEUE));
    queue->count = 0;
    queue->front = NULL;
    queue->rear = NULL;
    
    return queue;
}

void pushQueue(QUEUE * queue, int state){
    NODE * newNode = createNode(state);
    
    newNode->rear = queue->front;
    if(queue->count == 0)
        queue->rear =newNode;
    else
        queue->front->front = newNode;
    
    queue->front = newNode;
    queue->count++;
    
    return;
}


int popQueue(QUEUE * queue){
    NODE * ptr = queue->rear;
    int pop = ptr->state;
    
    if(queue->count == 1){
        queue->front = NULL;
        queue->rear = NULL;
    }else{
        ptr->front->rear = NULL;
        queue->rear = ptr->front;
    }
    
    free(ptr);
    queue->count--;
    
    return pop;
}

void freeQueue(QUEUE * queue){
    while(queue->count != 0)
        popQueue(queue);
    
    free(queue);
}

// 하노이의 상태가 state일때, hanoi번 원판이 꽂혀있는 기둥의 번호를 반환
int get(int state, int hanoi){
    return (state >> (hanoi*2)) & 3;
}

// 하노이의 hanoi번 원판을 pillar 기둥으로 이동
int set(int state, int hanoi, int pillar){
    return (state & ~(3 << (hanoi*2))) | (pillar << (hanoi*2));
}

int bidrectional(int start, int end){
    QUEUE * queue = createQueue();
    pushQueue(queue, start);
    pushQueue(queue, end);
    distance[start] = 1;
    distance[end] = -1;
    
    while(queue->count != 0){
        int pop = popQueue(queue);
        
        int top[4] = {-1, -1, -1, -1};
        for(int i=0; i<hanoiNum; i++){
            if(top[get(pop, i)] != -1)
                continue;
        
            top[get(pop, i)] = i;
        } 
        
        int newState;
        for(int i=0; i<4; i++){
            if(top[i] == -1)
                continue;
            
            for(int j=0; j<4; j++){
                if(i == j)
                    continue;
                
                if(top[j] != -1 && top[i] > top[j])
                    continue;
                
                newState = set(pop, top[i], j);
                
                if(distance[newState] != 0){
                    if(distance[pop] * distance[newState] < 0){
                        freeQueue(queue);
                        return abs(distance[pop]) + abs(distance[newState]) - 1;
                    }
                    
                    continue;
                }
                
                if(distance[pop] > 0)
                    distance[newState] = distance[pop] + 1;
                else
                    distance[newState] = distance[pop] - 1;
                
                pushQueue(queue, newState);
            }
        }
    }
}

int main() {
    int caseNum;
    scanf("%d", &caseNum);
    int answer[caseNum];
    
    for(int i=0; i<caseNum; i++){
        scanf("%d", &hanoiNum);
        int num, hanoi;
        int start = 0; 
        
        memset(distance, 0, sizeof(distance));
        
        for(int j=0; j<4; j++){
            scanf("%d", &num);
            
            for(int a=0; a<num; a++){
                scanf("%d", &hanoi);
                start = set(start, hanoi-1, j);
            }
        }
        
        answer[i] = bidrectional(start, (1<<(hanoiNum*2))-1);
    }
    
    for(int i=0; i<caseNum; i++)
        printf("%d\n", answer[i]);
    
	  return 0;
}
