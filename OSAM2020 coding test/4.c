#include <stdio.h>
#include <stdlib.h>

int cal(int tree[], int num1, int num2, int nodeNum){
	int route1[nodeNum];
	int route2[nodeNum];
	int length1 = 0, length2 = 0;
	int next;
	
	next = num1;
	while(1){
		route1[length1++] = next;
		if(tree[next] == next) break;
		next = tree[next];
	}
	
	next = num2;
	while(1){
		route2[length2++] = next;
		if(tree[next] == next) break;
		next = tree[next];
	}

	int cnt = 0;
	while(route1[length1-1-cnt] == route2[length2-1-cnt]){
		cnt++;
		if(length1-1-cnt < 0 || length2-1-cnt < 0) break;
	}
    
	return length1 + length2 - 2*cnt+1;
}

int soluytion(){
	int tree[N];
	
	for(int i = 0; i<N; i++)
		tree[i] = i;
	
	for(int i = 0; i<directory_row_len; i++)
		tree[directory[i][1]-1] = tree[directory[i][0]-1];
	
	int * answer = (int*)malloc(sizeof(int)*query_row_len);
	
	for(int i = 0; i<query_row_len; i++)
		answer[i] = cal(tree, query[i][0]-1, query[i][1]-1, N);
	
	return answer;
}





