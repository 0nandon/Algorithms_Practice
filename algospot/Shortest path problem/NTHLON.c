#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct node{
    int distance;
    int index;
}NODE;

typedef struct edge{
    int time;
    int interval;
}EDGE;

EDGE edge[500];
int distancePlus[202];
int distanceMinus[201];
int m;

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

int dijkstra(int start){
    NODE nodeList[10000];
    NODE newNode;
    newNode.index = start;
    newNode.distance = 0;
    distancePlus[start] = 0;
    int length = 0;
    
    insertMinHeap(nodeList, length++, newNode);
    
    int distancePop;
    while(length != 0){
        NODE pop = deleteMinHeap(nodeList, length--);
        
        distancePop = pop.index >= 0 ? distancePlus[pop.index] : distanceMinus[-pop.index];
        
        if(pop.distance > distancePop)
            continue;
        
        int there, distance;
        for(int i=0; i<m; i++){
            there = pop.index + edge[i].interval;
            
            if(abs(there) > 200)
                continue;
            
            distance = there >= 0 ? distancePlus[there] : distanceMinus[-there];
            
            if(distance > distancePop + edge[i].time || distance == 0){
                NODE pushNode;
                pushNode.distance = distancePop + edge[i].time;
                pushNode.index = there;
                
                if(there >= 0)
                    distancePlus[there] = pushNode.distance;
                else
                    distanceMinus[-there] = pushNode.distance;
                insertMinHeap(nodeList, length++, pushNode);
            }
        }
    }
    
    return distancePlus[0];
}

int main() {
    int caseNum;
    scanf("%d", &caseNum);
    
    for(int i=0; i<caseNum; i++){
        scanf("%d", &m);

        memset(distancePlus, 0, sizeof(distancePlus));
        memset(distanceMinus, 0, sizeof(distanceMinus));
        
        int answer;
        for(int j=0; j<m; j++){
            int num1, num2;
            scanf("%d%d", &num1, &num2);
            
            edge[j].time = num1;
            edge[j].interval = num1 - num2;
        }
        
        answer = dijkstra(0);
        
        if(answer == 0)
            printf("IMPOSSIBLE\n");
        else
            printf("%d\n", answer);
    }
    
    return 0;
}
