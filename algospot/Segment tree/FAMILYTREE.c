#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 987654321
#define MAXN 100000
#define MAXQ 10000

int N, Q;
int range[8 * MAXN + 8];
int preorder[2 * MAXN + 2];
int tree[MAXN+1];
int depthArr[MAXN+1];
int serialNum[MAXN+1];

int child[MAXN][20];
int numChild[MAXN];
int counter = 0;

int min(int num1, int num2){
    return depthArr[num1] > depthArr[num2] ? num2 : num1;
}

// RMQ 생성
int init(int left, int right, int node){
    if(left == right)
        return range[node] = preorder[left];

    int mid = (left + right) / 2;
    int leftM = init(left, mid, 2*node);
    int rightM = init(mid+1, right, 2*node+1);
    
    return range[node] = min(leftM, rightM);
}

int query(int left, int right, int node, int nodeLeft, int nodeRight){
    if(right < nodeLeft || nodeRight < left)
        return N;
    else if(left <= nodeLeft && nodeRight <= right)
        return range[node];
    
    int mid = (nodeLeft + nodeRight) / 2;
    return min(
        query(left, right, 2*node, nodeLeft, mid),
        query(left, right, 2*node+1, mid+1, nodeRight)
    );
}

void doPreorder(int root, int depth){
    serialNum[root] = counter;
    preorder[counter++] = root;
    depthArr[root] = depth;
    
    for(int i=0; i<numChild[root]; i++){
        doPreorder(child[root][i], depth+1);
        preorder[counter++] = root;
    }
}

void makeChild(){
    for(int i=1; i<N; i++){
        int root = tree[i];
        child[root][numChild[root]++] = i;
    }
}

int main(){
    int caseNum;
    scanf("%d", &caseNum);
    
    for(int i=0; i<caseNum; i++){
        scanf("%d%d", &N, &Q);
        
        for(int j=1; j<N; j++)
            scanf("%d", &tree[j]);
        
        memset(numChild, 0, sizeof(numChild));
        counter = 0;
        
        makeChild();
        doPreorder(0, 0); depthArr[N] = INF;
        init(0, counter-1, 1);
        
        for(int j=0; j<Q; j++){
            int num1, num2;
            scanf("%d%d", &num1, &num2);
            
            int index1 = serialNum[num1];
            int index2 = serialNum[num2];
            
            int temp;
            if(index1 > index2){
                temp = index1;
                index1 = index2;
                index2 = temp;
            }
            
            int LCA = query(index1, index2, 1, 0, counter-1);
            printf("%d\n", (depthArr[num1] + depthArr[num2]) - (2 * depthArr[LCA]));
        }
    }
    
    return 0;
}
