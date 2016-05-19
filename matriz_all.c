#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define MAX 500 // QUILES
#define DT 0.05 // QUILES

int main(){
    int i, j;
    for(i = 0; i< 500; i++){
        for(j = 0; j < 500; j++){
            if(i == j) continue;
            printf("%d %d\n", i, j);
        }
    }
}
