#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define W 0.1
#define alfa 6.0
#define beta 0.1
#define theta 0.5
#define epsilon 0.02
#define rho 0
#define I_at 0.2
#define I_des -0.2

struct no {
	double x;
	double y;
};

typedef struct no no;

double S(int matrix[500][500], no no[500], int linha){
    int i, j;
    double soma = 0;

    for(i = 0; i < 500; i++){
        if(matrix[linha][i] == 1 && no[linha].x > 0){
            soma += W;
        }
    }
    return soma;
}

double delta_x(int matriz[500][500], no neuronios[500], int id){
        double deltaX;
        deltaX = 3 * neuronios[id].x - pow(neuronios[id].x, 3) + 2 - neuronios[id].y  + (double)I_at + S(matriz, neuronios, id);

        return deltaX;
}

void main(){
    int matriz[500][500];
    int i, j;
    double vet_S[500];
    no neuronios[500];

    for(i = 0; i < 500; i++){
        vet_S[i] = S(matriz, neuronios, i);
    }
}
