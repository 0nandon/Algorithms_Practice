#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int partial[10002];
int num;
char state[101][20004];

void getPartial(char original[20004]){
    memset(partial, 0, sizeof(partial));
    int length = strlen(original);
    int start = 1, match = 0;
    
    while(start + match < length){
        if(original[start + match] == original[match]){
            match++;
            partial[start + match - 1] = match;
        }
        else{
            if(match == 0)
                start++;
            else{
                start += match - partial[match-1];
                match = partial[match-1];
            }
        }
    }
}

int kmp(char original[20004], char target[20004]){
    int start = 1, match = 0;
    int lengthO = strlen(original);
    int lengthT = strlen(target);
    
    getPartial(target);

    while(start <= lengthO - lengthT){
        if(match == lengthT)
            break;
        
        if(match < lengthT && original[start + match] == target[match]){
            match++;
        }else{
            if(match == 0){
                start++;
            }
            else{
                start += match - partial[match-1];
                match = partial[match-1];
            }
        }
    }

    return start;
}

int jaehasafe(){
    int answer = 0;
    for(int i=0; i<num; i++){
        if(i % 2 == 0){
            char temp[20004];
            strcpy(temp, state[i+1]);
            strcat(temp, state[i+1]);
            answer += kmp(temp, state[i]);
        }else{
            char temp[20004];
            strcpy(temp, state[i]);
            strcat(temp, state[i]);
            answer += kmp(temp, state[i+1]);
        }
    }
    
    return answer;
}

int main() {
	int caseNum;
    scanf("%d", &caseNum);
    int answer[caseNum];
    
    for(int i=0; i<caseNum; i++){
        scanf("%d", &num);
        
        for(int j=0; j<num+1; j++)
            scanf("%s", state[j]);
        
        answer[i] = jaehasafe(); 
    }
    
    for(int i=0; i<caseNum; i++)
        printf("%d\n", answer[i]);

	return 0;
}
