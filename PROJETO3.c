#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double W  = 0.1;
double alfa  = 6.0;
double beta  = 0.1;
double theta  = 0.5;
double epsilon  = 0.02;
double rho  = 0;
double I_at  = 0.2;
double I_des  = -0.2;
/*#define alfa 6.0
#define beta 0.1
#define theta 0.5
#define epsilon 0.02
#define rho 0
#define I_at 0.2
#define I_des -0.2*/

struct no {
	double x;
	double y;
};

typedef struct no no;

double S(int matrix[500][500], no no[500], int linha){
    int i;
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
        //printf("neuronio y: %.2f\n", neuronios[id].y);
        return deltaX;
}

double delta_y(int matriz[500][500], no neuronios[500], int id){
        double deltaY;
        deltaY = epsilon*(alfa*(1+tanh((neuronios[id].x)/beta))-neuronios[id].y);

        return deltaY;
}


int main(){
    int matriz[500][500];
    int i, j, t;
    double vet_S[500];
    no neuronios[500];

    neuronios[0].x=-1;
    neuronios[0].y=1;

    for(t=0;t<50;t++){
        /*for(i = 0; i < 500; i++){
            vet_S[i] = S(matriz, neuronios, i);
            neuronios[i].x = neuronios[i].x + delta_x(matriz,neuronios,i);
            neuronios[i].y = neuronios[i].y + delta_y(matriz,neuronios,i);
        }
        */
        neuronios[0].x += delta_x(matriz,neuronios,0);
        neuronios[0].y += delta_y(matriz,neuronios,0);
        printf("%.2f\n", neuronios[0].x);
    }


    return 0;
}
