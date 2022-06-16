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

//O grafico mostra algo diferente, tem vez que o jogador 1 recebe 0 no final, nao entendo.


tipo_Valor melhorP1;

int rod_melhorValor1;

void init_Player1() {
	// Determina posicao inicial.
	reinicializa_PosicaoAleatoria();

	rod_melhorValor1 = 0; //os valores finais estao estranhos
	
	// Implementacao das rotinas de inicializacao.
	melhorP1 = superf_VerAmbiente();
}
tipo_Movimento run_Player1() {
	tipo_Movimento movimento;

	//Pesquisa em sua volta para saber a direcao com maior valor
	int maiorVizinho=0;
	int direcao=0;
	// cout<<"VIZ: ";
	for (int i=0;i<NUMCAMINHOS;i++){
		int temp = superf_VerVizinho(id_Caminhos[i]);
		// cout<<temp<<" ";
		if (temp>=maiorVizinho){
			maiorVizinho = temp;
			direcao  = i;
		}
		
	}
	if(maiorVizinho >= rod_melhorValor1){
		rod_melhorValor1 = maiorVizinho;
	}
	// Define a direcao do movimento.
	movimento.direcao = id_Caminhos[direcao];
	
	
	// Define o tamanho do passo.
	movimento.passo = 1;
	
	return movimento;
}
tipo_Valor result_Player1() {
	cout<< rod_melhorValor<<endl;
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
int caminhando = 1;
int passos_restantes;
int temperatura;
void init_Player2() {
	// Determina posicao inicial.
	temperatura  = 1;
	passos_restantes = 1;
	reinicializa_PosicaoAleatoria();
	
	// Implementacao das rotinas de inicializacao.
	melhorP2 = superf_VerAmbiente();
}
tipo_Movimento run_Player2() {
	tipo_Movimento movimento;
	
	if(temperatura > 0){
		if(passos_restantes > 0){
			int seletor_direcao = rand()%NUMCAMINHOS;
			movimento.direcao = id_Caminhos[seletor_direcao];	
			passos_restantes--;
			//1 - nao ia usar o movimento.passo pq eu quero guardar o quanto andei em cada direcao
			//pra saber dos lugares que visitei qual o maior. 
			//no pdf as funcoes permitidas nao tem nenhuma que retorne a pos (x,y) atual
			//2 - se usar um passo fixo, a exemplo 5, pode chegar na borda e eu andar menos que 5,
			//perdendo a referencia
		}else{
			//aqui é quando chego no novo checkpoint antes do prox salto aleatorio
			//aqui olho a vizinhança pra guardar o maior valor
			int maiorVizinho=0;
			int direcao=0;
			for (int i=0;i<NUMCAMINHOS;i++){
				int temp = superf_VerVizinho(id_Caminhos[i]);
				// cout<<temp<<" ";
				if (temp>=maiorVizinho){
					maiorVizinho = temp;
					direcao  = i;
				}
				
			}

		}
	}else{
		//subida de encosta
		int maiorVizinho=0;
		int direcao=0;
		// cout<<"VIZ: ";
		for (int i=0;i<NUMCAMINHOS;i++){
			int temp = superf_VerVizinho(id_Caminhos[i]);
			// cout<<temp<<" ";
			if (temp>=maiorVizinho){
				maiorVizinho = temp;
				direcao  = i;
			}
			
		}
		if(maiorVizinho >= rod_melhorValor1){
			rod_melhorValor1 = maiorVizinho;
		}
		// Define a direcao do movimento.
		movimento.direcao = id_Caminhos[direcao];
	}
	//-----------------------------------------------------------------------
	//PRA RODAR POR FAVOR COMENTA O RESTO ACIMA E DESCOMENTA A LINHA ABAIXO - CODIGO INCOMPLETO INFELIZMENTE
	//-----------------------------------------------------------------------
	// movimento.direcao = id_Caminhos[rand()%NUMCAMINHOS];


	// Define o tamanho do passo.
	movimento.passo = 1;
	
	return movimento;
}
tipo_Valor result_Player2() {
	return melhorP2;
}


