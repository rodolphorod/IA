#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXLINE 3000
#define DELIM	" "
#define MAXCEL 500

#define PAREDE false
#define CAMINHO true
#define SEMVIZINHO -1

#define NUMCAMINHOS 8
const char *id_Caminhos[NUMCAMINHOS] = {"norte", "sul", "oeste", "leste","noroeste","nordeste","sudoeste","sudeste"};

typedef int tipo_Valor;

typedef struct str_Coordenada {
	int x,y;
} tipo_Coordenada;

typedef struct str_Tempo {
	long int count;
	long int maximo;
} tipo_Tempo;
tipo_Tempo tempoBusca;

