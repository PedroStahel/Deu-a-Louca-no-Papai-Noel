#ifndef CONSTANTES_H
#define CONSTANTES_H

/* Configurações da janela. */
#define SCREEN_W 1280 /* Largura. */
#define SCREEN_H 768 /* Altura. */
#define FPS 60

/* Configurações para a matriz de tiles. */
#define TILE_SIZE 64 /* Cada posição da matriz equivale a 64 pixels. */
#define MAP_LINHAS 12
#define MAP_COLUNAS 60

/* Hitbox do personagem. */
#define HITBOX_OFFSET_X 18
#define HITBOX_OFFSET_Y 8

#define HITBOX_LARGURA 28
#define HITBOX_ALTURA 56

/* Posições e tamanhos dos botões. */
#define BOTAO_JOGAR_X 540
#define BOTAO_JOGAR_Y 280
#define BOTAO_JOGAR_W 200
#define BOTAO_JOGAR_H 60
#define BOTAO_SAIR_X 540
#define BOTAO_SAIR_Y 380
#define BOTAO_SAIR_W 200
#define BOTAO_SAIR_H 60

/* Tipos de tiles. */
#define TILE_VAZIO 0
#define TILE_CHAO 1
#define TILE_PLATAFORMA 2
#define TILE_ESPINHO_C 3
#define TILE_PULO_DUPLO 4
#define TILE_VIDA 5
#define TILE_VITORIA 6
#define TILE_CAIXA 7
#define TILE_ESPINHO_B 8

/* Quantidade de frames de cada animação. */
#define FRAMES_MORTE 17
#define FRAMES_PARADO 16
#define FRAMES_PULO 16
#define FRAMES_DESLIZE 11
#define FRAMES_ANDAR 11
#define TEMPO_ANIMACAO 6

/* Definições do jogador. */
#define VIDA_MAXIMA 20
#define VELOCIDADE_ANDAR 5.0f
#define FORCA_PULO -16.0f
#define GRAVIDADE 0.8f
#define VELOCIDADE_MAX_Y 18.0f
#define TEMPO_DESLIZE 20
#define TEMPO_INVENCIBILIDADE 80
#define SPAWN_LINHA 8

/* Definições da câmera. */
#define CAMERA_MIN 0
#define CAMERA_MAX ( MAP_COLUNAS * TILE_SIZE - SCREEN_W )

/* Definições da interface. */
#define TAMANHO_CORACAO 48
#define VIDA_POR_CORACAO 4

#endif