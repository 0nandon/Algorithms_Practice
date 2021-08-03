#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int discovered[20000]; // 발견되었는지
int visited[20000]; // 방문했는지
int distance[20000]; // start부터 최단거리

int parent[20000];
int choice[20000];
char string[20000];

// input
int n, m;
int d[10];
int dLength;
int answer;

typedef struct node{
    int index;
    int sum;
    struct node * front;
    struct node * rear;
}NODE;

typedef struct queue{
    int count;
    struct node * front;
    struct node * rear;
}QUEUE;

NODE * createNode(int index, int sum){
    NODE * newNode;
    newNode = (NODE*)malloc(sizeof(NODE));
    
    // input data
    newNode->index = index;
    newNode->sum = sum;
    
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

void pushQueue(QUEUE * queue, int index, int sum){
    NODE * newNode = createNode(index, sum);
    
    newNode->rear = queue->front;
    if(queue->count == 0)
        queue->rear =newNode;
    else
        queue->front->front = newNode;
    
    queue->front = newNode;
    queue->count++;
    
    return;
}

NODE * popQueue(QUEUE * queue){
    NODE * ptr = queue->rear;
    
    if(queue->count == 1){
        queue->front = NULL;
        queue->rear = NULL;
    }else{
        ptr->front->rear = NULL;
        queue->rear = ptr->front;
    }
    
    queue->count--;
    
    return ptr;
}

//병합 정렬 소스
void merge(int arr[], int start, int half, int end){
	int temp[end-start+1];
	for(int i = 0; i<end-start+1; i++)
	    temp[i] = arr[start+i];
	
	int cnt = 0, left = 0, right = 0;
	while(left < half+1 && right < end-start-half){
	    if(temp[left] > temp[half+1+right]){
		arr[start+cnt] = temp[half+1+right]; 
                right++; cnt++;
            }
	    else{
                arr[start+cnt] = temp[left]; 
                left++; cnt++;
            }
	}
	
	if(left == half+1)
	    for(int i = 0; i<end-start-half-right; i++)
		arr[start+cnt+i] = temp[half+1+right+i];
	else if(right == end-start-half)
	    for(int i = 0; i<half+1-left; i++)
		arr[start+cnt+i] = temp[left+i];
}

// 병합정렬 구현 소스
void mergeSort(int arr[], int start, int end){
    if(start != end){
	int half = (end-start)/2;
	mergeSort(arr, start, start+half);
        mergeSort(arr, start+half+1, end);
        merge(arr, start, half, end);
    }
}

void changeList(char dString[10]){
    memset(d, -1, sizeof(d));
    dLength = strlen(dString);
    
    for(int i=0; i<dLength; i++)
        d[i] = dString[i] - '0';
    
    mergeSort(d, 0, dLength-1);
}

// 일반적인 BFS 코드
QUEUE * bfs(int start){
    QUEUE * queue = createQueue();
    pushQueue(queue, start, 0);
    discovered[start] = 1;
    distance[start] = 0;
    
    int pop, popSum;
    while(queue->count != 0){
        NODE * ptr = popQueue(queue);
        pop = ptr->index;
        popSum = ptr->sum;
        free(ptr);
        
        visited[pop] = 1;
        
        for(int i=0; i<dLength; i++){
            int there = ((pop*10) + d[i]) % n;
            int thereSum;
            
            if(pop >= n || (popSum*10 + d[i]) >= n+m){
                there += n;
                thereSum = -1;
            }
            else
                thereSum = popSum*10 + d[i];
            
            if(visited[there] == 1 || discovered[there] == 1)
                continue;

            distance[there] = distance[pop] + 1;
            discovered[there] = 1;
            pushQueue(queue, there, thereSum);
            
            parent[there] = pop;
            choice[there] = d[i];
        }
        
        if(pop == n+m){
            int ret = pop;
            int cnt = 0;
            while(ret != 0){
                string[cnt++] = choice[ret] + '0';
                ret = parent[ret];
            }
            
            for(int i=cnt-1; i>-1; i--)
                printf("%c", string[i]);
            
            answer = 1;
            break;
        }
    }
    
    return queue;
}

int main() {
    int caseNum;
    scanf("%d", &caseNum);
    
    for(int i=0; i<caseNum; i++){
        memset(discovered, -1, sizeof(discovered));
        memset(visited, -1, sizeof(visited));
        memset(distance, -1, sizeof(distance));
        
        memset(choice, -1, sizeof(choice));
        memset(parent, -1, sizeof(parent));
        
        dLength = 0; answer = 0;
        
        char dString[10];
        scanf("%s%d%d", dString, &n, &m);
        
        changeList(dString); 
        QUEUE * queue = bfs(0);
        free(queue);
        
        if(answer == 0)
            printf("IMPOSSIBLE\n");
        else
            printf("\n");
    }

    return 0;
}
