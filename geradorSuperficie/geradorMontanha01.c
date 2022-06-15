#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAXLINE 1000
#define MAXCEL 1000

int mediaPosicao(int matriz[MAXCEL][MAXCEL], int linha, int coluna, int posL, int posC) {
	int i, j;
	int cont = 0;
	for (i = posL - 1;i <= posL + 1 && i < linha; i++) {
 		for (j = posC - 1;j <= posC + 1 && j < coluna; j++) {
			if ((i == posL && j == posC) || (i < 0 || j < 0)) {
				continue;
			}
			cont += matriz[i][j];
		}
	}
	return cont/8;
}

void mediaMat(int matriz[MAXCEL][MAXCEL], int linha, int coluna, int altura) {
	int i, j;
	int temp[MAXCEL][MAXCEL];
	int cont = 0;
	for(i = 0; i < linha; i++) {
		for(j = 0; j < coluna; j++) {
			temp[i][j] = mediaPosicao(matriz, linha, coluna, i, j);
		}
	}
	for(i = 0; i < linha; i++) {
		for(j = 0; j < coluna; j++) {
			if (temp[i][j] > altura) {
				matriz[i][j] = altura;
			}
			else if (temp[i][j] < 0) {
				matriz[i][j] = 0;
			}
			else {
				matriz[i][j] = temp[i][j];
			}
		}
	}
}

void salva(int matriz[MAXCEL][MAXCEL], int linha, int coluna, char nomeArquivo[MAXLINE]) {
	FILE* arquivo;
	int i, j;
	
	arquivo = fopen(nomeArquivo, "w");
	if(arquivo == NULL)
		return;
	
	fprintf(arquivo, "c %d %d\n", coluna, linha);
	for(i = 0; i < linha; i++){
		for(j = 0; j < coluna; j++){
			fprintf(arquivo, "%d ", matriz[i][j]);
		}
		fprintf(arquivo, "\n");
	}
	fclose(arquivo);
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
	
	int i, j;
	srand(time(NULL));
	for(i = 0; i < linha; i++){
		for(j = 0; j < coluna; j++){
			mat[i][j] = rand()%altura;
		}
	}
	mediaMat(mat, linha, coluna, altura);
	salva(mat, linha, coluna, path);
	
	return 0;
}
