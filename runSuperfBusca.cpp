/*
	Autor: Luis Otavio Rigo Junior
	Objetivo:
		Programa Principal da busca local em superficie.

*/
#include "superfGL.h"
#include "userEstrategia.cpp"
//#include "userEstrategia_FilaEAleatorio.cpp"
//#include "userEstrategia_SubEncostaEAleatorio.cpp"
//#include "userEstrategia_SubEncostaESubEncostaGulosa.cpp"
//#include "userEstrategia_SimulatedAnnealingEBuscaGulosa.cpp"
//#include "userEstrategia_TP03_02.cpp"

// ------------------------------------------------------------------------
//	MAIN - PROGRAMA PRINCIPAL
// ------------------------------------------------------------------------
// Controle do jogo de labirinto.
// E manipulacao do jogo para 2 jogadores.
int main(int argc, char **argv) {
	char *path = argv[1];

	srand(time(NULL));
	
	// Define o tempo da busca (em numero de passos).
	tempoBusca.count = 0;
	tempoBusca.maximo = 1000;

	cria_SuperficieGrafica(path);
	init_Players();

	glutInit(&argc, argv);

	//Setting up  The Display
	//-RGB color model + Alpha Channel = GLUT_RGBA
	//
	glutInitDisplayMode(GLUT_DEPTH|GLUT_RGBA|GLUT_DOUBLE);

	//Configure Window Postion
	glutInitWindowPosition(50, 25);

	//Configure Window Size
	glutInitWindowSize(width,height);

	//Create Window
	glutCreateWindow("Busca Local I.A. 2017-01");

	//Call to the drawing function
	glutDisplayFunc(display);
	glutMouseFunc(mousePressCallback);
	glutMotionFunc(mouseMotionCallback);
//	glutKeyboardFunc(wasd);
//	glutSpecialFunc(setas);
//	glutIdleFunc(display);

	// Gatilho de Execucao dos Players.
	glutTimerFunc(1, run_Players, 0);

	init_Config();

	// Loop require by OpenGL
	glutMainLoop();
	
	// Libera memoria alocada para o labirinto.
	tSup_ApagaSuperficie();

	return true;
}


