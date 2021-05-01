#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char str[100001];
char reverse[100001];
int partial[100001];

int getPartial(){
    memset(partial, 0, sizeof(partial));
    int length = strlen(str);
    int match = 0, start = 1;
    
    for(int i=0; i<length; i++)
        reverse[i] = str[length-1-i];
    
    while(start + match < length){
        if(reverse[start + match] == reverse[match]){
            match++;
            partial[start+match-1] = match;
        }else{
            if(match == 0)
                start++;
            else{
                start += match - partial[match-1];
                match = partial[match-1];
            }
        }
    }
    
    return length;
}

int palindromize(){
    int length = getPartial();
    int start = 0, match = 0;
    
    while(start + match < length){
        if(str[start+match] == reverse[match])
            match++;
        else{
            if(match == 0)
                start++;
            else{
                start += match - partial[match-1];
                match = partial[match-1];
            }
        }
    }
    
    return 2*length - match;
}

int main() {
	int caseNum;
    scanf("%d", &caseNum);
    int answer[caseNum];
    
    for(int i=0; i<caseNum; i++){
        scanf("%s", str);
        answer[i] = palindromize();
    }
    
    for(int i=0; i<caseNum; i++)
        printf("%d\n", answer[i]);

	return 0;
}
