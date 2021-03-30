#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n, k, m, l;
int r[12][2];
int c[10][2];

int cache[10][1<<12];

int INF = 987654321;

int binCount(int num){
    int cnt = 0;
    while(num){
        if(num % 2)
            cnt++;
        num /= 2;
    }
    return cnt;
}

int bitCount(int num){
    int cnt = 0;
    while(num){
        cnt++;
        num /= 2;
    }
    
    return cnt-1;
}

int graduation(int semester, int subject, int count){
    if(semester > m)
        return INF;
    
    int * ret = &cache[semester][subject];
        
    if(count == k)
        return 0;
    
    if(*ret != -1)
        return cache[semester][subject];
    
    int cnt = 0, subset = 0;
    int firstBit, bitNum, thisSemester;
    for(int i=0; i<c[semester][0]; i++){
        firstBit = (c[semester][1] & -c[semester][1]);
        bitNum = bitCount(firstBit);
        
        if(!(firstBit & subject) && (r[bitNum][1] == (r[bitNum][1] & subject))){
            cnt++;
            subset |= firstBit;
        }
        c[semester][1] &= (c[semester][1] - 1);
    }
    
    if(subset == 0){
        *ret = graduation(semester + 1, subject, count);
        return *ret;
    }
    
    int *ret = INF;
    for(int i=subset; i; i = ((i-1) & subset)){
        int cnt = binCount(i);
        if(binCount(i) <= l){
            *ret = 1 + graduation(semester+1, subject | i, count + cnt);
            min = min > *ret ? *ret : min;
        }   
    }
}

int main() {
	int caseNum;
    scanf("%d", &caseNum);
    int answer[caseNum];
    
    for(int i=0; i<caseNum; i++){
        scanf("%d%d%d%d", &n, &k, &m, &l);
        
        memset(r, 0, sizeof(r));
        for(int j=0; j<n; j++){
            scanf("%d", &r[j][0]);
            
            for(int a=0; a<r[j][0]; a++){
                int bit;
                scanf("%d", &bit);
                r[j][1] |= (1 << bit);
            }
        }
        
        memset(c, 0, sizeof(c));
        for(int j=0; j<m; j++){
            scanf("%d", &c[j][0]);
            
            for(int a=0; a<c[j][0]; a++){
                int bit;
                scanf("%d", &bit);
                c[j][1] |= (1 << bit);
            }
        }
    
        memset(cache, -1, sizeof(cache));
        
        graduation(0, 0, 0);
        
        answer[i] = cache[0][0]; 
    }
    
    for(int i=0; i<caseNum; i++)
        if(answer[i] == INF)
            printf("IMPOSSIBLE");
        else
            printf("%d", answer[i]);
    
	return 0;
}

