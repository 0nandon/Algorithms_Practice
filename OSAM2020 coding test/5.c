#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct edge{
	int index;
	struct edge * link;
}EDGE;

typedef struct stack{
	int cycle;
	int startEdge;
	struct stack * link;
}STACK;

typedef struct dfs{
	int index;
	struct dfs * link;
}DFS;

typedef struct cycle{
	int data;
	int check;
	struct cycle * link;
}CYCLE;

//각각의 노드들이 몇개의 사이클 안에 포함되어 있는지 저장
CYCLE * cycleNum[200000];
CYCLE * ptrC[200000];

int visited[200000];
int check[200000];
int backT[200000];
int cycle = 0;

//사이클 저장 스택
STACK * stack = NULL;
DFS * stackDFS = NULL;

//사이클을 이루는 노드를 저장하는 트리
CYCLE * cycleTree = NULL;

EDGE * graph[200000];
EDGE * ptr[200000];

void doMalloc(int nodeNum){
	for(int i = 0; i<nodeNum; i++){
		EDGE * newEdge = (EDGE*)malloc(sizeof(EDGE));
		newEdge->index = 0;
		newEdge->link = NULL;
		graph[i] = newEdge;
		ptr[i] = graph[i];
	}
}

void addEdge(int num1, int num2){
	EDGE * newEdge = (EDGE*)malloc(sizeof(EDGE));
	newEdge->link = NULL;
	newEdge->index = num2;

	ptr[num1]->link = newEdge;
	ptr[num1] = ptr[num1]->link;
	graph[num1]->index++;
}

void pushStack(int num){
	STACK * newStack = (STACK*)malloc(sizeof(STACK));
	newStack->cycle = cycle;
	newStack->startEdge = num;
	newStack->link = NULL;
	
	if(stack->link == NULL)
		stack->link = newStack;
	else{
		STACK * ptr_s;
		ptr_s = stack->link;
		stack->link = newStack;
		newStack->link = ptr_s;
	}
}

void popStack(){
	STACK * ptr_s = stack->link;
	stack->link = ptr_s->link;
	free(ptr_s);
}

void makeCycleLink(int there){
	if(cycleNum[there] == NULL){
		CYCLE * newInCycle = (CYCLE*)malloc(sizeof(CYCLE));
		newInCycle->data = 0;
		newInCycle->link = NULL;
		cycleNum[there] = newInCycle;
		
		CYCLE * newCycle = (CYCLE*)malloc(sizeof(CYCLE));
	    newCycle->data = stack->link->cycle;
		newCycle->check = 0;
	    newCycle->link = NULL;
	    cycleNum[there]->link = newCycle;
	    cycleNum[there]->data++;

		ptrC[there] = cycleNum[there]->link;
		return;
	}
	
	CYCLE * newCycle = (CYCLE*)malloc(sizeof(CYCLE));
	newCycle->data = stack->link->cycle;
	newCycle->link = NULL;
	ptrC[there]->link = newCycle;
	cycleNum[there]->data++;
	
	ptrC[there] = ptrC[there]->link;
}

void pushStackDFS(int num){
	DFS * newStack = (DFS*)malloc(sizeof(DFS));
	newStack->index = num;
	newStack->link = NULL;
	
	if(stackDFS->link == NULL)
		stackDFS->link = newStack;
	else{
		DFS * ptr_s;
		ptr_s = stackDFS->link;
		stackDFS->link = newStack;
		newStack->link = ptr_s;
	}
}

void popStackDFS(){
	DFS * ptr_s = stackDFS->link;
	stackDFS->link = ptr_s->link;
	free(ptr_s);
}

int back = 0;
void dfs(int there){
	pushStackDFS(there);
	visited[there] = 1;
	check[there] = 1;
	
	int ret, temp, i;
	while(1){
		ret = stackDFS->link->index;
		if(stack->link != NULL && stack->link->startEdge == ret){
		    makeCycleLink(ret);
			popStack();
	    }
        
		EDGE * ptrE = graph[ret]->link;
		for(i = 0; i<graph[ret]->index; i++){
			if(ptrE->index == -1) {
				ptrE = ptrE->link;
				continue;
			}
			break;
		}
		
		if(i == graph[ret]->index){
			if(backT[ret]) back = backT[ret];
			if(stack->link != NULL && back)
				makeCycleLink(ret);
			check[ret] = 0;
			popStackDFS();
			if(stackDFS->link == NULL) break;
		}
		else{
			if(visited[ret]){
				if(!backT[ret]) backT[ret] = back;
			    back = 0; 
			}
			
			temp = ptrE->index;
		    ptrE->index = -1;
			
			if(visited[temp] && check[temp]){
				back = 1;
				pushStack(temp);
			    cycle++;
			}
			else if(!visited[temp]){
				pushStackDFS(temp);
				visited[temp] = 1;
				check[temp] = 1;
			}
		}
	}
	check[there] = 0;
}

void dfsAll(int nodeNum){
	for(int i = 0; i<nodeNum; i++)
		if(!visited[i])
			dfs(i);
}

void goBack(int isCycle[], int sortArr[], int start){
    CYCLE * ptr_t = cycleNum[sortArr[start]]->link;
	for(int i = 0; i<cycleNum[sortArr[start]]->data; i++){
		if(ptr_t->check){
		    isCycle[ptr_t->data] = 0;
			ptr_t->check = 0;
		}
		ptr_t = ptr_t->link;
	}
}

int eliminateCycle(int sortArr[], int isCycle[], int start, int length){
	if(start == length) return cycle;
	
	int ret = 0;
	int temp = cycle;
	
	CYCLE * ptr_t = cycleNum[sortArr[start]]->link;
	for(int i = 0; i<cycleNum[sortArr[start]]->data; i++){
		if(!isCycle[ptr_t->data]){
		    isCycle[ptr_t->data] = 1;
			ptr_t->check = 1;
			cycle--;
			ret = 1;
		}
		ptr_t = ptr_t->link;
	}
	
	if(!cycle) {
		goBack(isCycle, sortArr, start);
		return 1;
	}
	
	int num1 = eliminateCycle(sortArr, isCycle, start+1, length);
	cycle = temp;
	
	goBack(isCycle, sortArr, start);

	int num2 = eliminateCycle(sortArr, isCycle, start+1, length);

	if(ret+num1 > num2) return num2;
	else return ret+num1;
}

void destroyGraph(int nodeNum){
	EDGE * ptrE;
	for(int i = 0; i<nodeNum; i++){
		ptrE = graph[i]->link;
		for(int j = 0; j<graph[i]->index; j++){
			free(ptrE);
		    ptrE = ptrE->link;
		}
		free(graph[i]);
	}
}

void destroyCycleNum(int nodeNum){
	CYCLE * ptrT;
	for(int i = 0; i<nodeNum; i++){
		if(cycleNum[i] != NULL){
			ptrT = cycleNum[i]->link;
			for(int j = 0; j<cycleNum[i]->data; j++){
			    free(ptrT);
		        ptrT = ptrT->link;
		    }
		    free(cycleNum[i]);	
		}
	}
}

int solution(){
	doMalloc(n);
	memset(visited, 0, sizeof(visited));
	memset(check, 0, sizeof(check));
	memset(backT, 0, sizeof(back));
	
	for(int i = 0; i<res_rows; i++)
		addEdge(res[i][0], res[i][1]);

	stack = (STACK*)malloc(sizeof(STACK));
	stack->link = NULL;
	stackDFS = (DFS*)malloc(sizeof(DFS));
	stackDFS->link = NULL;
	
	for(int i = 0; i<n; i++)
		cycleNum[i] = NULL;

	dfsAll(n);

	int sortArr[n];
    int length = 0;
	for(int i = 0; i<n; i++){
		if(cycleNum[i] != NULL && cycleNum[i]->data > 1){
			sortArr[length] = i;
			length++;
		}
	}

	int isCycle[cycle];
	memset(isCycle, 0, sizeof(isCycle));

	int answer = n - eliminateCycle(sortArr, isCycle, 0, length);

	free(stack);
	free(stackDFS);
	destroyGraph(n);
	destroyCycleNum(n);
	
	return answer;
}
