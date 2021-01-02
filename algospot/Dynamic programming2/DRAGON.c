#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const int MAX = 1000000000 + 1;

int k = 0;
char store[51];
int calSkipArr[51];
int p, l;
int finalLevel;

void calSkip(){
	for(int i=0; i<51; i++){
		if(i == 0)
			calSkipArr[i] = 1;
		else{
			long long next = 3 * pow(2, i) - 2;
			calSkipArr[i] = MAX < next ? MAX : next;
		}
	}
}

void dragonCurv(char c){
	if(p-1 <= k && k < p+l-1)
		store[k-p+1] = c;
	k++;
}

void calDragon(char c, int level){
	
	if(p+l-1 <= k)
		return;
	
	if(c == 'X'){
		if(level == finalLevel){
			dragonCurv('X');
			dragonCurv('+');
			dragonCurv('Y');
			dragonCurv('F');	
		}
		else{
			if(calSkipArr[finalLevel-level] + k >= p)
				calDragon('X', level+1);
			else
				k += calSkipArr[finalLevel-level];
			dragonCurv('+');
			if(calSkipArr[finalLevel-level] + k >= p)
				calDragon('Y', level+1);
			else
				k += calSkipArr[finalLevel-level];
			dragonCurv('F');	
		}
	}else{
		if(level == finalLevel){
			dragonCurv('F');
			dragonCurv('X');
			dragonCurv('-');
			dragonCurv('Y');	
		}
		else{
			dragonCurv('F');
			if(calSkipArr[finalLevel-level] + k >= p)
				calDragon('X', level+1);
			else
				k += calSkipArr[finalLevel-level];
			dragonCurv('-');
			if(calSkipArr[finalLevel-level] + k >= p)
				calDragon('Y', level+1);
			else
				k += calSkipArr[finalLevel-level];
		}
	}
}

int main() {
	int caseNum;
	scanf("%d", &caseNum);
	
	char answer[caseNum][51];
	calSkip();
	
	for(int i=0; i<caseNum; i++){
		scanf("%d%d%d", &finalLevel, &p, &l);
		
		dragonCurv('F');
		calDragon('X', 0);
		store[l] = 0;
		
		strcpy(answer[i], store);
		k=0;
	}
	
	for(int i=0; i<caseNum; i++)
		printf("%s\n", answer[i]);
	
	return 0;
}

