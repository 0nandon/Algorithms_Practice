#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cache[1001][101];
int picked[101];
int cnt;
int input[101][2];
char name[101][21];

int calAns(int num, int weight){
	int * ret = &cache[weight][num];
	if(*ret != -1)
		return *ret;
	
	if(num == 0){
		if(input[num][0] <= weight)
			return input[num][1];
		else return 0;
	}
	
	*ret = calAns(num-1, weight) > *ret ? calAns(num-1, weight) : *ret;
	if(weight - input[num][0] >= 0)
		if(calAns(num-1, weight-input[num][0]) + input[num][1] > *ret)
			*ret = calAns(num-1, weight-input[num][0]) + input[num][1];
	
	return *ret;
}


void reconstruct(int num, int weight){
	if(num == 0){
		if(input[num][0] <= weight){
			picked[num]=1;
			cnt++;
		}
		return;
	}
	
	if(calAns(num-1, weight) == calAns(num, weight))
		reconstruct(num-1, weight);
	else{
		picked[num]=1;
		cnt++;
		reconstruct(num-1, weight - input[num][0]);
	}
}

int main(){
	
	int caseNum;
	scanf("%d", &caseNum);
	
	for(int i=0; i<caseNum; i++){
		int num, weight;
		scanf("%d%d", &num, &weight);
		
		memset(cache, -1, sizeof(cache));
		memset(picked, -1, sizeof(picked));
		cnt = 0;
		
		for(int j=0; j<num; j++){
			scanf("%s", name[j]);
			scanf("%d%d", &input[j][0], &input[j][1]);
		}
		
		int answer = calAns(num-1, weight);
		reconstruct(num-1, weight);
		
		printf("%d %d\n", answer, cnt);
	    for(int i = 0; i<num; i++)
			if(picked[i] == 1)
				printf("%s\n", name[i]);   
	}
	
	return 0;
}
