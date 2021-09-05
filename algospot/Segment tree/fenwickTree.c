#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 987654321
#define N 16
int tree[N+1];

// tree를 모두 0으로 초기화한다.
void initTree(){
    memset(tree, 0, sizeof(tree));
}

// 0...pos 까지의 부분합을 구한다.
int fenwickSum(int pos){
    int ret = 0;
    pos++;
    while(pos > 0){
        ret += tree[pos];
        pos &= (pos-1);
    }
    
    return ret;
}

void fenwickAdd(int pos, int val){
    pos++;
    while(pos < N+1){
        tree[pos] += val;
        pos += (pos & -pos);
    }
}

int main(){
    int input[N];
    init();
    for(int i=0; i<N; i++)
        input[i] = i;
    
    for(int i=0; i<N; i++)
        fenwickAdd(i, i);
    
    printf("preint fenwick tree : ");
    for(int i=0; i<N; i++)
        printf("%d ", tree[i+1]);
    
    return 0;
}
