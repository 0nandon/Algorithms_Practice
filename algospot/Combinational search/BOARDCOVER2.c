#include <stdio.h>
#include <stdlib.h>

typedef struct point{
	int x;
	int y;
	int num;
	int same;
}POINT;

int h, w, r, c;

char board[11][11];
char piece[11][11];

POINT point[4][101];
int pointNum = 0;

//병합 정렬 소스
void merge(POINT arr[], int start, int half, int end){
	POINT temp[end-start+1];
	for(int i = 0; i<end-start+1; i++)
		temp[i] = arr[start+i];
	
	int cnt = 0, left = 0, right = 0;
	while(left < half+1 && right < end-start-half){
		if(temp[left].num > temp[half+1+right].num){
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

void eliminateSame(){
	for(int i=0; i<4; i++){
		for(int j=i+1; j<4; j++){
			if(!(point[i][0].same || point[j][0].same)){
				int a = 0;
				for(a = 0; a<pointNum; a++)
					if(point[i][a].num != point[j][a].num)
						break;
				if(a == pointNum)
					point[j][0].same = 1;
			}
		}
	}
}

void rotate(){
	for(int i=1; i<4; i++){
		for(int j=0; j<pointNum; j++){
			point[i][j].x = point[i-1][j].y;
			point[i][j].y = -point[i-1][j].x;
		}
		for(int j=0; j<pointNum; j++){
			if(i % 2)
				point[i][j].y += r-1;
			else
				point[i][j].y += c-1;
			point[i][j].num = 10 * point[i][j].x + point[i][j].y;
		}
		mergeSort(point[i], 0, pointNum-1);
		point[i][0].same = 0;
	}
}

void generateRotations(){
	for(int i=0; i<r; i++){
		for(int j=0; j<c; j++){
			if(piece[i][j] == '#'){
				point[0][pointNum].x = i;
				point[0][pointNum].y = j;
				point[0][pointNum++].num = 10*i + j;
			}
		}
	}
	point[0][0].same = 0;
	
	rotate();
	eliminateSame();
}

int isSet(int num, int x, int y, int ret){
	int add1 = x - point[num][0].x;
	int add2 = y - point[num][0].y;
	
	if(ret){
		int i;
		for(i=0; i<pointNum; i++){
			int xBool = ((point[num][i].x + add1 < 0) || (point[num][i].x + add1 >= h));
			int yBool = ((point[num][i].y + add2 < 0) || (point[num][i].y + add2 >= w));
			
			if(xBool || yBool)
				return 0;
			
			if(board[point[num][i].x + add1][point[num][i].y + add2] == '#')
				return 0;
		}
		
		for(int i=0; i<pointNum; i++)
			board[point[num][i].x + add1][point[num][i].y + add2] = '#';
		
		return 1;
	}
	else
		for(int i=0; i<pointNum; i++)
			board[point[num][i].x + add1][point[num][i].y + add2] = '.';
}

int max = 0;
void boardCover(int ans, int empty){
	if((empty / pointNum) + ans <= max)
		return;
	
	int x = -1, y = -1;
	for(int i=0; i<h; i++){
		for(int j=0; j<w; j++){
			if(board[i][j] == '.'){
				x = i; y = j;
				goto HERE;
			}
		}
	}
	
	if(x == -1){
		max = ans > max ? ans : max;
		return;
	}
	
	HERE:
	for(int i=0; i<4; i++){
		if(point[i][0].same)
			continue;
		
		if(isSet(i, x, y, 1)){
			boardCover(ans+1, empty-pointNum);
			
			isSet(i, x, y, 0);
		}
	}
	
	board[x][y] = '#';
	boardCover(ans, empty-1);
	board[x][y] = '.';

	return;
}

int main(){
	
	int caseNum;
	scanf("%d", &caseNum);
	
	for(int i=0; i<caseNum; i++){
		scanf("%d%d%d%d", &h, &w, &r, &c);
		
		for(int j=0; j<h; j++)
			scanf("%s", board[j]);
		
		for(int j=0; j<r; j++)
			scanf("%s", piece[j]);
		
		pointNum = 0;
		max = 0;
		
		generateRotations();
		
		int empty = 0;
		for(int i=0; i<h; i++)
			for(int j=0; j<w; j++)
				if(board[i][j] == '.')
					empty++;
		
		boardCover(0, empty);
		printf("%d\n", max);
	}
		
	return 0;
}
