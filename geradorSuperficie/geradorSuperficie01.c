#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAXLINE 1000
#define MAXCEL 1000

int calcValor(int x, int altura){
	int i = rand()%2;
	int p;
	if (i) {
		p = x + 5;
	}
	else {
		p =  x - 5;
	}
	if (p > altura) {
		p = altura;
	}
	else if	(p < 0)	{
		p = 0;
	}
	return p;
}

void criaMatriz(int mat[MAXCEL][MAXCEL], int linha, int coluna, int altura) {
	int i,j;
	
	mat[0][0] = rand()%100;
	for (j=1; j<coluna; j++) {
		mat[0][j] = calcValor(mat[0][j-1], altura);
	}
	for(i=1; i<linha; i++) {
		for (j=0; j<coluna; j++) {
			mat[i][j] = calcValor(mat[i-1][j], altura);
		}
	}
}


int salvaMatriz(char *str, int mat[MAXCEL][MAXCEL], int linha, int coluna) {
	int i,j;
	FILE * arq = fopen(str, "w");
	
	if (arq!=NULL) {
		fprintf(arq, "c %d %d\n", coluna, linha);
		for (i=0; i<linha; i++) {
			for(j=0; j<coluna; j++) {
				fprintf(arq,"%d ",mat[i][j]);
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
	int linha, coluna, altura;
	
	if (argc != 5) {
		printf("ERRO: Numero invalido de parametros:\n");
		printf("\t01 - Arquivo de saida;\n");
		printf("\t02 - Tamanho do eixo X;\n");
		printf("\t03 - Tamanho do eixo Y;\n");
		printf("\t04 - Altitude maxima (valores de altitude serao sempre positivos).\n");
		exit(0);
	}
	strcpy(path, argv[1]);
	coluna = atoi(argv[2]);
	linha = atoi(argv[3]);
	altura = atoi(argv[4]);
	if ((linha < 1) || (linha >= MAXCEL) || (coluna < 1) || (coluna >= MAXCEL) || (altura < 1)) {
		printf("\tERRO: Valor do parametro invalido.\n");
		exit(0);
	}
	
	srand(time(NULL));
	
	criaMatriz(mat, linha, coluna, altura);
	salvaMatriz(path, mat, linha, coluna);
	
	return 0;
}
