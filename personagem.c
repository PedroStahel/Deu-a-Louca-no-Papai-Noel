#include <stdio.h>
#include <string.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "personagem.h"
#include "constantes.h"
#include "mapa.h"

int quantidadeFramesAnimacao( estadoAnimacao animacao ) {

    /* Cada estado de animação possui sua própria quantidade de frames. */
    switch ( animacao ) {

        case animacaoParado:
            return FRAMES_PARADO;

        case animacaoAndando:
            return FRAMES_ANDAR;

        case animacaoPulando:
            return FRAMES_PULO;

        case animacaoDeslizando:
            return FRAMES_DESLIZE;

        case animacaoMorrendo:
            return FRAMES_MORTE;
    }

    return 0;
}

/* Carrega uma sequência de sprites. */
int carregaAnimacao( ALLEGRO_BITMAP **animacao,
                     const char *diretorio,
                     int quantidadeFrames ) {

    char caminho[256];
    int i;

    /* Monta o caminho de cada frame e carrega o bitmap. */
    for ( i = 0; i < quantidadeFrames; i++ ) {

        sprintf( caminho,
                 "assets/santasprites/png/%s/%d.png",
                 diretorio,
                 i + 1 );

        animacao[ i ] = al_load_bitmap( caminho );

        /* Falha ao carregar algum frame. */
        if ( animacao[ i ] == NULL ) {
            return 0;
        }
    }

    return 1;
}

/* Libera uma sequência de sprites. */
void destroiAnimacao( ALLEGRO_BITMAP **animacao,
                      int quantidadeFrames ) {

    int i;

    /* Destroi cada bitmap carregado e zera o ponteiro. */
    for ( i = 0; i < quantidadeFrames; i++ ) {

        if ( animacao[ i ] != NULL ) {
            al_destroy_bitmap( animacao[ i ] );
            animacao[ i ] = NULL;
        }
    }
}

int inicializaPersonagem( personagem *papaiNoel ) {

    /* Posição inicial no mapa. */
    papaiNoel -> x = TILE_SIZE;
    papaiNoel -> y = TILE_SIZE * SPAWN_LINHA;

    /* Velocidade inicial zerada. */
    papaiNoel -> velocidadeX = 0;
    papaiNoel -> velocidadeY = 0;

    /* Dimensões do personagem em tela. */
    papaiNoel -> largura = TILE_SIZE;
    papaiNoel -> altura = TILE_SIZE;

    papaiNoel -> vida = VIDA_MAXIMA;

    /* Começa "pulando" para forçar a checagem de colisão com o chão. */
    papaiNoel -> pulando = 1;

    papaiNoel -> venceu = 0;

    /* Habilidades e estados desligados por padrão. */
    papaiNoel -> possuiPuloDuplo = 0;
    papaiNoel -> podeUsarSegundoPulo = 0;

    papaiNoel -> deslizando = 0;

    papaiNoel -> invencivel = 0;

    papaiNoel -> olhandoDireita = 1;

    papaiNoel -> animacaoAtual = animacaoParado;

    papaiNoel -> frameAtual = 0;
    papaiNoel -> contadorAnimacao = 0;

    /* Carrega cada conjunto de sprites do personagem. */
    if ( !carregaAnimacao(
            papaiNoel -> parado,
            "Parado",
            FRAMES_PARADO ) ) {

        return 0;
    }

    if ( !carregaAnimacao(
            papaiNoel -> andando,
            "Corrida",
            FRAMES_ANDAR ) ) {

        return 0;
    }

    if ( !carregaAnimacao(
            papaiNoel -> pulandoFrames,
            "Pulo",
            FRAMES_PULO ) ) {

        return 0;
    }

    if ( !carregaAnimacao(
            papaiNoel -> deslizandoFrames,
            "Deslize",
            FRAMES_DESLIZE ) ) {

        return 0;
    }

    if ( !carregaAnimacao(
            papaiNoel -> morrendo,
            "Morte",
            FRAMES_MORTE ) ) {

        return 0;
    }

    return 1;
}

void atualizaAnimacao( personagem *papaiNoel ) {

    int quantidadeFrames;

    papaiNoel -> contadorAnimacao++;

    /* Ainda não é hora de trocar de frame. */
    if ( papaiNoel -> contadorAnimacao < TEMPO_ANIMACAO ) {
        return;
    }

    papaiNoel -> contadorAnimacao = 0;

    quantidadeFrames = quantidadeFramesAnimacao(
        papaiNoel -> animacaoAtual );

    /* A animação de morte não entra em loop. */
    if ( papaiNoel -> animacaoAtual ==
         animacaoMorrendo ) {

        if ( papaiNoel -> frameAtual <
             quantidadeFrames - 1 ) {

            papaiNoel -> frameAtual++;
        }

        return;
    }

    /* Demais animações ficam em loop. */
    papaiNoel -> frameAtual++;

    if ( papaiNoel -> frameAtual >=
         quantidadeFrames ) {

        papaiNoel -> frameAtual = 0;
    }
}

/* Aplica a gravidade ao personagem. */
void aplicaGravidade( personagem *papaiNoel ) {

    papaiNoel -> velocidadeY += GRAVIDADE;

    /* Limita a velocidade de queda. */
    if ( papaiNoel -> velocidadeY > VELOCIDADE_MAX_Y ) {
        papaiNoel -> velocidadeY = VELOCIDADE_MAX_Y;
    }
}

/* Atualiza a colisão horizontal. */
void colisaoHorizontal( personagem *papaiNoel,
                        mapa *faseAtual ) {

    int linhaSuperior;
    int linhaInferior;

    int colunaEsquerda;
    int colunaDireita;

    float esquerda;
    float direita;
    float topo;
    float base;

    /* Move o personagem no eixo X antes de checar colisão. */
    papaiNoel->x += papaiNoel->velocidadeX;

    /* Calcula os limites da hitbox. */
    esquerda =
        papaiNoel->x + HITBOX_OFFSET_X;

    direita =
        esquerda + HITBOX_LARGURA;

    topo =
        papaiNoel->y + HITBOX_OFFSET_Y;

    base =
        topo + HITBOX_ALTURA;

    /* Converte os limites da hitbox em linhas e colunas da matriz. */
    linhaSuperior =
        (int) topo / TILE_SIZE;

    linhaInferior =
        (int) ( base - 1 ) / TILE_SIZE;

    colunaEsquerda =
        (int) esquerda / TILE_SIZE;

    colunaDireita =
        (int) ( direita - 1 ) / TILE_SIZE;

    /* Colisão andando para a direita. */
    if ( papaiNoel->velocidadeX > 0 ) {

        if ( tileSolido(
                 faseAtual,
                 linhaSuperior,
                 colunaDireita ) ||
             tileSolido(
                 faseAtual,
                 linhaInferior,
                 colunaDireita ) ) {

            /* Encosta o personagem na borda esquerda do tile sólido. */
            papaiNoel->x =
                colunaDireita * TILE_SIZE
                - HITBOX_LARGURA
                - HITBOX_OFFSET_X;

            papaiNoel->velocidadeX = 0;
        }
    }

    /* Colisão andando para a esquerda. */
    else if ( papaiNoel->velocidadeX < 0 ) {

        if ( tileSolido(
                 faseAtual,
                 linhaSuperior,
                 colunaEsquerda ) ||
             tileSolido(
                 faseAtual,
                 linhaInferior,
                 colunaEsquerda ) ) {

            /* Encosta o personagem na borda direita do tile sólido. */
            papaiNoel->x =
                ( colunaEsquerda + 1 ) * TILE_SIZE
                - HITBOX_OFFSET_X;

            papaiNoel->velocidadeX = 0;
        }
    }
}

/* Atualiza a colisão vertical. */
void colisaoVertical( personagem *papaiNoel,
                      mapa *faseAtual ) {

    int linhaSuperior;
    int linhaInferior;

    int colunaEsquerda;
    int colunaDireita;

    float esquerda;
    float direita;
    float topo;
    float base;

    /* Move o personagem no eixo Y antes de checar colisão. */
    papaiNoel->y += papaiNoel->velocidadeY;

    /* Calcula os limites da hitbox. */
    esquerda =
        papaiNoel->x + HITBOX_OFFSET_X;

    direita =
        esquerda + HITBOX_LARGURA;

    topo =
        papaiNoel->y + HITBOX_OFFSET_Y;

    base =
        topo + HITBOX_ALTURA;

    /* Converte os limites da hitbox em linhas e colunas da matriz. */
    linhaSuperior =
        (int) topo / TILE_SIZE;

    linhaInferior =
        (int) ( base - 1 ) / TILE_SIZE;

    colunaEsquerda =
        (int) esquerda / TILE_SIZE;

    colunaDireita =
        (int) ( direita - 1 ) / TILE_SIZE;

    /* Colisão caindo. */
    if ( papaiNoel->velocidadeY > 0 ) {

        if ( tileSolido(
                 faseAtual,
                 linhaInferior,
                 colunaEsquerda ) ||

             tileSolido(
                 faseAtual,
                 linhaInferior,
                 colunaDireita ) ) {

            /* Encosta o personagem em cima do tile sólido. */
            papaiNoel->y =
                linhaInferior * TILE_SIZE
                - HITBOX_ALTURA
                - HITBOX_OFFSET_Y;

            papaiNoel->velocidadeY = 0;

            /* Pousou no chão: libera o pulo novamente. */
            papaiNoel->pulando = 0;
        }
    }

    /* Colisão subindo. */
    else if ( papaiNoel->velocidadeY < 0 ) {

        if ( tileSolido(
                 faseAtual,
                 linhaSuperior,
                 colunaEsquerda ) ||

             tileSolido(
                 faseAtual,
                 linhaSuperior,
                 colunaDireita ) ) {

            /* Encosta o personagem embaixo do tile sólido. */
            papaiNoel->y =
                ( linhaSuperior + 1 ) * TILE_SIZE
                - HITBOX_OFFSET_Y;

            papaiNoel->velocidadeY = 0;
        }
    }
}

/* Verifica interações com o mapa. */
void verificaInteracoes( personagem *papaiNoel,
                         mapa *faseAtual ) {

    int linhaSuperior;
    int linhaInferior;

    int colunaEsquerda;
    int colunaDireita;

    int linha;
    int coluna;

    int tile;

    float esquerda;
    float direita;
    float topo;
    float base;

    /* Calcula os limites da hitbox. */
    esquerda =
        papaiNoel->x + HITBOX_OFFSET_X;

    direita =
        esquerda + HITBOX_LARGURA;

    topo =
        papaiNoel->y + HITBOX_OFFSET_Y;

    base =
        topo + HITBOX_ALTURA;

    /* Converte os limites da hitbox em linhas e colunas da matriz. */
    linhaSuperior =
        (int) topo / TILE_SIZE;

    linhaInferior =
        (int) (base - 1) / TILE_SIZE;

    colunaEsquerda =
        (int) esquerda / TILE_SIZE;

    colunaDireita =
        (int) (direita - 1) / TILE_SIZE;

    /* Varre todos os tiles cobertos pela hitbox do personagem. */
    for ( linha = linhaSuperior;
          linha <= linhaInferior;
          linha++ ) {

        for ( coluna = colunaEsquerda;
              coluna <= colunaDireita;
              coluna++ ) {

            tile = obtemTile(
                faseAtual,
                linha,
                coluna );

            /* Espinhos. */
            if ( tilePerigoso(
                     faseAtual,
                     linha,
                     coluna ) ) {

                /* Só toma dano se não estiver invencível. */
                if ( papaiNoel->invencivel == 0 ) {

                    papaiNoel->vida-=
                        VIDA_POR_CORACAO;

                    /* Deixa o personagem invencível por um tempo. */
                    papaiNoel->invencivel = TEMPO_INVENCIBILIDADE;

                    /* Knockback horizontal. */
                    if ( papaiNoel->velocidadeX >= 0 )
                        papaiNoel->velocidadeX = -5;
                    else
                        papaiNoel->velocidadeX = 5;

                    /* Knockback vertical. */
                    papaiNoel->velocidadeY = -8;
                }
            }

            /* Itens coletáveis. */
            else if ( tileColetavel(
                          faseAtual,
                          linha,
                          coluna ) ) {

                switch ( tile ) {

                    /* Recupera vida e remove o tile do mapa. */
                    case TILE_VIDA:

                        papaiNoel->vida +=
                            VIDA_POR_CORACAO;

                        if ( papaiNoel->vida >
                             VIDA_MAXIMA ) {

                            papaiNoel->vida =
                                VIDA_MAXIMA;
                        }

                        alteraTile(
                            faseAtual,
                            linha,
                            coluna,
                            TILE_VAZIO );

                        break;

                    /* Concede o pulo duplo e remove o tile do mapa. */
                    case TILE_PULO_DUPLO:

                        papaiNoel->
                            possuiPuloDuplo = 1;
                        papaiNoel->
                            podeUsarSegundoPulo = 1;

                        alteraTile(
                            faseAtual,
                            linha,
                            coluna,
                            TILE_VAZIO );

                        break;

                    /* Marca a vitória, sem remover o tile. */
                    case TILE_VITORIA:

                        papaiNoel->venceu = 1;

                        break;
                }
            }
        }
    }
}

/* Altera a animação atual do personagem. */
void alteraAnimacao( personagem *papaiNoel,
                     estadoAnimacao novaAnimacao ) {

    /* Evita reiniciar uma animação que já está em curso. */
    if ( papaiNoel -> animacaoAtual == novaAnimacao ) {
        return;
    }

    papaiNoel -> animacaoAtual = novaAnimacao;

    papaiNoel -> frameAtual = 0;
    papaiNoel -> contadorAnimacao = 0;
}

void atualizaPersonagem( personagem *papaiNoel,
                         mapa *faseAtual ) {

    /* Se morreu, toca apenas a animação de morte. */
    if ( papaiNoel -> vida <= 0 ) {

        papaiNoel -> vida = 0;

        alteraAnimacao(
            papaiNoel,
            animacaoMorrendo );

        atualizaAnimacao(
            papaiNoel );

        return;
    }

    /* Aplica a gravidade. */
    aplicaGravidade( papaiNoel );

    /* Atualiza a posição horizontal. */
    colisaoHorizontal(
        papaiNoel,
        faseAtual );

    /* Atualiza a posição vertical. */
    colisaoVertical(
        papaiNoel,
        faseAtual );

    /* Verifica interações com o mapa. */
    verificaInteracoes(
        papaiNoel,
        faseAtual );

    /* Atualiza estados. */
    if ( papaiNoel -> invencivel > 0 )
        papaiNoel -> invencivel--;

    /* Conta o tempo restante de deslize. */
    if ( papaiNoel -> deslizando ) {

        papaiNoel -> tempoDeslize--;

        if ( papaiNoel -> tempoDeslize <= 0 ) {

            papaiNoel -> deslizando = 0;
            papaiNoel -> tempoDeslize = 0;
        }
    }

    /* Atualiza o estado da animação conforme a ação atual. */
    if ( papaiNoel -> pulando ) {

        alteraAnimacao(
            papaiNoel,
            animacaoPulando );
    }

    else if ( papaiNoel -> deslizando ) {

        alteraAnimacao(
            papaiNoel,
            animacaoDeslizando );
    }

    else if ( papaiNoel -> velocidadeX != 0 ) {

        alteraAnimacao(
            papaiNoel,
            animacaoAndando );
    }

    else {

        alteraAnimacao(
            papaiNoel,
            animacaoParado );
    }

    /* Atualiza o frame da animação. */
    atualizaAnimacao(
        papaiNoel );
}

void pulaPersonagem( personagem *papaiNoel ) {

    /* Primeiro pulo, a partir do chão. */
    if ( !papaiNoel -> pulando ) {

        papaiNoel -> velocidadeY = FORCA_PULO;

        papaiNoel -> pulando = 1;

        alteraAnimacao(
            papaiNoel,
            animacaoPulando );

        return;
    }

    /* Segundo pulo, só se possuir e ainda não tiver usado. */
    if ( papaiNoel -> possuiPuloDuplo &&
         papaiNoel -> podeUsarSegundoPulo ) {

        papaiNoel -> velocidadeY = FORCA_PULO;

        papaiNoel -> podeUsarSegundoPulo = 0;
        papaiNoel -> possuiPuloDuplo = 0;

        alteraAnimacao(
            papaiNoel,
            animacaoPulando );
    }
}

void deslizaPersonagem( personagem *papaiNoel ) {

    /* Não é possível deslizar enquanto está no ar. */
    if ( papaiNoel -> pulando ) {
        return;
    }

    /* Já está deslizando, ignora o pedido. */
    if ( papaiNoel -> deslizando ) {
        return;
    }

    papaiNoel -> deslizando = 1;
    papaiNoel -> tempoDeslize = TEMPO_DESLIZE;

    alteraAnimacao(
        papaiNoel,
        animacaoDeslizando );
}

void controlaPersonagem( personagem *papaiNoel,
                         ALLEGRO_KEYBOARD_STATE *teclado ) {
    
    papaiNoel->velocidadeX = 0;

    /* Move para a esquerda. */
    if ( al_key_down( teclado, ALLEGRO_KEY_A ) ) {

        papaiNoel->velocidadeX = -VELOCIDADE_ANDAR;
        papaiNoel->olhandoDireita = 0;
    }

    /* Move para a direita. */
    if ( al_key_down( teclado, ALLEGRO_KEY_D ) ) {

        papaiNoel->velocidadeX = VELOCIDADE_ANDAR;
        papaiNoel->olhandoDireita = 1;
    }
}

void desenhaPersonagem( personagem *papaiNoel,
                        float cameraX ) {

    ALLEGRO_BITMAP *sprite = NULL;
    int flags = 0;

    /* Escolhe o sprite de acordo com a animação atual. */
    switch ( papaiNoel -> animacaoAtual ) {

        case animacaoParado:
            sprite =
                papaiNoel -> parado[
                    papaiNoel -> frameAtual ];
            break;

        case animacaoAndando:
            sprite =
                papaiNoel -> andando[
                    papaiNoel -> frameAtual ];
            break;

        case animacaoPulando:
            sprite =
                papaiNoel -> pulandoFrames[
                    papaiNoel -> frameAtual ];
            break;

        case animacaoDeslizando:
            sprite =
                papaiNoel -> deslizandoFrames[
                    papaiNoel -> frameAtual ];
            break;

        case animacaoMorrendo:
            sprite =
                papaiNoel -> morrendo[
                    papaiNoel -> frameAtual ];
            break;
    }

    /* Nenhum sprite válido para desenhar. */
    if ( sprite == NULL ) {
        return;
    }

    /* Inverte o sprite horizontalmente se estiver olhando para a esquerda. */
    if ( !papaiNoel -> olhandoDireita ) {
        flags = ALLEGRO_FLIP_HORIZONTAL;
    }

    /* Desenha o sprite já considerando o deslocamento da câmera. */
    al_draw_scaled_bitmap(
        sprite,
        0,
        0,
        al_get_bitmap_width(sprite),
        al_get_bitmap_height(sprite),

        papaiNoel->x - cameraX,
        papaiNoel->y,

        papaiNoel->largura,
        papaiNoel->altura,

        flags
    );
}

void finalizaPersonagem( personagem *papaiNoel ) {

    /* Libera todos os conjuntos de sprites carregados. */
    destroiAnimacao(
        papaiNoel -> parado,
        FRAMES_PARADO );

    destroiAnimacao(
        papaiNoel -> andando,
        FRAMES_ANDAR );

    destroiAnimacao(
        papaiNoel -> pulandoFrames,
        FRAMES_PULO );

    destroiAnimacao(
        papaiNoel -> deslizandoFrames,
        FRAMES_DESLIZE );

    destroiAnimacao(
        papaiNoel -> morrendo,
        FRAMES_MORTE );
}
