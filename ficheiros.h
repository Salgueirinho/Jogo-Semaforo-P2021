//
// Gonçalo Mendes Salgueirinho - 2020142627
// a2020142627@isec.pt
//
#ifndef JOGO_SEMAFORO_FICHEIROS_H
#define JOGO_SEMAFORO_FICHEIROS_H

#define FICHREGRAS "regras.txt"

pJogadas verificarJogoPorAcabar(pJogadas jogo, int *continuar);
pJogadas repoeJogo(pJogadas jogo,int linhas, int colunas,int jogada, int computador,pJogador player,char tabu[][colunas]);
void mostrarRegras();
void guardaHistorico(pJogadas jogo,char *nomeficheiro,Jogador vencedor);
void guardaJogoPorTerminar(pJogadas jogo);

#endif //JOGO_SEMAFORO_FICHEIROS_H
