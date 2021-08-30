#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 987654321
#define N 10

int * rangeMin; // RMQ
int arr[N];

// RMQ 생성
int init(int left, int right, int node){
    if(left == right)
        return rangeMin[node] = arr[left];

    int mid = (left + right) / 2;
    int leftMin = init(left, mid, 2*node);
    int rightMin = init(mid+1, right, 2*node+1);
    return rangeMin[node] = leftMin > rightMin ? rightMin : leftMin;
}

int min(int num1, int num2){
    return num1 > num2 ? num2 : num1;
}

// (left, right) 구간에서의 최소값을 반환
int query(int left, int right, int node, int nodeLeft, int nodeRight){
    if(right < nodeLeft || nodeRight < left)
        return INF;
    else if(left <= nodeLeft && nodeRight <= right)
        return rangeMin[node];
    
    int mid = (nodeLeft + nodeRight) / 2;
    return min(
        query(left, right, 2*node, nodeLeft, mid),
        query(left, right, 2*node+1, mid+1, nodeRight)
    );
}

int update(int index, int newValue, int node, int nodeLeft, int nodeRight){
    if(index < nodeLeft || nodeRight < index)
        return rangeMin[node];
    
    if(nodeLeft == nodeRight)
        return rangeMin[node] = newValue;
    
    int mid = (nodeLeft + nodeRight) / 2;
    return rangeMin[node] = min(
        update(index, newValue, node*2, nodeLeft, mid),
        update(index, newValue, node*2+1, mid+1, nodeRight)
    );
}

int main(){
    for(int i=0; i<N; i++)
        arr[i] = i;

    rangeMin = (int*)malloc(sizeof(int) * 4 * N);
    
    init(0, N-1, 1);
    
    printf("RMQ : ");
    for(int i=0; i<4*N; i++)
        printf("%d ", rangeMin[i]);
    
    printf("\n");
    int minNum = query(4, 9, 1, 0, N-1);
    printf("idx (4 ~ 9) 까지의 최솟값 : %d\n", minNum);
    
    update(4, 5, 1, 0, 9);
    minNum = query(4, 9, 1, 0, N-1);
    printf("arr[4] = 5를 한 후 idx (4 ~ 9) 까지의 최솟값 : %d\n", minNum);
    
    free(rangeMin);
    
	  return 0;
}
