#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NODENUM 7
#define MAXEDGE 21

// adjacency metrics
int graph[NODENUM][NODENUM] = {
    {0, 5, 1, 0, 0, 0, 0},
    {5, 0, 0, 1, 0, 3, 3},
    {1, 0, 0, 2, 0, 0, 0},
    {0, 1, 2, 0, 5, 3, 0},
    {0, 0, 0, 5, 0, 0, 0},
    {0, 3, 0, 3, 0, 0, 2},
    {0, 3, 0, 0, 0, 2, 0},
};

typedef struct node_t{
    int n1, n2;
    int distance;
}NODE;

NODE node[MAXEDGE];
NODE spanningTree[MAXEDGE];
int length = 0; // number of total edges
int sLength = 0; // number of spanning tree's edges

int belongsTo[NODENUM];
int height[NODENUM];

void merge(NODE arr[], int start, int half, int end){
    NODE temp[end-start+1];
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
void mergeSort(NODE arr[], int start, int end){
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

void kruskal(){
    for(int i=0; i<NODENUM-1; i++){
        for(int j=i+1; j<NODENUM; j++){
            if(graph[i][j] == 0)
                continue;
            
            node[length].n1 = i;
            node[length].n2 = j;
            node[length++].distance = graph[i][j];
        }
    }
    
    mergeSort(node, 0, length-1);
    
    for(int i=0; i<length; i++){
        if(findRoot(node[i].n1) == findRoot(node[i].n2))
            continue;
        
        spanningTree[sLength++] = node[i];
        mergeUnion(node[i].n1, node[i].n2);
    }
}

int main(){
    initialization(NODENUM);
    kruskal();
    
    for(int i=0; i<sLength; i++)
        printf("%d %d\n", spanningTree[i].n1, spanningTree[i].n2);
     
    return 0;
}
