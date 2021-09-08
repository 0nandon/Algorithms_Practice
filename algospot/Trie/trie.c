#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHABETS 26

typedef struct node_t{
    int isTerminal;
    struct node_t * child[ALPHABETS];
}NODE;

NODE * createNode(){
    NODE * newNode;
    newNode = (NODE*)malloc(sizeof(NODE));
    
    newNode->isTerminal = 0;
    for(int i=0; i<ALPHABETS; i++)
        newNode->child[i] = NULL;
    
    return newNode;
}

int toNumber(char c){
    return (int)(c - 'A');
}

void insert(NODE * root, const char * key){
    if(*key == 0){
        root->isTerminal = 1;
    }else{
        int index = toNumber(*key);
        if(root->child[index] == NULL)
            root->child[index] = createNode();
        
        insert(root->child[index], key+1);    
    }
}

NODE * find(NODE * root, const char * key){
    if(*key == 0) return root;
    int next = toNumber(*key);
    if(root->child[next] == NULL) return NULL;
    return find(root->child[next], key+1);
}

int main(){
    
    const char * arr1 = "BUS";
    const char * arr2 = "BET";
    const char * arr3 = "TEA";
    const char * arr4 = "TEN";
    
    NODE * root = createNode();
    
    insert(root, arr1);
    insert(root, arr2);
    insert(root, arr3);
    insert(root, arr4);
    
    NODE * isFind = find(root, arr1);
    if(isFind->isTerminal)
        printf("Find!");
    
    return 0;
}
