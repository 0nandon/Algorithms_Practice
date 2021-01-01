#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int start = 0;
char * makeReverse(char * zipFile){
	if(zipFile[start] == 'x'){
		start++;
		char * first = (char *)malloc(sizeof(char)* 1000);
		char * second = (char *)malloc(sizeof(char)* 1000);
		char * third = (char *)malloc(sizeof(char)* 1000);
		char * fourth = (char *)malloc(sizeof(char)* 1000);
		
		strcpy(first, makeReverse(zipFile));
		strcpy(second, makeReverse(zipFile));
	    strcpy(third, makeReverse(zipFile));
		strcpy(fourth, makeReverse(zipFile));

		static char reverseFile[1000];
		strcpy(reverseFile, "x");
		strcat(reverseFile, third);
		strcat(reverseFile, fourth);
		strcat(reverseFile, first);
		strcat(reverseFile, second);
		return reverseFile;
	}
	else{
		static char file[1]; 
		file[0] = zipFile[start];
		start++;
		return file;
	}
}

int main(){
	int caseNum;
	scanf("%d", &caseNum);
	char answer[caseNum][1000];
	
	for(int i = 0; i<caseNum; i++){
		char * zipFile;
		zipFile = (char*)malloc(sizeof(char)*1000);
		scanf("%s", zipFile);
        zipFile = makeReverse(zipFile);
		strcpy(answer[i], zipFile);
		start = 0;
	}
    
	for(int i = 0; i<caseNum; i++) printf("%s\n", answer[i]);
	return 0;
}

