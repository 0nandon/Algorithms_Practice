#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n, q;
int board[20][20];

int hint[20][20][2];
int value[20][20];
int sum[20 * 20];
int length[20 * 20];
int known[20 * 20];

int getSize(int num){
	int size=0;
	
	while(num){
		if(num%2 == 1)
			size++;
		num /= 2;
	}
	
	return size;
}
	
int getSum(int num){
	int s = 0;
	for(int i=1; i<10; i++)
		if(num & (1<<i))
			s += i;

	return s;
}

int candidates[10][46][1024];
void generateCandidates(){
	memset(candidates, 0, sizeof(candidates));
	for(int set=0; set<1024; set+=2){
		int l = getSize(set);
		int s = getSum(set);
		int subset = set;
		
		while(1){
			candidates[l][s][subset] |= (set & ~subset);
			if(subset == 0)
				break;
			subset = ((subset-1) & set);
		}
	}
}

void put(int x, int y, int val){
	known[hint[x][y][0]] += (1<<val);
	known[hint[x][y][1]] += (1<<val);
	value[x][y] = val;
}

void push(int x, int y, int val){
	known[hint[x][y][0]] -= (1<<val);
	known[hint[x][y][1]] -= (1<<val);
	value[x][y] = 0;
}

int getCandHint(int hint){
	return candidates[length[hint]][sum[hint]][known[hint]];
}

int getCandCoord(int x, int y){
	return getCandHint(hint[x][y][0]) & getCandHint(hint[x][y][1]);
}

void printSolution(){
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(!board[i][j])
				printf("0 ");
			else
				printf("%d ", value[i][j]);
		}
		printf("\n");
	}
}

int search(){
	int x = -1, y = -1, minCands = 1023;
	for(int i = 0; i<n; i++){
		for(int j=0; j<n; j++){
			if(board[i][j] && !value[i][j]){
				int cands = getCandCoord(i, j);
				if(getSize(minCands) > getSize(cands)){
					minCands = cands;
					x = i; y = j;
				}
			}
		}
	}
	
	if(minCands == 0)
		return 0;
	if(y == -1){
		printSolution();
		return 1;
	}
	
	for(int val=1; val<10; val++){
		if(minCands & (1<<val)){
			put(x, y, val);
			if(search())
				return 1;
			push(x, y, val);
		}
	}
	
	return 0;
}

int main(){
	int caseNum;
	scanf("%d", &caseNum);
	
	generateCandidates();

	for(int i=0; i<caseNum; i++){
		scanf("%d", &n);
		
		memset(board, 0, sizeof(board));
    memset(value, 0, sizeof(value));
    memset(hint, 0, sizeof(hint));
    memset(sum, 0, sizeof(sum));
    memset(length, 0, sizeof(length));
    memset(known, 0, sizeof(known));
		
		for(int j=0; j<n; j++)
			for(int a=0; a<n; a++)
				scanf("%d", &board[j][a]);
		
		scanf("%d", &q);
		for(int j=0; j<q; j++){
			int x, y, axis;
			
			scanf("%d%d%d%d", &x, &y, &axis, &sum[j]);
			if(axis == 0){
				x--; y--;
				while((y+1) < n && board[x][++y] == 1){
					hint[x][y][axis] = j;
					length[j]++;
				}
			}else{
				x--; y--;
				while((x+1) < n && board[++x][y] == 1){
					hint[x][y][axis] = j;
					length[j]++;
				}
			}
		}

		search();
	}
		
	return 0;
}
