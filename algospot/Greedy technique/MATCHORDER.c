#include <stdio.h>
#include <stdlib.h>

int num;

void swap(int arr[], int index1, int index2){
	int temp = arr[index1];
	arr[index1] = arr[index2];
	arr[index2] = temp;
}

void insertMaxHeap(int arr[], int length, int data){
	arr[length] = data;
	int temp;
	
	while(1){
		if(length == 0) break;
		if(arr[(length-1)/2] < data)
			swap(arr, length, (length-1)/2);
		else break;
		length = (length-1)/2;
	}
}

void deleteMaxHeap(int arr[], int length){
	arr[0] = arr[length-1];
	int index = 0;
	int temp;
	
	while(1){
		if((index+1)*2 <= length-2 && (index+1)*2-1 <= length-2){
		    if(arr[index] < arr[(index+1)*2] || arr[index] < arr[(index+1)*2-1]){
		        if(arr[(index+1)*2] < arr[(index+1)*2-1]){
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
			if(arr[index] < arr[(index+1)*2-1]){
				swap(arr, index,(index+1)*2-1);
			    index = (index+1)*2-1;
			}
			else break;
		}
		else break;
	}
}

int matchOrder(int russia[], int korea[]){
	int ret = 0;
	int koreaLength = num;
	int russiaLength = num;
	
	while(russiaLength > 0 && koreaLength > 0){
		if(russia[0] <= korea[0]){
			deleteMaxHeap(russia, russiaLength--);
			deleteMaxHeap(korea, koreaLength--);
			ret++;
		}
		else
			deleteMaxHeap(russia, russiaLength--);
	}
	
	return ret;
}


int main(){
	int caseNum;
	scanf("%d", &caseNum);
	int answer[caseNum];

	for(int i=0; i<caseNum; i++){
		scanf("%d", &num);
		
		int russia[100];
		for(int j=0; j<num; j++){
			int rating;
			scanf("%d", &rating);
			
			insertMaxHeap(russia, j, rating);
		}
		
		int korea[100];
		for(int j=0; j<num; j++){
			int rating;
			scanf("%d", &rating);
			
			insertMaxHeap(korea, j, rating);
		}
		
		answer[i] = matchOrder(russia, korea);
	}
	
	for(int i=0; i<caseNum; i++)
		printf("%d\n", answer[i]);
		
	return 0;
}

