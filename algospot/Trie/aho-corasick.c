#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHABETS 26
#define NUM 4

typedef struct node_t{
    int isTerminal;
    int HArray[NUM];
    int HLen;
    
    struct node_t * parent;
    struct node_t * fail;
    struct node_t * child[ALPHABETS];
}NODE;

typedef struct qnode_t{
    NODE * node;
    int c;
    struct qnode_t * front;
    struct qnode_t * rear;
}QNODE;

typedef struct queue{
    int count;
    struct qnode_t * front;
    struct qnode_t * rear;
}QUEUE;

NODE * createNode(){
    NODE * newNode = (NODE*)malloc(sizeof(NODE));
    newNode->isTerminal = 0;
    newNode->HLen = 0;
    
    newNode->fail = NULL;
    newNode->parent = NULL;
    for(int i=0; i<ALPHABETS; i++)
        newNode->child[i] = NULL;
    
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

QNODE * createQNode(NODE * node, int c){
    QNODE * qnode;
    qnode = (QNODE*)malloc(sizeof(QNODE));
    qnode->node = node;
    qnode->c = c;
    qnode->front = NULL;
    qnode->rear = NULL;
}

void pushQueue(QUEUE * queue, NODE * node, int c){
    QNODE * newNode = createQNode(node, c);
    
    newNode->rear = queue->front;
    if(queue->count == 0)
        queue->rear =newNode;
    else
        queue->front->front = newNode;
    
    queue->front = newNode;
    queue->count++;
    
    return;
}

QNODE * popQueue(QUEUE * queue){
    QNODE * ptr = queue->rear;

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

int toNumber(char c){
    return c - 'A';
}

void insertNode(NODE * root, char * c, int index){
    if(*c == 0){
        root->isTerminal = 1;
        root->HArray[root->HLen++] = index;
        return;
    }
    
    int next = toNumber(*c);
    if(root->child[next] == NULL){
        root->child[next] = createNode();
        root->child[next]->parent = root;
    }
    insertNode(root->child[next], c+1, index);
}

NODE * findFailure(NODE * check, int next){
    NODE * ret = check->fail;
    if(ret == NULL)
        return check;
    if(ret->child[next] != NULL)
        return ret->child[next];
    return findFailure(ret, next);
}

void outputCopy(NODE * node1, NODE * node2){
    int start = node1->HLen;
    for(int i=0; i<node2->HLen; i++)
        node1->HArray[start+i] = node2->HArray[i];
    node1->HLen += node2->HLen;
}

QUEUE * connectFailure(NODE * root){
    QUEUE * queue = createQueue();
    pushQueue(queue, root, -1);
    
    while(queue->count != 0){
        QNODE * popQ = popQueue(queue);
        NODE * pop = popQ->node;
        int popc = popQ->c;
        free(popQ);
        
        if(pop->parent != NULL){
            pop->fail = findFailure(pop->parent, popc);
            outputCopy(pop, pop->fail);
        }
            
        for(int i=0; i<ALPHABETS; i++){
            if(pop->child[i] == NULL)
                continue;

            pushQueue(queue, pop->child[i], i);
        }
    }
    
    return queue;
}

void destroyTrie(NODE * root){
    if(root){
        for(int i=0; i<ALPHABETS; i++)
            destroyTrie(root->child[i]);
        free(root);
    }
}

// 아호-코라이식으로 문자열 검색
void ahoCorasick(char * N, NODE * trie){
    int len = strlen(N);
    NODE * nowNode = trie;
    
    for(int i=0; i<len; i++){
        int next = toNumber(N[i]);
        while(nowNode->child[next] == NULL && nowNode != NULL)
             nowNode = nowNode->fail;
        
        if(nowNode == NULL)
            continue;
        
        nowNode = nowNode->child[next];
        
        if(nowNode->HLen > 0){
            printf("%d 인 지점에서 발견된 바늘 : ", i);
            for(int j=0; j<nowNode->HLen; j++)
                printf("%d ", nowNode->HArray[j]);
            printf("\n");
        }
    }
}

int main(){
    char * HArray[NUM] = {"CACHE", "HE", "CHEF", "ACHY"};
    char * N = "CACACHEFCACHY";
    
    NODE * trie = createNode();
    for(int i=0; i<NUM; i++)
        insertNode(trie, HArray[i], i);
    
    QUEUE * queue = connectFailure(trie);
    free(queue);
    
    ahoCorasick(N, trie);
    
    destroyTrie(trie);
    return 0;
}
