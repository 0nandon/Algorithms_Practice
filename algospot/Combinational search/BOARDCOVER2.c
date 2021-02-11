#include <stdio.h>
#include <stdlib.h>

typedef struct point{
	int x;
	int y;
	int same;
}POINT;

int h, w, r, c;

char board[10][10];
char piece[10][10];

POINT point[400][100];
int num = 0;
int pointNum = 0;

//병합 정렬 소스
void merge(POINT arr[], int start, int half, int end){
	POINT temp[end-start+1];
	for(int i = 0; i<end-start+1; i++)
		temp[i] = arr[start+i];
	
	int cnt = 0, left = 0, right = 0;
	while(left < half+1 && right < end-start-half){
		if(temp[left].x > temp[half+1+right].x){
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
void mergeSort(POINT arr[], int start, int end){
    if(start != end){
	    int half = (end-start)/2;
	    mergeSort(arr, start, start+half);
        mergeSort(arr, start+half+1, end);
        merge(arr, start, half, end);
	}
}

int same(){
	
}

void rotate(){
	for(int i=1; i<4; i++){
		for(int j=0; j<pointNum; j++){
			point[i][j].x = point[i-1][j].y;
			point[i][j].y = -point[i-1][j].x;
		}
		mergeSort(point[i], 0, pointNum-1);
		for(int j=0; j<pointNum; j++){
			point[i][j].x -= point[i][0].x;
			point[i][j].y -= point[i][0].y;
		}	
	}
}

void generateRotations(){
	for(int i=0; i<r; i++){
		for(int j=0; j<c; j++){
			if(piece[i][j] == '#'){
				if(pointNum == 0){
					point[0][pointNum].x = i;
					point[0][pointNum++].y = j;
				}
				else{
					point[0][pointNum].x = i - point[0][0].x;
					point[0][pointNum++].y = j - point[0][0].y;
				}
			}
		}
	}
	point[0][0].x = 0; point[0][0].y = 0;
	rotate();
	
	printf("\n");
	for(int i=0; i<4; i++){
		for(int j=0; j<pointNum; j++)
			printf("(%d, %d) ", point[i][j].x, point[i][j].y);
		printf("\n");
	}
}

int boardCover(){
	
}

int main(){
	int caseNum;
	scanf("%d", &caseNum);
	int answer[caseNum];
	
	for(int i=0; i<caseNum; i++){
		scanf("%d%d%d%d", &h, &w, &r, &c);
		
		for(int j=0; j<h; j++)
			scanf("%s", board[j]);
		
		for(int j=0; j<r; j++)
			scanf("%s", piece[j]);
		
		pointNum = 0;
		num = 0;
		
		generateRotations();
		// answer[i] = boardCover();
	}
	
	/*
	for(int i=0; i<caseNum; i++)
		printf("%d\n", answer[i]);
	*/
	
	return 0;
}
