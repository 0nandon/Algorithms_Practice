#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
	int data;
	struct node * link;
}NODE;

typedef struct queue{
	int count;
	struct node * rear;
	struct node * front;
}QUEUE;

long int signal = 1983;


long int expNum;

void makeSignal(int num){
	expNum = 4294967296;
	if(num != 0)
		signal = (signal*214013+2531011)%expNum;
}

QUEUE * pushNode(QUEUE * queue, int signal){
	NODE * newNode = (NODE*)malloc(sizeof(NODE));
	newNode->data = signal;
	newNode->link = NULL;
	
	NODE * ptr;
	if(queue->front == NULL){
		queue->front = newNode;
		queue->rear = newNode;
	}
	else{
		queue->rear->link = newNode;
		queue->rear = newNode;
	}
	queue->count++;
	
	return queue;
}

QUEUE * popNode(QUEUE * queue){
	NODE * ptr;
	ptr = queue->front;
	queue->front = ptr->link;
	free(ptr);
	queue->count--;
	
	return queue;
}

void destroyQueue(QUEUE * queue){
	while(queue->front != NULL){
		NODE * ptr;
		ptr = queue->front;
		queue->front = ptr->link;
		free(ptr);
	}
	free(queue);
}

int countSection(int sum, int num){
	QUEUE * queue = (QUEUE*)malloc(sizeof(QUEUE));
	queue->count = 0;
	queue->rear = NULL;
	queue->front = NULL;
	
	int signal_new;
	
	int index = 0, sumP = 0, ret = 0;
	while(index<num){
		while(sumP<sum){
			makeSignal(index);
			signal_new = signal%10000+1;
			sumP += signal_new;
			if(sumP == sum) ret++;
			queue = pushNode(queue, signal_new);
			index++;
		}
		while(sumP>=sum){
			sumP -= queue->front->data;
			queue = popNode(queue);
			if(sumP == sum) ret++;
		}
	}
	
	destroyQueue(queue);
    return ret;
}

int main() {
	int caseNum;
	scanf("%d", &caseNum);
	int answer[caseNum];
	
	for(int i = 0; i<caseNum; i++){
	    int sum, num;
		scanf("%d%d", &sum, &num);
		answer[i] = countSection(sum, num);
		signal = 1983;
	}
	for(int i = 0; i<caseNum; i++) printf("%d\n", answer[i]);
	
	return 0;
}
