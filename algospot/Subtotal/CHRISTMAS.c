#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MOD 20091101;

int N, K;
long long int mod[100001]; // christmas1()를 계산할 때, 오버플로우를 피하기 위해 64비트 정수형을 
int sum[100001];

int christmas1(){
    int answer = 0;
    
    for(int i=0; i<K; i++)
        if(mod[i] > 1)
            answer = (answer + ((mod[i] * (mod[i] - 1)) / 2)) % MOD;
    
    return answer;
}

int christmas2(int num){
    int prev[100001];
    memset(prev, -1, sizeof(prev));
    
    int cache[100001];
    memset(cache, 0, sizeof(cache));
    
    cache[0] = 0; prev[0] = 0;
    for(int i = 1; i < num+1; i++){
        cache[i] = cache[i-1];
        
        if(prev[sum[i]] != -1)
            cache[i] = cache[i] > 1 + cache[prev[sum[i]]] ? cache[i] : 1 + cache[prev[sum[i]]];
        
        prev[sum[i]] = i;
    }
    
    return cache[num];
}

int main() {
	int caseNum;
    scanf("%d", &caseNum);
    
    for(int i=0; i<caseNum; i++){
        scanf("%d%d", &N, &K);
        
        for(int j=0; j<100001; j++)
            mod[j] = 0;
        memset(sum, 0, sizeof(sum));
        
        sum[0] = 0; mod[0] = 1;
        for(int j=1; j<N+1; j++){
            int temp;
            scanf("%d", &temp);
            
            sum[j] = (sum[j-1] + temp) % K;
            mod[sum[j]]++;
        }
        
        printf("%d ", christmas1());
        printf("%d\n", christmas2(N));
    }
    
	return 0;
}
