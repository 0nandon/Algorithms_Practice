#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cache[10002];
int input[10002];

int min(int a, int b, int c){
	int min = a;
	
	if(min > b)
		min = b;
	if(min > c && c != 0)
		min = c;
	
	return min;
}

int calWeight(int start, int end){
	int len = end - start + 1;
	
	if(input[start] == input[start + 1]){
		for(int i = 2; i < len; i++)
			if(input[start+i] != input[start+i-1])
				return 10;
		return 1;
	}
	else if(input[start] == input[start + 2]){
		for(int i = 3; i < len; i++)
			if(input[start+i] != input[start+i-2])
				return 10;
		return 4;
    }
	else{
		int ret = input[start+1] - input[start];
		
		for(int i = 2; i<len; i++)
			if(input[start+i] - input[start+i-1] != ret)
				return 10;
		if(ret == 1 || ret == -1)
			return 2;
		else return 5;
	}
}

int calAns(int n){
	int * ret = &cache[n];
	
	if(*ret != -1)
		return *ret;
	
	if(n <= 4)
		return calWeight(0, n);
	else if(n == 5)
		return calAns(n-3) + calWeight(n-2, n);
	else if(n == 6)
		return min(calAns(n-3) + calWeight(n-2, n),
				   calAns(n-4) + calWeight(n-3, n), 0);
	else{
		*ret = min(calAns(n-3) + calWeight(n-2, n),
				   calAns(n-4) + calWeight(n-3, n),
				   calAns(n-5) + calWeight(n-4, n));
		return *ret;
	}
}

int main(){
	
	int caseNum = 0;
	
	scanf("%d", &caseNum);
	int answer[caseNum];
	
	for(int i = 0; i<caseNum; i++){
		char str[10001];
		
		scanf("%s", str);
		
		memset(cache, -1, sizeof(cache));
		
		int length = strlen(str);
		
		for(int j=0; j<length; j++)
			input[j] = str[j] - 48;
		
		answer[i] = calAns(length-1);
	}
	
	for(int i=0; i<caseNum; i++)
		printf("%d\n", answer[i]);

    return 0;
}

