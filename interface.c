#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "interface.h"
#include "constantes.h"

/* Variáveis globais da interface. */
ALLEGRO_FONT *fonte;

ALLEGRO_BITMAP *backgroundMenu;
ALLEGRO_BITMAP *coracao;

int inicializaInterface() {
    /* Cria a fonte que será utilizada na interface. */
    fonte = al_create_builtin_font();

    if ( fonte == NULL ) {
        return 0;
    }

    /* Inicializa o addon de primitivas, usado para desenhar os retângulos. */
    al_init_primitives_addon();

    /* Carrega a imagem de fundo do menu. */
    backgroundMenu = al_load_bitmap(
        "assets/wintertileset/png/BG/BG.png"
    );

    if ( backgroundMenu == NULL ) {
        return 0;
    }

    /* Carrega os corações que ficarão no canto da tela durante o jogo.*/
    coracao = al_load_bitmap(
        "assets/heart pixel art/heart pixel art 32x32.png"
    );

    if ( coracao == NULL ) {
        return 0;
    }

    return 1;
}

void desenhaMenu( int hoverJogar, int hoverSair ) {
    ALLEGRO_COLOR corJogar;
    ALLEGRO_COLOR corSair;

    /* Desenha o fundo do menu, a partir da imagem carregada. */
    al_draw_scaled_bitmap( backgroundMenu, 0, 0,
        al_get_bitmap_width( backgroundMenu ),
        al_get_bitmap_height( backgroundMenu ),
        0, 0, SCREEN_W, SCREEN_H, 0 );

    /* Muda a cor dos botões caso hover, ou seja, quando o mouse está sobre eles. */
    if ( hoverJogar )
        corJogar = al_map_rgb( 220, 240, 255 );
    else
        corJogar = al_map_rgb( 150, 180, 210 );

    if ( hoverSair )
        corSair = al_map_rgb( 220, 240, 255 );
    else
        corSair = al_map_rgb( 150, 180, 210 );

    /* Coloca o título do jogo na tela. */
    al_draw_text( fonte, al_map_rgb( 255, 255, 255 ),
        SCREEN_W / 2, 80, ALLEGRO_ALIGN_CENTER, "DEU A LOUCA" );

    al_draw_text( fonte, al_map_rgb( 255, 255, 255 ),
        SCREEN_W / 2, 140, ALLEGRO_ALIGN_CENTER, "NO PAPAI NOEL" );

    /* Desenha o botão "JOGAR". */
    al_draw_filled_rectangle( 540, 280, 740, 350, corJogar );
    al_draw_rectangle( 540, 280, 740, 350,
        al_map_rgb( 255, 255, 255 ), 2 );
    al_draw_text( fonte, al_map_rgb( 255, 255, 255 ), 640,
        300, ALLEGRO_ALIGN_CENTER, "JOGAR" );

    /* Desenha o botão "SAIR". */
    al_draw_filled_rectangle( 540, 390, 740, 460, corSair );
    al_draw_rectangle( 540, 390, 740, 460,
        al_map_rgb( 255, 255, 255 ), 2 );
    al_draw_text( fonte, al_map_rgb( 255, 255, 255 ), 640,
        410, ALLEGRO_ALIGN_CENTER, "SAIR" );
}

void desenhaTelaVitoria() {
    /* Desenha o fundo da tela de vitória. */
    al_draw_scaled_bitmap( backgroundMenu, 0, 0,
        al_get_bitmap_width( backgroundMenu ),
        al_get_bitmap_height( backgroundMenu ),
        0, 0, SCREEN_W, SCREEN_H, 0 );

    /* Coloca "VOCE VENCEU!" na tela. */
    al_draw_text( fonte, al_map_rgb( 255, 255, 255 ),
        SCREEN_W / 2, SCREEN_H / 2 - 50,
        ALLEGRO_ALIGN_CENTER, "VOCE VENCEU!" );

    /* Coloca a mensagem de "PRESSIONE ENTER" na tela,
     * aguardando a ação do jogador. */
    al_draw_text( fonte, al_map_rgb( 255, 255, 255 ),
        SCREEN_W / 2, SCREEN_H / 2 + 20,
        ALLEGRO_ALIGN_CENTER, "PRESSIONE ENTER" );
}

void desenhaTelaGameOver() {
    /* Desenha o fundo da tela de Game Over. */
    al_draw_scaled_bitmap( backgroundMenu, 0, 0,
        al_get_bitmap_width( backgroundMenu ),
        al_get_bitmap_height( backgroundMenu ),
        0, 0, SCREEN_W, SCREEN_H, 0 );

    /* Coloca "GAME OVER" na tela. */
    al_draw_text( fonte, al_map_rgb( 255, 255, 255 ),
        SCREEN_W / 2, SCREEN_H / 2 - 50,
        ALLEGRO_ALIGN_CENTER, "GAME OVER" );

    /* Coloca a mensagem de "PRESSIONE ENTER" na tela,
     * aguardando a ação do jogador. */
    al_draw_text( fonte, al_map_rgb( 255, 255, 255 ),
        SCREEN_W / 2, SCREEN_H / 2 + 20,
        ALLEGRO_ALIGN_CENTER, "PRESSIONE ENTER" );
}

void desenhaVida( personagem *personagem ) {
    int i;
    int quantidadeCoracoes;

    /* Como a vida máxima do personagem é 20,
     * cada coração representa 4 pontos de vida.
     * Com isso, é calculada a quantidade de corações a serem colocados na tela. */
    quantidadeCoracoes = personagem -> vida / VIDA_POR_CORACAO;

    /* Desenha um coração ao lado do outro, no canto superior esquerdo. */
    for ( i = 0; i < quantidadeCoracoes; i++ ) {
        al_draw_bitmap( coracao, 10 + ( i * ( TAMANHO_CORACAO ) ), 10, 0 );
    }
}

void finalizaInterface() {
    /* Libera cada recurso somente se ele tiver sido carregado. */
    if ( coracao != NULL )
        al_destroy_bitmap( coracao );

    if ( backgroundMenu != NULL )
        al_destroy_bitmap( backgroundMenu );

    if ( fonte != NULL )
        al_destroy_font( fonte );

}
