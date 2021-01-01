#include <stdio.h>
#include <stdlib.h>

int calPair(int pair[][2], int person[], int pairNum, int start, int wholePair, int personNum){
	if(pairNum == 0) return 1;
    if(start == wholePair && wholePair - start < pairNum) return 0;
	
	while(person[pair[start][0]] == 1 || person[pair[start][1]] == 1){
		start++;
		if(start == wholePair) return 0;
	}
	int person_new[personNum];
	for(int i = 0; i<personNum; i++) person_new[i] = person[i];
	person[pair[start][0]] = 1; person[pair[start][1]] = 1;
		
	return calPair(pair, person, pairNum-1, start+1, wholePair, personNum)
		   + calPair(pair, person_new, pairNum, start+1, wholePair, personNum);
}

int main(){
	int caseNum;
	scanf("%d", &caseNum);
	int answer[caseNum];
	int studentNum; int pairNum;
	
	for(int i = 0; i<caseNum; i++){
		scanf("%d%d", &studentNum, &pairNum);
		int pair[pairNum][2];
		for(int j = 0; j<pairNum; j++) scanf("%d%d", &pair[j][0], &pair[j][1]);
		int person[studentNum];
	    for(int i = 0; i<studentNum; i++) person[i] = 0;
		answer[i] = calPair(pair, person, studentNum/2, 0, pairNum, studentNum);
	}
    
	for(int i = 0; i<caseNum; i++) printf("%d\n", answer[i]);
	return 0;
}

