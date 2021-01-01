#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int sumLis[101];
int sumCou[101];
int cache[101][51];
int num;

//병합 정렬 소스

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
void mergeSort(int arr[], int start, int end){
    if(start != end){
	    int half = (end-start)/2;
	    mergeSort(arr, start, start+half);
        mergeSort(arr, start+half+1, end);
        merge(arr, start, half, end);
	}
}


int calQuan(int start, int end){
	int ret = 0;
	int len = end-start+1;
	int mean;
	
	if(start == 0)
		mean = (int)floor(((double)sumLis[end] / len) + 0.5);
	else
		mean = (int)floor(((double)(sumLis[end]-sumLis[start-1]) / len) + 0.5); 
	
	if(start == 0){
		ret += sumCou[end];
		ret -= 2 * mean * sumLis[end];
		ret += mean * mean * len;
	}else{
		ret += sumCou[end] - sumCou[start-1];
		ret -= 2 * mean * (sumLis[end] - sumLis[start-1]);
		ret += mean * mean * len;
	}
	
	return ret;
}

int calAns(int arr[], int start, int n){
	int * ret = &cache[start][n];
	
	if(*ret != -1)
		return *ret;
	
	if(start == num)
		return 0;
	if(n == 1)
		return calQuan(start, num-1);
	
	*ret = calQuan(start, start) + calAns(arr, start+1, n-1);
	for(int i =1; i<num-start; i++){
		int cal = calQuan(start, start+i) + calAns(arr, start+1+i, n-1);
		*ret = *ret > cal ? cal : *ret;
	}

	return *ret;
}

int main(){
	
	int caseNum = 0;
	
	scanf("%d", &caseNum);
	int answer[caseNum];
	
	for(int i = 0; i<caseNum; i++){
		int quan;
		scanf("%d%d", &num, &quan);
		
		memset(cache, -1, sizeof(cache));
		
		int lis[num];
		for(int j=0; j<num; j++)
			scanf("%d", &lis[j]);
		
		mergeSort(lis, 0, num-1);
		
		sumLis[0] = lis[0];
		sumCou[0] = lis[0] * lis[0];
		for(int j=0; j<num; j++){
			sumLis[j] = sumLis[j-1] + lis[j];
			sumCou[j] = sumCou[j-1] + lis[j]*lis[j];
		}
		
		answer[i] = calAns(lis, 0, quan);
	}
	
	for(int i=0; i<caseNum; i++)
		printf("%d\n", answer[i]);
		
	return 0;
}


