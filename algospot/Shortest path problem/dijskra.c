#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int distance;
    int index;
}NODE;

int graph[7][7] = {
    {0, 5, 1, 0, 0, 0, 0},
    {5, 0, 0, 1, 0, 3, 3},
    {1, 0, 0, 2, 0, 0, 0},
    {0, 1, 2, 0, 5, 3, 0},
    {0, 0, 0, 5, 0, 0, 0},
    {0, 3, 0, 3, 0, 0, 2},
    {0, 3, 0, 0, 0, 2, 0},
};

int distance[7];

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
    NODE nodeList[7];
    NODE newNode;
    newNode.index = start;
    newNode.distance = 0;
    distance[0] = 0;
    int length = 0;
    
    insertMinHeap(nodeList, length++, newNode);
    
    while(length != 0){
        NODE pop = deleteMinHeap(nodeList, length--);
        
        if(pop.distance > distance[pop.index])
            continue;
        
        for(int i=0; i<7; i++){
            if(graph[pop.index][i] == 0)
                continue;
            
            if(distance[i] > distance[pop.index] + graph[pop.index][i] || distance[i] == -1){
                NODE pushNode;
                pushNode.distance = distance[pop.index] + graph[pop.index][i];
                pushNode.index = i;
                distance[i] = pushNode.distance;
                insertMinHeap(nodeList, length++, pushNode);
            }
        }
    }
}

int main() {
    memset(distance, -1, sizeof(distance));
    dijkstra(0);
    
    for(int i=0; i<7; i++)
        printf("%d ", distance[i]);
    
    return 0;
}
