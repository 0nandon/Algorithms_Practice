#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 10

int sort[MAXN];
int group[MAXN+1];
char string[MAXN+1] = "mississipi";
int ret = 0;

int compare(int index1, int index2){
    if(group[index1] != group[index2])
        return (group[index1] > group[index2]);
    else if(ret != 0)
        return (group[index1+ret] > group[index2+ret]);
    return 0;
}

void merge(int start, int half, int end){
	int temp[end-start+1];
	for(int i = 0; i<end-start+1; i++)
	    temp[i] = sort[start+i];
	
	int cnt = 0, left = 0, right = 0;
	while(left < half+1 && right < end-start-half){
	    if(compare(temp[left], temp[half+1+right])){
	        sort[start+cnt] = temp[half+1+right]; 
                right++; cnt++;
            }else{ 
                sort[start+cnt] = temp[left]; 
                left++; cnt++;	
            }
	}
	
	if(left == half+1)
	    for(int i = 0; i<end-start-half-right; i++)
	        sort[start+cnt+i] = temp[half+1+right+i];
	else if(right == end-start-half)
	    for(int i = 0; i<half+1-left; i++)
	        sort[start+cnt+i] = temp[left+i];
}

// 병합정렬 구현 소스
void mergeSort(int start, int end){
    if(start != end){
        int half = (end-start)/2;
	mergeSort(start, start+half);
        mergeSort(start+half+1, end);
        merge(start, half, end);
    }
}

void makeGroup(){
    int temp[MAXN];
    temp[sort[0]] = group[sort[0]];
    for(int i=0; i<MAXN-1; i++){
        int c1 = sort[i+1];
        int c2 = sort[i];
        
        if(compare(c1, c2))
            temp[c1] = temp[c2] + 1;
        else
            temp[c1] = temp[c2];
    }
    
    for(int i=0; i<MAXN; i++)
        group[i] = temp[i];
}

void makeSuffixArray(){
    while(ret < MAXN){
        mergeSort(0, MAXN-1);
        makeGroup();
        ret = (ret == 0) ? ret + 1 : ret * 2;
    }
}

int find(int start, int end, char * N, int len){
    if(end < start)
        return -1;
        
    int half = (start + end) / 2;
    int c = strncmp(string + sort[half], N, len);
    if(c > 0)
        return find(start, half-1, N, len);
    else if(c < 0)
        return find(half+1, end, N, len);
    return sort[start];
}


int main(){
    for(int i=0; i<MAXN; i++){
        sort[i] = i;
        group[i] = string[i] - 'a';
    }
    group[MAXN] = -1;
    
    makeSuffixArray();
    
    char * N = "ssi";
    printf("부분 문자열 'ssi'는 %d index에 등장합니다.", find(0, MAXN-1, N, strlen(N)));
    
    return 0;
}
