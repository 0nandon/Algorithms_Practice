#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cache[10000];

void merge(int arr[], int start, int half, int end){
	int temp[end-start+1];
	for(int i = 0; i<end-start+1; i++)
		temp[i] = arr[start+i];
	
	int cnt = 0, left = 0, right = 0;
	while(left < half+1 && right < end-start-half){
		if(temp[left] > temp[half+1+right]){
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

void mergeSort(int arr[], int start, int end){
    if(start != end){
	    int half = (end-start)/2;
	    mergeSort(arr, start, start+half);
        mergeSort(arr, start+half+1, end);
        merge(arr, start, half, end);
	}
}

int findNum(int arr[], int num, int start, int end){
	if(end == start){
		if(arr[start] <= num) return start;
		else return start-1;
	}
	else if(end-start == 1){
		if(num < arr[start]) return start-1;
		else if(arr[start] <= num && num < arr[end]) return start;
		else return start+1;
	}
	
	int half = (start+end)/2;
	if(arr[half] < num) return findNum(arr, num, half+1, end);
	else if(num < arr[half]) return findNum(arr, num, start, half-1);
	else return half;
}

int findList(int arr[], int num, int half){
	if(arr[half] == num)
	    while(arr[half] == num)
		    half++;
	else return half;
	return half-1;
}

int solution(){
	memset(cache, -1, sizeof(cache));
	
	mergeSort(grade, 0, grade_length-1);
	
	int answer = 0;
	for(int i = 0; i<grade_length; i++){
		if(cache[arr[i]] != -1) continue;
		int half = findNum(arr, arr[i]+max_diff, i, grade_length-1);
		int list = findList(arr, arr[i]+max_diff, half);
		cache[arr[i]] = list;
		if(answer < list-i+1) answer = list-i+1;
	}
	
	return answer;
}



