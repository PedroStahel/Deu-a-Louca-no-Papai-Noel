#ifndef INTERFACE_H
#define INTERFACE_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include <allegro5/allegro_font.h>

#include "personagem.h"
#include "mapa.h"

/* Responsável por inicializar os recursos da interface. */
int inicializaInterface();

/* Responsável por desenhar o menu principal. */
void desenhaMenu( int hoverJogar, int hoverSair );

/* Responsável por desenhar a tela de vitória. */
void desenhaTelaVitoria();

/* Responsável por desenhar a tela de Game Over. */
void desenhaTelaGameOver();

/* Responsável por desenhar a barra de vida do jogador. */
void desenhaVida( personagem *personagem );

/* Responsável por liberar os recursos da interface. */
void finalizaInterface();

#endif