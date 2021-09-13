#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHABETS 26
#define MAXN 10000
#define MAXM 20000

typedef struct input_t{
    char * input;
    int priority;
}INPUT;

typedef struct node_t{
    char * recommend;
    struct node_t * child[ALPHABETS];
}NODE;

int N, M;
char * words[MAXM];
INPUT inputs[MAXN];

void malloc_(){
    for(int i=0; i<N; i++)
        inputs[i].input = (char*)malloc(sizeof(char) * 12);
    for(int i=0; i<M; i++)
        words[i] = (char*)malloc(sizeof(char) * 12);
}

void free_(){
    for(int i=0; i<N; i++)
        free(inputs[i].input);
    for(int i=0; i<M; i++)
        free(words[i]);
}

void freeTrie(NODE * trie){
    if(trie){
        int cnt = 0;
        while(trie->child[cnt])
            freeTrie(trie->child[cnt++]);
        free(trie);
    }
}

NODE * createNode(){
    NODE * newNode;
    newNode = (NODE*)malloc(sizeof(NODE));
    
    newNode->recommend = NULL;
    for(int i=0; i<ALPHABETS; i++)
        newNode->child[i] = NULL;
    
    return newNode;
}

int toNumber(char c){
    return (int)(c - 'A');
}

void insert(NODE * root, const char * key, int index){
    if(root->recommend == NULL)
        root->recommend = inputs[index].input;
    
    if(*key != 0){
        int next = toNumber(*key);
        if(root->child[next] == NULL)
            root->child[next] = createNode();
        
        insert(root->child[next], key+1, index);    
    }
}

int find(NODE * root, const char * key, const char * start, int cnt){
    if(*key == 0) return cnt;
    if(root == NULL) return strlen(start);
    if(strcmp(start, root->recommend) == 0)
        return cnt + 1;
    
    int next = toNumber(*key);
    return find(root->child[next], key+1, start, cnt+1);
}

int dict(char * arr1, char * arr2, int num1, int num2){
    int ret = strcmp(arr1, arr2);
    if(ret > 0)
        return num2;
    return num1;
}

//병합 정렬 소스
void merge(int start, int half, int end){
    INPUT temp[end-start+1];
    for(int i = 0; i<end-start+1; i++)
        temp[i] = inputs[start+i];
	
    int cnt = 0, left = 0, right = 0;
    while(left < half+1 && right < end-start-half){
        if(temp[left].priority < temp[half+1+right].priority){
	    inputs[start+cnt] = temp[half+1+right]; 
            right++;
        }else if(temp[left].priority > temp[half+1+right].priority){
            inputs[start+cnt] = temp[left]; 
            left++;
        }else{
            int pre = dict(temp[left].input, temp[half+1+right].input, left, half+1+right);
            inputs[start+cnt] = temp[pre];
            if(pre == left) left++;
            else right++;
        }
        cnt++;
    }
	
    if(left == half+1)
	for(int i = 0; i<end-start-half-right; i++)
            inputs[start+cnt+i] = temp[half+1+right+i];
    else if(right == end-start-half)
	for(int i = 0; i<half+1-left; i++)
	    inputs[start+cnt+i] = temp[left+i];
}

// 병합정렬 구현 소스
void mergeSort(int start, int end){
    if(start != end){
	int half = (end-start)/2;
	mergeSort(start, start+half);
        mergeSort(start+half+1, end);
        merge(start, half, end);
    }
}

int main(){
    int caseNum;
    scanf("%d", &caseNum);
    
    for(int i=0; i<caseNum; i++){
        scanf("%d%d", &N, &M);

        malloc_(inputs);
        
        for(int j=0; j<N; j++)
            scanf("%s%d", inputs[j].input, &inputs[j].priority);
        
        for(int j=0; j<M; j++)
            scanf("%s", words[j]);
        
        mergeSort(0, N-1);
        
        NODE * trie = createNode();
        trie->recommend = "a";
        for(int j=0; j<N; j++)
            insert(trie, inputs[j].input, j);
        
        int answer = 0;
        for(int j=0; j<M; j++){
            answer += find(trie, words[j], words[j], 0);
            answer++;
        }
        printf("%d\n", answer-1);

        free_(inputs);
        freeTrie(trie);
    }
    
    return 0;
}
