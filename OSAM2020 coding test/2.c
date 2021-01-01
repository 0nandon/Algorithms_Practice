#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int start, int half, int end){
	int temp[end-start+1];
	for(int i = 0; i<end-start+1; i++)
		temp[i] = arr[start+i];
	
	int cnt = 0, left = 0, right = 0;
	while(left < half+1 && right < end-start-half){
		if(temp[left] < temp[half+1+right]){
			arr[start+cnt] = temp[half+1+right]; 
			right++; cnt++;
		}
		else {
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

int solution(){
	mergeSort(tshirts, 0, tshirts_length-1);
	mergeSort(people, 0, people_length-1);
	
	int check = 0, answer = 0;
	for(int i = 0; i<people_length; i++){
		if(check == tshirts_length) break;
		if(tshirts[check] >= people[i]){
			answer++;
			check++;
		}
	}
	
	return answer;
}


