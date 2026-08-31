#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include <allegro5/allegro.h>
#include <allegro5/keyboard.h>
#include "constantes.h"
#include "mapa.h"

/* Estados possíveis da animação do personagem. */
typedef enum {
    animacaoParado,
    animacaoAndando,
    animacaoPulando,
    animacaoDeslizando,
    animacaoMorrendo
} estadoAnimacao;

/* Estrutura que armazena as informações do personagem. */
typedef struct {

    /* Posição do personagem no mapa. */
    float x;
    float y;

    /* Velocidades horizontal e vertical. */
    float velocidadeX;
    float velocidadeY;

    /* Dimensões do personagem. */
    int largura;
    int altura;

    /* Vida do personagem. */
    int vida;

    /* Indica se o personagem está no ar. */
    int pulando;

    /* Indica se o personagem possui o pulo duplo. */
    int possuiPuloDuplo;

    /* Indica se o segundo pulo pode ser utilizado. */
    int podeUsarSegundoPulo;

    /* Indica se o personagem está deslizando. */
    int deslizando;
    /* Tempo restante do deslize. */
    int tempoDeslize;

    /* Tempo restante de invencibilidade após sofrer dano. */
    int invencivel;

    /* Indica se o personagem venceu o jogo. */
    int venceu;

    /* Indica para qual lado o personagem está olhando. */
    int olhandoDireita;

    /* Estado atual da animação. */
    estadoAnimacao animacaoAtual;

    /* Frame atual da animação. */
    int frameAtual;

    /* Tempo restante do knockback. */
    int knockbackFrames;

    /* Controla a velocidade da animação. */
    int contadorAnimacao;

    /* Frames da animação parado. */
    ALLEGRO_BITMAP *parado[ FRAMES_PARADO ];

    /* Frames da animação andando. */
    ALLEGRO_BITMAP *andando[ FRAMES_ANDAR ];

    /* Frames da animação de pulo. */
    ALLEGRO_BITMAP *pulandoFrames[ FRAMES_PULO ];

    /* Frames da animação de deslize. */
    ALLEGRO_BITMAP *deslizandoFrames[ FRAMES_DESLIZE ];

    /* Frames da animação de morte. */
    ALLEGRO_BITMAP *morrendo[ FRAMES_MORTE ];

} personagem;

/* Retorna a quantidade de frames da animação. */
int quantidadeFramesAnimacao( estadoAnimacao animacao );

/* Inicializa o personagem. */
int inicializaPersonagem( personagem *papaiNoel );

/* Atualiza a animação do personagem. */
void atualizaAnimacao( personagem *papaiNoel );

/* Atualiza o personagem. */
void atualizaPersonagem( personagem *papaiNoel, mapa *faseAtual );

/* Faz o personagem pular. */
void pulaPersonagem( personagem *papaiNoel );

/* Faz o personagem deslizar. */
void deslizaPersonagem( personagem *papaiNoel );

/* Responsável por controlar o personagem. */
void controlaPersonagem( personagem *papaiNoel, ALLEGRO_KEYBOARD_STATE *teclado );

/* Desenha o personagem. */
void desenhaPersonagem( personagem *papaiNoel, float cameraX );

/* Libera os recursos do personagem. */
void finalizaPersonagem( personagem *papaiNoel );

#endif