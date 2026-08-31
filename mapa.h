#ifndef MAPA_H
#define MAPA_H

#include <allegro5/allegro.h>
#include "constantes.h"

/* Estrutura que armazena as informações do mapa. */
typedef struct {
    int tiles[ MAP_LINHAS ][ MAP_COLUNAS ];

    /* Fundo da fase */
    ALLEGRO_BITMAP *background;

    /* Tiles */
    ALLEGRO_BITMAP *tileChao;
    ALLEGRO_BITMAP *tilePlataforma;

    /* Objetos */
    ALLEGRO_BITMAP *objCaixa;
    ALLEGRO_BITMAP *itemVida;
    ALLEGRO_BITMAP *itemPuloDuplo;
    ALLEGRO_BITMAP *bandeira;
    ALLEGRO_BITMAP *tileEspinhoC;
    ALLEGRO_BITMAP *tileEspinhoB;
} mapa;

/* Responsável por inicializar o mapa. */
int inicializaMapa( mapa *fase );

/* Responsável por desenhar o mapa. */
void desenhaMapa( mapa *fase, float cameraX );

/* Retorna o tile presente em uma posição da matriz. */
int obtemTile( mapa *fase, int linha, int coluna );

/* Retorna 1 caso o tile seja sólido.
 * Retorna 0 caso contrário. */
int tileSolido( mapa *fase, int linha, int coluna );

/* Retorna 1 caso o tile seja perigoso.
 * Retorna 0 caso contrário. */
int tilePerigoso( mapa *fase, int linha, int coluna );

/* Retorna 1 caso o tile seja um coletável.
 * Retorna 0 caso contrário. */
int tileColetavel( mapa *fase, int linha, int coluna );

/* Altera o tile em uma posição da matriz. */
void alteraTile( mapa *fase, int linha, int coluna, int novoTile );

/* Responsável por liberar os recursos do mapa. */
void finalizaMapa( mapa *fase );

#endif