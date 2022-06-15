#!/bin/bash
reset
g++ runSuperfBusca.cpp -o superfBuscaExec -lGLU -lGL -lglut
#g++ /System/Library/Frameworks/GLUT.framework/GLUT /System/Library/Frameworks/OpenGL.framework/OpenGL teste.cpp -o mazeExec

./superfBuscaExec $1

rm superfBuscaExec
