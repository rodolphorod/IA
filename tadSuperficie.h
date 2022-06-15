/* TAD SUPERFICIE
	Objetivo: TAD contendo metodos de manipulacao de um superficie.
*/
#include "globais.h"

typedef struct str_Superficie {
	int num_CoordX, num_CoordY;
	tipo_Valor matriz[MAXCEL][MAXCEL];
	tipo_Valor maximo_Global;
	
} tipo_Superficie;
tipo_Superficie *sup = NULL;

bool tSup_CarregaArquivoMapa(char path[MAXLINE]);
bool tSup_AlocaSuperficie(int tamX, int tamY);
bool tSup_CriaSuperficie(tipo_Valor mapa[MAXCEL][MAXCEL], int tamX, int tamY);
bool tSup_ApagaSuperficie();
int tSup_VerTamX();
int tSup_VerTamY();
bool tSup_EscolhePosicaoAleatoria(tipo_Coordenada *pos);
tipo_Valor tSup_VerAmbiente(tipo_Coordenada pos);
tipo_Valor tSup_VerVizinho(tipo_Coordenada pos, const char *coord);
tipo_Valor tSup_VerificaMaximoGlobal();

#include "tadSuperficie.cpp"

