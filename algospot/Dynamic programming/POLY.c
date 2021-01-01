#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 10000000;

int cache[101][101];

int poly(int num, int first){
    if(num == first) return 1;
	int * ret = &cache[num][first];
	if(*ret != 0) return *ret;
	
	for(int i = 1; i<num-first + 1; i++){
		*ret += (first - 1 + i)*poly(num-first, i) % MOD;
		*ret %= MOD; // MOD으로 한번 더 나눠 줘야 함.
	}

    return *ret;
}

int main() {
    int caseNum, num;
	scanf("%d", &caseNum);
	int answer[caseNum];
	
	memset(cache, 0, sizeof(cache));
	
	for(int i = 0; i<caseNum; i++){
		answer[i] = 0;
		scanf("%d", &num);
		for(int j = 1; j<num+1; j++){
			answer[i] += poly(num, j);
			answer[i] %= MOD;
		}
	}
	
	for(int i = 0; i < caseNum; i++) printf("%d\n", answer[i]);
	
	return 0;
}

