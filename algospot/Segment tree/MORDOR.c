#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 987654321

typedef struct node_t{
    int min, max;
}NODE;

int N, Q;
NODE range[400000];
int arrN[100000];

// RMQ 생성
int init(int left, int right, int node, int isMin){
    if(left == right){
        if(isMin)
            return range[node].min = arrN[left];
        else
            return range[node].max = arrN[left];
    }

    int mid = (left + right) / 2;
    int leftM = init(left, mid, 2*node, isMin);
    int rightM = init(mid+1, right, 2*node+1, isMin);
    
    if(isMin)
        return range[node].min = leftM > rightM ? rightM : leftM;
    else
        return range[node].max = rightM > leftM ? rightM : leftM;
}

int compare(int num1, int num2, int isMin){
    if(isMin)
        return num1 > num2 ? num2 : num1;
    return num1 > num2 ? num1 : num2;
}

// (left, right) 구간에서의 최소값을 반환
int query(int left, int right, int node, int nodeLeft, int nodeRight, int isMin){
    if(right < nodeLeft || nodeRight < left)
        return isMin ? INF : -INF;
    else if(left <= nodeLeft && nodeRight <= right)
        return isMin ? range[node].min : range[node].max;
    
    int mid = (nodeLeft + nodeRight) / 2;
    return compare(
        query(left, right, 2*node, nodeLeft, mid, isMin),
        query(left, right, 2*node+1, mid+1, nodeRight, isMin),
        isMin
    );
}

int main(){
    int caseNum;
    scanf("%d", &caseNum);
    
    for(int i=0; i<caseNum; i++){
        scanf("%d%d", &N, &Q);
        
        for(int j=0; j<N; j++)
            scanf("%d", &arrN[j]);
        
        init(0, N-1, 1, 1);
        init(0, N-1, 1, 0);
        for(int j=0; j<Q; j++){
            int left, right;
            scanf("%d%d", &left, &right);
            
            int min = query(left, right, 1, 0, N-1, 1);
            int max = query(left, right, 1, 0, N-1, 0);
            
            printf("%d\n", max-min);
        }
    }
    
    return 0;
}

