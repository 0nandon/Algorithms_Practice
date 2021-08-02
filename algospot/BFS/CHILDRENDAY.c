#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int discovered[10000]; // 발견되었는지
int Bdiscovered[10000];
int visited[10000]; // 방문했는지
int Bvisited[10000];
int distance[10000]; // start부터 최단거리
int Bdistance[10000];

// input
int n, m;
int d[9];
int dLength;
int answer;

typedef struct node{
    int index;
    int sum;
    char store[1000];
    int storeLen;
    struct node * front;
    struct node * rear;
}NODE;

typedef struct queue{
    int count;
    struct node * front;
    struct node * rear;
}QUEUE;

NODE * createNode(int index, int sum, char store[1000], int storeLen){
    NODE * newNode;
    newNode = (NODE*)malloc(sizeof(NODE));
    
    // input data
    newNode->index = index;
    newNode->sum = sum;
    newNode->storeLen = storeLen;
    strcpy(newNode->store, store);
    
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

void pushQueue(QUEUE * queue, int index, int sum, char store[1000], int storeLen){
    NODE * newNode = createNode(index, sum, store, storeLen);
    
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

void changeList(int num){
    memset(d, -1, sizeof(d));
    
    int mod;
    while(1){
        mod = num % 10;
        d[dLength++] = mod;
        num /= 10;
        
        if(num == 0)
            break;
    }
}

// 일반적인 BFS 코드
QUEUE * bfs(int start){
    QUEUE * queue = createQueue();
    char store[1000];
    pushQueue(queue, start, 0, store, 0);
    discovered[start] = 1;
    distance[start] = 0;
    
    int pop, popSum, storeLen;
    while(queue->count != 0){
        NODE * popNode = popQueue(queue);
        pop = popNode->index;
        popSum = popNode->sum;
        strcpy(store, popNode->store);
        storeLen = popNode->storeLen;
        free(popNode);
        
        // printf("%d %d\n", pop, popSum);
        
        if(popSum == -1)
            Bvisited[pop] = 1;
        else
            visited[pop] = 1;
        
        for(int i=0; i<dLength; i++){
            int there = ((pop*10) + d[i]) % n;
            int isBig;
            
            if(popSum == -1)
                isBig = 1;
            else
                isBig = ((popSum*10 + d[i]) >= n+m);
            
            if(isBig){
                if(Bvisited[there] == 1 || Bdiscovered[there] == 1)
                    continue;
            }else{
                if(visited[there] == 1 || discovered[there] == 1)
                    continue;
            }

            if(isBig && popSum == -1)
                Bdistance[there] = Bdistance[pop] + 1;
            else if(isBig && popSum != -1)
                Bdistance[there] = distance[pop] + 1;
            else
                distance[there] = distance[pop] + 1;
            
            store[storeLen] = '0' + d[i];
            if(isBig){
                Bdiscovered[there] = 1;
                pushQueue(queue, there, -1, store, storeLen+1);
            }else{
                discovered[there] = 1;
                pushQueue(queue, there, popSum*10 + d[i], store, storeLen+1);
            }
        }
        
        if(pop == m && popSum == -1){
            answer = 1;
            for(int i=0; i<storeLen; i++)
                printf("%c", store[i]);
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
        memset(Bdiscovered, -1, sizeof(discovered));
        memset(visited, -1, sizeof(visited));
        memset(Bvisited, -1, sizeof(visited));
        memset(distance, -1, sizeof(distance));
        memset(Bdistance, -1, sizeof(distance));
        
        dLength = 0; answer = 0;
        
        int dNum;
        scanf("%d%d%d", &dNum, &n, &m);
        
        changeList(dNum);
        mergeSort(d, 0, dLength-1);
        QUEUE * queue = bfs(0);
        free(queue);
        
        if(answer == 0)
            printf("IMPOSSIBLE\n");
        else
            printf("\n");
    }

	return 0;
}
