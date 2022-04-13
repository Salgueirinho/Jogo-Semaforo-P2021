//
// Gonçalo Mendes Salgueirinho - 2020142627
// a2020142627@isec.pt
//
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "tabuleiro.h"
#include "motorjogo.h"
#include "menu.h"
#include "ficheiros.h"

int main() {
    initRandom();

    int opcaomenuinicial;
    int linhas=3,colunas=3;
    char *tabuleiro = NULL;
    pJogadas jogo = NULL;

    do {
        Jogador A = {'A', 1, 2, 2};
        Jogador B = {'B', 1, 2, 2};
        jogo = initMenu(jogo, &opcaomenuinicial);
        if(opcaomenuinicial==1){
            tabuleiro = iniciaTabuleiro(tabuleiro,&linhas,&colunas);
            printf("\n\n");
            printf("|    Modo Um Jogador    |\n");
            initJogoS(tabuleiro,&linhas,&colunas,jogo, &A, &B);
        }else{
            if(opcaomenuinicial==2){
                tabuleiro = iniciaTabuleiro(tabuleiro,&linhas,&colunas);
                printf("\n\n");
                printf("|   Modo Multijogador   |\n");
                initJogoM(tabuleiro,&linhas,&colunas,jogo, &A, &B);
            }else{
                if(opcaomenuinicial==3){
                    mostrarRegras();
                    printf("\n\n\n");
                }else{
                    if(opcaomenuinicial==0) {
                            printf("\n\nA Sair :( ...\n\n");
                    }}}}}while(opcaomenuinicial!=0);


    libertamemo(jogo);
    return 0;
}
