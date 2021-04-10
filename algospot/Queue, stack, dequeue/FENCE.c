#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int height;
    int left;
    int right;
    int index;
    struct node * link;
}NODE;

int n;
int max;

NODE * createNode(int height, int index){
    NODE * node = (NODE*)malloc(sizeof(NODE));
    node->height = height;
    node->index = index;
    node->left = -1;
    node->right = -1;
    node->link = NULL;
    return node;
}

NODE * pushStack(NODE * stack, NODE * new){
    new->link = stack;

    return new;
}

NODE * popStack(NODE * node){
    NODE * ptr;
    ptr = node->link;
    node->link = NULL;
    free(node);
    
    return ptr;
}

NODE * fence(NODE * stack, NODE * node){
    while(stack && stack->height > node->height){
        stack->right = node->index;
        int size = stack->height * (stack->right - stack->left -1);
        max = size > max ? size : max;
            
        stack = popStack(stack);
    }
    
    if(stack)
        node->left = stack->index;
    
    stack = pushStack(stack, node);
    
    return stack;
}

void last(NODE * stack){
    while(stack){
        int size = stack->height * (n - stack->left -1);
        max = size > max ? size : max;
        stack = popStack(stack);
    }
}

int main() {
	int caseNum;
    scanf("%d", &caseNum);
    int answer[caseNum];
    
    for(int i=0; i<caseNum; i++){
        scanf("%d", &n);

        NODE * node = createNode(0, -1);
        
        NODE * stack = NULL;
        stack = pushStack(stack, node);
        max = -1;
        
        for(int j=0; j<n; j++){
            int height;
            scanf("%d", &height);
            
            NODE * node = createNode(height, j);
            
            if(stack->height > node->height){
                stack = fence(stack, node);
            }else if(stack->height == node->height){
                node->left = stack->left;
                stack = popStack(stack);
                stack = pushStack(stack, node);
            }else{
                node->left = stack->index;
                stack = pushStack(stack, node);
            }
        }
        last(stack);
        
        answer[i] =max;
    }
    
    for(int i=0; i<caseNum; i++)
        printf("%d\n", answer[i]);
    
	return 0;
}
