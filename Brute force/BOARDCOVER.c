#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int x[12][3] = {
	{0, 0, 1}, {0, 0, 1},
	{0, 0, -1}, {0, -1, 0},
	{0, 0, 1}, {0, 1, 1},
	{0, 0, -1}, {0, -1, -1},
	{0, 0, -1}, {0, 1, 1},
	{0, 0, 1}, {0, -1, -1}
};

int y[12][3] = {
	{0, 1, 0}, {0, -1, 0},
	{0, -1, 0}, {0, 0, 1},
	{0, 1, 1}, {0, 0, -1},
	{0, -1, -1}, {0, 0, 1},
	{0, 1, 1}, {0, 0, 1},
	{0, -1, -1}, {0, 0, -1}	
};

int makeFull(char game[][20], int xSize, int ySize){
	int i, j, ret = 0;
	for(i = 0; i<xSize; i++)
		for(j = 0; j<ySize; j++)
			if(game[i][j] == '.') goto EXIT;
	return 1;
	EXIT:
	for(int a = 0; a<12; a++){
		int b;
		for(b = 1; b<3; b++){
			if((i+x[a][b]<0 || i+x[a][b]>=xSize) ||
			        (j+y[a][b]<0 || j+y[a][b]>=ySize)) break;
			else if(game[i+x[a][b]][j+y[a][b]] != '.') break;
			if(b == 2){
				for(int c= 0; c<3; c++)
					game[i+x[a][c]][j+y[a][c]] = '#';
				ret += makeFull(game, xSize, ySize);
			}
		}
		if(b == 3)
			for(b = 0; b<3; b++)
				game[i+x[a][b]][j+y[a][b]] = '.';
	}
	return ret;
}

int main(){
    int caseNum;
	scanf("%d", &caseNum);
	int answer[caseNum];
	char game[20][20];
	
	for(int i = 0; i<caseNum; i++){
		int xSize, ySize;
		scanf("%d%d", &xSize, &ySize);
		for(int j = 0; j<xSize; j++) scanf("%s", game[j]);
		answer[i] = makeFull(game, xSize, ySize);
	}
	for(int i = 0; i<caseNum; i++) printf("%d\n", answer[i]);
	return 0;
}

