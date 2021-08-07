#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int distance;
    int index;
}NODE;

NODE graph[1001][1001];
int edgeNum[1001];
int distance[1001];

int v, e, n, m;
int fire[1001];
int station[1001];

void swap(NODE arr[], int index1, int index2){
    NODE temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;
}

void insertMinHeap(NODE arr[], int length, NODE data){
    arr[length] = data;
	
    while(1){
        if(length == 0) break;
	if(arr[(length-1)/2].distance > data.distance)
	    swap(arr, length, (length-1)/2);
	else break;
	length = (length-1)/2;
    }
}

NODE deleteMinHeap(NODE arr[], int length){
    NODE ret = arr[0];
    arr[0] = arr[length-1];
    int index = 0;
	
    while(1){
        if((index+1)*2 <= length-2 && (index+1)*2-1 <= length-2){
            if(arr[index].distance > arr[(index+1)*2].distance || arr[index].distance > arr[(index+1)*2-1].distance){
	        if(arr[(index+1)*2].distance > arr[(index+1)*2-1].distance){
		    swap(arr, index, (index+1)*2-1);
	            index = (index+1)*2-1;
		}else{
		    swap(arr, index, (index+1)*2);
	            index = (index+1)*2;
		}
	    }else break;
	}else if((index+1)*2-1 == length-2){
	    if(arr[index].distance > arr[(index+1)*2-1].distance){
	        swap(arr, index,(index+1)*2-1);
	        index = (index+1)*2-1;
	    }else break;
        }else break;
    }
    
    return ret;
}

void dijkstra(int start){
    NODE nodeList[1001];
    NODE newNode;
    newNode.index = start;
    newNode.distance = 0;
    distance[start] = 0;
    int length = 0;
    
    insertMinHeap(nodeList, length++, newNode);
    
    while(length != 0){
        NODE pop = deleteMinHeap(nodeList, length--);
        
        if(pop.distance > distance[pop.index])
            continue;
        
        int there;
        for(int i=0; i<edgeNum[pop.index]; i++){   
            there = graph[pop.index][i].index;
            if(distance[there] > distance[pop.index] + graph[pop.index][i].distance || distance[there] == -1){
                NODE pushNode;
                pushNode.distance = distance[pop.index] + graph[pop.index][i].distance;
                pushNode.index = there;
                distance[there] = pushNode.distance;
                insertMinHeap(nodeList, length++, pushNode);
            }
        }
    }
}

int main() {
    int caseNum;
    scanf("%d", &caseNum);
    int answer[caseNum];
    memset(answer, 0, sizeof(answer));
    
    for(int i=0; i<caseNum; i++){
        scanf("%d%d%d%d", &v, &e, &n, &m);
        
        memset(edgeNum, 0, sizeof(edgeNum));
        memset(distance, -1, sizeof(distance));
        memset(fire, -1, sizeof(fire));
        memset(station, -1, sizeof(station));
        
        for(int j=0; j<e; j++){
            int num1, num2, distance;
            scanf("%d%d%d", &num1, &num2, &distance);
            
            graph[num1][edgeNum[num1]].index = num2;
            graph[num1][edgeNum[num1]++].distance = distance;
            graph[num2][edgeNum[num2]].index = num1;
            graph[num2][edgeNum[num2]++].distance = distance;
        }
        
        for(int j=0; j<n; j++)
            scanf("%d", &fire[j]);
        
        for(int j=0; j<m; j++)
            scanf("%d", &station[j]);
        
        // 그래프 변형
        for(int j=0; j<m; j++){
            graph[0][edgeNum[0]].index = station[j];
            graph[0][edgeNum[0]++].distance = 0;
        }
        
        dijkstra(0);
        
        for(int j=0; j<n; j++)
            answer[i] += distance[fire[j]];
    }
    
    for(int i=0; i<caseNum; i++)
        printf("%d\n", answer[i]);

    return 0;
}
