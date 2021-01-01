#include <stdio.h>
#include <stdlib.h>

int maxRec(int arr[], int length, int start){
	if(length == 1) return arr[start];
    int max, maxMiddle, min;
	
	int left = maxRec(arr, length/2, start);
	int right = maxRec(arr, length-length/2, start + length/2);
    if(left>right) max=left;
	else max = right;
	
	if(arr[start + length/2 - 1] > arr[start + length/2]){
		maxMiddle = 2*arr[start + length/2];
		min = arr[start + length/2];
	}
	else{
		maxMiddle = 2*arr[start + length/2-1];
		min = arr[start + length/2-1];
	}
	int first = start + length/2-1;
	int last = start + length/2;
	
	while(1){
		if(first == start && last == start + length - 1) break;
		else if(first == start) {
			last++;
			if(min > arr[last]) min = arr[last];
		}
		else if(last == start + length-1) {
			first--;
			if(min > arr[first]) min = arr[first];
		}
		else if(arr[first-1] > arr[last+1]){
			if(min > arr[first-1]) min = arr[first-1];
			first--;
		}
		else{
			if(min > arr[last+1]) min = arr[last + 1];
			last++;
		}
		
		if(maxMiddle < (last-first+1)*min) maxMiddle = (last-first+1)*min;
	}
	
	if(max<maxMiddle) max = maxMiddle;
	return max;
}

int main() {	
    int caseNum;
	scanf("%d", &caseNum);
	int answer[caseNum];
	
	for(int i = 0; i< caseNum; i++){
		int length;
		scanf("%d", &length);
		int arr[length];
		
		for(int i = 0; i<length; i++) scanf("%d", &arr[i]);
		
		answer[i] = maxRec(arr, length, 0);
	}
	
	for(int i = 0; i<caseNum; i++) printf("%d\n", answer[i]);
	
	return 0;
}

