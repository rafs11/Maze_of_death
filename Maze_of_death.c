#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>

#define CHAO 0
#define PAREDE 1
#define VOCE 2
#define SAIDA 3
#define MONSTRO 4

#define ACIMA 119
#define ABAIXO 115
#define DIREITA 100
#define ESQUERDA 97


int coluna_atual = 1,
linha_atual = 1,
coluna_atual2 = 1,
linha_atual2 = 1;

struct jogador {
    int pos;
    char nome[30];
    double tempo;
};

struct jogador jogadores[100];
int numJogadoresSalvos = 0;

int key,passos;


//declaração dos mapas

int mapa1[6][10] = {
    1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,1,0,4,0,1,
    1,1,0,1,0,1,0,0,0,1,
    1,0,0,1,0,1,0,1,0,1,
    1,0,0,1,0,0,0,1,0,3,
    1,1,1,1,1,1,1,1,1,1,
};
int mapa2[10][20] = {
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,0,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,
1,0,1,0,0,0,1,1,0,0,0,1,1,1,0,1,1,1,0,1,
1,0,1,1,1,0,0,1,1,1,0,1,0,0,0,0,1,0,0,1,
1,0,1,0,0,1,0,0,0,1,0,1,0,0,1,1,1,0,0,1,
1,0,1,1,0,1,1,1,0,1,0,1,1,0,1,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,1,0,0,1,0,1,1,1,0,0,1,
1,1,1,1,0,1,1,0,1,1,1,0,1,1,0,0,0,1,1,1,
1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,4,0,0,0,3,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,


};
int mapa3[10][30] = {
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,0,1,0,1,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,1,
1,0,1,0,0,0,1,0,1,1,1,0,0,0,1,1,1,0,1,1,1,0,1,1,1,1,1,0,0,1,
1,0,1,0,1,0,1,0,1,0,0,0,1,1,1,0,1,0,0,0,1,0,1,0,0,0,1,1,0,1,
1,0,0,0,1,0,0,0,1,1,1,1,1,0,0,0,1,0,1,0,1,0,0,1,1,1,0,1,0,1,
1,1,1,1,1,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,1,0,0,0,0,4,0,1,0,1,
1,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,0,1,0,0,1,0,0,1,0,0,0,1,0,1,
1,0,1,1,1,1,1,1,1,0,1,0,1,0,1,1,0,1,1,1,1,1,1,0,1,0,1,1,0,1,
1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,3,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,

};

int mapa1b[6][10] = {

  1,1,1,1,1,1,1,1,1,1,
  1,0,0,0,1,0,1,1,0,3,
  1,0,1,0,0,0,4,1,0,1,
  1,0,1,0,1,0,0,0,0,1,//Freddy aqui
  1,0,1,0,0,1,0,1,0,1,
  1,1,1,1,1,1,1,1,1,1,

};
int mapa2b[10][20] = {

  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,0,0,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,
  1,1,0,1,0,0,1,0,1,0,1,1,1,0,0,0,0,0,1,1,
  1,0,0,1,1,0,1,0,1,0,1,0,1,0,1,1,0,0,0,1,
  1,1,0,1,0,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,
  1,1,0,1,1,0,1,0,0,0,1,0,0,0,1,1,0,0,0,1,
  1,0,0,1,0,0,1,1,1,0,4,0,1,1,1,0,0,0,0,1,
  1,0,1,1,1,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,
  1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,1,0,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,1,
};
int mapa3b[30][15] = {
  1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,
  1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,
  1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
  1,0,1,1,1,1,1,1,0,1,1,1,1,0,1,
  1,0,1,1,1,1,1,1,0,0,0,0,1,0,1,
  1,0,1,1,1,1,1,0,0,1,1,1,1,0,1,
  1,0,1,1,1,1,0,0,0,1,1,1,0,0,1,
  1,0,1,1,1,0,0,0,0,0,0,1,0,1,1,
  1,0,1,1,0,0,0,0,0,0,0,1,0,1,1,
  1,0,1,0,0,0,0,0,0,1,1,1,0,4,1,
  1,0,0,0,0,0,0,0,0,1,1,1,0,0,1,
  1,0,0,1,1,1,1,1,1,1,1,1,1,0,1,
  1,0,0,1,1,1,1,1,1,1,1,0,1,0,1,
  1,0,0,1,1,1,1,1,1,0,0,0,1,0,1,
  1,1,0,1,0,0,0,0,0,0,1,0,1,0,1,
  1,1,0,1,1,1,1,0,0,1,1,0,0,0,1,
  1,1,0,0,0,0,0,0,1,0,1,1,1,1,1,
  1,1,0,1,0,1,1,1,1,0,1,1,1,1,1,
  1,1,0,1,0,1,1,1,1,0,1,1,1,1,1,
  1,1,0,1,0,1,1,1,1,0,1,1,1,1,1,
  1,1,0,1,0,1,1,1,1,0,1,1,1,1,1,
  1,1,0,1,0,1,1,1,1,0,1,1,1,1,1,
  1,1,0,1,0,0,0,0,0,0,0,0,0,0,1,
  1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,
  1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,
  1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,0,1,1,1,1,1,0,0,0,0,0,0,1,1,
  1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,
  1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};

int mapa1c[6][12] = {

  1,1,1,1,1,1,1,1,1,1,1,1,
  1,0,1,0,1,0,1,1,0,0,0,1,
  1,0,1,0,0,0,1,0,0,0,0,1,
  1,0,0,0,1,0,0,0,0,4,0,1,
  1,0,1,0,1,0,1,1,0,1,0,3,
  1,1,1,1,1,1,1,1,1,1,1,1,
};
int mapa2c[10][16] = {

  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,0,1,0,1,0,1,1,0,1,0,1,0,0,0,1,
  1,0,0,0,0,0,1,0,0,0,1,1,1,1,1,0,
  1,1,1,1,1,0,0,1,1,1,1,1,0,0,0,1,
  1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
  1,0,1,0,1,1,1,0,4,1,1,0,0,1,0,1,
  1,0,1,0,0,0,1,0,0,1,1,0,0,1,0,1,
  1,0,0,1,0,1,0,1,0,1,0,1,1,0,1,1,
  1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,3,//Slender aqui
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,

};
int mapa3c[25][30] = {
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
  1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,
  1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,1,1,
  1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,1,0,0,0,0,1,1,
  1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,
  1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,0,0,0,1,
  1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,
  1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,
  1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,
  1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,1,
  1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,
  1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,1,1,1,1,
  1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,1,0,1,
  1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,1,1,1,1,
  1,0,0,0,0,0,1,0,0,1,0,1,0,1,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,1,
  1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,0,0,0,1,0,1,
  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
  1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,4,0,0,0,1,//Slender aqui
  1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,0,0,0,0,0,0,1,1,0,1,0,1,
  1,0,1,0,1,0,0,1,1,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,0,1,0,1,
  1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,0,3,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,


};



void primeira_tela(){

    system("color 0F");

    printf("\t\t\t\t     ¶¶¶¶          s¶¶¶¶¶              s¶¶¶\n\t\t\t\t      ¶¶¶¶¢     7¶¶¶¶¶¶¶¶¶¶¶¶¶        ¶¶¶¶\n\t\t\t\t     7¶¶¶¶¢   ¢¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶    s¶¶¶¶s\n\t\t\t\t    ¶¶¶¶¶¶¶¶ ø¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶1 ¶¶¶¶¶¶¶¶\n\t\t\t\t    ¢øs$¶¶¶¶1¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶ ¶¶¶¶¢¢$$\n\t\t\t\t         7¢ø¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶s ø\n\t\t\t\t            ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n\t\t\t\t            1¶¶¶¶ø  7¶¶¶¶¶1 ø¶¶¶¶¶s\n\t\t\t\t             ¶¶       ¶¶¶      s¶¶\n\t\t\t\t            1¶¶      $¶¶¶1      ¶¶1\n\t\t\t\t             ¶¶¶  s¶¶¶  ø¶¶s  ¶¶¶¶\n\t\t\t\t             7¶¶¶¶¶¶¶¶   ¶¶¶¶¶¶¶¶1\n\t\t\t\t               ¶¶¶¶¶¶¶s$s¶¶¶¶¶¶\n\t\t\t\t             ø¶ ¶s¶¶¶¶¶¶¶¶¶¶¶¶ ¶  ¶s\n\t\t\t\t      7    $¶¶¶ ¶            $  ¶¶¶¶¶\n\t\t\t\t   1¶¶¶¶¶¶¶¶¶¶ø ¶ ¶¶$¶¶$¶¶$¶7¶1  ¶¶¶¶¶¶¶¶¶¶¶\n\t\t\t\t    ¶¶¶¶¶¶¶¶    ¶¶¶¶¶¶¶¶¶¶¶¶¶¶1   ¶¶¶¶¶¶¶¶¶\n\t\t\t\t     ø¶¶¶¶¶      1¶¶¶¶¶¶¶¶¶¶¢      ¶¶¶¶¶¶¶\n\t\t\t\t       s¶¶ø         $¶¶¶¶¶s        1¶¶¶\n"); //caveira

    getch();

    system("cls");



    system("color 04");

    printf("\t\t\t\t     ¶¶¶¶          s¶¶¶¶¶              s¶¶¶\n\t\t\t\t      ¶¶¶¶¢     7¶¶¶¶¶¶¶¶¶¶¶¶¶        ¶¶¶¶\n\t\t\t\t     7¶¶¶¶¢   ¢¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶    s¶¶¶¶s\n\t\t\t\t    ¶¶¶¶¶¶¶¶ ø¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶1 ¶¶¶¶¶¶¶¶\n\t\t\t\t    ¢øs$¶¶¶¶1¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶ ¶¶¶¶¢¢$$\n\t\t\t\t         7¢ø¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶s ø\n\t\t\t\t            ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n\t\t\t\t            1¶¶¶¶ø  7¶¶¶¶¶1 ø¶¶¶¶¶s\n\t\t\t\t             ¶¶       ¶¶¶      s¶¶\n\t\t\t\t            1¶¶      $¶¶¶1      ¶¶1\n\t\t\t\t             ¶¶¶  s¶¶¶  ø¶¶s  ¶¶¶¶\n\t\t\t\t             7¶¶¶¶¶¶¶¶   ¶¶¶¶¶¶¶¶1\n\t\t\t\t               ¶¶¶¶¶¶¶s$s¶¶¶¶¶¶\n\t\t\t\t             ø¶ ¶s¶¶¶¶¶¶¶¶¶¶¶¶ ¶  ¶s\n\t\t\t\t      7    $¶¶¶ ¶            $  ¶¶¶¶¶\n\t\t\t\t   1¶¶¶¶¶¶¶¶¶¶ø ¶ ¶¶$¶¶$¶¶$¶7¶1  ¶¶¶¶¶¶¶¶¶¶¶\n\t\t\t\t    ¶¶¶¶¶¶¶¶    ¶¶¶¶¶¶¶¶¶¶¶¶¶¶1   ¶¶¶¶¶¶¶¶¶\n\t\t\t\t     ø¶¶¶¶¶      1¶¶¶¶¶¶¶¶¶¶¢      ¶¶¶¶¶¶¶\n\t\t\t\t       s¶¶ø         $¶¶¶¶¶s        1¶¶¶\n"); //caveira


    printf("\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\t\t\t~~~~~~~~~~~~~~~                                 ~~~~~~~~~~~~~~~\n\t\t\t~~~~~~~~~~~~~~~                                 ~~~~~~~~~~~~~~~\n\t\t\t~~~~~~~~~~~~~~~     M A Z E  O F  D E A T H     ~~~~~~~~~~~~~~~\n\t\t\t~~~~~~~~~~~~~~~                                 ~~~~~~~~~~~~~~~\n\t\t\t~~~~~~~~~~~~~~~                                 ~~~~~~~~~~~~~~~\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"); //nome do jogo

    getch();

    system("cls");

}



void salvaRanking(double tempo) {
    char nome[30];
    int i;
    int novaPosicao = numJogadoresSalvos + 1;

    printf("Digite seu nome: \n");
    scanf("%s", nome);

    for (i = 0; i < numJogadoresSalvos; i++) {
        if (jogadores[i].tempo >= tempo) {
            // atribui depois incrementa
            int pos = jogadores[i].pos++;
            if (novaPosicao > pos) {
                novaPosicao = pos;
            }
        }
    }

    // operador ternário
    jogadores[numJogadoresSalvos].pos = novaPosicao;
    strcpy(jogadores[numJogadoresSalvos].nome, nome);
    jogadores[numJogadoresSalvos].tempo = tempo;
    numJogadoresSalvos++;
}



int Mapa1(){
    int i,j;


    for(i=0;i<6;i++){
        for(j=0;j<10;j++){
            if ((i == linha_atual) && (j == coluna_atual)) {
                printf("@");
                continue;
            }

            if(mapa1[i][j]==CHAO) {
                printf(" ");
            }

            if(mapa1[i][j]==PAREDE){
                    if(j==0 || j==9){
                        printf("::");
                    }
                    else{
                        printf(":");
                    }
            }

            if(mapa1[i][j]==SAIDA){
                printf("##");
            }
            if(mapa1[i][j]==MONSTRO){
                printf("M");
            }

        }
        printf("\n");
    }
    printf("\n");
return 1;
}

int Mapa2(){
    int i,j;

    for(i=0;i<10;i++){
        for(j=0;j<20;j++){
            if ((i == linha_atual) && (j == coluna_atual)) {
                printf("@");
                continue;
            }

            if(mapa2[i][j]==CHAO) {
                printf(" ");
            }

            if(mapa2[i][j]==PAREDE){
                    if(j==0 || j==19){
                        printf("::");
                    }
                    else{
                        printf(":");
                    }
            }

            if(mapa2[i][j]==SAIDA){
                printf("##");
            }

            if(mapa2[i][j]==MONSTRO){
                printf("M");
            }

        }
        printf("\n");
    }
    printf("\n");
return 1;
}

int Mapa3(){
    int i,j;

    for(i=0;i<10;i++){
        for(j=0;j<30;j++){
            if ((i == linha_atual) && (j == coluna_atual)) {
                printf("@");
                continue;
            }

            if(mapa3[i][j]==CHAO) {
                printf(" ");
            }

            if(mapa3[i][j]==PAREDE){
                if(j==0 || j==29){
                    printf("::");
                }
                else{
                    printf(":");
                }
            }

            if(mapa3[i][j]==SAIDA){
                printf("##");
            }

            if(mapa3[i][j]==MONSTRO){
                printf("M");
            }

        }
        printf("\n");
    }
    printf("\n");
return 1;
}



double RodaMapa1(){

    int level = 1;
    int i,j;

    clock_t t;
    t = clock();

    while(mapa1[linha_atual][coluna_atual]!= SAIDA){
        key = getch();
        if(key == ACIMA){
            linha_atual --;
            passos ++;

            if(mapa1[linha_atual][coluna_atual] == 1){
                linha_atual ++;
                passos --;
            }
            system("cls");
            Mapa1();
        }
        if(key == ABAIXO){
            linha_atual ++;
            passos ++;

            if(mapa1[linha_atual][coluna_atual] == 1){
                linha_atual --;
                passos --;
            }
            system("cls");
            Mapa1();
        }
        if(key == DIREITA){
            coluna_atual ++;
            passos ++;

            if(mapa1[linha_atual][coluna_atual] == 1){
                coluna_atual --;
                passos --;
            }

            system("cls");
            Mapa1();
        }
        if(key == ESQUERDA){
            coluna_atual --;
            passos ++;

            if(mapa1[linha_atual][coluna_atual] == 1){
                coluna_atual ++;
                passos --;
            }
            system("cls");
            Mapa1();
        }
        if(mapa1[linha_atual][coluna_atual] == MONSTRO){
            printf("O MINOTAURO TE PEGOU!!!!\n");
            printf("Aperte qualquer tecla para voltar para o checkpoint\n");
            coluna_atual =1;
            linha_atual=1;
            getch();
            system("cls");
            Mapa1();

        }
    }
    coluna_atual =1;
    linha_atual=1;
    int level2 = level +1;

    t = clock() - t;
    double tempo = ((double)t)/CLOCKS_PER_SEC; // in seconds

    printf("\n\nLevel %i Concluido\nTotal de Passos Level %i: %i\nTempo: %.2fs\nPressione Qualquer Tecla Para ir Ao Level %i\n",level,level,passos,tempo,level2);
    getch();
    passos = 0;
    system("cls");
    level++;


    return tempo;
}

double RodaMapa2(){

    int level = 2;
    int i,j;

    clock_t t;
    t = clock();

    while(mapa2[linha_atual][coluna_atual]!= SAIDA){
        key = getch();
        if(key == ACIMA){
            linha_atual --;
            passos ++;

            if(mapa2[linha_atual][coluna_atual] == 1){
                linha_atual ++;
                passos --;
            }
            system("cls");
            Mapa2();
        }
        if(key == ABAIXO){
            linha_atual ++;
            passos ++;

            if(mapa2[linha_atual][coluna_atual] == 1){
                linha_atual --;
                passos --;
            }
            system("cls");
            Mapa2();
        }
        if(key == DIREITA){
            coluna_atual ++;
            passos ++;

            if(mapa2[linha_atual][coluna_atual] == 1){
                coluna_atual --;
                passos --;
            }

            system("cls");
            Mapa2();
        }
        if(key == ESQUERDA){
            coluna_atual --;
            passos ++;

            if(mapa2[linha_atual][coluna_atual] == 1){
                coluna_atual ++;
                passos --;
            }
            system("cls");
            Mapa2();
        }
        if(mapa2[linha_atual][coluna_atual] == MONSTRO){
            printf("O MINOTAURO TE PEGOU!!!!\n\n");
            printf("Aperte qualquer tecla para voltar para o checkpoint\n");
            coluna_atual =1;
            linha_atual=1;
            getch();
            system("cls");
            Mapa2();

        }
    }
    coluna_atual =1;
    linha_atual=1;
    int level2 = level +1;

    t = clock() - t;
    double tempo = ((double)t)/CLOCKS_PER_SEC; // in seconds

    printf("\n\nLevel %i Concluido\nTotal de Passos Level %i: %i\nTempo: %.2fs\nPressione Qualquer Tecla Para ir Ao Level %i\n",level,level,passos,tempo,level2);
    getch();
    passos = 0;
    system("cls");
    level++;

    return tempo;
}

double RodaMapa3(){

    int level = 3;
    int i,j;

    clock_t t;
    t = clock();

    while(mapa3[linha_atual][coluna_atual]!= SAIDA){
        key = getch();
        if(key == ACIMA){
            linha_atual --;
            passos ++;

            if(mapa3[linha_atual][coluna_atual] == 1){
                linha_atual ++;
                passos --;
            }
            system("cls");
            Mapa3();
        }
        if(key == ABAIXO){
            linha_atual ++;
            passos ++;

            if(mapa3[linha_atual][coluna_atual] == 1){
                linha_atual --;
                passos --;
            }
            system("cls");
            Mapa3();
        }
        if(key == DIREITA){
            coluna_atual ++;
            passos ++;

            if(mapa3[linha_atual][coluna_atual] == 1){
                coluna_atual --;
                passos --;
            }

            system("cls");
            Mapa3();
        }
        if(key == ESQUERDA){
            coluna_atual --;
            passos ++;

            if(mapa3[linha_atual][coluna_atual] == 1){
                coluna_atual ++;
                passos --;
            }
            system("cls");
            Mapa3();
        }
        if(mapa3[linha_atual][coluna_atual] == MONSTRO){
            printf("O MINOTAURO TE PEGOU!!!!\n\n");
            printf("Aperte qualquer tecla para voltar para o checkpoint\n");
            coluna_atual =1;
            linha_atual=1;
            getch();
            system("cls");
            Mapa3();

        }
    }
    coluna_atual =1;
    linha_atual=1;
    int level2 = level +1;

    t = clock() - t;
    double tempo = ((double)t)/CLOCKS_PER_SEC; // in seconds

    printf("\n\nLevel %i Concluido\nTotal de Passos Level %i: %i\nTempo: %.2fs\nPressione Qualquer Tecla para finalizar\n",level,level,passos,tempo,level2);
    getch();
    passos = 0;
    system("cls");
    level++;

    return tempo;
}



int Mapa1b(){
    int i,j;


    for(i=0;i<6;i++){
        for(j=0;j<10;j++){
            if ((i == linha_atual) && (j == coluna_atual)) {
                printf("@");
                continue;
            }

            if(mapa1b[i][j]==CHAO) {
                printf(" ");
            }

            if(mapa1b[i][j]==PAREDE){
                    if(j==0 || j==9){
                        printf("::");
                    }
                    else{
                        printf(":");
                    }
            }

            if(mapa1b[i][j]==SAIDA){
                printf("##");
            }

            if(mapa1b[i][j]==MONSTRO){
                printf("F");
            }

        }
        printf("\n");
    }
    printf("\n");
return 1;
}

int Mapa2b(){
    int i,j;


    for(i=0;i<10;i++){
        for(j=0;j<20;j++){
            if ((i == linha_atual) && (j == coluna_atual)) {
                printf("@");
                continue;
            }

            if(mapa2b[i][j]==CHAO) {
                printf(" ");
            }

            if(mapa2b[i][j]==PAREDE){
                    if(j==0 || j==19){
                        printf("::");
                    }
                    else{
                        printf(":");
                    }
            }

            if(mapa2b[i][j]==SAIDA){
                printf("#");
            }
            if(mapa2b[i][j]==MONSTRO){
                printf("F");
            }

        }
        printf("\n");
    }
    printf("\n");
return 1;
}

int Mapa3b(){
    int i,j;


    for(i=0;i<30;i++){
        for(j=0;j<15;j++){
            if ((i == linha_atual) && (j == coluna_atual)) {
                printf("@");
                continue;
            }

            if(mapa3b[i][j]==CHAO) {
                printf(" ");
            }

            if(mapa3b[i][j]==PAREDE){
                    if(j==0 || j==14){
                        printf("::");
                    }
                    else{
                        printf(":");
                    }
            }

            if(mapa3b[i][j]==SAIDA){
                printf("#");
            }

            if(mapa3b[i][j]==MONSTRO){
                printf("F");
            }

        }
        printf("\n");
    }
    printf("\n");
return 1;
}



double RodaMapa1b(){

    int level = 1;
    int i,j;

    clock_t t;
    t = clock();

    while(mapa1b[linha_atual][coluna_atual]!= SAIDA){
        key = getch();
        if(key == ACIMA){
            linha_atual --;
            passos ++;

            if(mapa1b[linha_atual][coluna_atual] == 1){
                linha_atual ++;
                passos --;
            }
            system("cls");
            Mapa1b();
        }
        if(key == ABAIXO){
            linha_atual ++;
            passos ++;

            if(mapa1b[linha_atual][coluna_atual] == 1){
                linha_atual --;
                passos --;
            }
            system("cls");
            Mapa1b();
        }
        if(key == DIREITA){
            coluna_atual ++;
            passos ++;

            if(mapa1b[linha_atual][coluna_atual] == 1){
                coluna_atual --;
                passos --;
            }

            system("cls");
            Mapa1b();
        }
        if(key == ESQUERDA){
            coluna_atual --;
            passos ++;

            if(mapa1b[linha_atual][coluna_atual] == 1){
                coluna_atual ++;
                passos --;
            }
            system("cls");
            Mapa1b();
        }
        if(mapa1b[linha_atual][coluna_atual] == MONSTRO){
            printf("O FRRDDY TE PEGOU!!!!\n\n");
            printf("Aperte qualquer tecla para voltar para o checkpoint\n");
            coluna_atual =1;
            linha_atual=1;
            getch();
            system("cls");
            Mapa1b();

        }
    }
    coluna_atual =1;
    linha_atual=1;
    int level2 = level +1;

    t = clock() - t;
    double tempo = ((double)t)/CLOCKS_PER_SEC; // in seconds

    printf("\n\nLevel %i Concluido\nTotal de Passos Level %i: %i\nTempo: %.2fs\nPressione Qualquer Tecla Para ir Ao Level %i\n",level,level,passos,tempo,level2);
    getch();
    passos = 0;
    system("cls");
    level++;


    return tempo;
}

double RodaMapa2b(){

    int level = 1;
    int i,j;

    clock_t t;
    t = clock();

    while(mapa2b[linha_atual][coluna_atual]!= SAIDA){
        key = getch();
        if(key == ACIMA){
            linha_atual --;
            passos ++;

            if(mapa2b[linha_atual][coluna_atual] == 1){
                linha_atual ++;
                passos --;
            }
            system("cls");
            Mapa2b();
        }
        if(key == ABAIXO){
            linha_atual ++;
            passos ++;

            if(mapa2b[linha_atual][coluna_atual] == 1){
                linha_atual --;
                passos --;
            }
            system("cls");
            Mapa2b();
        }
        if(key == DIREITA){
            coluna_atual ++;
            passos ++;

            if(mapa2b[linha_atual][coluna_atual] == 1){
                coluna_atual --;
                passos --;
            }

            system("cls");
            Mapa2b();
        }
        if(key == ESQUERDA){
            coluna_atual --;
            passos ++;

            if(mapa2b[linha_atual][coluna_atual] == 1){
                coluna_atual ++;
                passos --;
            }
            system("cls");
            Mapa2b();
        }
        if(mapa2b[linha_atual][coluna_atual] == MONSTRO){
            printf("O FRRDDY TE PEGOU!!!!\n\n");
            printf("Aperte qualquer tecla para voltar para o checkpoint\n");
            coluna_atual =1;
            linha_atual=1;
            getch();
            system("cls");
            Mapa2b();

        }
    }
    coluna_atual =1;
    linha_atual=1;
    int level2 = level +1;

    t = clock() - t;
    double tempo = ((double)t)/CLOCKS_PER_SEC; // in seconds

    printf("\n\nLevel %i Concluido\nTotal de Passos Level %i: %i\nTempo: %.2fs\nPressione Qualquer Tecla Para ir Ao Level %i\n",level,level,passos,tempo,level2);
    getch();
    passos = 0;
    system("cls");
    level++;


    return tempo;
}

double RodaMapa3b(){


    int level = 3;
    int i,j;

    clock_t t;
    t = clock();

    while(mapa3b[linha_atual][coluna_atual]!= SAIDA){
        key = getch();
        if(key == ACIMA){
            linha_atual --;
            passos ++;

            if(mapa3b[linha_atual][coluna_atual] == 1){
                linha_atual ++;
                passos --;
            }
            system("cls");
            Mapa3b();
        }
        if(key == ABAIXO){
            linha_atual ++;
            passos ++;

            if(mapa3b[linha_atual][coluna_atual] == 1){
                linha_atual --;
                passos --;
            }
            system("cls");
            Mapa3b();
        }
        if(key == DIREITA){
            coluna_atual ++;
            passos ++;

            if(mapa3b[linha_atual][coluna_atual] == 1){
                coluna_atual --;
                passos --;
            }

            system("cls");
            Mapa3b();
        }
        if(key == ESQUERDA){
            coluna_atual --;
            passos ++;

            if(mapa3b[linha_atual][coluna_atual] == 1){
                coluna_atual ++;
                passos --;
            }
            system("cls");
            Mapa3b();
        }

        if(mapa3b[linha_atual][coluna_atual] == MONSTRO){
            printf("O FRRDDY TE PEGOU!!!!\n\n");
            printf("Aperte qualquer tecla para voltar para o checkpoint\n");
            coluna_atual =1;
            linha_atual=1;
            getch();
            system("cls");
            Mapa3b();

        }
    }
    coluna_atual =1;
    linha_atual=1;
    int level2 = level +1;

    t = clock() - t;
    double tempo = ((double)t)/CLOCKS_PER_SEC; // in seconds

    printf("\n\nLevel %i Concluido\nTotal de Passos Level %i: %i\nTempo: %.2fs\nPressione Qualquer Tecla para finalizar\n",level,level,passos,tempo,level2);
    getch();
    passos = 0;
    system("cls");
    level++;

    return tempo;
}



int Mapa1c(){
    int i,j;


    for(i=0;i<6;i++){
        for(j=0;j<12;j++){
            if ((i == linha_atual) && (j == coluna_atual)) {
                printf("@");
                continue;
            }

            if(mapa1c[i][j]==CHAO) {
                printf(" ");
            }

            if(mapa1c[i][j]==PAREDE){
                    if(j==0 || j==11){
                        printf("::");
                    }
                    else{
                        printf(":");
                    }
            }

            if(mapa1c[i][j]==SAIDA){
                printf("##");
            }

            if(mapa1c[i][j]==MONSTRO){
                printf("S");
            }


        }
        printf("\n");
    }
    printf("\n");
return 1;
}

int Mapa2c(){
    int i,j;


    for(i=0;i<10;i++){
        for(j=0;j<16;j++){
            if ((i == linha_atual) && (j == coluna_atual)) {
                printf("@");
                continue;
            }

            if(mapa2c[i][j]==CHAO) {
                printf(" ");
            }

            if(mapa2c[i][j]==PAREDE){
                    if(j==0 || j==15){
                        printf("::");
                    }
                    else{
                        printf(":");
                    }
            }

            if(mapa2c[i][j]==SAIDA){
                printf("##");
            }

            if(mapa2c[i][j]==MONSTRO){
                printf("S");
            }

        }
        printf("\n");
    }
    printf("\n");
return 1;
}

int Mapa3c(){
    int i,j;


    for(i=0;i<25;i++){
        for(j=0;j<30;j++){
            if ((i == linha_atual) && (j == coluna_atual)) {
                printf("@");
                continue;
            }

            if(mapa3c[i][j]==CHAO) {
                printf(" ");
            }

            if(mapa3c[i][j]==PAREDE){
                    if(j==0 || j==29){
                        printf("::");
                    }
                    else{
                        printf(":");
                    }
            }

            if(mapa3c[i][j]==SAIDA){
                printf("##");
            }

            if(mapa3c[i][j]==MONSTRO){
                printf("S");
            }

        }
        printf("\n");
    }
    printf("\n");
return 1;
}



double RodaMapa1c(){

    int level = 1;
    int i,j;

    clock_t t;
    t = clock();

    while(mapa1c[linha_atual][coluna_atual]!= SAIDA){
        key = getch();
        if(key == ACIMA){
            linha_atual --;
            passos ++;

            if(mapa1c[linha_atual][coluna_atual] == 1){
                linha_atual ++;
                passos --;
            }
            system("cls");
            Mapa1c();
        }
        if(key == ABAIXO){
            linha_atual ++;
            passos ++;

            if(mapa1c[linha_atual][coluna_atual] == 1){
                linha_atual --;
                passos --;
            }
            system("cls");
            Mapa1c();
        }
        if(key == DIREITA){
            coluna_atual ++;
            passos ++;

            if(mapa1c[linha_atual][coluna_atual] == 1){
                coluna_atual --;
                passos --;
            }

            system("cls");
            Mapa1c();
        }
        if(key == ESQUERDA){
            coluna_atual --;
            passos ++;

            if(mapa1c[linha_atual][coluna_atual] == 1){
                coluna_atual ++;
                passos --;
            }
            system("cls");
            Mapa1c();
        }

        if(mapa1c[linha_atual][coluna_atual] == MONSTRO){
            printf("O SLENDERMAN TE PEGOU!!!!\n\n");
            printf("Aperte qualquer tecla para voltar para o checkpoint\n");
            coluna_atual =1;
            linha_atual=1;
            getch();
            system("cls");
            Mapa1c();

        }
    }
    coluna_atual =1;
    linha_atual=1;
    int level2 = level +1;

    t = clock() - t;
    double tempo = ((double)t)/CLOCKS_PER_SEC; // in seconds

    printf("\n\nLevel %i Concluido\nTotal de Passos Level %i: %i\nTempo: %.2fs\nPressione Qualquer Tecla Para ir Ao Level %i\n",level,level,passos,tempo,level2);
    getch();
    passos = 0;
    system("cls");
    level++;


    return tempo;
}

double RodaMapa2c(){

    int level = 1;
    int i,j;

    clock_t t;
    t = clock();

    while(mapa2c[linha_atual][coluna_atual]!= SAIDA){
        key = getch();
        if(key == ACIMA){
            linha_atual --;
            passos ++;

            if(mapa2c[linha_atual][coluna_atual] == 1){
                linha_atual ++;
                passos --;
            }
            system("cls");
            Mapa2c();
        }
        if(key == ABAIXO){
            linha_atual ++;
            passos ++;

            if(mapa2c[linha_atual][coluna_atual] == 1){
                linha_atual --;
                passos --;
            }
            system("cls");
            Mapa2c();
        }
        if(key == DIREITA){
            coluna_atual ++;
            passos ++;

            if(mapa2c[linha_atual][coluna_atual] == 1){
                coluna_atual --;
                passos --;
            }

            system("cls");
            Mapa2c();
        }
        if(key == ESQUERDA){
            coluna_atual --;
            passos ++;

            if(mapa2c[linha_atual][coluna_atual] == 1){
                coluna_atual ++;
                passos --;
            }
            system("cls");
            Mapa2c();
        }

        if(mapa2c[linha_atual][coluna_atual] == MONSTRO){
            printf("O SLENDERMAN TE PEGOU!!!!\n\n");
            printf("Aperte qualquer tecla para voltar para o checkpoint\n");
            coluna_atual =1;
            linha_atual=1;
            getch();
            system("cls");
            Mapa2c();

        }

    }
    coluna_atual =1;
    linha_atual=1;
    int level2 = level +1;

    t = clock() - t;
    double tempo = ((double)t)/CLOCKS_PER_SEC; // in seconds

    printf("\n\nLevel %i Concluido\nTotal de Passos Level %i: %i\nTempo: %.2fs\nPressione Qualquer Tecla Para ir Ao Level %i\n",level,level,passos,tempo,level2);
    getch();
    passos = 0;
    system("cls");
    level++;


    return tempo;
}

double RodaMapa3c(){


    int level = 3;
    int i,j;

    clock_t t;
    t = clock();

    while(mapa3c[linha_atual][coluna_atual]!= SAIDA){
        key = getch();
        if(key == ACIMA){
            linha_atual --;
            passos ++;

            if(mapa3c[linha_atual][coluna_atual] == 1){
                linha_atual ++;
                passos --;
            }
            system("cls");
            Mapa3c();
        }
        if(key == ABAIXO){
            linha_atual ++;
            passos ++;

            if(mapa3c[linha_atual][coluna_atual] == 1){
                linha_atual --;
                passos --;
            }
            system("cls");
            Mapa3c();
        }
        if(key == DIREITA){
            coluna_atual ++;
            passos ++;

            if(mapa3c[linha_atual][coluna_atual] == 1){
                coluna_atual --;
                passos --;
            }

            system("cls");
            Mapa3c();
        }
        if(key == ESQUERDA){
            coluna_atual --;
            passos ++;

            if(mapa3c[linha_atual][coluna_atual] == 1){
                coluna_atual ++;
                passos --;
            }
            system("cls");
            Mapa3c();
        }

        if(mapa3c[linha_atual][coluna_atual] == MONSTRO){
            printf("O SLENDERMAN TE PEGOU!!!!\n\n");
            printf("Aperte qualquer tecla para voltar para o checkpoint\n");
            coluna_atual =1;
            linha_atual=1;
            getch();
            system("cls");
            Mapa3c();

        }
    }
    coluna_atual =1;
    linha_atual=1;
    int level2 = level +1;

    t = clock() - t;
    double tempo = ((double)t)/CLOCKS_PER_SEC; // in seconds

    printf("\n\nLevel %i Concluido\nTotal de Passos Level %i: %i\nTempo: %.2fs\nPressione Qualquer Tecla para finalizar\n",level,level,passos,tempo,level2);
    getch();
    passos = 0;
    system("cls");
    level++;

    return tempo;
}



void grupo1() {
    double tempoTotal = 0;

    printf("\n\nVoce foi sorteado a encarar o desafio do Minotauro e deve escapar\nde seu labirinto o mais rapido possivel antes que ele te encontre.\nEsta criatura mitologica possui uma velocidade extraordinaria e uma força fisica invejavel!\nEntao, cuidado com seus movimentos rapidos e boa sorte!\n\n");
    printf("\n\nBOM JOGO!!!\n\n\n\n\n\n\nPressione qualquer tecla para jogar...\n");
    getch();
    system("cls");

    Mapa1();
    tempoTotal += RodaMapa1();

    Mapa2();
    tempoTotal += RodaMapa2();

    Mapa3();
    tempoTotal += RodaMapa3();

    if (tempoTotal >= 50) {
        printf("Achei que nao ia acabar...\n");
    }
    else if (tempoTotal >= 33) {
        printf("Foi bem...\n");
    } else {
        printf("Parecia o the flash...\n");
    }
    printf("Tempo total: %.2fs\n", tempoTotal);

    salvaRanking(tempoTotal);
}

void grupo2() {
    double tempoTotal = 0;

    printf("\n\nVoce foi sorteado a enfrentar o Freddy Krugger e deve escapar\nde seu labirinto o mais rapido possivel antes que ele te encontre.\nEsta criatura cinematografica possui uma criatividade incrivel na hora\nde encontrar seus inimigos, entao, muito cuidado com isso e boa sorte!\n\n");
    printf("\n\nBOM JOGO!!!\n\n\n\n\n\n\nPressione qualquer tecla para jogar...");
    getch();
    system("cls");

    Mapa1b();
    tempoTotal += RodaMapa1b();

    Mapa2b();
    tempoTotal += RodaMapa2b();

    Mapa3b();
    tempoTotal += RodaMapa3b();

    if (tempoTotal >= 50) {
        printf("Achei que nao ia acabar...\n");
    }
    else if (tempoTotal >= 33) {
        printf("Foi bem...\n");
    } else {
        printf("Parecia o the flash...\n");
    }
    printf("Tempo total: %.2fs\n", tempoTotal);

    salvaRanking(tempoTotal);
}

void grupo3() {
    double tempoTotal = 0;

    printf("\n\nVoce foi sorteado a enfrentar a grande lenda dos jogos de computador!\nSlenderman, o terrivel homem sem face, mais aterrorizante da internet, possui a habilidade\nde deixar seus inimigos com bastante medo e usar isso a seu favor. Slender gosta de deixar pistas\nem seu mapa para que ele seja derrotado, mas voce nao terá isso a seu favor, corra o mais rapido\npossivel dele e saira vivo desse pesadelo!\n\n");
    printf("\n\nBOM JOGO!!!\n\n\n\n\n\n\nPressione qualquer tecla para jogar...");
    getch();
    system("cls");

    Mapa1c();
    tempoTotal += RodaMapa1c();

    Mapa2c();
    tempoTotal += RodaMapa2c();

    Mapa3c();
    tempoTotal += RodaMapa3c();

    if (tempoTotal >= 50) {
        printf("Achei que nao ia acabar...\n");
    }
    else if (tempoTotal >= 30) {
        printf("Foi bem...\n");
    } else {
        printf("Parecia o the flash!!!\n");
    }
    printf("Tempo total: %.2fs\n", tempoTotal);

    salvaRanking(tempoTotal);
}



void mostrarRanking() {
    int pos = 1;
    for (int i =0; i < numJogadoresSalvos; i++) {
        for (int j = 0; j<numJogadoresSalvos; j++) {
            if (pos == jogadores[j].pos) {
                printf("Posicao: #%d\n", jogadores[j].pos);
                printf("Nome: %s\n", jogadores[j].nome);
                printf("Tempo: %.2fs\n\n", jogadores[j].tempo);
                pos++;
                break;
            }
        }
    }
}



void start(){
    int n;

    srand(time(NULL));
    n = rand() % 3;
    int numeroJogadas;

    system("color F0");

    printf("Digite a quantidade de jogadores: ");
    scanf("%d", &numeroJogadas);

    while (numeroJogadas--) {
        switch (n) {
        case 0:
            grupo1();
            break;
        case 1:
            grupo2();
            break;
        case 2:
            grupo3();
            break;
        }
    }

    mostrarRanking();
    getch();
    system("cls");
    menu();

}



void ajuda(){

    system("color 09");

    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ O QUE E O JOGO? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t\tO jogo de labirinto se consiste em entrar em um mapa e conseguir sair dele.\n\tPorem, nele ha caminhos que nao te levam a nada, entao precisa ir pelo caminho certo para\n\tchegar ate o objetivo. Mas nao sera tao facil assim! Pois ha monstros que nao se agradam com sua\n\tpresenca e querem te eliminar! Sera sorteado um monstro que vc ira enfrentar. Entre eles:\n\t\tMinotauro: uma criatura mitologica que possui uma velocidade extraordinaria e\n\tuma força fisica invejavel!\n\t\tFreddy Krugger: uma criatura cinematografica que possui uma criatividade incrivel na hora\n\tde encontrar seus inimigos\n\t\tSlenderman: um homem gigante, sem face que possui a habilidade de deixar seus inimigos\n\tcom bastante medo e usa isso a seu favor!\n\tVoce pode, tambem, competir com o seu amigo. Aquele que completar\n\tos 3 niveis em menos tempo, vence!\n\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Objetivo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t\tO objetivo deste jogo e manobrar o seu personagem (@) atraves do labirinto\n\tsem ser pego pelo monstro e chegar ao portal (#) que te levara para o proximo nivel. Ao vencer\n\to ultimo nivel, venceras o jogo. Porem voce precisa fazer tudo no menor tempo possivel,\n\tpara vencer seu adversario, se houver. O jogador que chegar ao objetivo em menos tempo, ganhara o jogo.\n\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Como Jogar? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t\tControles para mover o jogador: [W] - Para cima\t\t\t  W\n\t\t                                [A] - Para esquerda\t\tA S D\n\t\t                                [S] - Para baixo\n\t\t                                [D] - Para direita\n\n\n");

    printf("\t\t\t\t\tPressione qualquer tecla para retornar para o menu\n");

    getch();
    system("cls");

    menu();

}



int menu(){

  int a;

  system("color 6F"); //fundo azul e letra amarela

  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n~~~~~~~~~~~~~~~                                 ~~~~~~~~~~~~~~~\n~~~~~~~~~~~~~~~                                 ~~~~~~~~~~~~~~~\n~~~~~~~~~~~~~~~     M A Z E  O F  D E A T H     ~~~~~~~~~~~~~~~\n~~~~~~~~~~~~~~~                                 ~~~~~~~~~~~~~~~\n~~~~~~~~~~~~~~~                                 ~~~~~~~~~~~~~~~\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); //nome do jogo

  printf("\t\t       Criado por: Andre Macedo Rodrigues Alves\n\t\t                   Guilherme Franca Dib\n\t\t                   Rafael Santana Goncalves\n\n"); //credito


  printf("1 - START\n");
  printf("2 - HELP\n");
  printf("3 - EXIT\n");
  printf("\n");

  printf("Comando: ");
  scanf("%d", &a);

  if(a == 1){
    system("cls");
    start();
  }

  else if(a == 2){
    system("cls");
    ajuda();
  }

  else if(a == 3){
    system("cls");
    return 0;
  }

  else{
    menu();
  }

  system("cls");

}



int main(){

  int a;

  primeira_tela();

  menu();

  system("cls");

  return 0;
}
