#include <stdio.h>
#include <stdlib.h>

typedef struct lunch{
	int m;
	int e;
}LUNCH;

LUNCH lunch[10000];
int num;

//병합 정렬 소스
void merge(LUNCH arr[], int start, int half, int end){
	LUNCH temp[end-start+1];
	for(int i = 0; i<end-start+1; i++)
		temp[i] = lunch[start+i];
	
	int cnt = 0, left = 0, right = 0;
	while(left < half+1 && right < end-start-half){
		if(temp[left].e < temp[half+1+right].e){
			arr[start+cnt] = temp[half+1+right]; 
			right++; cnt++;
		}
		else{
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
void mergeSort(LUNCH arr[], int start, int end){
    if(start != end){
	    int half = (end-start)/2;
	    mergeSort(arr, start, start+half);
        mergeSort(arr, start+half+1, end);
        merge(arr, start, half, end);
	}
}

int lunchBox(){
	int ret = 0;
	int temp = 0;
	
	for(int i=0; i<num; i++){
		temp += lunch[i].m;
		ret = temp + lunch[i].e > ret ? temp + lunch[i].e : ret;
	}
	
	return  ret;
}

int main(){
	int caseNum;
	scanf("%d", &caseNum);
	
	int answer;
	for(int i=0; i<caseNum; i++){
		
		scanf("%d", &num);

		for(int j=0; j<num; j++)
			scanf("%d", &lunch[j].m);
		
		for(int j=0; j<num; j++)
			scanf("%d", &lunch[j].e);
		
		mergeSort(lunch, 0, num-1);
		answer = lunchBox();
		printf("%d\n", answer);
	}
	
	return 0;
}

