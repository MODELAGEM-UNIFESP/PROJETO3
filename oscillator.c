#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define MAX 500 // QUILES
#define DT 0.05 // QUILES
#define LINHAS_ENTRADA 500


//Parâmetros
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

//Carregamento da matriz pelo terminal.
void carrega_matrizF(int matriz[MAX][MAX]){
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

//Carregamento da matriz diretamente no codeblocks.
void carrega_matrizH(int matriz[MAX][MAX]){
    int i, j;
    int lin, col;

    FILE* file = fopen("graph_REG.txt", "r");

    for(i = 0; i < MAX; i++){
        for(j = 0; j< MAX; j++){
            matriz[i][j] = 0;
        }
    }

    while (!feof(file)) {
        fscanf(file, "%d %d", &lin, &col);
        matriz[lin][col] = 1;
        matriz[col][lin] = 1;
        i++;
    }

    fclose(file);
}

//Cálculo de S.
double S(int matrix[MAX][MAX], Tno neu[MAX], int linha){
    int i;
    double soma = 0;

    for(i = 0; i < 500; i++){
        if((matrix[linha][i] == 1) && (neu[i].x-theta >= 0.0)){
            soma += W;
        }
    }
    return soma;
}

//Desvio máximo dos valores de x em relação à média dos valores de x.
double DesvioMaximo (Tno neuronios[500]){
    int i;
    double media, desviomaximo;
    media = 0;
    desviomaximo = 0;

    for(i=0;i<500;i++){
        media+=neuronios[i].x/500;
    }

    for(i=0;i<500;i++){
        if(fabs(neuronios[i].x -media) > desviomaximo)
            desviomaximo=fabs(neuronios[i].x-media);
    }
    return desviomaximo;
}

//Ativação aleatória de uma quantidade fixa 'q' de neurônios.
void AtivacaoQuantidade(Tno neuronios[500], int q){
    int i, x;

    for(i=0;i<500;i++){
        neuronios[i].I = I_des;
    }


    srand( (unsigned)time(NULL) );
    for(i=1;i<=q;i++){
        x = rand()%500;
        if(neuronios[x].I == I_at){
            i--;
        }
        neuronios[x].I = I_at;
    }
}

int main(){
    int matriz[MAX][MAX];
    int i, j, t;
    Tno neuronios[MAX];
    double xAnt[MAX];

    AtivacaoQuantidade(neuronios, 500);

    carrega_matrizH(matriz);

    srand( (unsigned)time(NULL) );
    for (i=0 ; i<500 ; i++){
        neuronios[i].x = -2.0 + (double)(rand()%2001) / 500.0; // valor entre -2 e 2;
        neuronios[i].y = (double)(rand()%20001) / 500.0; // valor entre 0 e 4;
    }

    for(t=0;t<1000000;t++){

        //Calcula-se S para cada neurônio.
        for(i = 0; i < 500; i++){
            neuronios[i].S = S(matriz, neuronios, i);
        }

        if(t % 500 == 0){
            printf("%.2f, ",neuronios[0].x);
            printf("%.2f, ",neuronios[99].x);
            printf("%.2f, ",neuronios[199].x);
            printf("%.2f, ",neuronios[299].x);
            printf("%.2f, ",neuronios[399].x);
            printf("%.2f, ",neuronios[499].x);
            /*printf("Y: ");
            printf("%.2f, ",neuronios[0].y);
            printf("%.2f, ",neuronios[1].y);
            printf("%.2f, ",neuronios[2].y);
            printf("%.2f, ",neuronios[3].y);
            printf("%.2f, ",neuronios[4].y);
            printf("%.2f, ",neuronios[5].y);
            printf("\n");*/
            printf("%.2f\n", DesvioMaximo(neuronios));
        }

        for(i = 0; i < 500; i++){

            //xAnt armazena o valor antigo de x.
            xAnt[i]= neuronios[i].x;

            //O valor de x é atualizado.
            neuronios[i].x += (3.0 * neuronios[i].x - pow(neuronios[i].x, 3.0) + 2.0 - neuronios[i].y  + neuronios[i].I + neuronios[i].S)*DT;

            //O valor de y é atualizado, com base no valor antigo de x.
            neuronios[i].y += (epsilon*(alfa*(1.0+tanh(xAnt[i]/beta))-neuronios[i].y))*DT;
        }
    }

    return 0;
}

