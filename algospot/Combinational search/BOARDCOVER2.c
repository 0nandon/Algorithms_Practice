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

POINT point[410][101];
int num = 4;
int pointNum = 0;
int start = 0;

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
				if(a == pointNum){
					point[j][0].same = 1;
					num--;
				}
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
	
	/*
	printf("\n");
	for(int i=0; i<4; i++){
		if(point[i][0].same)
			continue;
		for(int j=0; j<pointNum; j++)
			printf("(%d, %d) %d  /  ", point[i][j].x, point[i][j].y, point[i][j].num);
		printf("\n");
	}
	*/	
}

void makeCover(){
	int r_t, c_t, temp;
	
	r_t = c; c_t = r;
	for(int i=0; i<4; i++){
		temp = r_t;
		r_t = c_t;
		c_t = temp;
		
		if(point[i][0].same)
			continue;
		
		for(int a=0; a<h-r_t+1; a++){
			for(int b=0; b<w-c_t+1; b++){
				int c;
				for(c=0; c<pointNum; c++)
					if(board[point[i][c].x + a][point[i][c].y + b] == '#')
						break;

				if(c == pointNum){
					for(c=0; c<pointNum; c++){
						point[num][c].x = point[i][c].x + a;
						point[num][c].y = point[i][c].y + b;
					}
					num++;
				}
			}
		}
	}
}


int max = 0;
void boardCover(int next, int ans, int empty){
	if((empty / pointNum) + ans <= max)
		return;
	
	int cnt = 0;
	for(int i=next; i<num; i++){
		int j;
		for(j=0; j<pointNum; j++)
			if(board[point[i][j].x][point[i][j].y] == '#')
				break;
	    
		if(j == pointNum){
			cnt++;
			for(j = 0; j<pointNum; j++)
				board[point[i][j].x][point[i][j].y] = '#';
			
			boardCover(i+1, ans+1, empty-pointNum);
			
			for(j = 0; j<pointNum; j++)
				board[point[i][j].x][point[i][j].y] = '.';
		}
	}
		
	if(!cnt)
		max = ans > max ? ans : max;
	
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
		num = 4;
		max = 0;
		
		generateRotations();
		start = num;
		// printf("%d\n", num);
		makeCover();
		// printf("%d\n", num);
		
		/*
		for(int i=start; i<num; i++){
			for(int j=0; j<pointNum; j++)
				printf("(%d, %d) %d\n", point[i][j].x, point[i][j].y);
			printf("\n");
		}
		*/
		
		int empty = 0;
		for(int i=0; i<h; i++)
			for(int j=0; j<w; j++)
				if(board[i][j] == '.')
					empty++;
		
		boardCover(start, 0, empty);
		printf("%d\n", max);
	}
		
	return 0;
}
