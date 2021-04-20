#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int partial[400002];
int answer[400002];
int sort = 0;

int naming(char str[400002]){
    int length = strlen(str);
    answer[sort++] = length;
    
    int start = 1, ret = 0;
    while(start < length){
        int cnt = 0;
        while(str[start + ret + cnt] == str[ret + cnt] && start + ret + cnt <= length-1){
            cnt++;
            partial[start + cnt + ret] = ret + cnt;
        }
        
        if(ret + cnt > 0){
            if(start + ret + cnt == length)
                answer[sort++] = ret + cnt;
            start = start + ret + cnt - partial[ret + cnt];
            ret = partial[ret + cnt];
        }else{
            start++;
            ret = 0;
        }
    }
}

int main() {
    char s1[400002];
    char s2[400002];
    
    scanf("%s%s", s1, s2);
    
    strcat(s1, s2);
    memset(partial, 0, sizeof(partial));
    
    naming(s1);

    for(int i=sort-1; i > -1; i--)
        printf("%d ", answer[i]);
    
    return 0;
}
