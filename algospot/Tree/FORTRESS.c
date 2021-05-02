#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

typedef struct circle{
	int x, y, rad;
}CIRCLE;

typedef struct node{
	CIRCLE circle;
	int length;
	struct node * link[100];
}NODE;

float distance(int x1, int y1, int x2, int y2){
	int a = (x1-x2)*(x1-x2);
	int b = (y1-y2)*(y1-y2);
	return sqrt(a+b);
}

bool isInclude(CIRCLE circle[], int big, int small){
	float dis = distance(circle[big].x, circle[big].y, circle[small].x, circle[small].y);
	if(dis < circle[big].rad + circle[small].rad && circle[big].rad > circle[small].rad)
		return true;
	else return false;
}

bool isChild(CIRCLE circle[], int parent, int child, int circleNum){
	if(!isInclude(circle, parent, child)) return false;
	for(int i = 0; i<circleNum; i++){
		if(parent == i || child == i) continue;
		if(isInclude(circle, parent, i) && isInclude(circle, i, child))
			return false;
	}
	return true;
}


NODE * makeTree(CIRCLE circle[], int index, int circleNum){
	NODE * newNode = (NODE*)malloc(sizeof(NODE));
	newNode->circle = circle[index];
	newNode->length = 0;
	newNode->link[0] = NULL;
	
	int * ret = &(newNode->length);
	for(int i = 0; i<circleNum; i++){
		if(isChild(circle, index, i, circleNum) && index != i){
			newNode->link[*ret] = makeTree(circle, i, circleNum);
			*ret += 1; 
		}
	}
	
	return newNode;
}


int calHeight(NODE * root){
	int max = 0, ret;
	
	if(root->link[0] == NULL) return 1;
	for(int i = 0; i<root->length; i++){
		ret = calHeight(root->link[i])+1;
		if(max < ret) max = ret;
	}
	return max;
}

int maxHeight(NODE * root){
	int max1 = 0, max2 = 0, ret, temp;
	
	for(int i = 0; i<root->length; i++){
		ret = calHeight(root->link[i]);
		if(max1 < ret){
			temp = max1;
			max1 = ret;
			max2 = temp;
		}
		else if(max2 < ret) max2 = ret;
	}
	return max1 + max2;
}

int calMax(NODE * root){
    int max = 0, ret;
	for(int i = 0; i<root->length; i++){
		ret = calMax(root->link[i]);
		if(max < ret) max = ret;
	}
	ret = maxHeight(root);
	if(max < ret) max = ret;
	
	return max;
}

void destroyTree(NODE * root){
	if(root){
		for(int i = 0; i<root->length; i++) destroyTree(root->link[i]);
		free(root);
	}
}

int main() {
	int caseNum;
	scanf("%d", &caseNum);
	int answer[caseNum];
	
	for(int i = 0; i<caseNum; i++){
		NODE * tree;
		int circleNum;
		scanf("%d", &circleNum);
		CIRCLE circle[circleNum];
		
		for(int j = 0; j<circleNum; j++)
			scanf("%d%d%d", &circle[j].x, &circle[j].y, &circle[j].rad);
		
		tree = makeTree(circle, 0, circleNum);
		answer[i] = calMax(tree);
		destroyTree(tree);
	}
	for(int i = 0; i<caseNum; i++) printf("%d\n", answer[i]); 
	
	return 0;
}
