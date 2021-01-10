#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int length;
int overlap[15][15];
char str[15][40];
int cache[15][1<<15];
int used, firstUsed;
int out;

int ENF = 987654321;

void calOverlap(){
	for(int i=0; i<length; i++){
		for(int j=0; j<length; j++){
			if(i == j)
				continue;
			if((used & (1<<i)) || (used & (1<<j)))
				continue;
			
			int length1 = strlen(str[i]);
			int length2 = strlen(str[j]);
			
			int ret = length1 > length2 ? length2 : length1;
			int retLong = length1 > length2 ? length1 : length2;
			int big = length1 > length2 ? i : j;
			int small = length1 > length2 ? j : i;
			
			char str1[ret+1];
			char str2[ret+1];
			
			char * check = strstr(str[big], str[small]);
			
			if(check){
				if((used & (1<<small)) == 0){
					used = used | (1<<small);
				    out++;
				}
			}
			else{
				int cnt = 0;
				for(int a=0; a<ret; a++){
					strncpy(str1, str[i]+length1-a-1, a+1);
					strncpy(str2, str[j], a+1);
					str1[a+1] = '\0';
					str2[a+1] = '\0';
				
					if(!strcmp(str1, str2))
						cnt = a + 1;
				}
				
				overlap[i][j] = length1 - cnt;
			}
		}
	}	
}

int restore(int index, int last, int used){
	int * ret = &cache[last][used];
												 
	if(*ret != -1)
		return *ret;
	
	*ret = ENF;
	for(int i=0; i<length; i++){
		if(index == length-out)
			*ret = strlen(str[last]);
		else if((used & 1<<i) != 0)
			continue;
		else{
			int temp = overlap[last][i] + restore(index+1, i, (used | 1<<i));
			*ret = *ret > temp ? temp : *ret;	
		}
	}
	
	return *ret;
}


char * reconstruct(int index, int last, int used){
	
	char * strRe = (char*)malloc(sizeof(char) * 600);
	
	for(int i=0; i<length; i++){
		if(index == length - out)
			return str[last];
		else if((used & 1<<i) != 0)
			continue;
		else if(restore(index, last, used) == overlap[last][i] + restore(index+1, i, (used | 1<<i))){
			strncpy(strRe, str[last], overlap[last][i]);
			strcat(strRe, reconstruct(index+1, i, (used | 1<<i)));
			break;
		}	
	}
	
	return strRe;
}


int main() {
	
	int caseNum;
	scanf("%d", &caseNum);
	char answer[caseNum][600];
	
	for(int i=0; i<caseNum; i++){
		scanf("%d", &length);
		
		for(int j=0; j<length; j++)
			scanf("%s", str[j]);
		
		used = 0; out = 0;
		calOverlap();
		firstUsed = used;
				
		memset(cache, -1, sizeof(cache));
		// memset(overlap, -1, sizeof(overlap));
		
		int min = ENF;
		int first = 0;
		for(int j = 0; j<length; j++){
			if((used & 1<<j) != 0)
				continue;

			int temp = restore(1, j, (used | 1<<j));
			if(min > temp){
				min = temp;
				first = j;
			}	
		}
		
		strcpy(answer[i], reconstruct(1, first, (firstUsed | (1<<first))));
	}
	
	
	for(int i=0; i<caseNum; i++)
		printf("%s\n", answer[i]);
		
	return 0;
}
