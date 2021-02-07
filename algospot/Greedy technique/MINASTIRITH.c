#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.141592

int INF = 987654321;
int point;

typedef struct range{
	double start;
	double end;
	int used;
}RADIAN;

RADIAN radian[100];

//병합 정렬 소스
void merge(RADIAN arr[], int start, int half, int end){
	RADIAN temp[end-start+1];
	for(int i = 0; i<end-start+1; i++)
		temp[i] = arr[start+i];
	
	int cnt = 0, left = 0, right = 0;
	while(left < half+1 && right < end-start-half){
		if(temp[left].start > temp[half+1+right].start){
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
void mergeSort(RADIAN arr[], int start, int end){
    if(start != end){
	    int half = (end-start)/2;
	    mergeSort(arr, start, start+half);
        mergeSort(arr, start+half+1, end);
        merge(arr, start, half, end);
	}
}

int solveLinear(double start, double end){
	int ret = 0;
	
	while(start < end){
		int i=0;
		double max = -1.0;
		
		while(i < point && radian[i].start <= start){
			if(!(radian[i].used)){
				max = radian[i].end > max ? radian[i].end : max;
				radian[i].used = 1;
			}
			i++;
		}
		
		if(max <= start)
			return INF;
		else
			start = max;
		
		ret++;
	}
	
	return ret;
}

int solveCircular(){
	int ret = INF;
	
	for(int i=0; i<point; i++){
		if(radian[i].start <= 0 || radian[i].end >= 2*PI){
			double start = fmod(radian[i].end, 2*PI);
			double end = fmod(radian[i].start + 2*PI, 2*PI);
			
			for(int j=0; j<point; j++)
				radian[j].used = 0;
			
			radian[i].used = 1;
			int cand = solveLinear(start, end) + 1;
			ret = ret > cand ? cand : ret;
		}
	}
	
	return ret;
}

int main(){
	int caseNum;
	scanf("%d", &caseNum);
	int answer[caseNum];
	
	for(int i=0; i<caseNum; i++){
		scanf("%d", &point);
		
		for(int j=0; j<point; j++){
			double x, y;
			double r;
			scanf("%lf%lf%lf", &x, &y, &r);
					
			double loc = fmod(2*PI + atan2(y, x), 2*PI);
			double range = 2.0 * asin((r / 2.0) / 8.0);
			
			radian[j].start = loc - range;
			radian[j].end = loc + range;
		}
		
		mergeSort(radian, 0, point-1);
		answer[i] = solveCircular();
	}
	
	for(int i=0; i<caseNum; i++)
		if(answer[i] == INF)
			printf("IMPOSSIBLE\n");
		else
			printf("%d\n", answer[i]);
		
	return 0;
}
