#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char store[201];
int idx = 0;
int k;

const int M = 1000000000 + 100;

int bino[201][201];
void calcBino(){
	memset(bino, 0, sizeof(bino));
	for(int i=0; i<=200; i++){
		bino[i][0] = 1;
		bino[i][i] = 1;
		for(int j=0; j<i; j++){
			bino[i][j] = M < bino[i-1][j-1] + bino[i-1][j] ? M :
			                 bino[i-1][j-1] + bino[i-1][j];
		}
	}
}

void calAns(int n, int m){
	
	if(n == 0 && m == 0)
		return;
	else if(n == 0){
		store[idx] = 'o';
		idx++;
		calAns(n, m-1);
		return;
	}
	else if(m == 0){
		store[idx] = '-';
		idx++;
		calAns(n-1, m);
		return;
	}
	
	if(k <= bino[n+m-1][n-1]){
		store[idx] = '-';
		idx++;
		calAns(n-1, m);
		return;
	}
	
	store[idx] = 'o';
	idx++;
	k -= bino[n+m-1][n-1];
	calAns(n, m-1);
	return;
}


int main(){
	
	int caseNum;
	scanf("%d", &caseNum);
	char answer[caseNum][201];
	
	calcBino();
	for(int i=0; i<caseNum; i++){
		
		int n, m;
		scanf("%d%d%d", &n, &m, &k);
		
		calAns(n, m); store[idx] = 0;
		strcpy(answer[i], store);
		
		idx = 0;
	}
	
	for(int i=0; i<caseNum; i++)
		printf("%s\n", answer[i]);
	
	return 0;
}

