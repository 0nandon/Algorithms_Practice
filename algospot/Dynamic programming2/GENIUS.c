#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n, k, m;
int sing[50];
int favorite[50];
double probability[50][50];
double c[200];
double ** w;
double answer[50][50];

double ** powCal(double ** arr1, double ** arr2){
	double ** cal;
	cal = (double **)malloc(sizeof(double *) * 4 * n);
	for(int i=0; i<4*n; i++)
		cal[i] = (double *)malloc(sizeof(double) * 4 * n);
	
	for(int a=0; a<4*n; a++){
		for(int b=0; b<4*n; b++){
			double temp = 0.0;
			for(int c=0; c<4*n; c++)
				temp += arr1[a][c] * arr2[c][b];
			cal[a][b] = temp;
		}
	}
	
	return cal;
}

double ** powMatrix(int num){
	if(num == 1)
		return w;

	if(num % 2 == 0)
		return powCal(powMatrix(num/2), powMatrix(num/2));
	else
		return powCal(w, powMatrix(num-1));
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

	w = powMatrix(k-3);
	
	double cAnswer[200];
	memset(cAnswer, 0.0, sizeof(cAnswer));
	for(int i=0; i<4*n; i++){
		double temp = 0.0;
		for(int j=0; j<4*n; j++)
			temp += w[i][j] * c[j];
		cAnswer[i] = temp;
	}
	
	for(int i=0; i<m; i++)
		for(int j=0; j<sing[favorite[i]]; j++)
			answer[caseNum][i] += cAnswer[n*(3-j) + favorite[i]];
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
		
		w = (double **)malloc(sizeof(double *) * 4 * n);
		for(int j=0; j<4*n; j++)
			w[j] = (double *)malloc(sizeof(double) * 4 * n);
		
		for(int a=0; a<4*n; a++)
			for(int b=0; b<4*n; b++)
				w[a][b] = 0.0;
		
		memset(c, 0.0, sizeof(c));
		
		calGenius(i);
		
		for(int j=0; j<m; j++)
			printf("%lf ", answer[i][j]);
		printf("\n");
	}
		
	return 0;
}	

