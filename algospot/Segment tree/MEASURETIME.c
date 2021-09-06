#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 999999
#define MAX 50000

int N;
long long int tree[MAXN+1];
int arr[MAX];
int arr2[MAX];
int idx[MAXN+1];
int sort[MAX];

//병합 정렬 소스
void merge(int arr[], int start, int half, int end){
	int temp[end-start+1];
	for(int i = 0; i<end-start+1; i++)
	    temp[i] = arr[start+i];
	
	int cnt = 0, left = 0, right = 0;
	while(left < half+1 && right < end-start-half){
	    if(temp[left] > temp[half+1+right]){
	        arr[start+cnt] = temp[half+1+right]; 
                right++; cnt++;
            }else{
                arr[start+cnt] = temp[left]; 
                left++; cnt++;
            }
	}
	
	if(left == half+1)
	    for(int i = 0; i<end-start-half-right; i++)
		arr[start+cnt+i] = temp[half+1+right+i];
	else if(right == end-start-half)
	    for(int i = 0; i<half+1-left; i++)
		arr[start+cnt+i] = temp[left+i];
}

// 병합정렬 구현 소스
void mergeSort(int arr[], int start, int end){
    if(start != end){
	int half = (end-start)/2;
	mergeSort(arr, start, start+half);
        mergeSort(arr, start+half+1, end);
        merge(arr, start, half, end);
    }
}

// tree를 모두 0으로 초기화한다.
void initTree(){
    for(int i=0; i<N+1; i++)
        tree[i] = 0;
}

// 0...pos 까지의 부분합을 구한다.
long long int fenwickSum(int pos){
    long long int ret = 0;
    while(pos > 0){
        ret += tree[pos];
        pos &= (pos-1);
    }
    
    return ret;
}

void fenwickAdd(int pos, int val){
    while(pos < N+1){
        tree[pos] += val;
        pos += (pos & -pos);
    }
}

long long int countMoves(){
    long long int ret = 0;
    
    initTree();
    
    for(int i=0; i<N; i++){
        ret += fenwickSum(N) - fenwickSum(arr2[i]);
        fenwickAdd(arr2[i], 1);
    }
    return ret;
}

int main(){
    int caseNum;
    scanf("%d", &caseNum);
    
    for(int i=0; i<caseNum; i++){
        scanf("%d", &N);
        
        for(int j=0; j<N; j++)
            scanf("%d", &arr[j]);
        
        for(int j=0; j<N; j++)
            sort[j] = arr[j];
        
        mergeSort(sort, 0, N-1);
        
        for(int j=0; j<N; j++)
            idx[sort[j]] = j+1;
        
        for(int j=0; j<N; j++)
            arr2[j] = idx[arr[j]];
    
        printf("%lld\n", countMoves()); 
    }
    
    return 0;
}
