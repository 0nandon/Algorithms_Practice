#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cache[201];
int info[20][2];
int n, m;

int sushi(){
	for(int i=0; i<n; i++)
		cache[info[i][0]] = cache[info[i][0]] > info[i][1] ? cache[info[i][0]] : info[i][1];
	
	int max=0;
	for(int i=0; i<m+1; i++){
		if(cache[i % 201] != -1){
			for(int j=0; j<n; j++){
				if((i + info[j][0]) > m)
					continue;
				
				cache[(i + info[j][0]) % 201] = cache[i % 201] + info[j][1] > cache[(i + info[j][0]) % 201]
												? cache[i % 201] + info[j][1] : cache[(i + info[j][0]) % 201];
			}
			max = cache[i % 201] > max ? cache[i % 201] : max;
			cache[i % 201] = -1;
		}
	}
	
	return max;	
}

int main(){
	int caseNum;
	scanf("%d", &caseNum);
	int answer[caseNum];
	
	for(int i=0; i<caseNum; i++){
		scanf("%d%d", &n, &m);
		
		for(int j=0; j<n; j++)
			scanf("%d%d", &info[j][0], &info[j][1]);
		
		for(int j=0; j<n; j++)
			info[j][0] /= 100;
		m /= 100;
		
		memset(cache, -1, sizeof(cache));
		answer[i] = sushi();
	}
	
	for(int i=0; i<caseNum; i++)
		printf("%d\n", answer[i]);

	return 0;
}	