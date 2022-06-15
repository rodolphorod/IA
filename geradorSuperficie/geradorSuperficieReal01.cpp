#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define MAXLINE 1000
#define MAXCEL 1000
#define VALORINICIAL -1
#define DECREMENTO 1
#define TAXA 2

bool medicao_TaxaDePlanicie(int mat[MAXCEL][MAXCEL], int tam_X, int tam_Y, float t) {
	int x, y;
	int count;
	float aux;
	
	count = 0;
	for (x=0; x<tam_X; x++) {
		for (y=0; y<tam_Y; y++) {
			// Permite apenas alturas positivas.
			if (mat[x][y] <= 0) {
				count++;
			}
		}
	}
	aux = (float) count / (tam_X * tam_Y);
printf("Taxa: %.3f\n", aux);
	if (aux > t) {
		return true;
	}
	return false;
}

void atribui_ValorDeMontanha(int mat[MAXCEL][MAXCEL], int pX, int pY, int tam_X, int tam_Y, int altura) {
	int x,y;
	int novaAltura;
	float dist;
	
	for (x=0; x<tam_X; x++) {
		for (y=0; y<tam_Y; y++) {
			// Calcula distancia euclidiana para atribuicao da altura do ponto.
			dist = sqrt((pow((x-pX),2)+pow((y-pY),2)));
			novaAltura = altura - (DECREMENTO*dist);
			// Permite apenas alturas positivas.
			if (novaAltura < 0) {
				novaAltura = 0;
			}
			// Verifica se eh um ponto de intersecao entre montanhas
			if (novaAltura > mat[x][y]) {
				// Atribui nova altura.
				mat[x][y] = novaAltura;
			}
		}
	}
}

void criaMatriz(int mat[MAXCEL][MAXCEL], int tam_X, int tam_Y, int altura) {
	int x, y, pX, pY;
	int alturaMaximaLocal, loop, potencia;
	
	// Resseta matriz.
	for (x=0; x<tam_X; x++) {
		for (y=0; y<tam_Y; y++) {
			mat[x][y] = VALORINICIAL;
		}
	}
	
	loop = 2;
	potencia = 1;
	alturaMaximaLocal = altura;
//while (potencia < 7) {
	while (medicao_TaxaDePlanicie(mat, tam_X, tam_Y, 0.1)) {
		// Escolhe ponto maximo inicial.
		pX = rand()%tam_X;
		pY = rand()%tam_Y;
		printf("Sorteio[%i][%i] - %i\n", pX, pY, alturaMaximaLocal);
		
		// Chama Procedimento para geracao da montanha.
		atribui_ValorDeMontanha(mat, pX, pY, tam_X, tam_Y, alturaMaximaLocal);
		
		if (loop >= pow(2, potencia)) {
			potencia++;
			alturaMaximaLocal = alturaMaximaLocal - DECREMENTO;
		}
		loop++;
	}
}


int salvaMatriz(char *str, int mat[MAXCEL][MAXCEL], int tam_X, int tam_Y) {
	int x, y;
	FILE * arq = fopen(str, "w");
	
	if (arq!=NULL) {
		fprintf(arq, "c %d %d\n", tam_X, tam_Y);
		for (y=0; y<tam_Y; y++) {
			for(x=0; x<tam_X; x++) {
				fprintf(arq,"%d ",mat[x][y]);
			}
			fprintf(arq,"\n");
		}
		printf("%s armazenado com sucesso\n",str);
		return 1;
	}
	else {
		printf("ERRO: %s armazenado sem sucesso\n",str);
		return 0;
	}
}

int main(int argc, char **argv) {
	char path[MAXLINE];
	int mat[MAXCEL][MAXCEL];
	int tam_X, tam_Y, altura;
	
	if (argc != 5) {
		printf("ERRO: Numero invalido de parametros:\n");
		printf("\t01 - Arquivo de saida;\n");
		printf("\t02 - Tamanho do eixo X;\n");
		printf("\t03 - Tamanho do eixo Y;\n");
		printf("\t04 - Altitude maxima (valores de altitude serao sempre positivos).\n");
		exit(0);
	}
	strcpy(path, argv[1]);
	tam_X = atoi(argv[2]);
	tam_Y = atoi(argv[3]);
	altura = atoi(argv[4]);
	if ((tam_X < 1) || (tam_X >= MAXCEL) || (tam_Y < 1) || (tam_Y>= MAXCEL) || (altura < 1)) {
		printf("\tERRO: Valor do parametro invalido.\n");
		exit(0);
	}
	
	srand(time(NULL));
	
	criaMatriz(mat, tam_X, tam_Y, altura);
	salvaMatriz(path, mat, tam_X, tam_Y);
	
	return 0;
}
