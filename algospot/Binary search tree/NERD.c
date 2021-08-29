#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct nerd{
	int p, q;
}NERD;

typedef struct node{
	NERD nerd;
	int priority;
	int size;
	struct node * left;
	struct node * right;
}NODE;

NERD findMax(NODE * root){
	if(root->right == NULL) return root->nerd;
	else return findMax(root->right);
}

int calSize(NODE * root){
	if(root) return root->size;
	else return 0;
}

NODE * rejectNode(NODE * root, NERD nerd){
	if(root->nerd.p < nerd.p) root->right = rejectNode(root->right, nerd);
	else if(root->nerd.p > nerd.p) root->left = rejectNode(root->left, nerd);
	else{
		if(root->left == NULL){
			NODE * ptr;
			ptr = root->right;
			free(root);
			return ptr;
		}
		else if(root->right == NULL){
			NODE  * ptr;
			ptr = root->left;
			free(root);
			return ptr;
		}
		else{
			NERD max = findMax(root->left);
			root->nerd = max;
			root->left = rejectNode(root->left, max);
			root->size = calSize(root->left) + calSize(root->right) + 1;
			return root;
		}
	}
    root->size = calSize(root->left) + calSize(root->right) + 1;
	return root;
}

NODE * makeTree(NODE * root, NERD nerd, int priority){
	if(!root) {
	    NODE * newNode = (NODE*)malloc(sizeof(NODE));
	    newNode->priority = priority;
	    newNode->nerd = nerd;
	    newNode->size = 1;
	    newNode->left = NULL;
	    newNode->right = NULL;
		return newNode;
	}
	if(root->nerd.p <= nerd.p){
		root->right = makeTree(root->right, nerd, priority);
		root->size = calSize(root->left) + calSize(root->right) + 1;
		if(root->priority < root->right->priority){
			NODE * ptr = root->right;
			
			root->size -= calSize(root->right);
			root->size += calSize(root->right->left);
			root->right->size -= calSize(root->right->left);
			root->right = ptr->left;
			
			ptr->size += calSize(root);
			ptr->left = root;
			return ptr;
		}
		else return root;
    }
	else if(root->nerd.p > nerd.p){
		root->left = makeTree(root->left, nerd, priority);
		root->size = calSize(root->left) + calSize(root->right) + 1;
		if(root->priority < root->left->priority){
			NODE * ptr = root->left;
			
			root->size -= calSize(root->left);
			root->size += calSize(root->left->right);
			root->left->size -= calSize(root->left->right);
			root->left = ptr->right;
			
			ptr->size += calSize(root);
			ptr->right = root;
			return ptr;
		}
		else return root;
	}
}

NERD findNode(NODE * root, int num){
	if(calSize(root->left) + 1 == num) return root->nerd;
	else if(calSize(root->left) + 1 < num)
		return findNode(root->right, num-calSize(root->left) - 1);
	else if(calSize(root->left) + 1 > num)
		return findNode(root->left, num);
}

int calKth(NODE * root, NERD nerd){
	if(root->nerd.p == nerd.p) return calSize(root->left)+1;
	else if(root->nerd.p < nerd.p) 
		return calSize(root->left) + calKth(root->right, nerd) + 1;
	else if(root->nerd.p > nerd.p) 
		return calKth(root->left, nerd);
}

void destroyTree(NODE * tree){
	if(tree){
		destroyTree(tree->left);
		destroyTree(tree->right);
		free(tree);
    }
}

int main() {
	int caseNum;
	scanf("%d", &caseNum);
	int answer[caseNum];
	memset(answer, 0 , sizeof(answer));
	srand(time(NULL));
	
	for(int i = 0; i<caseNum; i++){
		int people;
		scanf("%d", &people);
		NERD nerd[people];
		NODE * tree = NULL;
		
		for(int j = 0; j<people; j++){
			scanf("%d%d", &nerd[j].p, &nerd[j].q);
			tree = makeTree(tree, nerd[j], rand());
			
			int kth = calKth(tree, nerd[j]);
			if(calSize(tree) != kth){
				NERD nextNerd = findNode(tree, kth+1);
				if(nextNerd.q > nerd[j].q){
					tree = rejectNode(tree, nerd[j]);
					goto HERE;
				}
			}
			if(kth != 1){
				while(1){
					if(kth == 1) break;
					NERD frontNerd = findNode(tree, --kth);
					if(frontNerd.q < nerd[j].q)
						tree = rejectNode(tree, frontNerd);
					else break;
				}
			}
			HERE :
			answer[i] += calSize(tree);
		}
		destroyTree(tree);
	}
	for(int i = 0; i<caseNum; i++) printf("%d\n", answer[i]);
	
	return 0;
}
