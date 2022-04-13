//
// Gonçalo Mendes Salgueirinho - 2020142627
// a2020142627@isec.pt
//

#ifndef JOGO_SEMAFORO_MENU_H
#define JOGO_SEMAFORO_MENU_H

#include "tabuleiro.h"

void menuContinuarJogo(int *continuar);
pJogadas initMenu(pJogadas jogo,int *opcao);
int menuJogadas();
char *inserirPecaMenu(char *tabu,int colunas,pJogador jogador);
void mostraJogador(Jogador player);
#endif //JOGO_SEMAFORO_MENU_H
