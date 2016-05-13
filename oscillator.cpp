#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAX 500 // QUILES
#define DT 0.01 // QUILES

double W  = 0.1;
double alfa  = 6.0;
double beta  = 0.1;
double theta  = 0.5;
double epsilon  = 0.02;
double rho  = 0;
double I_at  = 0.2;
double I_des  = -0.02;
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
    double S; // Quiles
    double I; // Quiles
};

typedef struct no Tno;

void carrega_matriz(int matriz[MAX][MAX]){
    int i, j, k;
    int lin, col;

    for(i = 0; i < MAX; i++){
        for(j = 0; j< MAX; j++){
            matriz[i][j] = 0;
        }
    }

    for(i = 0; i < MAX; i++){
        scanf("%d %d", &lin, &col);
        matriz[lin][col] = 1;
        matriz[col][lin] = 1;
    }

//    for(k = 0; k < 100; k++)
//        for(i = 0; i < MAX; i++){
//            for(j = 0; j< MAX; j++){
//                printf("%d\n", matriz[i][j]);
//            }
//            printf("\n");
//        }
}


double S(int matrix[MAX][MAX], Tno neu[MAX], int linha){
    int i;
    double soma = 0;

    for(i = 0; i < MAX; i++){
        if(matrix[linha][i] == 1 && neu[linha].x > 0){
            soma += W;
        }
    }
    return soma;
}

double delta_x(int matriz[MAX][MAX], Tno neuronios[MAX], int id){
        double deltaX;
    // QUILES - em equações envolvendo ponto flutuante, evitar o uso de inteiros, por exemplo, na equacao abaixo, substitui 3 por 3.0, etc.
    // QUILES - Faltou o passo de integração DT
        deltaX = (3.0 * neuronios[id].x - pow(neuronios[id].x, 3) + 2.0 - neuronios[id].y  + I_at)*DT /*+ S(matriz, neuronios, id)*/;
        //printf("neuronio y: %.2f\n", neuronios[id].y);
        return deltaX;
}

double delta_y(int matriz[500][500], Tno neuronios[500], int id){
        double deltaY;
        deltaY = (epsilon*(alfa*(1.0+tanh(neuronios[id].x/beta))-neuronios[id].y))*DT;

        return deltaY;
}


int main(){
    int matriz[500][500];
    int i, j, t;
    double vet_S[500];
    Tno neuronios[500];
    Tno armaz[500];

    //Valores Iniciais do Neurônio
// QUILES    neuronios[0].x=10;
// QUILES    neuronios[0].y=1000;
    //neuronios[1].x=1;
    //neuronios[1].y=0;

    carrega_matriz(matriz);
    // Quiles
    for (i=0 ; i<500 ; i++){
        neuronios[i].x = -2.0 + (double)(rand()%2001) / 500.0; // valor entre -2 e 2;
        neuronios[i].x = (double)(rand()%2001) / 500.0; // valor entre 0 e 4;
    }

//    matriz[0][0]=0;
//    matriz[0][1]=1;
//    matriz[1][0]=1;
//    matriz[1][1]=0;

    for(t=0;t<1000000;t++){
        for(i = 0; i < 500; i++){
            vet_S[i] = S(matriz, neuronios, i);
            armaz[i].x = neuronios[i].x;
            armaz[i].y = neuronios[i].y;
            neuronios[i].x += delta_x(matriz,armaz,i);
            neuronios[i].y += delta_y(matriz,armaz,i);
        }
//        vet_S[1] = S(matriz, neuronios, 1);
//
//        armaz[1].x = neuronios[1].x;
//        armaz[1].y = neuronios[1].y;
//
//
//        neuronios[1].x += delta_x(matriz,armaz,1);
//        neuronios[1].y += delta_y(matriz,armaz,1);
        printf("x_0 = %.2f\n", neuronios[0].x);
//        printf("y_0 = %.2f\n", neuronios[0].y);
        printf("x_1 = %.2f\n", neuronios[1].x);
        //printf("y_1 = %.2f\n", neuronios[1].y);
    }


    return 0;
}

