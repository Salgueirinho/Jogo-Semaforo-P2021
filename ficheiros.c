//
// Gonçalo Mendes Salgueirinho - 2020142627
// a2020142627@isec.pt
//
#include <stdio.h>
#include <stdlib.h>
#include "tabuleiro.h"
#include "ficheiros.h"
#include "menu.h"
#include <string.h>

#define FICHPORTERMINAR "jogo.bin"

pJogadas verificarJogoPorAcabar(pJogadas jogo, int *continuar){

    FILE *f = fopen(FICHPORTERMINAR,"rb");
    if(!f){
        fprintf(stderr,"|   Sem Jogo guardado   |\n");
        *continuar=0;
        return NULL;
    }

    int total=0,linhas,colunas,jogada,computador;
    fread(&total,sizeof(int),1,f);
    for(int i=0;i<total;i++){
        fread(&linhas, sizeof(int), 1, f);
        fread(&colunas,sizeof(int),1,f);
        fread(&jogada,sizeof(int),1,f);
        fread(&computador,sizeof(int),1,f);
        char temp[linhas][colunas];                 //array temporario para ler o tabuleiro
        fread(temp, sizeof(char), sizeof(temp), f);
        Jogador sup;
        fread(&sup,sizeof(Jogador),1,f);

        jogo = repoeJogo(jogo,linhas,colunas,jogada,computador,&sup,temp);
    }

    menuContinuarJogo(continuar);
    fclose(f);
    return jogo;
}

pJogadas repoeJogo(pJogadas jogo,int linhas, int colunas,int jogada, int computador,pJogador player,char tabu[][colunas]){
    char* novotabuleiro = (char*)malloc(linhas * colunas * sizeof(char));
    if (novotabuleiro == NULL){
        printf("Erro a alocar memória! [1]");
        return jogo;
    }
    for(int l=0;l<linhas;l++){
        for(int c=0;c<colunas;c++){
            *(novotabuleiro+ (l*colunas+c)) = tabu[l][c];
        }}
    pJogador temp = malloc(sizeof(Jogador));
    *temp = *player;
    Jogadas jogadaAtual = {novotabuleiro, linhas,colunas,jogada, temp,computador, NULL};
    pJogadas auxJogada = malloc(sizeof(jogadaAtual));
    if(!auxJogada){
        fprintf(stderr,"Erro a alocar memória [6]\n");
        return jogo;
    }
    pJogadas auxiliarJOGO = NULL;
    *auxJogada = jogadaAtual;
    auxJogada->prox= NULL;
    if(jogo == NULL){
        jogo = auxJogada;       // se o jogo estiver vazio adiciona no inicio
    }else{
        auxiliarJOGO=jogo;
        while(auxiliarJOGO->prox!=NULL){
            auxiliarJOGO = auxiliarJOGO->prox;  //percorre até ao ultimo elemento
        }
        auxiliarJOGO->prox = auxJogada;   //adiciona no final da lista ligada
    }
    return jogo;
}

void mostrarRegras(){
    /*
     * Função que imprime as Regras do jogo no ecrã depois de pedido pelo o utilizador no menu inicial
     * As regras estão escritas num ficheiro txt
     */
    FILE *f = fopen(FICHREGRAS,"rt");

    if(!f){
        fprintf(stderr,"Erro a abrir ficheiro: %s\n",FICHREGRAS);
        return;
    }
    char c;
    while((c = fgetc(f)) != EOF)
        putchar(c);                     //lê e imprime no ecrã todos os caracteres do ficheiro até ao final do mesmo
    fclose(f);
}

void guardaHistorico(pJogadas jogo,char *nomeficheiro,Jogador vencedor){
/*
 *  Função que guarda o jogo completo num ficheiro txt com o nome pedido ao utilizador
 *  Guarda o vencedor no topo seguido das jogadas, mostrando o tabuleiro e o jogador
 */

    char destino[40] = "historico\\";
    strcat(destino,nomeficheiro);
    FILE *f = fopen(destino,"wt");
    if(!f){
        fprintf(stderr,"Erro a abrir ficheiro %s\n",nomeficheiro);
        return;
    }
    fprintf(f,"Vencedor: %c\n",vencedor.c);     // vencedor do jogo no inicio do ficheiro
    while(jogo!=NULL){
        fprintf(f,"Jogador: %c, Jogada:%d\n\n",jogo->player->c,jogo->jogada);   // jogador e o numero  da jogada

        for(int ic=0;ic<jogo->colunasTB;ic++){
            fprintf(f,"  %d ",ic+1);
        }
        fprintf(f,"\n");                                                //  Tabuleiro da jogada
        for (int l = 0; l < jogo->linhasTB; l++){
            for (int c = 0; c < jogo->colunasTB; c++) {
                fprintf(f,"| %c ", (jogo->tabuleiro + (l*jogo->colunasTB))[c]);
            }
            fprintf(f,"| %d\n\n",l+1);
        }
        jogo = jogo->prox;
    }

    fclose(f);
}

void guardaJogoPorTerminar(pJogadas jogo) {

    FILE *f = fopen(FICHPORTERMINAR, "wb");
    if (!f) {
        fprintf(stderr, "Erro a abrir ficheiro %s\n", FICHPORTERMINAR);
        return;
    }
    int total = jogo->jogada;
    fwrite(&total, sizeof(int), 1, f);
    pJogadas aux=jogo;
    while (aux !=NULL){
        fwrite(&aux->linhasTB, sizeof(int), 1, f);
        fwrite(&aux->colunasTB,sizeof(int),1,f);
        fwrite(&aux->jogada,sizeof(int),1,f);       //informações do tabuleiro e do jogo no inicio
        fwrite(&aux->computador,sizeof(int),1,f);
        char temp[aux->linhasTB][aux->colunasTB];
        char *tab = aux->tabuleiro;
        for(int l=0;l<aux->linhasTB;l++){
            for(int c=0;c<aux->colunasTB;c++){
                temp[l][c]= (tab + l*aux->colunasTB)[c];    // escreve os caracteres todos do tabuleiro
            }}
        fwrite(temp, sizeof(char), aux->linhasTB*aux->colunasTB, f);
        Jogador sup = {aux->player->c,aux->player->pedraADC,aux->player->linhasADC,aux->player->colunaADC};
        fwrite(&sup,sizeof(Jogador),1,f);       //escreve as informações dos jogadores
        aux = aux->prox;
    }
    fclose(f);
}
