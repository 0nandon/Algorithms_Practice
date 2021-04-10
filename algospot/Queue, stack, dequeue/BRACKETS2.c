#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
	char bracket;
	struct node * link;
}NODE;

typedef struct stack{
	int count;
	struct node * link;
}STACK;

char b[3][2] = {
	{'(', ')'}, {'[', ']'}, {'{', '}'}
};

STACK * pushNode(STACK * stack, char c){
	NODE * newNode = (NODE*)malloc(sizeof(newNode));
	newNode->link = NULL;
	newNode->bracket = c;
	
	NODE * ptr;
	ptr = stack->link;
	newNode->link = ptr;
	stack->link = newNode;
	stack->count++;
	
	return stack;
}

STACK * popNode(STACK * stack){
	NODE * ptr;
	ptr=stack->link;
	
	stack->link = ptr->link;
	free(ptr);
	
	stack->count--;
	return stack;
}

void destroy(STACK * stack){
	while(stack->count != 0)
		stack = popNode(stack);
	free(stack);
}

int isChecked(char bracket[10000]){
    STACK * stack = (STACK*)malloc(sizeof(STACK));
	stack->count = 0;
	stack->link = NULL;
	
	int index = 0;
	
	while(index < strlen(bracket)){
		int i = 0, check = 0;
		for(i = 0; i<3; i++){
			if(bracket[index] == b[i][0]) { check = 1; break; }
			else if(bracket[index] == b[i][1] ) break; 
		}
		
		if(check == 1) stack = pushNode(stack, bracket[index]);
		else { 
		    if(stack->count == 0) return 0;
			else if(stack->link->bracket != b[i][0]) return 0;
			else stack = popNode(stack);
		}
		index++;	
	}
	
	int count = stack->count;
	destroy(stack);
	
	if(count != 0) return 0;
	else return 1;
}

int main() {
	int caseNum;
	scanf("%d", &caseNum);
	int answer[caseNum];
	
	STACK * stack = (STACK*)malloc(sizeof(STACK));
	stack->count = 0;
	stack->link = NULL;
	
	for(int i = 0; i<caseNum; i++){
		char bracket[10000];
		scanf("%s", bracket);
		answer[i] = isChecked(bracket);
	}
	for(int i = 0; i<caseNum; i++) {
		if(answer[i]) printf("YES\n");
		else printf("NO\n");
	}

	return 0;
}
