#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXV 2000
#define MAXE 4000
#define INF 987654321

typedef struct edge_t{
    int n1, n2;
    int distance;
}EDGE;
EDGE edge[MAXE];

int V, E;

int belongsTo[MAXV];
int height[MAXV];

void merge(EDGE arr[], int start, int half, int end){
    EDGE temp[end-start+1];
    for(int i = 0; i<end-start+1; i++)
    	temp[i] = arr[start+i];
	
    int cnt = 0, left = 0, right = 0;
    while(left < half+1 && right < end-start-half){
        if(temp[left].distance > temp[half+1+right].distance){
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
void mergeSort(EDGE arr[], int start, int end){
    if(start != end){  
        int half = (end-start)/2;
	      mergeSort(arr, start, start+half);
        mergeSort(arr, start+half+1, end);
        merge(arr, start, half, end);
    }
}

void initialization(int n){
    memset(height, 0, sizeof(height));
    
    for(int i=0; i<n; i++)
        belongsTo[i] = i;
}

int findRoot(int num){
    if(belongsTo[num] == num)
        return num;
    belongsTo[num] = findRoot(belongsTo[num]);
    return belongsTo[num];
}

int mergeUnion(int num1, int num2){
    int root1 = findRoot(num1);
    int root2 = findRoot(num2);
    
    if(root1 == root2)
        return -1;
    
    int big = height[root1] > height[root2] ? root1 : root2;
    int small = root1 + root2 - big;
    
    belongsTo[small] = big;
    
    if(height[root1] == height[root2])
        height[big]++;
        
    return big;
}

int kruskal(int L){
    for(int i=0; i<E; i++){
        if(findRoot(edge[i].n1) == findRoot(edge[i].n2))
            continue;
        
        if(L > edge[i].distance)
            continue;
        
        mergeUnion(edge[i].n1, edge[i].n2);

        if(findRoot(0) == findRoot(V-1))
            return edge[i].distance;
    }
    
    return INF;
}

int tpath(){
    int ret = INF;
    for(int i=0; i<E; i++){
        initialization(V);

        int L = edge[i].distance;
        int U = kruskal(L);

        ret = ret > U - L ? U - L : ret;
    }
    
    return ret;
}

int main(){
    int caseNum;
    scanf("%d", &caseNum);
    
    for(int i=0; i<caseNum; i++){
        scanf("%d%d", &V, &E);
        
        for(int j=0; j<E; j++)
            scanf("%d%d%d", &edge[j].n1, &edge[j].n2, &edge[j].distance);
        
        mergeSort(edge, 0, E-1);
        
        printf("%d\n", tpath());
    }
     
    return 0;
}

