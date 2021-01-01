#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int connect[50];
double cache[101][51];
int road[51][51];

double calculateP(int day, int village, int villageNum, int prison){
	if(day == 0) return (village == prison ? 1.0 : 0.0);
	
	double * ret = &cache[day][village];
	if(*ret > -0.5) return *ret;
	
	*ret = 0.0;
	for(int i = 0; i<villageNum; i++)
		if(road[village][i] == 1) *ret += calculateP(day-1, i, villageNum, prison)/connect[i];
	
	return *ret;	
}

int main() {	
    int caseNum;
	scanf("%d", &caseNum);
	
	for(int i = 0; i< caseNum; i++){
		memset(connect, 0, sizeof(connect));
		memset(cache, -1, sizeof(cache));
		memset(road, -1, sizeof(road));
		
		int villageNum, day, prison;
		scanf("%d%d%d", &villageNum, &day, &prison);

		for(int j = 0; j<villageNum; j++)
			for(int k = 0; k<villageNum; k++)
				scanf("%d", &road[j][k]);
		
		for(int j = 0; j<villageNum; j++)
			for(int k = 0; k<villageNum; k++)
				if(road[j][k] == 1) connect[j]++;
		
		int num;
        scanf("%d", &num);
		double village[num];
		for(int j = 0; j<num; j++){
			int v;
			scanf("%d", &v);
			village[j] = calculateP(day, v, villageNum, prison);
		}
		
		for(int j = 0; j<num; j++) printf("%.8lf ", village[j]);
		printf("\n");
	}
	
	return 0;
}

