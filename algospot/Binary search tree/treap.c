#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define INF 987654321

// treap
typedef struct node_t{
    int data;
    int priority;
    int num;
    struct node_t * left;
    struct node_t * right;
}NODE;

NODE * createNode(int data){
    NODE * newNode;
    newNode = (NODE*)malloc(sizeof(NODE));
    newNode->data = data;
    newNode->priority = rand();
    newNode->num = 0;
    newNode->left = NULL;
    newNode->right = NULL;
    
    return newNode;
}

// treap에서 노드를 삽입할 때 필요
NODE * swap(NODE * root, NODE * child, int isLeft){
    if(isLeft){
        root->left = child->right;
        child->right = root;
    }else{
        root->right = child->left;
        child->left = root;
    }
    
    return child;
}
    
NODE * insertNode(NODE * root, int data){
    if(root){
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

// treap에서 노드를 삭제할 때 필요
NODE * merge(NODE * left, NODE * right){
    if(left == NULL)
        return right;
    else if(right == NULL)
        return left;
    
    if(left->priority < right->priority){
        right->left = merge(left, right->left);
        return right;
    }
    left->right = merge(left->right, right);
    return left;
}

NODE * rejectNode(NODE * root, int data){
    if(root){
        if(root->data == data){
            NODE * ptr = merge(root->left, root->right);
            free(root);
            return ptr;
        }
        else if(data < root->data)
            return rejectNode(root->left, data);
        else
            return rejectNode(root->right, data);
    }
    
    return NULL;
}

static int num = -2;
void printTree(NODE *root) {
	  num++;
	  if (root != NULL) {
		    printTree(root->right);
		    for (int i = 0; i < num; i++) {
			      printf("\t");
		    }
		    printf("(%d, %d)\n", root->data, root->priority);
		    num--;
		    printTree(root->left);
		    num--;
	  }
};

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
        
        if(root == NULL){
            printf("그런 노드는 없습니다.\n");
            continue;
        }
        printTree(root);
        num = -2;
    }
     
    return 0;
}
