#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

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
        if(matrix[linha][i] == 1 && neu[i].x > 0){
            soma += W;
        }
    }
    return soma;
}

double delta_x(int matriz[MAX][MAX], Tno neuronios[MAX], int id){
        double deltaX;
    // QUILES - em equações envolvendo ponto flutuante, evitar o uso de inteiros, por exemplo, na equacao abaixo, substitui 3 por 3.0, etc.
    // QUILES - Faltou o passo de integração DT
        deltaX = (3.0 * neuronios[id].x - pow(neuronios[id].x, 3) + 2.0 - neuronios[id].y  + I_at + neuronios[id].S)*DT;
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
    Tno neuronios[500];
    Tno armaz[500];

    carrega_matriz(matriz);
    srand( (unsigned)time(NULL) );

    for (i=0 ; i<500 ; i++){
        neuronios[i].x = -2.0 + (double)(rand()%2001) / 500.0; // valor entre -2 e 2;
        neuronios[i].y   = (double)(rand()%2001) / 500.0; // valor entre 0 e 4;
    }

    for(t=0;t<10000;t++){
        for(i = 0; i < 500; i++){
            neuronios[i].S = S(matriz, neuronios, i);
            armaz[i].x = neuronios[i].x;
            armaz[i].y = neuronios[i].y;
            neuronios[i].x += (3.0 * neuronios[i].x - pow(neuronios[i].x, 3) + 2.0 - neuronios[i].y  + I_at + neuronios[i].S)*DT;
            neuronios[i].y += (epsilon*(alfa*(1.0+tanh(neuronios[i].x/beta))-neuronios[i].y))*DT;
        }
        if(t % 50 == 0){
            for(j = 0; j < 6; j++ ){
                printf("%.2f\t",neuronios[j].x);
            }
            printf("\n");
        }
    }


    return 0;
}

