#ifndef JOGO_H
#define JOGO_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "personagem.h"
#include "mapa.h"

/* Enumeração dos estados do jogo. */
typedef enum {
    estadoMenu,
    estadoJogando,
    estadoVitoria,
    estadoGameOver /* Estado caso o jogador perca. */
} estadoJogo;

/* Estrutura que armazena as informações/estruturas do jogo. */
typedef struct {
    /* O que está acontecendo atualmente no jogo. */
    estadoJogo estado;

    /* Indica se o jogo está em execução. */
    int rodando;

    /* Indica se a tela deve ser atualizada. */
    int atualizarTela;

    /* Posição da câmera.
     * A câmera acompanha o jogador de forma horizontal.
     * Não colocaremos cameraY, visto que o jogo não é verticalizado.
     */
    float cameraX;

    /* Informações sobre o jogador. */
    personagem personagem;

    /* Informações sobre o mapa. */
    mapa faseAtual;

    /* Estruturas do Allegro. */
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *filaEventos;
    ALLEGRO_TIMER *temporizador;

} jogo;

/* Responsável por inicializar o jogo. */
int inicializaJogo( jogo *j );

/* Responsável por executar o jogo. */
void executaJogo( jogo *j );

/* Responsável por finalizar/acabar o jogo. */
void finalizaJogo( jogo *j );

#endif