#include <string.h>
#include <allegro5/allegro_image.h>
#include "mapa.h"
#include <stdio.h>

/* Matriz da fase. */
const int faseMatriz[ MAP_LINHAS ][ MAP_COLUNAS ] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 4, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 1, 1, 1, 1 }
};

int inicializaMapa( mapa *fase ) {
    /* Copia a matriz fixa da fase para dentro da struct do mapa. */
    memcpy( fase -> tiles, faseMatriz, sizeof( fase -> tiles ) );

    /* Carrega o fundo do mapa e os bitmaps de cada tipo de tile. */
    fase -> background = al_load_bitmap( "assets/wintertileset/png/BG/BG.png" );
    fase -> tileChao = al_load_bitmap( "assets/wintertileset/png/Tiles/2.png" );
    fase -> tilePlataforma = al_load_bitmap( "assets/wintertileset/png/Tiles/Plataforma.png" );
    fase -> tileEspinhoC = al_load_bitmap( "assets/wintertileset/png/Object/espinhoC.png" );
    fase -> objCaixa = al_load_bitmap( "assets/wintertileset/png/Object/Crate.png" );
    fase -> itemVida = al_load_bitmap( "assets/wintertileset/png/Object/maisVida.png" );
    fase -> itemPuloDuplo = al_load_bitmap( "assets/wintertileset/png/Object/doubleJump.png" );
    fase -> bandeira = al_load_bitmap( "assets/wintertileset/png/Object/bandeiraFim.png" );
    fase -> tileEspinhoB = al_load_bitmap( "assets/wintertileset/png/Object/espinhoB.png" );

    if ( !fase -> tileChao ||
         !fase -> tilePlataforma ||
         !fase -> tileEspinhoC ||
         !fase -> objCaixa ||
         !fase -> itemVida ||
         !fase -> itemPuloDuplo ||
         !fase -> bandeira ||
         !fase -> tileEspinhoB ) {

        /* Mostra qual bitmap falhou ao carregar, para facilitar o debug. */
        printf("tileChao       = %p\n", (void*)fase->tileChao);
        printf("tilePlataforma = %p\n", (void*)fase->tilePlataforma);
        printf("tileEspinhoC   = %p\n", (void*)fase->tileEspinhoC);
        printf("objCaixa       = %p\n", (void*)fase->objCaixa);
        printf("itemVida       = %p\n", (void*)fase->itemVida);
        printf("itemPuloDuplo  = %p\n", (void*)fase->itemPuloDuplo);
        printf("bandeira       = %p\n", (void*)fase->bandeira);
        printf("tileEspinhoB   = %p\n", (void*)fase->tileEspinhoB);

        return 0;
    }

    return 1;
}

void desenhaMapa( mapa *fase, float cameraX ) {
    int linha;
    int coluna;
    float x;
    float y;

    /* Desenha o fundo do mapa, fixo na tela. */
    al_draw_scaled_bitmap(
        fase->background,
        0, 0,
        al_get_bitmap_width(fase->background),
        al_get_bitmap_height(fase->background),
        0, 0,
        SCREEN_W,
        SCREEN_H,
        0
    );

    /* Percorre toda a matriz desenhando cada tile na posição correta. */
    for ( linha = 0; linha < MAP_LINHAS; linha++ ) {
        for ( coluna = 0; coluna < MAP_COLUNAS; coluna++ ) {

            /* Converte linha/coluna em coordenadas de tela,
             * já descontando o deslocamento da câmera. */
            x = coluna * TILE_SIZE - cameraX;
            y = linha * TILE_SIZE;

            switch ( fase -> tiles[ linha ][ coluna ] ) {
                case TILE_CHAO:
                    al_draw_scaled_bitmap(
                        fase->tileChao,
                        0, 0,
                        128, 128,          // tamanho original do bitmap
                        x, y,
                        64, 64,            // tamanho na tela
                        0
                    );
                    break;

                case TILE_PLATAFORMA:
                    al_draw_scaled_bitmap(
                        fase->tilePlataforma,
                        0, 0,
                        128, 128,
                        x, y,
                        64, 64,
                        0
                    );
                    break;

                case TILE_ESPINHO_C:
                    al_draw_scaled_bitmap(
                        fase->tileEspinhoC,
                        0, 0,
                        512, 512,
                        x, y,
                        64, 64,
                        0
                    );
                    break;

                case TILE_CAIXA:
                    al_draw_scaled_bitmap(
                        fase->objCaixa,
                        0, 0,
                        101, 101,
                        x, y,
                        64, 64,
                        0
                    );
                    break;

                case TILE_VIDA:
                    al_draw_scaled_bitmap(
                        fase->itemVida,
                        0, 0,
                        101, 101,
                        x, y,
                        64, 64,
                        0
                    );
                    break;

                case TILE_PULO_DUPLO:
                    al_draw_scaled_bitmap(
                        fase->itemPuloDuplo,
                        0, 0,
                        101, 101,
                        x, y,
                        64, 64,
                        0
                    );
                    break;

                case TILE_VITORIA:
                    al_draw_scaled_bitmap(
                        fase->bandeira,
                        0, 0,
                        101, 101,
                        x, y,
                        64, 64,
                        0
                    );
                    break;

                case TILE_ESPINHO_B:
                    al_draw_scaled_bitmap(
                        fase->tileEspinhoB,
                        0, 0,
                        512, 512,
                        x, y,
                        64, 80,
                        0
                    );
            }
        }
    }
}

int obtemTile( mapa *fase, int linha, int coluna ) {
    /* Fora dos limites da matriz é tratado como chão sólido. */
    if ( linha < 0 || linha >= MAP_LINHAS ||
         coluna < 0 || coluna >= MAP_COLUNAS )

        return TILE_CHAO;

    return fase -> tiles[linha][coluna];
}

int tileSolido( mapa *fase, int linha, int coluna ) {
    switch ( obtemTile( fase, linha, coluna ) ) {

        /* Chão, plataforma e caixa bloqueiam o personagem. */
        case TILE_CHAO:
        case TILE_PLATAFORMA:
        case TILE_CAIXA:
            return 1;

        default:
            return 0;
    }
}

int tilePerigoso( mapa *fase, int linha, int coluna ) {
    switch ( obtemTile( fase, linha, coluna ) ) {

        /* Os dois tipos de espinho causam dano. */
        case TILE_ESPINHO_B:
        case TILE_ESPINHO_C:
            return 1;

        default:
            return 0;
    }
}

int tileColetavel( mapa *fase, int linha, int coluna ) {
    switch ( obtemTile( fase, linha, coluna ) ) {

        /* Vida, pulo duplo e vitória são tratados como coletáveis. */
        case TILE_VIDA:
        case TILE_PULO_DUPLO:
        case TILE_VITORIA:
            return 1;

        default:
            return 0;
    }
}

void alteraTile( mapa *fase, int linha,
                 int coluna, int novoTile ) {

    /* Ignora posições fora dos limites da matriz. */
    if ( linha < 0 || linha >= MAP_LINHAS ||
         coluna < 0 || coluna >= MAP_COLUNAS )

        return;

    fase -> tiles[ linha ][ coluna ] = novoTile;
}

void finalizaMapa( mapa *fase ) {
    /* Libera todos os bitmaps carregados na inicialização do mapa. */
    al_destroy_bitmap( fase -> tileChao );
    al_destroy_bitmap( fase -> tilePlataforma );
    al_destroy_bitmap( fase -> tileEspinhoB );
    al_destroy_bitmap( fase -> objCaixa );
    al_destroy_bitmap( fase -> itemVida );
    al_destroy_bitmap( fase -> itemPuloDuplo );
    al_destroy_bitmap( fase -> bandeira );
    al_destroy_bitmap( fase -> tileEspinhoC );
}
