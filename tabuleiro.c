//
// Gonçalo Mendes Salgueirinho - 2020142627
// a2020142627@isec.pt
//
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "tabuleiro.h"

char *iniciaTabuleiro(char *tabu,int *linhas, int *colunas){
    int tam;
    tam = intUniformRnd(3, 5);

    char* novo = (char*)malloc(tam * tam * sizeof(char));
    if (novo == NULL){
        printf("Erro a alocar memória! [1]");
        return NULL;
    }
    tabu = novo;
    *linhas = tam;
    *colunas = tam;

    for (int l = 0; l < tam; l++){
        for (int c = 0; c < tam; c++)               //  preenche o tabuleiro com '_'. carater a indicar espaço vazio.
            *(tabu + l*(*colunas) + c) = '_';
    }
    return tabu;
}
int verificarJogadaP(char *tabu,int colunas,int x,int y,char peca){
    //verifica se a peça é valida numa certa posição
    //devove 1 se for válida
    //0 se inválida
    if(peca=='G' && *(tabu + (x-1)*colunas + (y-1)) == '_') {
        return 1;
    }else{
        if(peca=='Y' && *(tabu + (x-1)*colunas + (y-1)) == 'G') {
            return 1;
        }else{
            if(peca=='R' && *(tabu + (x-1)*colunas + (y-1)) == 'Y') {
                return 1;
            }else{
                if(peca=='P' && *(tabu + (x-1)*colunas + (y-1)) == '_') {
                    return 1;
                }else {
                    printf("\nJogada Inválida!\n");
                    return 0;
                }}}}
}
char *inserirPeca(char *tabu,int colunas,int x,int y,char peca){
//x -> linha
//y -> coluna
    int valido;
    valido = verificarJogadaP(tabu, colunas, x, y, peca);
    if (valido)
        *(tabu + (x-1)*colunas + (y-1)) = peca;
    return tabu;
}
Jogador verificarVitoria(char *tabu,int linhas, int colunas,Jogador player){

    Jogador SemVencedor = {'N',0,0,0};
    int verificacao;

    int c;
    int l;
    //percorre linha a linha
    for(l=0;l<linhas;l++){
        verificacao=1;
        for(c=0;c<colunas-1;c++){
            if(*(tabu +(l*colunas+c))==*(tabu +(l*colunas+(c+1)))  && *(tabu +(l*colunas+c))!= '_'){
                verificacao++;
            }
            if(verificacao==colunas) {
                printf("LINHA\n");
                return player;
            }}}

    //percorre coluna a coluna
    for(c=0;c<colunas;c++){
        verificacao=1;
        for(l=0;l<linhas-1;l++){
            if(*(tabu +(l*colunas+c))==*(tabu +((l+1)*colunas+(c))) && *(tabu +(l*colunas+c))!= '_'){
                verificacao++;
            }
            if(verificacao==linhas){
                printf("COLUNA\n");
                return player;
            }}}
    //se o tabuleiro for quadrado para verificar a diagonal
    if(linhas==colunas){
        verificacao=1;
        for(int i=0;i<linhas-1;i++){
            if(*(tabu +(i*colunas+i))==*(tabu +((i+1)*colunas+(i+1)))&& *(tabu +(i*colunas+i))!= '_'){          //se as peças da diagonal forem iguais
                verificacao++;
                }
            if(verificacao==linhas) {
                printf("Diagonal\n");
                return player;
            }}}
    return SemVencedor;
}
void mostraTabuleiro(char *tabu,int linhas,int colunas){

    for(int ic=0;ic<colunas;ic++){
        printf("  %d ",ic+1);
    }
    putchar('\n');
    for (int l = 0; l < linhas; l++){
        for (int c = 0; c < colunas; c++) {
            printf("| %c ", (tabu + l*colunas)[c]);
        }
        printf("| %d\n\n",l+1);
    }
}

char *aumentaTabuleiroL(char *tabu,int *linhas,int colunas,pJogador jogador){
    if(jogador->linhasADC==0){
        puts("Já não pode adicionar mais linhas!");
        return tabu;
    }
    char *temp = realloc(tabu,sizeof(char)*(*linhas+1)*colunas);
    if(temp==NULL){
        puts("Erro a alocar memória! [2]");
        return tabu;
    }
    tabu = temp;
    *linhas += 1;
    int l=*linhas-1;
    for(int c=0;c<colunas;c++){
        *(tabu + (l * (colunas) + c)) = '_';
    }
    jogador->linhasADC--;
    return tabu;
}

char *aumentaTabuleiroC(char *tabu,int linhas,int *colunas,pJogador jogador){
    if(jogador->colunaADC==0){
        puts("Já não pode adicionar mais colunas!");
        return tabu;
    }
    char aux[linhas][*colunas];
    for(int l=0;l<linhas;l++){
        for(int c=0;c<*colunas;c++){
            aux[l][c] = *(tabu +(l*(*colunas)+c));
        }}
    char *temp = realloc(tabu, sizeof(char)*linhas* (*colunas+1));
    if(temp==NULL){
        puts("Erro a alocar memória! [3]");
        return tabu;
    }
    tabu = temp;
    *colunas +=1;
    for(int l=0;l<linhas;l++){
        for(int c=0;c<*colunas;c++){
            *(tabu + (l * (*colunas) + c)) = aux[l][c];
        }}
    int c= *colunas-1;
    for(int l=0;l<linhas;l++){
        *(tabu + (l * (*colunas) + c)) = '_';
    }
    jogador->colunaADC--;
    return tabu;
}

pJogadas guardaTabuleiro(pJogadas jogo,int linhas,int colunas,char *tabu,pJogador player,int nmrJogada, int computador){
// Guarda cada jogada na lista dinamica jogo
    char *aux = malloc(sizeof(char)*linhas*colunas);
    if(aux == NULL){
        fprintf(stderr,"Erro a alocar memória[4]");
        return jogo;
    }
    for(int l=0;l<linhas;l++){
        for(int c=0;c<colunas;c++){
            *(aux +(l*colunas+c))=   *(tabu +(l*colunas+c));
        }}

    Jogadas jogadaAtual ={aux,linhas,colunas,nmrJogada,player, computador, NULL}; // jogada a adicionar à lista

    pJogadas novaJogada = malloc(sizeof(jogadaAtual));
    if(novaJogada == NULL){
        fprintf(stderr,"Erro a alocar memória [5]\n");
        return jogo;
    }
    *novaJogada = jogadaAtual;      // adiciona no inicio da lista
    novaJogada->prox = jogo;
    jogo = novaJogada;
    return jogo;
}

void mostrarJogadasAnteriores(pJogadas jogo,int k){
    if(jogo==NULL){
        printf("Nenhuma Jogada Feita!\n");
        return;
    }
    if(k>jogo->jogada) {
        printf("K maior que as jogadas realizadas!\n");
        return;
    }
    for(int i=0;jogo!=NULL && i<k;i++){
        printf("Jogador: %c, Jogada:%d\n\n",jogo->player->c,jogo->jogada);
        mostraTabuleiro(jogo->tabuleiro,jogo->linhasTB,jogo->colunasTB);
        jogo = jogo->prox;
    }
}
void libertamemo(pJogadas jogo){
    pJogadas aux;
    while (jogo != NULL) {
        aux = jogo;
        jogo = jogo->prox;
        free(aux);
    }


}
