#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// adjacency metrics
int graph[9][9] = {
    {0, 1, 0, 1, 1, 0, 0, 1, 0},
    {1, 0, 1, 1, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 1, 1, 0, 0},
    {1, 1, 0, 0, 0, 0, 1, 0, 0},
    {1, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 1, 0, 1, 0, 0, 0, 0},
    {0, 0, 1, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0},
};
int discovered[9]; // 발견되었는지
int visited[9]; // 방문했는지
int distance[9]; // start부터 최단거리
int parent[9]; // BFS spanning tree

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

// 일반적인 BFS 코드
// BFS 탐색 결과, BFS spanning tree, start로 부터 최단거리 등을 계산
QUEUE * bfs(int start){
    QUEUE * queue = createQueue();
    pushQueue(queue, start);
    discovered[start] = 1;
    
    distance[start] = 0;
    parent[start] = start;
    
    printf("BFS 탐색 결과 : ");
    while(queue->count != 0){
        int pop = popQueue(queue);
        visited[pop] = 1;
        printf("%d ", pop);
        
        for(int i=0; i<9; i++){
            if(graph[pop][i] == 0)
                continue;
            if(visited[i] == 1 || discovered[i] == 1)
                continue;
            
            distance[i] = distance[pop] + 1;
            parent[i] = pop;
            
            pushQueue(queue, i);
            discovered[i] = 1;
        }
    }
    
    return queue;
}

int main() {
    memset(discovered, -1, sizeof(discovered));
    memset(visited, -1, sizeof(visited));
    memset(distance, -1, sizeof(distance));
    memset(parent, -1, sizeof(parent));
    
    // BFS 코드
    QUEUE * queue = bfs(0);
    free(queue);
    printf("\n");
    
    // BFS spanning tree
    printf("BFS spanning tree : ");
    for(int i=0; i<9; i++)
        printf("%d ", parent[i]);
    printf("\n");
    
    // 최단거리
    printf("최단거리 : ");
    for(int i=0; i<9; i++)
        printf("%d ", distance[i]);

    return 0;
}
