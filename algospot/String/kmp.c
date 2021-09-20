#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 8

int pi[MAXN];

void getPartialMatch(char * string){
    int begin = 1; 
    int match = 0;
    
    memset(pi, 0, sizeof(pi));
    int len = strlen(string);
    while(begin + match < len){
        if(string[begin + match] == string[match]){
            pi[begin + match] = match + 1; 
            match++;
        }else{
            if(match == 0)
                begin++;
            else{
                begin += match - pi[match-1];
                match = pi[match-1];
            }
        }
    }
}

void kmpSearch(char * H, char * N){
    getPartialMatch(N);
    
    int begin = 0;
    int match = 0;
    
    int lenH = strlen(H);
    int lenN = strlen(N);
    
    while(begin + match < lenH){
        if(H[begin + match] == N[match]){
            match++;
        }else{
            if(match == 0)
                begin++;
            else{
                begin += match - pi[match-1];
                match = pi[match-1];
            }
        }

        if(match == lenN){
            printf("Find in %d\n", begin);
            
            begin += match;
            match = 0;
        }
    }
}

int main(){
    char stringH[9] = "ababbaba";
    char stringN[4] = "aba";
    kmpSearch(stringH, stringN);
    
    return 0;
}
