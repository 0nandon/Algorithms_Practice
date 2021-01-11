#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char cache[1<<25]; // 메모리를 줄이기 위해 char형 캐시배열을 사용
int moves[104];

int calPos(int x, int y){
	return 1<<(5*x + y);
}

// 넣을 수 있는 블록의 위치를 미리 저장한다.
// 이후 비트마스트를 사용해서 일괄적으로 빠르게 처리한다.
void calMoves(){
	int size = 0;
	
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			moves[size++] = calPos(i, j) + calPos(i+1, j) + calPos(i, j+1);
			moves[size++] = calPos(i, j) + calPos(i+1, j) + calPos(i+1, j+1);
			moves[size++] = calPos(i, j) + calPos(i, j+1) + calPos(i+1, j+1);
			moves[size++] = calPos(i+1, j) + calPos(i, j+1) + calPos(i+1, j+1);
		}
	}
	
	for(int i=0; i<5; i++){
		for(int j=0; j<4; j++){
			moves[size++] = calPos(i, j) + calPos(i, j+1);
			moves[size++] = calPos(j, i) + calPos(j+1, i);
		}
	}
}

int blockGame(int board){
	char * ret = &cache[board];
	
	if(*ret != -1)
		return *ret;
	
	*ret = 0;
	for(int i=0; i<104; i++){
		if(!(board & moves[i])){
			if(!blockGame(board | moves[i])){
				*ret = 1;
				break;
			}
		}
	}

	return *ret;
}

int main() {
	
	int caseNum;
	scanf("%d", &caseNum);
	int answer[caseNum];

	calMoves();
	
	for(int i=0; i<caseNum; i++){
		char board[5];
		int state = 0;
		
		for(int j=0; j<5; j++){
			scanf("%s", board);
			
			for(int k=0; k<5; k++)
				if(board[k] == '#')
					state = state | (1<<(5*j + k));	
		}
		
		memset(cache, -1, sizeof(cache));
		answer[i] = blockGame(state);	
	}
	
	for(int i=0; i<caseNum; i++)
		if(answer[i])
			printf("WINNING\n");
		else
			printf("LOSING\n");
				
	return 0;
}

