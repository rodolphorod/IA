/* TAD SUPERFICIE
	Objetivo: TAD contendo metodos de manipulacao de um superficie.
*/

bool tSup_CarregaArquivoMapa(char path[MAXLINE]) {
	tipo_Valor mapa[MAXCEL][MAXCEL];
	int tamX, tamY;
	
	FILE *fp;
	char buffer[MAXLINE];
	char *token;
	
	// Abre arquivo com instancia.
	if ((fp = fopen(path,"r")) == NULL) {
		printf("ERRO: ARQUIVO COM O MAPA NAO PODE SER ABERTO\n");
		exit(1);
	}
	
	// Leitura do cabecalho do arquivo.
	
	// Leitura das informacoes iniciais (num de linhas e colunas).
	if (!(fgets(buffer, MAXLINE, fp) == NULL)) {
		sscanf(buffer, "c %i %i", &tamX, &tamY);
	}
	if ((tamX < 1) || (tamX >= MAXCEL) || (tamY < 1) || (tamY >= MAXCEL)) {
		printf("ERRO: Limite no numero de celulas excedido!\n");
		return 0;
	}
	
	// Leitura do mapa.
	// Y eh a coordenada Vertical (linha).
	// X eh a coordenada Horizontal (coluna).
	for (int y=0; y<tamY; y++) {
		if ((fgets(buffer, MAXLINE, fp) == NULL)) {
			printf("ERRO: Linhas faltando!\n");
			exit(1);
		}
		token=strtok(buffer,DELIM);
		sscanf(token, "%i", &mapa[0][y]);
		if (mapa[0][y] < 0) {
			printf("ERRO: Valor de celula invalido [0][%i]!\n", y);
			exit(1);
		}
		for (int x=1; x<tamX; x++) {
			token=strtok(NULL, DELIM);
			sscanf(token, "%i", &mapa[x][y]);
			if (mapa[x][y] < 0) {
				printf("ERRO: Valor de celula invalido [%i][%i]!\n", x, y);
				exit(1);
			}
		}
	}
	// Fechamento do arquivo.
	fclose(fp);
	
	// Verifica informacoes existentes no mapa , caso o mapa seja valido.
	if (!tSup_CriaSuperficie(mapa, tamX, tamY)) {
		printf("ERRO: Superficie invalida!\n");
		return false;
	}
	
	return true;
}

bool tSup_AlocaSuperficie(int tamX, int tamY) {
	sup = (tipo_Superficie *)malloc(sizeof(tipo_Superficie));
	
	// X eh a coordenada Horizontal (coluna).
	// Y eh a coordenada Vertical (linha).
	sup->num_CoordX = tamX;
	sup->num_CoordY = tamY;
	
	return true;
}

bool tSup_CriaSuperficie(tipo_Valor mapa[MAXCEL][MAXCEL], int tamX, int tamY) {
	// Aloca estrutura da superficie.
	if (!tSup_AlocaSuperficie(tamX, tamY)) {
		printf("ERRO: nao foi possivel alocar memoria para a superficie.\n");
		return false;
	}
	
	// X eh a coordenada Horizontal (coluna).
	// Y eh a coordenada Vertical (linha).
	sup->maximo_Global = -1;
	for (int x=0; x<tamX; x++) {
		for (int y=0; y<tamY; y++) {
			sup->matriz[x][y] = mapa[x][y];
			if (sup->matriz[x][y] > sup->maximo_Global) {
				sup->maximo_Global = sup->matriz[x][y];
			}
		}
	}
	return true;
}

// Libera memoria reservada para o labirinto.
bool tSup_ApagaSuperficie() {
	free(sup);
	sup = NULL;
	
	return true;
}

// Visualiza o tamanho de X e Y.
int tSup_VerTamX() {
	return sup->num_CoordX;
}
int tSup_VerTamY() {
	return sup->num_CoordY;
}

// Escolhe posicao aleatoria.
bool tSup_EscolhePosicaoAleatoria(tipo_Coordenada *pos) {
	pos->x = rand() % tSup_VerTamX();
	pos->y = rand() % tSup_VerTamY();
	
	return true;
}


// Visualiza alguma informacao especifica do ambiente em que o jogador estah.
tipo_Valor tSup_VerAmbiente(tipo_Coordenada pos) {
	return sup->matriz[pos.x][pos.y];
}

// Ver um vizinho especifico no ambiente em que o jogador estah.
tipo_Valor tSup_VerVizinho(tipo_Coordenada pos, const char *coord) {
	tipo_Valor vizinho = SEMVIZINHO;
	
	if (!strcmp("norte", coord)) {
		if (pos.y > 0) {
			vizinho = sup->matriz[pos.x][pos.y-1];
		}
	}
	else if (!strcmp("sul", coord)) {
		if (pos.y < (sup->num_CoordY-1)) {
			vizinho = sup->matriz[pos.x][pos.y+1];
		}
	}
	else if (!strcmp("oeste", coord)) {
		if (pos.x > 0) {
			vizinho = sup->matriz[pos.x-1][pos.y];
		}
	}
	else if (!strcmp("leste", coord)) {
		if (pos.x < (sup->num_CoordX-1)) {
			vizinho = sup->matriz[pos.x+1][pos.y];
		}
	}
	else if (!strcmp("noroeste", coord)) {
		if ((pos.x > 0) && (pos.y > 0)) {
			vizinho = sup->matriz[pos.x-1][pos.y-1];
		}
	}
	else if (!strcmp("nordeste", coord)) {
		if ((pos.x < (sup->num_CoordX-1)) && (pos.y > 0)) {
			vizinho = sup->matriz[pos.x+1][pos.y-1];
		}
	}
	else if (!strcmp("sudoeste", coord)) {
		if ((pos.x > 0) && (pos.y < (sup->num_CoordY-1))) {
			vizinho = sup->matriz[pos.x-1][pos.y+1];
		}
	}
	else if (!strcmp("sudeste", coord)) {
		if ((pos.x < (sup->num_CoordX-1)) && (pos.y < (sup->num_CoordY-1))) {
			vizinho = sup->matriz[pos.x+1][pos.y+1];
		}
	}
	
	return vizinho;
}

tipo_Valor tSup_VerificaMaximoGlobal() {
	return sup->maximo_Global;
}



