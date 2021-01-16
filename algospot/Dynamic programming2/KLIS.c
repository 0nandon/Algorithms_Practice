#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const long ENF = (long)1<<32;

int n;
long k;
int lis[501];
int cache[501];
long count[501];
int answer[50][500];
int answerLis[50];

int len;

//병합 정렬 소스
void merge(int arr[], int start, int half, int end){
	int temp[end-start+1];
	for(int i = 0; i<end-start+1; i++)
		temp[i] = arr[start+i];
	
	int cnt = 0, left = 0, right = 0;
	while(left < half+1 && right < end-start-half){
		if(lis[temp[left]] > lis[temp[half+1+right]]){
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

int maxLis(int num){
	int * ret = &cache[num];
	
	if(*ret != -1)
		return *ret;
	
	int cnt = num+1; 
	if(cnt == n)
		return 1;
	
	*ret = 1;
	while(cnt < n){
		if(lis[num] < lis[cnt])
			*ret = maxLis(cnt) + 1 > *ret ? maxLis(cnt) + 1 : *ret;
		cnt++;
	}
	
	return *ret;
}

long calCount(int kth){
	long * ret = &count[kth];
	
	if(*ret != -1)
		return *ret;
	
	if(maxLis(kth)==1)
		return 1;
	
	*ret = 0; 
	for(int i=1; i<n-kth; i++)
		if((lis[kth + i] > lis[kth]) && (maxLis(kth + i) == maxLis(kth) - 1))
			*ret = ENF > *ret + calCount(kth+i) ? *ret + calCount(kth+i) : ENF;
	
	return *ret;
}

int sort[501];
void calKlis(int th, int kth){
	int cnt = 0;
	for(int i=1; i<n-kth; i++)
		if((lis[kth + i] > lis[kth]) && (maxLis(kth + i) == maxLis(kth) - 1))
			sort[cnt++] = kth+i;

	mergeSort(sort, 0, cnt-1);
	
	for(int i=0; i<cnt; i++){
		if(calCount(sort[i]) >= k){
			if(sort[i] != 0)
				answer[th][len++] = lis[sort[i]];
			if(len == answerLis[th]-1)
				break;
			calKlis(th, sort[i]);
			break;
		}
		else
			k -= calCount(sort[i]);
	}
	
}


int main(){
	int caseNum;
	scanf("%d", &caseNum);
	
	for(int i=0; i<caseNum; i++){
		scanf("%d%ld", &n, &k);
		memset(cache, -1, sizeof(cache));
		memset(count, -1, sizeof(count));
		
		lis[0] = -1; n++;
		len = 0;
		
		for(int j=1; j<n; j++)
			scanf("%d", &lis[j]);
		
		answerLis[i] = maxLis(0);
		calCount(0);
		calKlis(i, 0);
	}
	
	for(int i=0; i<caseNum; i++){
		printf("%d\n", --answerLis[i]);
		
		for(int j=0; j<answerLis[i]; j++)
			printf("%d ", answer[i][j]);
		printf("\n");
	}

	return 0;
}	

