// /*
// 	Autor: Luis Otavio Rigo Junior
// 	Objetivo:
// 		Implementacao das estrategias definidas pelo programador.
// */
// *** 	FUNCOES DE INICIALIZACAO E EXECUCAO DO JOGADOR 1 ***
// Funcao de inicializacao e execucao da estrategia 1.


//*******************************************************
//*                                                     *
//*         Jogador 1: Subida de Encosta Gulosa         *
//*                                                     *
//*******************************************************




tipo_Valor melhorP1;

int maiorVizinho(){
	int maiorVizinho=0;
	int direcao;
	cout<<"VIZ: ";
	for (int i=0;i<NUMCAMINHOS;i++){
		int temp = superf_VerVizinho(id_Caminhos[i]);
		cout<<temp<<" ";
		if (temp>=maiorVizinho){
			maiorVizinho = temp;
			direcao  = i;
		}
		cout<<endl;
	}
	return direcao;
}

void init_Player1() {
	// Determina posicao inicial.
	reinicializa_PosicaoAleatoria();
	
	// Implementacao das rotinas de inicializacao.
	melhorP1 = superf_VerAmbiente();
}
tipo_Movimento run_Player1() {
	tipo_Movimento movimento;

	//Pesquisa em sua volta para saber a direcao com maior valor
	int direcao = 0;//;maiorVizinho();
	
	// Define a direcao do movimento.
	movimento.direcao = id_Caminhos[direcao];
	
	
	// Define o tamanho do passo.
	movimento.passo = 2;
	
	return movimento;
}
tipo_Valor result_Player1() {
	return melhorP1;
}


//*******************************************************
//*                                                     *
//*           Jogador 2: Simulated annealing            *
//*                                                     *
//*******************************************************


// *** 	FUNCOES DE INICIALIZACAO E EXECUCAO DO JOGADOR 2 ***
//	Implementacao da segunda estrategia de jogo.
tipo_Valor melhorP2;
void init_Player2() {
	// Determina posicao inicial.


	reinicializa_PosicaoAleatoria();
	
	// Implementacao das rotinas de inicializacao.
	melhorP2 = superf_VerAmbiente();
}
tipo_Movimento run_Player2() {
	tipo_Movimento movimento;
	

	int direcao = maiorVizinho();
	// Define a direcao do movimento.
	movimento.direcao = id_Caminhos[0];
	
	// Define o tamanho do passo.
	movimento.passo = 5;
	
	return movimento;
}
tipo_Valor result_Player2() {
	return melhorP2;
}


