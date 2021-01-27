
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define min -1e200 // 음의 무한대에 가까운 수

int m, q;
char word[502][10];
double firstProb[502];
double nextProb[502][502];
double miss[502][502];
double cache[102][502];
int choice[102][502];

int n;
int got[102];
int answer[102];

void init(){
	for(int i=0; i<102; i++)
		for(int j=0; j<502; j++)
			cache[i][j] = 1.0; // 저장될 값에 따라 초기화 값 조정이 달라진다는 것에 주의
}

double log(double prob){
	if(prob == 0.0)
		return min;
	else
		return log10(prob);
}

double ocr(int last, int index){
	double * ret = &cache[index][last];
	
	if(index == n)
		return 0;
	
	if(*ret != 1.0)
		return *ret;
	
	*ret = min; // 
	for(int i=0; i<m; i++){
		double cand = nextProb[last][i] + miss[i][got[index]]
				      + ocr(i, index+1);
		
		if(cand > *ret){
			*ret = cand;
			choice[index][last] = i;
		}
	}
	
	return *ret;
}

void reconstruct(int last, int index){
	if(index == n)
		return;
	
	answer[index] = choice[index][last];
	reconstruct(choice[index][last], index+1);
}

int main(){
	
	scanf("%d%d", &m, &q);
	
	for(int i=0; i<m; i++)
		scanf("%s", word[i]);
		
	for(int i=0; i<m; i++){
		scanf("%lf", &firstProb[i]);		
		firstProb[i] = log(firstProb[i]); // 확률을 계속 곱하다 보면 언더플로우가 발생할 수 있기 때문에 로그값으로 변환하여 계산
	}
	
	for(int i=0; i<m; i++){
		for(int j=0; j<m; j++){
			scanf("%lf", &nextProb[i][j]);
			nextProb[i][j] = log(nextProb[i][j]);
		}
	}
	
	for(int i=0; i<m; i++){
		for(int j=0; j<m; j++){
			scanf("%lf", &miss[i][j]);
			miss[i][j] = log(miss[i][j]);
		}
	}
	

	for(int i=0; i<q; i++){
		
		scanf("%d", &n);
		for(int j=0; j<n; j++){
			char temp[10];
			scanf("%s", temp);
			
			for(int x=0; x<m; x++)
				if(!strcmp(word[x], temp))
					got[j] = x;
		}
		
		init();
		memset(choice, -1, sizeof(choice));
		
		double ret = min;
		int choice;
		for(int j=0; j<m; j++){	
			double cand = firstProb[j] + miss[j][got[0]] + ocr(j, 1);

			if(cand > ret){
				ret = cand;
				choice = j;
			}
		}
		answer[0] = choice;
		reconstruct(choice, 1);
		
		for(int j=0; j<n; j++)
			printf("%s ", word[answer[j]]);
		printf("\n");
	}
		
	return 0;
}

