#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int N;

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

int calSize(NODE * ptr){
    return ptr != NULL ? ptr->size : 0;
}

int findIndex(NODE * root, int index){
    if(calSize(root->left) + 1 == index)
        return root->data;
    else if(calSize(root->left) < index)
        return findIndex(root->right, index - calSize(root->left) - 1);
    else
        return findIndex(root->left, index);
}

int main(){
    srand(time(NULL));
    int caseNum;
    scanf("%d", &caseNum);
    
    for(int i=0; i<caseNum; i++){
        scanf("%d", &N);
        
        int arr[N];
        for(int j=0; j<N; j++)
            scanf("%d", &arr[j]);
        
        NODE * tree = NULL;
        for(int j=0; j<N; j++)
            tree = insertNode(tree, j+1);
        
        int data; 
        int answer[N];
        for(int j=N-1; j>-1; j--){
            data = findIndex(tree, j+1 - arr[j]);
            answer[j] = data;
            tree = rejectNode(tree, data);
        }
        
        for(int j=0; j<N; j++)
            printf("%d ", answer[j]);
        printf("\n");
    }
     
    return 0;
}
