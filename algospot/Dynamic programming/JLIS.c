#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lenNum1, lenNum2;
int cache[101][101];

int max(int a, int b){
	return a > b ? a : b;
}

int calAns(long long len1[], long long len2[], int index1, int index2){
	int * ret = &cache[index1][index2];
	
	if(*ret != -1)
		return *ret;
	
	long long maxIndex;
	if(index1 == 0)
		maxIndex = len2[index2];
	else if(index2 == 0)
		maxIndex = len1[index1];
	else
	    maxIndex = len1[index1] > len2[index2] ? len1[index1] : len2[index2];
	
	if(index1 == 0 && index2 == 0)
		*ret = 0;
	else if(index1 == 0 || index2 == 0)
		*ret = 1;
	else
		*ret = 2;
	
	for(int i=1; i<lenNum1 - index1; i++)
		if(maxIndex < len1[index1+i] || (index1 == 0 && index2 == 0))
			if(index1 == 0)
				*ret = max(*ret, calAns(len1, len2, index1+i, index2));
	        else
				*ret = max(*ret, calAns(len1, len2, index1+i, index2) + 1);
	
	for(int i=1; i<lenNum2 - index2; i++)
		if(maxIndex < len2[index2+i] || (index1 == 0 && index2 == 0))
			if(index2 == 0)
				*ret = max(*ret, calAns(len1, len2, index1, index2+i));
	        else
				*ret = max(*ret, calAns(len1, len2, index1, index2+i) + 1);
	
	return *ret;
}

int main(){
	
	int caseNum = 0;
	
	scanf("%d", &caseNum);
	int answer[caseNum];
	
	for(int i = 0; i<caseNum; i++){
		
		scanf("%d%d", &lenNum1, &lenNum2);
		
		long long len1[++lenNum1];
		long long len2[++lenNum2];
		
		len1[0] = -1;
		len2[0] = -1;
		
		for(int j=1; j<lenNum1; j++)
			scanf("%lld", &len1[j]);
		for(int j=1; j<lenNum2; j++)
			scanf("%lld", &len2[j]);
		
		memset(cache, -1, sizeof(cache));
		answer[i] = calAns(len1, len2, 0, 0);
	}
	
	for(int i=0; i<caseNum; i++)
		printf("%d\n", answer[i]);
		
	return 0;
}


