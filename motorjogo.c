//
// Gonçalo Mendes Salgueirinho - 2020142627
// a2020142627@isec.pt
//

#include "motorjogo.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "tabuleiro.h"
#include "menu.h"
#include <string.h>
#include "ficheiros.h"


pJogador trocaJogador(pJogador Atual, pJogador A, pJogador B){
    //troca o jogador Atual
    if((*Atual).c=='A')
        return B;
    else
        return A;
}

void initJogoM(char *tabu,int *linhas, int *colunas,pJogadas jogo, pJogador A, pJogador B) {
    //motor de jogo multiplayer
    pJogador Atual;

    if(jogo==NULL)
        Atual=A;            // se o jogo for novo o primeiro a jogar é o A
    else{
        tabu=jogo->tabuleiro;
        if(jogo->player->c=='A'){   //quando o jogo é retomado
            Atual = A;              // verifica qual é o jogador a jogar
        }else
            Atual= B;
    }

    Jogador vencedor;
    int jogada;
    int k, nmrJogada = 1;
    char nomeficheiro[20];  //para o histórico

    do {
        printf("\n\n");
        mostraTabuleiro(tabu, *linhas, *colunas);

            printf("\n\n");
            mostraJogador(*Atual);
            jogada = menuJogadas();     // ESCOLHA DA JOGADA
            if (jogada == 1) {
                tabu = inserirPecaMenu(tabu, *colunas, Atual);
            } else {
                if (jogada == 2) {
                    if (Atual->linhasADC > 0) {
                        tabu = aumentaTabuleiroL(tabu, linhas, *colunas, Atual);
                    } else {
                        printf("Já não pode adicionar mais linhas!\n");
                        Atual = trocaJogador(Atual, A, B);
                    }
                } else {
                    if (jogada == 3) {
                        if (Atual->colunaADC > 0) {
                            tabu = aumentaTabuleiroC(tabu, *linhas, colunas, Atual);
                        } else {
                            printf("Já não pode adicionar mais Colunas!\n");
                            Atual = trocaJogador(Atual, A, B);
                        }
                    } else {
                        if (jogada == 4) {
                            printf("Quantas jogadas?\n");
                            scanf("%d", &k);
                            fflush(stdin);
                            mostrarJogadasAnteriores(jogo, k);
                            Atual = trocaJogador(Atual, A, B);
                        } else {
                            if (jogada == 5) {
                                printf("\nA guardar e Sair!\n\n");
                            } else {
                                printf("\nOpção Inválida\n");
                            }}}}}
            if (jogada != 4)
                jogo = guardaTabuleiro(jogo, *linhas, *colunas, tabu, Atual, nmrJogada, 0);

            vencedor = verificarVitoria(tabu, *linhas, *colunas, *Atual);
            if (vencedor.c == 'N') {
                Atual = trocaJogador(Atual, A, B);
                nmrJogada++;
            }
        }while (vencedor.c == 'N' && jogada != 5);

        if (jogada != 5) {
            printf("\n\nJogo Terminado\n");
            printf("Vencedor : %c\n", (*Atual).c);          //Output no final do jogo quando há vencedores!
            mostraTabuleiro(tabu, *linhas, *colunas);
            putchar('\n');
            printf("Nome do ficheiro para guardar histórico do jogo: ");
            scanf("%s", nomeficheiro);
            strcat(nomeficheiro, ".txt");
            guardaHistorico(jogo, nomeficheiro, *Atual);    // guarda num txt as jogadas
        } else {
            printf("Jogo por terminar guardado!\n");        //output quando o jogo é interrompido a meio
            guardaJogoPorTerminar(jogo);                //guarda no jogo.bin

        }
        libertamemo(jogo);              // liberta a memória da lista dinamica
}


char *jogadaComputador(char *tabu,int *linhas,int *colunas,pJogador Computador){
//jogadas do computador
//feitas com números aleatórios
    int escolhaMenu,escolhaPeca,legal=0;
    int x,y;
    int verificarIns;
    char Peca;

    do{
        escolhaMenu = intUniformRnd(1,3);
        if(escolhaMenu==1){
            do {
                escolhaPeca = intUniformRnd(1,4);
                x = intUniformRnd(1,*linhas);
                y = intUniformRnd(1,*colunas);
                //Peça G (Verde)
                if(escolhaPeca==1){
                    Peca = 'G';
                    verificarIns = verificarJogadaP(tabu,*colunas,x,y,Peca);
                    if(verificarIns==1){
                        tabu = inserirPeca(tabu,*colunas,x,y,Peca);
                        legal=1;
                    }
                }else{
                    //Peça Y (Amarela)
                    if(escolhaPeca==2){
                        Peca = 'Y';
                        verificarIns = verificarJogadaP(tabu,*colunas,x,y,Peca);
                        if(verificarIns==1){
                            tabu = inserirPeca(tabu,*colunas,x,y,Peca);
                            legal=1;
                        }
                    }else{
                        //Peça R (Vermelha)
                        if(escolhaPeca==3){
                            Peca = 'R';
                            verificarIns = verificarJogadaP(tabu,*colunas,x,y,Peca);
                            if(verificarIns==1){
                                tabu = inserirPeca(tabu,*colunas,x,y,Peca);
                                legal=1;
                            }
                        }else{
                            //Peça P (Pedra)
                            if(escolhaPeca==4){
                                Peca = 'P';
                                if(Computador->pedraADC>0){
                                    verificarIns = verificarJogadaP(tabu,*colunas,x,y,Peca);
                                    if(verificarIns==1){
                                        tabu = inserirPeca(tabu,*colunas,x,y,Peca);
                                        Computador->pedraADC--;
                                        legal=1;
                                    }}}}}}} while (verificarIns==0);
            printf("Inseriu a peça %c em %d, %d",Peca,x,y);
        }else{
            //Aumentar Linha
            if(escolhaMenu==2){
                if(Computador->linhasADC>0){
                    tabu = aumentaTabuleiroL(tabu,linhas,*colunas,Computador);
                    legal=1;
                    printf("Aumentou uma linha!\n");
                }
            } else{
                //Aumentar Coluna
                if(escolhaMenu==3){
                    if(Computador->colunaADC>0){
                        tabu = aumentaTabuleiroC(tabu,*linhas,colunas,Computador);
                        legal=1;
                        printf("Aumentou uma coluna!\n");
                    }
                }}}}while(legal==0);

    return tabu;
}


void initJogoS(char *tabu,int *linhas, int *colunas,pJogadas jogo,pJogador A, pJogador B){
// motor de jogo contra o computador
    pJogador Atual;

    if(jogo==NULL)
        Atual=A;
    else{
        tabu=jogo->tabuleiro;
        if(jogo->player->c=='A'){
            Atual = A;
        }else
            Atual= B;
    }

    Jogador vencedor;
    int jogada = 1;
    int k, nmrJogada = 1;
    char nomeficheiro[20];

    do {
        printf("\n\n");
        mostraTabuleiro(tabu, *linhas, *colunas);
        printf("\n\n");

        if(Atual->c == 'B'){
            printf("Vez do Computador\n");
            tabu = jogadaComputador(tabu,linhas,colunas,Atual);
        }else {
            printf("É a tua vez!\n");
            mostraJogador(*Atual);
            jogada = menuJogadas();     // ESCOLHA DA JOGADA
            if (jogada == 1) {
                tabu = inserirPecaMenu(tabu, *colunas, Atual);
            } else {
                if (jogada == 2) {
                    if(Atual->linhasADC>0) {
                        tabu = aumentaTabuleiroL(tabu, linhas, *colunas, Atual);
                    }else{
                        printf("Já não pode adicionar mais linhas!\n");
                        Atual = trocaJogador(Atual, A, B);
                    }

                } else {
                    if (jogada == 3) {
                        if(Atual->colunaADC>0){
                        tabu = aumentaTabuleiroC(tabu, *linhas, colunas, Atual);
                        }else{
                            printf("Já não pode adicionar mais Colunas!\n");
                            Atual = trocaJogador(Atual, A, B);
                        }
                    } else {
                        if (jogada == 4) {
                            printf("Quantas jogadas?\n");
                            scanf("%d", &k);
                            fflush(stdin);
                            mostrarJogadasAnteriores(jogo, k);
                            Atual = trocaJogador(Atual, A, B);
                        } else {
                            if (jogada == 5) {
                                printf("\nA guardar e Sair!\n\n");
                                //guardarJogo(jogo);
                            } else {
                                printf("\nOpção Inválida\n");
                            }
                        }}}}}
        if(jogada !=4)
            jogo = guardaTabuleiro(jogo, *linhas, *colunas, tabu, Atual, nmrJogada, 1);

        vencedor = verificarVitoria(tabu, *linhas, *colunas, *Atual);
        if (vencedor.c == 'N') {
            Atual = trocaJogador(Atual, A, B);
            nmrJogada++;
        }
    } while (vencedor.c == 'N' && jogada != 5);

    if (jogada != 5) {
        printf("\n\nJogo Terminado\n");
        printf("Vencedor : %c\n", (*Atual).c);          //Output no final do jogo quando há vencedores!
        mostraTabuleiro(tabu, *linhas, *colunas);
        putchar('\n');
        printf("Nome do ficheiro para guardar histórico do jogo: ");
        scanf("%s",nomeficheiro);
        strcat(nomeficheiro,".txt");
        guardaHistorico(jogo,nomeficheiro,*Atual);
    }
    else{
        printf("Jogo por terminar guardado!\n");        //output quando o jogo é interrompido a meio
        guardaJogoPorTerminar(jogo);
    }
    libertamemo(jogo);
}

