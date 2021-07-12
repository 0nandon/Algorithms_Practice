#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// adjacency list
int graph[40320][28];
int count[40320];
int discovered[40320]; // 발견되었는지
int visited[40320]; // 방문했는지
int distance[40320]; // start부터 최단거리

typedef struct node{
    int index;
    struct node * front;
    struct node * rear;
}NODE;

typedef struct queue{
    int count;
    struct node * front;
    struct node * rear;
}QUEUE;

NODE * createNode(int index){
    NODE * newNode;
    newNode = (NODE*)malloc(sizeof(NODE));
    newNode->index = index;
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

void pushQueue(QUEUE * queue, int index){
    NODE * newNode = createNode(index);
    
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
    int ret = ptr->index;

    if(queue->count == 1){
        queue->front = NULL;
        queue->rear = NULL;
    }else{
        ptr->front->rear = NULL;
        queue->rear = ptr->front;
    }
    
    free(ptr);
    queue->count--;
    
    return ret;
}

int fac(int num){
    if(num == 1 || num == 0)
        return 1;
    else 
        return num * fac(num-1);
}

int calBit(int num){
    int cnt = 0;
    while(1){
        if(num == 0)
            break;

        if(num%2 == 1)
            cnt++;
        
        num /= 2;
    }
    return cnt;
}

int calIndex(int array[8], int used, int index){
    if(index == 8)
        return 0;

    int idx = (1<<array[index]);
    int cnt = ~used & (idx-1);
    int bitNum = calBit(cnt);
    
    used |= idx;

    return bitNum * fac(7-index) + calIndex(array, used, index+1);
}

int flip(int array[8], int num1, int num2){
    int newArray[8];
    
    for(int i=0; i<8; i++)
        newArray[i] = array[i];
    
    for(int i=0; i<num2-num1+1; i++)
        newArray[num1+i] = array[num2-i];
    
    return calIndex(newArray, 0, 0);
}

void makeGraph(int array[8]){
    int here = calIndex(array, 0, 0);
    int there;
    for(int i=0; i<8; i++){
        for(int j=i+1; j<8; j++){
            there = flip(array, i, j);
            graph[here][count[here]++] = there;
        }
    }
}

void permutation(int array[8], int used, int index){
 
    if(index == 8){
        makeGraph(array);
        return;
    }
    
    for(int i=0; i<8; i++){
        if((used & (1<<i)) == 0){
            array[index] = i;
            permutation(array, used | (1<<i), index+1);
        }
    }
}

// 일반적인 BFS 코드
// BFS 탐색 결과, BFS spanning tree, start로 부터 최단거리 등을 계산
QUEUE * bfs(int start){
    QUEUE * queue = createQueue();
    pushQueue(queue, start);
    discovered[start] = 1;
    distance[start] = 0;
    
    while(queue->count != 0){
        int pop = popQueue(queue);
        visited[pop] = 1;
        
        for(int i=0; i<count[pop]; i++){
            int there = graph[pop][i];
            if(visited[there] == 1 || discovered[there] == 1)
                continue;
            
            distance[there] = distance[pop] + 1;
            
            pushQueue(queue, there);
            discovered[there] = 1;
        }
    }
    
    return queue;
}

int changeIndex(int array[8], int length){
    int cnt = 0;
    int changed[8];
    for(int i=0; i<length; i++){
        for(int j=0; j<length; j++)
            if(i != j && array[i] > array[j])
                cnt++;

        changed[i] = cnt;
        cnt = 0;
    }
    
    for(int i=length; i<8; i++)
        changed[i] = i;
    
    return calIndex(changed, 0, 0);
}

int main() {
    int array[8];
    memset(array, -1, sizeof(array));
    memset(count, 0, sizeof(count));
    
    permutation(array, 0, 0); // making adjacency list
    QUEUE * queue = bfs(0);
    free(queue);

    int caseNum;
    scanf("%d", &caseNum);
    
    for(int i=0; i<caseNum; i++){
        int length;
        scanf("%d", &length);
        
        int input[8];
        for(int j=0; j<length; j++)
            scanf("%d", &input[j]);
        
        printf("%d\n", distance[changeIndex(input, length)]);
    }

    return 0;
}
