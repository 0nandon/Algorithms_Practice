#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// treap
typedef struct node_t{
    int data;
    int priority;
    int size;
    struct node_t * left;
    struct node_t * right;
}NODE;

NODE * createNode(int data){
    NODE * newNode;
    newNode = (NODE*)malloc(sizeof(NODE));
    newNode->data = data;
    newNode->priority = rand();
    newNode->size = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    
    return newNode;
}

NODE * swap(NODE * root, NODE * child, int isLeft){    
    if(isLeft){
        root->size -= (root->left != NULL ? root->left->size : 0);
        root->size += (child->right != NULL ? child->right->size : 0);
        root->left = child->right;
        child->size -= (child->right != NULL ? child->right->size : 0);
        child->size += root->size;
        child->right = root;
    }else{
        root->size -= (root->right != NULL ? root->right->size : 0);
        root->size += (child->left != NULL ? child->left->size : 0);
        root->right = child->left;
        child->size -= (child->left != NULL ? child->left->size : 0);
        child->size += root->size;
        child->left = root;
    }
    
    return child;
}
    
NODE * insertNode(NODE * root, int data){
    if(root){
        root->size++;
        if(root->data > data){
            root->left = insertNode(root->left, data);
            
            if(root->priority < root->left->priority)
                return swap(root, root->left, 1);
            return root;
        }else{
            root->right = insertNode(root->right, data);
            
            if(root->priority < root->right->priority)
                return swap(root, root->right, 0);
            return root;
        }
    }
    
    NODE * newNode = createNode(data);
    return newNode;
}

NODE * merge(NODE * left, NODE * right){
    if(left == NULL)
        return right;
    else if(right == NULL)
        return left;
    
    NODE * mergePtr;
    if(left->priority < right->priority){
        right->size -= (right->left != NULL ? right->left->size : 0);
        mergePtr = merge(left, right->left);
        right->size += (mergePtr != NULL ? mergePtr->size : 0);
        right->left = mergePtr;
        return right;
    }
    left->size -= (left->right != NULL ? left->right->size : 0);
    mergePtr = merge(left->right, right);
    left->size += (mergePtr != NULL ? mergePtr->size : 0);
    left->right = mergePtr;
    return left;
}

NODE * rejectNode(NODE * root, int data){
    if(root){
        root->size--;
        if(root->data == data){
            NODE * ptr = merge(root->left, root->right);
            free(root);
            return ptr;
        }else if(data < root->data){
            root->left = rejectNode(root->left, data);
            return root;
        }else{
            root->right = rejectNode(root->right, data);
            return root;
        }
    }
}

static int num = -2;
void printTree(NODE *root) {
    num++;
    if (root != NULL) {
	printTree(root->right);
	for (int i = 0; i < num; i++) 
	    printf("\t");
	
        printf("(%d, %d)\n", root->data, root->priority);
	num--;
	printTree(root->left);
        num--;
    }
}

int main(){
    srand(time(NULL));
    int input;
    NODE * root = NULL;
    for(int i=0; i<10; i++){
        scanf("%d", &input);
    
        root = insertNode(root, input);
        printf("======================\n");
        printTree(root);
        num = -2;
    }

    for(int i=0; i<10; i++){
        scanf("%d", &input);
        
        root = rejectNode(root, input);
        printf("======================\n");
        printTree(root);
        num = -2;
    }
     
    return 0;
}
