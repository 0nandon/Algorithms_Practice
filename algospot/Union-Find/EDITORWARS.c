#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 10000
#define MAXM 100000

int belongsTo[MAXN];
int height[MAXN];
int size[MAXN];
int enemy[MAXN];
int n, m;

typedef struct comment_t{
    int what;
    int n1, n2;
}COMMENT;

COMMENT comment[MAXM];

void initialization(int n){
    memset(height, 0, sizeof(height));
    memset(enemy, -1, sizeof(enemy));
    
    for(int i=0; i<n; i++){
        belongsTo[i] = i;
        size[i] = 1;
    }
}

int findRoot(int num){
    if(belongsTo[num] == num)
        return num;
    belongsTo[num] = findRoot(belongsTo[num]);
    return belongsTo[num];
}

int merge(int num1, int num2){
    int root1 = findRoot(num1);
    int root2 = findRoot(num2);
    
    if(root1 == root2)
        return -1;
    
    int big = height[root1] > height[root2] ? root1 : root2;
    int small = root1 + root2 - big;
    
    belongsTo[small] = big;
    size[big] += size[small];
    
    if(height[root1] == height[root2])
        height[big]++;
        
    return big;
}

void ACK(int n1, int n2){
    int root1 = findRoot(n1);
    int root2 = findRoot(n2);
    
    int newRoot = merge(root1, root2);
    int enemyRoot = -1;
    
    if(enemy[root1] != -1 && enemy[root2] != -1)
        enemyRoot = merge(enemy[root1], enemy[root2]);
    else if(enemy[root1] != -1 || enemy[root2] != -1)
        enemyRoot = (enemy[root1] != -1) ? enemy[root1] : enemy[root2];
    
    if(enemyRoot != -1){
        enemy[newRoot] = enemyRoot;
        enemy[enemyRoot] = newRoot;
    }
}

void DIS(int n1, int n2){
    int root1 = findRoot(n1);
    int root2 = findRoot(n2);
    
    if(enemy[root1] != -1)
        merge(root2, enemy[root1]);
    if(enemy[root2] != -1)
        merge(root1, enemy[root2]);
    
    enemy[root1] = root2;
    enemy[root2] = root1;
}

int editorWars(){
    int i;
    int ret = 1;
    for(i=0; i<m; i++){
        int n1 = comment[i].n1;
        int n2 = comment[i].n2;
        
        if(comment[i].what == 1){
            if(enemy[findRoot(n1)] == findRoot(n2)){
                ret = -1; break;
            }
            
            ACK(n1, n2);
        }else{
            if(findRoot(n1) == findRoot(n2)){
                ret = -1; break;
            }
            
            DIS(n1, n2);
        }
    }
    
    if(ret == -1)
        printf("CONTRADICTION AT %d\n", i+1);
    
    return ret;
}

int calMax(){
    int visited[n];
    memset(visited, -1, sizeof(visited));
    
    int ret = 0, root, max;
    for(int i=0; i<n; i++){
        root = findRoot(i);
        if(visited[root] == 1)
            continue;
        
        if(enemy[root] == -1)
            ret += size[root];
        else{
            max = size[root] > size[enemy[root]] ? size[root] : size[enemy[root]];
            ret += max;
            visited[enemy[root]] = 1;
        }
        visited[root] = 1;
    }
    
    return ret;
}

int main(){
    int caseNum;
    scanf("%d", &caseNum);
    
    for(int i=0; i<caseNum; i++){
        scanf("%d%d", &n, &m);
        
        initialization(n);
        
        char what[3];
        for(int j=0; j<m; j++){
            scanf("%s%d%d", what, &comment[j].n1, &comment[j].n2);
            
            if(strcmp(what, "ACK") == 0)
                comment[j].what = 1;
            else
                comment[j].what = -1;
        }
        
        int ret = editorWars();
        if(ret == 1)
            printf("MAX PARTY SIZE IS %d\n", calMax());
    }
     
    return 0;
}
