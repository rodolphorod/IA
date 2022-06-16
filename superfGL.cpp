// ------------------------------------------------------------------------
//	Funcoes que podem ser utilizadas pelo usuario.
// ------------------------------------------------------------------------
// Atribui nova posicao aleatoria aos jogadores.
bool reinicializa_PosicaoAleatoria() {
	if (flag_Player1)
		return tSup_EscolhePosicaoAleatoria(&posAtual);
	else
		return tSup_EscolhePosicaoAleatoria(&posAtualP2);
}

// Funcao que retorna o valor da funcao objetivo armazenado no ambiente atual.
tipo_Valor superf_VerAmbiente() {
	if (flag_Player1) {
		return tSup_VerAmbiente(posAtual);
	}
	else {
		return tSup_VerAmbiente(posAtualP2);
	}
}
// Funcao que retorna o valor da funcao objetivo armazenada no vizinho, olhando para uma coordenada.
tipo_Valor superf_VerVizinho(const char *coord) {
	if (flag_Player1) {
		return tSup_VerVizinho(posAtual, coord);
	}
	else {
		return tSup_VerVizinho(posAtualP2, coord);
	}
}

// ------------------------------------------------------------------------
//	Funcoes internas.
// ------------------------------------------------------------------------
// Inicializa estrategias e posiciona players, de acordo com a estrategia de inicializacao.
void init_Players() {
	// Inicia as posicoes dos jogadores aleatoriamente.
	tSup_EscolhePosicaoAleatoria(&posAtual);
	tSup_EscolhePosicaoAleatoria(&posAtualP2);



	init_Player1();
	printf("Posicao incial do player 1: [%i][%i]\n", posAtual.x, posAtual.y);
	//posAtual.x = 312;
	//posAtual.y = 100;
	posMelhor.x = posAtual.x;
	posMelhor.y = posAtual.y;

	init_Player2();
	//posAtualP2.x = 342;
	//posAtualP2.y = 30;
	printf("Posicao incial do player 2: [%i][%i]\n", posAtualP2.x, posAtualP2.y);
	posMelhorP2.x = posAtualP2.x;
	posMelhorP2.y = posAtualP2.y;

	flag_Player1 = true;
}

// Inicializa algumas configuracoes para o correto funcionamento
// do programa.
void init_Config() {
  glClearColor(0.7f, 0.7f, 0.7f, 0.0f);

  //glDisable(GL_DITHER);
  glEnable(GL_DEPTH_TEST);
  //glDepthFunc( GL_LEQUAL );
  glDepthFunc( GL_LEQUAL );

  VectorFloat *_mediumPoint = found_Center();
  mVirtualTrackball = new VirtualTrackball();
  mVirtualTrackball->updateWindowSize(width, height);
  mVirtualTrackball->setCenter(new VectorFloat(_mediumPoint->getX(),
                                               _mediumPoint->getY(),
                                               _mediumPoint->getZ()),
                               -1.8f);//(-0.1f,0.1f,0.25f),-1.8f);

  setPerspectiveProjection();
  setModelViewProjection();

  delete _mediumPoint;
}

// Acha o centro do grafico para configurar a Virtual Trackball corretamente.
VectorFloat* found_Center() {
  VectorFloat* _maxPoint = new VectorFloat(3);
  VectorFloat* _minPoint = new VectorFloat(3);
  VectorFloat* _mediumPoint = new VectorFloat(3);
  _maxPoint->setX(supGraf[0][0].cX);
  _maxPoint->setY(supGraf[0][0].cY);
  _maxPoint->setZ(supGraf[0][0].cZ);
  _minPoint->setX(_maxPoint->getX());
  _minPoint->setY(_maxPoint->getY());
  _minPoint->setZ(_maxPoint->getZ());

  for(int i=0;i<tSup_VerTamX();i++)
    {
      for(int j=0;j<tSup_VerTamY();j++)
        {
          float x = supGraf[i][j].cX;
          float y = supGraf[i][j].cY;
          float z = supGraf[i][j].cZ;

          if( x > _maxPoint->getX() ) _maxPoint->setX(x);
          if( y > _maxPoint->getY() ) _maxPoint->setY(y);
          if( z > _maxPoint->getZ() ) _maxPoint->setZ(z);
          if( x < _minPoint->getX() ) _minPoint->setX(x);
          if( y < _minPoint->getY() ) _minPoint->setY(y);
          if( z < _minPoint->getZ() ) _minPoint->setZ(z);
        }
    }

  _mediumPoint->setX( (_maxPoint->getX() + _minPoint->getX())*0.5f );
  _mediumPoint->setY( (_maxPoint->getY() + _minPoint->getY())*0.5f );
  _mediumPoint->setZ( (_maxPoint->getZ() + _minPoint->getZ())*0.5f );

  return _mediumPoint;
}

void run_Players(int lixo) {
	const char *movimento;
	tipo_Movimento mov;
	
	// A busca acontece ateh que o tempo definido seja atingido.
	if (tempoBusca.count < tempoBusca.maximo) {
		if (flag_Player1)
			mov = run_Player1();
		else
			mov = run_Player2();

		move_Player(mov);
		if (flag_Player1) {
			if (tSup_VerAmbiente(posAtual) > tSup_VerAmbiente(posMelhor)) {
				posMelhor.x = posAtual.x;
				posMelhor.y = posAtual.y;
			}
		}
		else {
			if (tSup_VerAmbiente(posAtualP2) > tSup_VerAmbiente(posMelhorP2)) {
				posMelhorP2.x = posAtualP2.x;
				posMelhorP2.y = posAtualP2.y;
			}
		}

		flag_Player1 = !flag_Player1;
		
		// Atualiza o contador de tempo.
		tempoBusca.count++;

		glutPostRedisplay();
		glutTimerFunc(1, run_Players, 0);
	}
	else {
		// Realiza verificacao final dos resultados encontrados.
		result_Players();
		
		// Imprime valor maximo global.
		printf("Valor Maximo Global: %i\n", superf_VerificaMaximoGlobal());
	}
}

void result_Players() {
	tipo_Valor auxResult;
	
	printf("-----------------------------------------------------\n");
	auxResult = result_Player1();
	printf("Melhor resultado encontrado pelo player 1: %i\n", auxResult);

	auxResult = result_Player2();
	printf("Melhor resultado encontrado pelo player 2: %i\n", auxResult);
}

bool move_Player(tipo_Movimento mov) {
	bool flag_Movimento = false;
	tipo_Coordenada posAux;

	for (int p=0; p<mov.passo; p++) {
		if (flag_Player1) {
			posAux.x = posAtual.x;
			posAux.y = posAtual.y;
		}
		else {
			posAux.x = posAtualP2.x;
			posAux.y = posAtualP2.y;
		}

		if (superf_VerVizinho(mov.direcao) != SEMVIZINHO) {
			if (!strcmp(mov.direcao, "norte")) {
				posAux.y = posAux.y-1;
			}
			else if (!strcmp(mov.direcao, "sul")) {
				posAux.y = posAux.y+1;
			}
			else if (!strcmp(mov.direcao, "oeste")) {
				posAux.x = posAux.x-1;
			}
			else if (!strcmp(mov.direcao, "leste")) {
				posAux.x = posAux.x+1;
			}
			else if (!strcmp(mov.direcao, "noroeste")) {
				posAux.x = posAux.x-1;
				posAux.y = posAux.y-1;
			}
			else if (!strcmp(mov.direcao, "nordeste")) {
				posAux.x = posAux.x+1;
				posAux.y = posAux.y-1;
			}
			else if (!strcmp(mov.direcao, "sudoeste")) {
				posAux.x = posAux.x-1;
				posAux.y = posAux.y+1;
			}
			else if (!strcmp(mov.direcao, "sudeste")) {
				posAux.x = posAux.x+1;
				posAux.y = posAux.y+1;
			}
			flag_Movimento = true;
		}
		if (flag_Movimento) {
			// Atualiza posicoes e manipula visualmente o jogador.
			if(flag_Player1) {
				posAtual.x = posAux.x;
				posAtual.y = posAux.y;
				supGraf[posAtual.x][posAtual.y].red = 0.0;
				supGraf[posAtual.x][posAtual.y].green = 0.0;
				supGraf[posAtual.x][posAtual.y].blue = 0.0;
				cout << "Jogador 01 - Foi para o " << mov.direcao << endl;
			}
			else {
				posAtualP2.x = posAux.x;
				posAtualP2.y = posAux.y;
				supGraf[posAtualP2.x][posAtualP2.y].red = 0.8;
				supGraf[posAtualP2.x][posAtualP2.y].green = 0.2;
				supGraf[posAtualP2.x][posAtualP2.y].blue = 0.2;
				cout << "Jogador 02 - Foi para o " << mov.direcao << endl;
			}
		}
		else {
			cout << "Movimento para o " << mov.direcao << " mal sucedido!!!" << endl;
		}
	}

	return flag_Movimento;
}

void setPerspectiveProjection() {
  glMatrixMode( GL_PROJECTION );

  Matrix::perspective(mProjectionMatrix,_FOV, mAspectRatio, _NEARPLANE, _FARPLANE);

  glLoadMatrixf(mProjectionMatrix);
}

void setModelViewProjection() {
  glMatrixMode( GL_MODELVIEW );
  //glLoadIdentity();

  float* _modelViewMatrix = mVirtualTrackball->getMatrix();
  //for (int i = 0; i < 16; i++)
    //mModelViewMatrix[i] = _modelViewMatrix[i];

  glLoadMatrixf( _modelViewMatrix );

  delete _modelViewMatrix;
}

void grid() {
	//glLineWidth(3);
	glPointSize(4);

	for(int i=0;i<tSup_VerTamX();i++) {
		glPushMatrix();
		for(int j=0;j<tSup_VerTamY();j++) {
			glColor3f(supGraf[i][j].red,supGraf[i][j].green,supGraf[i][j].blue);
			//glBegin( GL_POLYGON );
        //glVertex3f(supGraf[i][j].x1, supGraf[i][j].y1, supGraf[i][j].z1);
        //glVertex3f(supGraf[i][j].x1, supGraf[i][j].y2, supGraf[i][j].z1);
        //glVertex3f(supGraf[i][j].x2, supGraf[i][j].y2, supGraf[i][j].z2);
        //glVertex3f(supGraf[i][j].x2, supGraf[i][j].y1, supGraf[i][j].z2);
			//glEnd();
			//glRectf(supGraf[i][j].x1,supGraf[i][j].y1,supGraf[i][j].x2,supGraf[i][j].y2);
			glBegin( GL_POINTS );
        glVertex3f(supGraf[i][j].cX, supGraf[i][j].cY, supGraf[i][j].cZ);
			glEnd();
		}
		glPopMatrix();
	}

	glFlush();
}

void desenha_player1(tipo_Coordenada pos) {
	glPointSize(10);
	int i = pos.x;
	int j = pos.y;

//	supGraf[i][j].red = 0.6;
//	supGraf[i][j].green = 0.8;
//	supGraf[i][j].blue = 0.6;

	glBegin(GL_POINTS);
	glColor3f(0.0, 0.0, 0.0);
	//glVertex2f(supGraf[i][j].cX,supGraf[i][j].cY);
	glVertex3f(supGraf[i][j].cX,supGraf[i][j].cY,supGraf[i][j].cZ);
	glEnd();

	glFlush();
}

void desenha_player2(tipo_Coordenada pos) {
	glPointSize(10);
	int i = pos.x;
	int j = pos.y;

//	supGraf[i][j].red = 0.8;
//	supGraf[i][j].green = 0.6;
//	supGraf[i][j].blue = 0.6;

	glBegin(GL_POINTS);
	glColor3f(0.8, 0.2, 0.2);
	//glVertex2f(supGraf[i][j].cX,supGraf[i][j].cY);
	glVertex3f(supGraf[i][j].cX,supGraf[i][j].cY,supGraf[i][j].cZ);
	glEnd();

	glFlush();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	setModelViewProjection();

	grid();

	desenha_player1(posAtual);
	desenha_player2(posAtualP2);

	glutSwapBuffers();
}

void mousePressCallback(int button, int state, int x, int y) {
  if ( button == GLUT_LEFT_BUTTON )
    {
      if ( state == GLUT_DOWN )
        mVirtualTrackball->pointerDown(x, y);
      else
        mVirtualTrackball->pointerUp();
    }
  else if ( button == 3 ) // Wheel UP
    {
      mVirtualTrackball->zoom(0.04f);
    }
  else if ( button == 4 ) // Wheel DOWN
    {
      mVirtualTrackball->zoom(-0.04f);
    }
  else if ( button == GLUT_MIDDLE_BUTTON )
    {
      if ( state == GLUT_DOWN )
        {
          oldX = x;
          oldY = y;
          middleButtonPressed = 1;
        }
      else
        middleButtonPressed = 0;
    }
}

void mouseMotionCallback(int x, int y) {
  if ( middleButtonPressed )
    {
      float dx = (x-oldX)*0.001f;
      float dy = (y-oldY)*0.001f;
      mVirtualTrackball->move(dx, dy);
      oldX = x;
      oldY = y;
    }
  else
    mVirtualTrackball->pointerMove(x, y);
}

void cria_SuperficieGrafica(char* path) {
	float maximoGlobal;
	int valorMatriz;
	if (!tSup_CarregaArquivoMapa(path)) {
		printf("ERRO: Superficie invalida!\n");
		exit(1);
	}

	//posAtual.x=;
	//posAtual.y=18;

	//posAtualP2.x = 310;
	//posAtualP2.y = 0;

	supGraf.resize(tSup_VerTamX());
	for(int i=0;i<supGraf.size();i++)
		supGraf[i].resize(tSup_VerTamY());

	maximoGlobal = superf_VerificaMaximoGlobal();
	for(int i=0; i<tSup_VerTamX();i++) {
		for(int j=0; j<tSup_VerTamY();j++) {
			supGraf[i][j].x1 = xInicialA+i*(passoX);
			supGraf[i][j].x2 = xInicialB+i*(passoX);

			supGraf[i][j].y1 = yInicialA-j*(passoY);
			supGraf[i][j].y2 = yInicialB-j*(passoY);

			supGraf[i][j].cX = (supGraf[i][j].x1+supGraf[i][j].x2)/2.0;
			supGraf[i][j].cY = (supGraf[i][j].y1+supGraf[i][j].y2)/2.0;

			valorMatriz = sup->matriz[i][j];

      float val = (valorMatriz/maximoGlobal)*0.45f;

			supGraf[i][j].cZ = val;
			supGraf[i][j].z1 = val + passoZ;
			supGraf[i][j].z2 = val - passoZ;

			if ( val == 0 )
        supGraf[i][j].blue = 0.965f;
			else
        supGraf[i][j].blue = 1.0;

      supGraf[i][j].red = valorMatriz/maximoGlobal;
      supGraf[i][j].green = valorMatriz/maximoGlobal;
		}
	}
}

tipo_Valor superf_VerificaMaximoGlobal() {
	return tSup_VerificaMaximoGlobal();
}


