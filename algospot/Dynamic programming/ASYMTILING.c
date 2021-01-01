#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000007

int cache[101];

int block(int num){
	if(cache[num] != -1) return cache[num];
	cache[num] = ((block(num-1)%MOD) + (block(num-2)%MOD)) % MOD;
	return cache[num];
}

int calculate(int num){
	int ret;
	
	if(num == 1 || num == 2) return 0;
	else if(num%2 != 0) return (block(num) - block(num/2)) % MOD;
	else {
        ret = (block(num) - block(num/2) + MOD) % MOD;
	    return ret = (ret - block((num-2)/2) + MOD) % MOD;
	}
}

int main() {	
	int caseNum;
	int num;
	scanf("%d", &caseNum);
	
	int answer[caseNum];
	memset(cache, -1, sizeof(cache));
	cache[1] = 1; cache[2] = 2;
		
	for(int i = 0; i<caseNum; i++) {
		scanf("%d", &num);
		answer[i] = calculate(num);
	}
    
	for(int i = 0; i<caseNum; i++) printf("%d\n", answer[i]);

	return 0;
}

