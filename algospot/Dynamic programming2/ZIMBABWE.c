#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cache[1<<14][20][2];
int length, m;
int e_int[15];
char e[15];

int MOD = 1000000007;

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

int cntPrice(int index, int used, int mod, int less){
	
	int * ret = &cache[used][mod][less];
	if(*ret != -1)
		return *ret;
	
	if(index == length)
		return (!mod && less) ? 1 : 0;
	
	*ret = 0;
	int nextLess, nextMod, nextUsed;
	for(int i=0; i<length; i++){
		if((less == 0 && e[index] - '0' < e_int[i]) || (used & (1<<i)) != 0)
			continue;
		if((i != 0 && e_int[i-1] == e_int[i]) && (used & (1<<(i-1))) == 0)
			continue;
		
		nextLess = ((less == 0) && (e[index] - '0' > e_int[i])) || less;
		nextUsed = used | (1<<i);
		nextMod = (10 * mod + e_int[i]) % m;
		
		*ret += cntPrice(index+1, nextUsed, nextMod, nextLess);
		*ret %= MOD;
	}
	
	return *ret;
}

int main() {
	int caseNum;
	scanf("%d", &caseNum);
	int answer[caseNum];
	
	for(int i=0; i<caseNum; i++){
		scanf("%s%d", e, &m);
		length = strlen(e);
		
		for(int j=0; j<length; j++)
			e_int[j] = e[j] - '0';

		mergeSort(e_int, 0, length-1);
		
		memset(cache, -1, sizeof(cache));
		answer[i] = cntPrice(0, 0, 0, 0);
	}
	
	for(int i=0; i<caseNum; i++)
		printf("%d\n", answer[i]); 
	
	return 0;
}

