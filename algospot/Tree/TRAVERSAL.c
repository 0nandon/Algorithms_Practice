#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int preorder[100];
int inorder[100];
int nodeNum;

void traversal(int p1, int p2, int i1, int i2){
    if(p1 <= p2 && i1 <= i2){
        int cnt = 0;
        while(inorder[i1+cnt] != preorder[p1]) cnt++;
        
        traversal(p1+1, p1+cnt, i1, i1+cnt-1);
        traversal(p1+cnt+1, p2, i1+cnt+1, i2);
        printf("%d ", preorder[p1]);
    }
}

int main() {
    int caseNum;
    scanf("%d", &caseNum);
    
    for(int i=0; i<caseNum; i++){
        scanf("%d", &nodeNum);
        
        for(int j=0; j<nodeNum; j++)
            scanf("%d", &preorder[j]);
        for(int j=0; j<nodeNum; j++)
            scanf("%d", &inorder[j]);
        
        traversal(0, nodeNum-1, 0, nodeNum-1);
        printf("\n");
    }

    return 0;
}

