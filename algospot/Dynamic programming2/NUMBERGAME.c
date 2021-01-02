#include <stdio.h>
#include <stdlib.h>

int board[50];
int cache[50][50];

int ENF = -987654321;

int playGame(int left, int right){
	int * ret = &cache[left][right];
	int leftChoice, rightChoice;
	
	if(left > right)
		return 0;
	
	if(*ret != ENF)
		return *ret;
	
	if(left == right)
		return board[left];
	
	leftChoice = board[left] - playGame(left+1, right);
	rightChoice = board[right] - playGame(left, right-1);
	*ret = leftChoice > rightChoice ? leftChoice : rightChoice;
	
	if(right-left+1 >= 2){
		leftChoice = -playGame(left+2, right);
	    rightChoice = -playGame(left, right-2);
		*ret = leftChoice > *ret ? leftChoice : *ret;
		*ret = rightChoice > *ret ? rightChoice : *ret;
	}
	
	return *ret;
}

int main() {
	int caseNum;
	scanf("%d", &caseNum);
	
	int answer[caseNum];
	
	for(int i=0; i<caseNum; i++){
		int length;
		scanf("%d", &length);
		
		for(int j=0; j<length; j++)
			scanf("%d", &board[j]);
		
		for(int a=0; a<50; a++)
			for(int b=0; b<50; b++)
				cache[a][b] = ENF;
		
		answer[i] = playGame(0, length-1);
	}
	
	for(int i=0; i<caseNum; i++)
		printf("%d\n", answer[i]);
	
	return 0;
}

