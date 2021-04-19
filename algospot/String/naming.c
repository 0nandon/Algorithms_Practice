#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int partial[400001];
int answer[400001];
int sort = 0;

int naming(char str[400001]){
    int length = strlen(str);
    answer[sort++] = length;
    
    int start = 1, ret = 0;
    while(start < length){
        int cnt = 0;
        while(str[start + cnt] == str[cnt] && start + cnt <= length-1){
            cnt++;
            partial[start + cnt] = cnt + ret > partial[start + cnt] ? cnt + ret : partial[start + cnt];
        }
        
        if(start + cnt == length){
            answer[sort++] = cnt;
            start++;
            ret = 0;
        }else if(cnt){
            start = start + cnt;
            ret = partial[cnt];
        }
        else{
            start++;
            ret = partial[cnt];
        }
    }
}

int main() {
	char s1[400001];
    char s2[400001];
    
    scanf("%s%s", s1, s2);
    
    strcat(s1, s2);
    memset(partial, 0, sizeof(partial));
    
    naming(s1);

    for(int i=sort-1; i > -1; i--)
        printf("%d ", answer[i]);
    
	return 0;
}
