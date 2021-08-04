#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct node{
    double distance;
    int index;
}NODE;

NODE graph[10000][20];
int edgeNum[10000];
double distance[10000];
int n, m;

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
		        }
		        else{
					swap(arr, index, (index+1)*2);
			        index = (index+1)*2;
		        }
		    }
			else break;
		}
		else if((index+1)*2-1 == length-2){
			if(arr[index].distance > arr[(index+1)*2-1].distance){
				swap(arr, index,(index+1)*2-1);
			    index = (index+1)*2-1;
			}
			else break;
		}
		else break;
	}
    
    return ret;
}

float dijkstra(int start){
    NODE nodeList[10000];
    NODE newNode;
    newNode.index = start;
    newNode.distance = 0.0;
    distance[start] = 0.0;
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
        
        if(pop.index == n-1)
            return distance[pop.index];
    }
}

int main() {
    int caseNum;
    scanf("%d", &caseNum);
    double answer[caseNum];
    
    for(int i=0; i<caseNum; i++){
        scanf("%d%d", &n, &m);
        
        memset(edgeNum, 0, sizeof(edgeNum));
        for(int j=0; j<10000; j++)
            distance[j] = -1;
        
        int num1, num2;
        double amp;
        for(int j=0; j<m; j++){
            scanf("%d%d%lf", &num1, &num2, &amp);
            
            graph[num1][edgeNum[num1]].index = num2;
            graph[num1][edgeNum[num1]++].distance = log10(amp);
            graph[num2][edgeNum[num2]].index = num1;
            graph[num2][edgeNum[num2]++].distance = log10(amp);
        }
        
        answer[i] = dijkstra(0);
    }
    
    for(int i=0; i<caseNum; i++)
        printf("%.10lf\n", pow(10.0, answer[i]));
    
	  return 0;
}
