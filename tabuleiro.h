//
// Gonçalo Mendes Salgueirinho - 2020142627
// a2020142627@isec.pt
//

#ifndef JOGO_SEMAFORO_TABULEIRO_H
#define JOGO_SEMAFORO_TABULEIRO_H


typedef struct jogadas Jogadas, *pJogadas;
typedef struct jogador Jogador, *pJogador;

struct jogadas{
    char *tabuleiro;
    int linhasTB;
    int colunasTB;
    int jogada;
    pJogador player;
    int computador;
    pJogadas prox;
};

struct jogador{
    char c;
    int pedraADC;
    int linhasADC;
    int colunaADC;
};

char *iniciaTabuleiro(char *tabu,int *linhas, int *colunas);
int verificarJogadaP(char *tabu,int colunas,int x,int y,char peca);
char *inserirPeca(char *tabu,int colunas,int x,int y,char peca);
Jogador verificarVitoria(char *tabu,int linhas, int colunas,Jogador player);
void mostraTabuleiro(char *tabu,int linhas,int colunas);
char *aumentaTabuleiroL(char *tabu,int *linhas,int colunas,pJogador jogador);
char *aumentaTabuleiroC(char *tabu,int linhas,int *colunas,pJogador jogador);
pJogadas guardaTabuleiro(pJogadas jogo,int linhas,int colunas,char *tabu,pJogador player,int nmrJogada, int computador);
void mostrarJogadasAnteriores(pJogadas jogo,int k);
void libertamemo(pJogadas jogo);

#endif //JOGO_SEMAFORO_TABULEIRO_H
