#include <stdio.h>
#include <stdlib.h>

int num;

void swap(int arr[], int index1, int index2){
	int temp = arr[index1];
	arr[index1] = arr[index2];
	arr[index2] = temp;
}

void insertMinHeap(int arr[], int length, int data){
	arr[length] = data;
	int temp;
	
	while(1){
		if(length == 0) break;
		if(arr[(length-1)/2] > data)
			swap(arr, length, (length-1)/2);
		else break;
		length = (length-1)/2;
	}
}

void deleteMinHeap(int arr[], int length){
	arr[0] = arr[length-1];
	int index = 0;
	int temp;
	
	while(1){
		if((index+1)*2 <= length-2 && (index+1)*2-1 <= length-2){
		    if(arr[index] > arr[(index+1)*2] || arr[index] > arr[(index+1)*2-1]){
		        if(arr[(index+1)*2] > arr[(index+1)*2-1]){
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
			if(arr[index] > arr[(index+1)*2-1]){
				swap(arr, index,(index+1)*2-1);
			    index = (index+1)*2-1;
			}
			else break;
		}
		else break;
	}
}

int strJoin(int str[]){
	int ret = 0;
	int temp1, temp2;
	while(num > 1){
		temp1 = str[0];
		deleteMinHeap(str, num--);
		temp2 = str[0];
		deleteMinHeap(str, num--);
		
		ret += temp1 + temp2;
		
		insertMinHeap(str, num++, temp1 + temp2);
	}
	
	return ret;
}

int main(){
	int caseNum;
	scanf("%d", &caseNum);
	int answer[caseNum];

	for(int i=0; i<caseNum; i++){
		scanf("%d", &num);
		
		int str[100];
		for(int j=0; j<num; j++){
			int temp;
			scanf("%d", &temp);
			
			insertMinHeap(str, j, temp);
		}
		
		answer[i] = strJoin(str);
	}
	
	for(int i=0; i<caseNum; i++)
		printf("%d\n", answer[i]);
		
	return 0;
}

