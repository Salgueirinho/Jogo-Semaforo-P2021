//
// Gonçalo Mendes Salgueirinho - 2020142627
// a2020142627@isec.pt
//
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include "motorjogo.h"
#include "ficheiros.h"


void menuContinuarJogo(int *continuar){
        int c;
        printf("+------------------------------+\n");
        printf("| Existe um jogo para terminar |\n"
               "| Deseja Continuar?            |\n"
               "+------------------------------+\n"
               "| Sim - [1]                    |\n"
               "| Não - [0]                    |\n"
               "+------------------------------+\n");
        printf("Opção: ");
        scanf(" %d", &c);


        if (c == 1) {
            *continuar = 7;   // continuar o jogo
        } else {
            *continuar = 0;
        }
}



pJogadas initMenu(pJogadas jogo,int *opcao) {
    int continuar;
    printf("+-----------------------+\n"
           "|       SEMÁFORO        |\n"
           "+-----------------------+\n");
    jogo = verificarJogoPorAcabar(jogo, &continuar);

    fflush(stdin);
    if (continuar){
        //Coloca o jogo por terminar no motor de jogo
        Jogador A,B;
        if(jogo->player->c=='A'){
            A = *jogo->player;
            B = *jogo->prox->player;
        }else{
            B = *jogo->player;
            A = *jogo->prox->player;
        }
        int linhas = jogo->linhasTB,colunas=jogo->colunasTB;
        if(jogo->computador==0) {
            initJogoM(jogo->tabuleiro, &linhas, &colunas, jogo,&A,&B);
        }else{
            initJogoS(jogo->tabuleiro, &linhas, &colunas, jogo,&A,&B);
        }
        remove("jogo.bin");
    }
    printf("+-----------------------+\n"
           "| Um Jogador       -> 1 |\n"
           "|-----------------------|\n"
           "| Multijogador     -> 2 |\n"
           "|-----------------------|\n"
           "| Regras           -> 3 |\n"
           "|-----------------------|\n"
           "| Sair             -> 0 |\n"
           "+-----------------------+\n");
    do {
        printf("| Opção: ");
        scanf(" %d", opcao);
        fflush(stdin);
    } while (*opcao < 0 || *opcao > 4);
//    system("CLEAR");

    return NULL;
}


int menuJogadas(){
    int op;
    printf("+-----------------------+\n"
           "|       Opções          |\n"
           "|-----------------------+\n"
           "| Inserir Peça    -> 1  |\n"
           "|-----------------------+\n"
           "| Aumentar Linha  -> 2  |\n"
           "|-----------------------+\n"
           "| aumentar Coluna -> 3  |\n"
           "|-----------------------+\n"
           "| Ver Anteriores  -> 4  |\n"
           "|-----------------------+\n"
           "| Salvar e Sair   -> 5  |\n"
           "+-----------------------+\n");
    do {
        printf("Opção: ");
        scanf(" %d]", &op);
        fflush(stdin);
    }while(op<1 || op>5);

    return op;
}

void pedeinfoPeca(char *peca, int *x,int *y){
    printf("Peça: ");
    scanf(" %c",peca);
    printf("Linha: ");
    scanf(" %d",x);
    printf("Coluna: ");
    scanf(" %d",y);
}


char *inserirPecaMenu(char *tabu,int colunas,pJogador jogador){
    int x,y;
    int inc;
    char peca;
    printf("+-------------------+\n"
           "|       Peças       |\n"
           "+-------------------+\n"
           "| Verde     -> G    |\n"
           "| Amarela   -> Y    |\n"
           "| Vermelha  -> R    |\n"
           "| Pedra     -> P    |\n"
           "+-------------------+\n");
    do {
        pedeinfoPeca(&peca,&x,&y);
        fflush(stdin);
        inc = verificarJogadaP(tabu, colunas, x, y, peca);
        if(peca=='P' && jogador->pedraADC==0){
            puts("Não pode adicionar mais pedras!");
            inc = 0;
        }
        if(peca=='P' && jogador->pedraADC>0) {
            inc = 1;
            jogador->pedraADC--;
        }
    }while(inc==0);
    tabu = inserirPeca(tabu,colunas,x,y,peca);

    return tabu;
}

void mostraJogador(Jogador player){
    printf("Jogador %c\n"
           "Pedras restantes: %d\n"
           "Aumentar linhas restantes: %d\n"
           "Aumentar colunas restantes: %d\n",player.c,player.pedraADC,player.linhasADC,player.colunaADC);
}