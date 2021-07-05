#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char input[100][11];
int num;
int graph[26][26];
int storeNum[26][26];
char store[26][26][100][11];
int inDegree[26];
int outDegree[26];

int circuitNum;
int circuit[200];

void makeGraph(){
    for(int i=0; i<num; i++){
        int start = input[i][0] - 'a';
        int end = input[i][strlen(input[i])-1] - 'a';
        strcpy(store[start][end][graph[start][end]++], input[i]);
        storeNum[start][end]++;
        inDegree[end]++;
        outDegree[start]++;
    }
}

int checkEuler(){
    int start = 0;
    int end = 0;
    for(int i=0; i<26; i++){
        int interval = inDegree[i] - outDegree[i];
        if(interval == 1) end++;
        else if(interval == -1) start++;
        else if(interval > 1 || interval < -1) return 0;
    }

    return (start == 1 && end == 1) || (!start && !end);
}

void getEulerCircuit(int num){
    for(int i=0; i<26; i++){
        while(graph[num][i] > 0){
            graph[num][i]--;
            getEulerCircuit(i);
        }
    }
        
    circuit[circuitNum++] = num;
}

void getEulerTrailerOrCircuit(){
    for(int i=0; i<26; i++){
        if(outDegree[i] - inDegree[i] == 1){
            getEulerCircuit(i);
            return;
        }
    }

    for(int i=0; i<26; i++){
        if(outDegree[i] > 0){
            getEulerCircuit(i);
            return;
        }
    }
}

int main() {
    int caseNum;
    scanf("%d", &caseNum);
    
    for(int i=0; i<caseNum; i++){
        scanf("%d", &num);
        memset(graph, 0, sizeof(graph));
        memset(inDegree, 0, sizeof(inDegree));
        memset(outDegree, 0, sizeof(outDegree));
        memset(storeNum, 0, sizeof(storeNum));
        circuitNum = 0;
        
        for(int j=0; j<num; j++)
            scanf("%s", input[j]);
        
        makeGraph();
        
        int check = checkEuler();
        
        if(check == 1) getEulerTrailerOrCircuit();
        else{
            printf("IMPOSSIBLE");
            continue;
        }
        
        if(circuitNum-1 != num)
            printf("IMPOSSIBLE");
        else{
            for(int j=circuitNum-1; j>0; j--){
                int start = circuit[j];
                int end = circuit[j-1];
                printf("%s ", store[start][end][--storeNum[start][end]]);
            }
        }
        printf("\n");
    }

	return 0;
}
