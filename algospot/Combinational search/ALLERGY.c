#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long num[50]; // 친구들이 먹을 수 있는 음식을 비트 배열로 저장
long long food[50]; // 각 음식이 먹일 수 있는 친구들의 정보를 비트로 저장
int n, m;

int INF = 51;

typedef struct input{
    int num;
    char name[50][11];
}INPUT;

//병합 정렬 소스
void merge(INPUT arr[], int start, int half, int end){
    INPUT temp[end-start+1];
    for(int i = 0; i<end-start+1; i++)
        temp[i] = arr[start+i];

    int cnt = 0, left = 0, right = 0;
    while(left < half+1 && right < end-start-half){
        if(temp[left].num < temp[half+1+right].num){
            arr[start+cnt] = temp[half+1+right]; 
            right++; cnt++;
        }
        else{
            arr[start+cnt] = temp[left]; 
            left++; cnt++;
        }
    }

    if(left == half+1)
        for(int i = 0; i<end-start-half-right; i++)
            arr[start+cnt+i] = temp[half+1+right+i];
    else if(right == end-start-half)
        for(int i = 0; i<half+1-left; i++)
            arr[start+cnt+i] = temp[left+i];
}

// 병합정렬 구현 소스
void mergeSort(INPUT arr[], int start, int end){
    if(start != end){
        int half = (end-start)/2;
        mergeSort(arr, start, start+half);
        mergeSort(arr, start+half+1, end);
        merge(arr, start, half, end);
    }
}

int min;
void allergy(int ans, long long check){
    if(ans >= min)
        return;

    if(check == (1LL<<n)-1){
        min = ans;
        return;
    }

    int i;
    for(i=0; i<n; i++)
        if(!(check & (1LL<<i)))
            break;

    for(int j=0; j<m; j++)
        if(num[i] & (1LL<<j))
            allergy(ans+1, check | food[j]);

    return;
}

int main(){
    int caseNum;
    scanf("%d", &caseNum);
    int answer[caseNum];

    for(int i=0; i<caseNum; i++){
        scanf("%d%d", &n, &m);

        char friend[n][11];

        for(int j=0; j<n; j++)
            scanf("%s", friend[j]);

        INPUT input[m];
        for(int j=0; j<m; j++){
            scanf("%d", &input[j].num);

            for(int a=0; a<input[j].num; a++)
                scanf("%s", input[j].name[a]);
        }

        mergeSort(input, 0, m-1); // 많은 친구들이 먹을 수 있는 음식 순으로 정렬

        for(int j=0; j<50; j++)
            num[j] = 0;
        for(int j=0; j<50; j++)
            food[j] = 0;


        for(int j=0; j<m; j++){
            for(int a=0; a<input[j].num; a++){
                for(int b=0; b<n; b++){
                    if(!strcmp(friend[b], input[j].name[a])){
                        num[b] += (1LL<<j);
                        food[j] += (1LL<<b);
                        break;
                    }
                }
            }
        }

        min = INF;
        allergy(0, 0);
        answer[i] = min;
    }

    for(int i=0; i<caseNum; i++)
        printf("%d\n", answer[i]);

    return 0;
}
