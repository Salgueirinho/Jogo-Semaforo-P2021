//
// Gonçalo Mendes Salgueirinho - 2020142627
// a2020142627@isec.pt
//

#ifndef JOGO_SEMAFORO_MOTORJOGO_H
#define JOGO_SEMAFORO_MOTORJOGO_H

#include "tabuleiro.h"

pJogador trocaJogador(pJogador Atual, pJogador A, pJogador B);
void initJogoM(char *tabu,int *linhas, int *colunas,pJogadas jogo, pJogador A, pJogador B);
char *jogadaComputador(char *tabu,int *linhas,int *colunas,pJogador Computador);
void initJogoS(char *tabu,int *linhas, int *colunas,pJogadas jogo,pJogador A, pJogador B);


#endif //JOGO_SEMAFORO_MOTORJOGO_H
