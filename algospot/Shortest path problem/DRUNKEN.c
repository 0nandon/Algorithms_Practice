#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 987654321

typedef struct drunken_t{
    int index;
    int drunken;
}DRUNKEN;

int v, e;
DRUNKEN drunken[500];
int graph[500][500];
int distance[500][500];

int min(int num1, int num2){
    return num2 > num1 ? num1 : num2;
}

void merge(DRUNKEN arr[], int start, int half, int end){
    DRUNKEN temp[end-start+1];
    for(int i = 0; i<end-start+1; i++)
    	temp[i] = arr[start+i];
	
    int cnt = 0, left = 0, right = 0;
    while(left < half+1 && right < end-start-half){
        if(temp[left].drunken > temp[half+1+right].drunken){
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
void mergeSort(DRUNKEN arr[], int start, int end){
    if(start != end){  
        int half = (end-start)/2;
	mergeSort(arr, start, start+half);
        mergeSort(arr, start+half+1, end);
        merge(arr, start, half, end);
    }
}

// 플로이드 알고리즘
void floyd(){
    for(int i=0; i<v; i++)
        for(int j=0; j<v; j++)
            if(i != j)
                distance[i][j] = graph[i][j];
            else
                distance[i][j] = 0;
    
    for(int k=0; k<v; k++){
        int w = drunken[k].index;
        
        for(int i=0; i<v; i++){
            for(int j=0; j<v; j++){
                if(i == w || j == w)
                    continue;
                
                graph[i][j] = min(graph[i][j], graph[i][w] + graph[w][j]);
                distance[i][j] = min(distance[i][j], graph[i][w] + graph[w][j] + drunken[k].drunken);
            }
        }
    }
}

int main(){
    scanf("%d%d", &v, &e);
    for(int i=0; i<v; i++){
        scanf("%d", &drunken[i].drunken);
        drunken[i].index = i;
    }
    
    mergeSort(drunken, 0, v-1);
    
    for(int i=0; i<v; i++)
        for(int j=0; j<v; j++)
            distance[i][j] = INF;
    
    for(int i=0; i<v; i++)
        for(int j=0; j<v; j++)
            graph[i][j] = INF;
    
    for(int i=0; i<e; i++){
        int num1, num2, distance;
        scanf("%d%d%d", &num1, &num2, &distance);
        
        graph[num1-1][num2-1] = distance;
        graph[num2-1][num1-1] = distance;
    }
    
    floyd();
            
    int caseNum;
    scanf("%d", &caseNum);
    for(int i=0; i<caseNum; i++){
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        
        printf("%d\n", distance[v1-1][v2-1]);
    }
    
    return 0;
}
