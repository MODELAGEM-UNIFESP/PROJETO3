#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define MAX 500 // QUILES
#define DT 0.05 // QUILES

/*
all_connected -> 249500
graph_REG-> 500
*/
#define LINHAS_ENTRADA 249500



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
    int i, j;
    int lin, col;

    for(i = 0; i < MAX; i++){
        for(j = 0; j< MAX; j++){
            matriz[i][j] = 0;
        }
    }

    for(i = 0; i < LINHAS_ENTRADA; i++){
        scanf("%d %d", &lin, &col);
        matriz[lin][col] = 1;
        matriz[col][lin] = 1;
    }
}


double S(int matrix[MAX][MAX], Tno neu[MAX], int linha){
    int i;
    double soma = 0;

    for(i = 0; i < 500; i++){
        if((matrix[linha][i] == 1) && (neu[i].x >= 0.0)){
            soma += W;
        }
    }
    return soma;
}


double MediaDesvios (Tno neuronios[500]){
    int i;
    double media, mediadesvios;
    media = 0;
    mediadesvios = 0;

    for(i=0;i<500;i++){
        media+=neuronios[i].x/500;
    }

    for(i=0;i<500;i++){
        mediadesvios+=fabs(neuronios[i].x-media)/500;
    }
    return mediadesvios;

}

void AtivacaoQuantidade(Tno neuronios[500], int q){
    int i, x;

    for(i=0;i<500;i++){
        neuronios[x].I = -0.02;
    }


    srand( (unsigned)time(NULL) );
    for(i=1;i<=q;i++){
        x = rand()%500;
        if(neuronios[x].I == 0.2){
            i--;
        }
        neuronios[x].I = 0.2;
    }
}

int main(){
    int matriz[MAX][MAX];
    int i, j, t;
    Tno neuronios[MAX];
    Tno armaz[MAX];


    AtivacaoQuantidade(neuronios, 10);

    carrega_matriz(matriz);
    srand( (unsigned)time(NULL) );

    for (i=0 ; i<500 ; i++){
        neuronios[i].x = -2.0 + (double)(rand()%2001) / 500.0; // valor entre -2 e 2;
        neuronios[i].y   = (double)(rand()%20001) / 500.0; // valor entre 0 e 4;
    }


    for(t=0;t<1000000;t++){
        for(i = 0; i < 500; i++){
            neuronios[i].S = S(matriz, neuronios, i);
        }

        for(i = 0; i < 500; i++){
            neuronios[i].x += (3.0 * neuronios[i].x - pow(neuronios[i].x, 3) + 2.0 - neuronios[i].y  + neuronios[i].I + neuronios[i].S)*DT;
            neuronios[i].y += (epsilon*(alfa*(1.0+tanh(neuronios[i].x/beta))-neuronios[i].y))*DT;
        }
        if(t % 500 == 0){
            printf("%.2f, ",neuronios[0].x);
            printf("%.2f, ",neuronios[99].x);
            printf("%.2f, ",neuronios[199].x);
            printf("%.2f, ",neuronios[299].x);
            printf("%.2f, ",neuronios[399].x);
            printf("%.2f, ",neuronios[499].x);
            printf("%.4f", MediaDesvios(neuronios));
            printf("\n");
        }
    }


    return 0;
}

