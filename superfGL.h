#include <GL/glut.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <time.h>
#include "tadSuperficie.h"
#include "virtualTrackball/VirtualTrackball.h"

#define width 800
#define height 600
#define xInicialA -0.99
#define yInicialA 0.99
#define xInicialB -0.98625
#define yInicialB 0.98375
#define passoX 0.00375
#define passoY 0.00625
#define passoZ 0.00500

// Valores para uso na configuracao da perspectiva 3D.
#define _FOV 60
#define _NEARPLANE 0.001
#define _FARPLANE  300

using namespace std;

typedef struct structSala {
	float x1,y1,z1,x2,y2,z2, cX, cY, cZ;
	float red,green,blue;
}CoordSala;

typedef struct str_Movimento {
	const char *direcao;
	int passo;
} tipo_Movimento;

tipo_Coordenada posAtual, posAtualP2;
tipo_Coordenada posMelhor, posMelhorP2;

vector<vector<CoordSala> > supGraf;
bool flag_Player1;

GLdouble mAspectRatio = ((GLdouble) width)/height;
VirtualTrackball *mVirtualTrackball;
float mProjectionMatrix[16];
int   oldX, oldY;
int   middleButtonPressed;
//float mModelViewMatrix[16];
//float mModelViewProjectionMatrix[16];

// ------------------------------------------------------------------------
//	Estrategias que devem ser implementadas pelo usuario.
// ------------------------------------------------------------------------
void init_Player1();
tipo_Movimento run_Player1();
tipo_Valor result_Player1();
void init_Player2();
tipo_Movimento run_Player2();
tipo_Valor result_Player2();

// ------------------------------------------------------------------------
//	Funcoes que podem ser utilizadas pelo usuario.
// ------------------------------------------------------------------------
// Atribui posicao aleatoria aos jogadores.
bool reinicializa_PosicaoAleatoria();
// Funcao que retorna o valor da funcao objetivo armazenado no ambiente atual.
tipo_Valor superf_VerAmbiente();
// Funcao que retorna o valor da funcao objetivo armazenada no vizinho, olhando para uma coordenada.
tipo_Valor superf_VerVizinho(const char *coord);

// ------------------------------------------------------------------------
//	Funcoes internas.
// ------------------------------------------------------------------------
void init_Players();
void init_Config();
VectorFloat* found_Center();
void run_Players(int lixo);
void result_Players();
bool move_Player(tipo_Movimento mov);
void setPerspectiveProjection();
void setModelViewProjection();
void grid();
void desenha_player1(tipo_Coordenada pos);
void desenha_player2(tipo_Coordenada pos);
void display(void);
void mousePressCallback(int button, int state, int x, int y);
void mouseMotionCallback(int x, int y);
void cria_SuperficieGrafica(char* path);
tipo_Valor superf_VerificaMaximoGlobal();

#include "superfGL.cpp"


