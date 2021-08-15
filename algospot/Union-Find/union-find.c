#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NODENUM 9

int belongsTo[NODENUM];
int height[NODENUM];
int size[NODENUM];

void initialization(){
    memset(height, 0, sizeof(height));
    
    for(int i=0; i<NODENUM; i++){
        belongsTo[i] = i;
        size[i] = 1;
    }
}

int findRoot(int num){
    if(belongsTo[num] == num)
        return num;
    belongsTo[num] = findRoot(belongsTo[num]);
    return belognsTo[num];
}

int merge(int num1, int num2){
    int root1 = findRoot(num1);
    int root2 = findRoot(num2);
    
    if(root1 == root2)
        return -1;
    
    int big = height[root1] > height[root2] ? root1 : root2;
    int small = root1 + root2 - big;
    
    belongsTo[small] = big;
    size[big] += size[samll];
    
    if(height[root1] == height[root2])
        height[big]++;
        
    return 1;
}

int main(){
    initialization();
    
    return 0;
}
