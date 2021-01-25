#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n, k, m;
int sing[50];
int favorite[50];
double probability[50][50];
double c[200];
double w[200][200]; // 배열 크기를 잡을 때 주의하자.
double store[2][200][200];
double answer[50][50];

int binary[100];
int size;

void calBinary(int num){
	size = 0;
	
	while(num > 1){
		if(num % 2 == 0){
			binary[size++] = 0;
			num /= 2;
		}
		else{
			binary[size++] = 1;
			num--;
		}
	}
}

void powCal(int num){
	for(int a=0; a<4*n; a++){
		for(int b=0; b<4*n; b++){
			double temp = 0.0;
			for(int c=0; c<4*n; c++)
				temp += store[(num+1)%2][a][c] * store[(num+1)%2][c][b];
			store[num][a][b] = temp; // 행렬 곱을 계산할 때는 결과 값을 다른 배열에 저장해 주어야 한다.
		}
	}
}

void powMatrix(){
	// for문으로 행렬곱을 수행하여 메모리 부하를 줄이고, 속도를 높였다.
	for(int i=size-1; i > -1; i--){
		if(i == size-1){
			for(int a=0; a<4*n; a++){
				for(int b=0; b<4*n; b++){
					double temp = 0.0;
					for(int c=0; c<4*n; c++)
						temp += w[a][c] * w[c][b];
					store[i%2][a][b] = temp;
				}
			}
		}
		else if(!binary[i]){
			powCal(i%2);
		}else{
			for(int a=0; a<4*n; a++){
				for(int b=0; b<4*n; b++){
					double temp = 0.0;
					for(int c=0; c<4*n; c++)
						temp += w[a][c] * store[(i+1)%2][c][b];
					store[i%2][a][b] = temp;
				}
			}
		}	
	}
}

void firstStart(){
	c[0] = 1.0;
	
	for(int i=1; i<4; i++)
		for(int a=0; a<n; a++)
			for(int b=0; b<n; b++)
				if(i-sing[b] >= 0)
					c[n*i + a] += c[n*(i-sing[b]) + b] * probability[b][a];
}

void calGenius(int caseNum){
	firstStart();
	
	for(int i=0; i<3*n; i++)
		w[i][n+i] = 1.0;
	
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			w[3*n + i][n*(4-sing[j]) + j] = probability[j][i];
	
	if(k >= 4){
		double cAnswer[200];
		memset(cAnswer, 0.0, sizeof(cAnswer));
		if(k > 4){
			calBinary(k-3);
			powMatrix();
	
			for(int i=0; i<4*n; i++){
				double temp = 0.0;
				for(int j=0; j<4*n; j++)
					temp += store[0][i][j] * c[j];
				cAnswer[i] = temp;
			}
		}else{
			for(int i=0; i<4*n; i++){
				double temp = 0.0;
				for(int j=0; j<4*n; j++)
					temp += w[i][j] * c[j];
				cAnswer[i] = temp;
			}	
		}
		
		for(int i=0; i<m; i++)
			for(int j=0; j<sing[favorite[i]]; j++)
				answer[caseNum][i] += cAnswer[n*(3-j) + favorite[i]];
	}
	else{
		for(int i=0; i<m; i++){
			for(int j=0; j<sing[favorite[i]]; j++)
				answer[caseNum][i] += c[n*(3-j) + favorite[i]];
		}	
	}
}

int main(){
	int caseNum;
	scanf("%d", &caseNum);
	memset(answer, 0.0, sizeof(answer));
	
	for(int i=0; i<caseNum; i++){
		scanf("%d%d%d", &n, &k, &m);
		
		for(int j=0; j<n; j++)
			scanf("%d", &sing[j]);
		
		for(int a=0; a<n; a++)
			for(int b=0; b<n; b++)
				scanf("%lf", &probability[a][b]);
		
		for(int j=0; j<m; j++)
			scanf("%d", &favorite[j]);
		
		
		memset(c, 0.0, sizeof(c)); // memset은 double을 초기화할때도 사용할 수 있다.
		memset(w, 0.0, sizeof(w));
		memset(store, 0.0, sizeof(store));
		memset(binary, -1, sizeof(binary));
		
		calGenius(i);
		
		for(int j=0; j<m; j++)
			printf("%.8lf ", answer[i][j]);
		printf("\n");
	}
	
	return 0;
}



