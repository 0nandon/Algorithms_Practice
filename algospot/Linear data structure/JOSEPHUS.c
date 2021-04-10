#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int index;
	struct node * link;
}NODE;

int count = 0;

NODE * addNode(NODE * node, int index){
	NODE * newNode;
	newNode = (NODE*)malloc(sizeof(NODE));
	newNode->index = index;
	newNode->link = NULL;
	
	if(node == NULL) {count ++ ; return newNode;}
	if(count == 1){
		node->link = newNode;
		newNode->link = node;
	}
	else{
	    newNode->link = node->link;
	    node->link = newNode;
	}
    count++;
	
	return newNode;
}

int * kill(NODE * list, int order){
	static int arr[2];
	
	NODE * ptr = list;
	NODE * rptr = list->link;
	while(1){
	    ptr->link = rptr->link;
	    free(rptr);
		rptr = ptr->link;
		count--;
		if(count == 2) break;
		
		for(int i = 0; i<order-1; i++) {
			ptr = ptr->link;
			rptr = rptr->link;
		}
	}

	if(ptr->index > rptr->index){ arr[0] = rptr->index; arr[1] = ptr->index; }
	else { arr[0] = ptr->index; arr[1] = rptr->index; }
	free(ptr); free(rptr);
	
	return arr;
}

int main() {
	int caseNum;
	scanf("%d", &caseNum);
	int answer[caseNum][2];
	
	for(int i = 0; i<caseNum; i++){
		int people, order;
		scanf("%d%d", &people, &order);

		NODE * list = NULL;
		for(int j = 0; j<people; j++) list = addNode(list, j+1);
		
	    int * arr;
		arr = kill(list, order);
		answer[i][0] = arr[0]; answer[i][1] = arr[1];
		count = 0;
	}

	for(int i = 0; i<caseNum; i++) 
        printf("%d %d\n", answer[i][0], answer[i][1]);

	return 0;
}
