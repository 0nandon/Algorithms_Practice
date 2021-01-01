#include <stdio.h>
#include <stdlib.h>

int memory[10][6] = {
	{0, 1, 2, -1, -1},
	{3, 7, 9, 11, -1},
	{4, 10, 14, 15, -1},
	{0, 4, 5, 6, 7},
	{6, 7, 8, 10, 12},
	{0, 2, 14, 15, -1},
	{3, 14, 15, -1, -1},
	{4, 5, 7, 14, 15},
	{1, 2, 3, 4, 5},
	{3, 4, 5, 9, 13},
};

int clockArr[16];

int twelveClock(int switchArr[], int clockArr[]){
	int arr[16];
	for(int i = 0; i<16; i++) arr[i] = clockArr[i];
	
	for(int i = 0; i<10; i++){
		for(int j = 0; j<5; j++){
			if(memory[i][j] == -1) break;
			arr[memory[i][j]] += 3*switchArr[i];
		}
	}
	
	int i;
	for(i = 0; i<16; i++)
		if(arr[i]%12 != 0) break;
	
	if(i == 16) return 1;
	else return 0;
}

int calSwitch(int switchArr[], int num){
	if(num == 9){
		for(int i = 0; i<4; i++){
			switchArr[num] = i;
			if(twelveClock(switchArr, clockArr)) return switchArr[num];
		}
		return -1;
	}
	
    int arr[4];
	for(int i = 0; i<4; i++){
	    for(int j = num+1; j<10; j++) switchArr[j] = 0;
		switchArr[num] = i;
		arr[i] = calSwitch(switchArr, num+1);
	}
	
	int min = arr[0]; int ret = 0; int i;
	for(i = 1; i<4; i++){
		if(arr[i] == -1) continue;
		else if(min == -1) { min = arr[i]; ret = i; }
		else if(min > arr[i]){
			min = arr[i]; ret = i;
		}
	}
    
	if(min == -1) return -1;
	else return ret + min;	
}

int main() {
	int caseNum;
	scanf("%d", &caseNum);

	int switchArr[10] = {0, };
	int answer[caseNum];
	
	for(int i = 0; i<caseNum; i++){
		for(int j = 0; j<16; j++)
			scanf("%d", &clockArr[j]);
	    answer[i] = calSwitch(switchArr, 0);
	}
	
	for(int i = 0; i<caseNum; i++) printf("%d\n", answer[i]);
	return 0;
}


