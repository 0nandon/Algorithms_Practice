#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char str[4001];
int group[4001];
int order[4001];
int length, k;

int compare(int a, int b, int t){
    if(group[a] != group[b])
        return (group[a] > group[b]);
    else
        return (group[a+t] > group[b+t]);
}

//병합 정렬 소스
void merge(int arr[], int start, int half, int end, int t){
	int temp[end-start+1];
	for(int i = 0; i<end-start+1; i++)
		temp[i] = arr[start+i];
	
	int cnt = 0, left = 0, right = 0;
	while(left < half+1 && right < end-start-half){
		if(compare(temp[left], temp[half+1+right], t)){
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
void mergeSort(int arr[], int start, int end, int t){
    if(start != end){
	    int half = (end-start)/2;
	    mergeSort(arr, start, start+half, t);
        mergeSort(arr, start+half+1, end, t);
        merge(arr, start, half, end, t);
	}
}

void getSuffixArray(){
    int t=1;
    length = strlen(str);
    
    for(int i=0; i<length; i++){
        group[i] = str[i];
        order[i] = i;
    }
    group[length] = -1;

    while(t < length){
        mergeSort(order, 0, length-1, t);
        
        int newGroup[4001];
        newGroup[order[0]] = 0;
        for(int i=0; i<length-1; i++){
            if(compare(order[i+1], order[i], t))
                newGroup[order[i+1]] = newGroup[order[i]] + 1;
            else
                newGroup[order[i+1]] = newGroup[order[i]];
        }
        newGroup[length] = -1;
        
        for(int i=0; i<length+1; i++)
            group[i] = newGroup[i];
        t *= 2;
    }
}

int commonPrefix(int i, int j){
    int a = order[i];
    int b = order[j];
    int cnt = 0;
    
    while(str[a+cnt] == str[b+cnt] && (a+cnt < length && b+cnt < length))
        cnt++;
    
    return cnt;
}

int habit(){
    int ret = 0;
    for(int i=0; i<=length-k; i++){
        int temp = commonPrefix(i, i+k-1);
        ret = temp > ret ? temp : ret;
    }
    
    return ret;
}

int main() {
	  int caseNum;
    scanf("%d", &caseNum);
    int answer[caseNum];
    
    for(int i=0; i<caseNum; i++){
        scanf("%d", &k);
        scanf("%s", str);
        
        getSuffixArray();
        answer[i] = habit();
    }
    
    for(int i=0; i<caseNum; i++)
        printf("%d\n", answer[i]);

	  return 0;
}
