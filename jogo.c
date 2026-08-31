#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

#include "jogo.h"
#include "interface.h"

void processaTeclaPressionada( jogo *j, int tecla );
void processaTeclaSolta( jogo *j, int tecla );
void desenhaJogo( jogo *j );
void atualizaJogo( jogo *j );

int inicializaJogo( jogo *j ) {

    /* Inicializa o Allegro. */
    if ( !al_init() )
        return 0;

    /* Inicializa o teclado. */
    if ( !al_install_keyboard() )
        return 0;

    /* Inicializa o mouse. */
    if ( !al_install_mouse() )
        return 0;

    /* Inicializa o addon de imagens. */
    if ( !al_init_image_addon() )
        return 0;

    /* Inicializa os addons de fonte. */
    al_init_font_addon();
    al_init_ttf_addon();

    /* Cria a janela do jogo. */
    j -> display = al_create_display(
        SCREEN_W,
        SCREEN_H
    );

    if ( j -> display == NULL )
        return 0;

    /* Cria a fila de eventos. */
    j -> filaEventos = al_create_event_queue();

    if ( j -> filaEventos == NULL ) {

        al_destroy_display(
            j -> display
        );

        return 0;
    }

    /* Cria o temporizador. */
    j -> temporizador = al_create_timer(
        1.0 / FPS
    );

    if ( j -> temporizador == NULL ) {

        al_destroy_event_queue(
            j -> filaEventos
        );

        al_destroy_display(
            j -> display
        );

        return 0;
    }

    /* Registra os eventos da janela. */
    al_register_event_source(
        j -> filaEventos,
        al_get_display_event_source(
            j -> display
        )
    );

    /* Registra os eventos do teclado. */
    al_register_event_source(
        j -> filaEventos,
        al_get_keyboard_event_source()
    );

    /* Registra os eventos do mouse. */
    al_register_event_source(
        j -> filaEventos,
        al_get_mouse_event_source()
    );

    /* Registra os eventos do temporizador. */
    al_register_event_source(
        j -> filaEventos,
        al_get_timer_event_source(
            j -> temporizador
        )
    );

    /* Inicializa as variáveis do jogo. */
    j -> estado = estadoMenu;
    j -> rodando = 1;
    j -> atualizarTela = 0;
    j -> cameraX = CAMERA_MIN;

    /* Inicializa o mapa. */
    if ( !inicializaMapa(
        &( j -> faseAtual ) ) ) {

        /* Desfaz o que já tinha sido criado antes de falhar. */
        al_destroy_timer(
            j -> temporizador
        );

        al_destroy_event_queue(
            j -> filaEventos
        );

        al_destroy_display(
            j -> display
        );

        printf(
            "Erro ao inicializar o mapa.\n"
        );

        return 0;
    }

    /* Inicializa o personagem. */
    if ( !inicializaPersonagem(
        &( j -> personagem ) ) ) {

        /* Desfaz o que já tinha sido criado antes de falhar. */
        finalizaMapa(
            &( j -> faseAtual )
        );

        al_destroy_timer(
            j -> temporizador
        );

        al_destroy_event_queue(
            j -> filaEventos
        );

        al_destroy_display(
            j -> display
        );

        printf(
            "Erro ao inicializar o personagem.\n"
        );

        return 0;
    }

    /* Inicializa a interface. */
    if ( !inicializaInterface() ) {

        /* Desfaz o que já tinha sido criado antes de falhar. */
        finalizaPersonagem(
            &( j -> personagem )
        );

        finalizaMapa(
            &( j -> faseAtual )
        );

        al_destroy_timer(
            j -> temporizador
        );

        al_destroy_event_queue(
            j -> filaEventos
        );

        al_destroy_display(
            j -> display
        );

        printf(
            "Erro ao inicializar a interface.\n"
        );

        return 0;
    }

    /* Inicia o temporizador. */
    al_start_timer(
        j -> temporizador
    );

    return 1;
}

/* Processa uma tecla pressionada, ou seja, um evento de tecla. */
void processaTeclaPressionada( jogo *j, int tecla ) {

    /* O comportamento da tecla depende do estado atual do jogo. */
    switch ( j -> estado ) {

        case estadoMenu:

            /* Confirma a entrada no menu, indo para o jogo. */
            if ( tecla == ALLEGRO_KEY_ENTER )
                j -> estado = estadoJogando;

            /* Sai do jogo a partir do menu. */
            if ( tecla == ALLEGRO_KEY_ESCAPE )
                j -> rodando = 0;

            break;

        case estadoJogando:

            switch ( tecla ) {

                /* Move o personagem para a esquerda. */
                case ALLEGRO_KEY_A:

                    j -> personagem.velocidadeX = -VELOCIDADE_ANDAR;

                    break;

                /* Move o personagem para a direita. */
                case ALLEGRO_KEY_D:

                    j -> personagem.velocidadeX = VELOCIDADE_ANDAR;

                    break;

                /* Faz o personagem pular. */
                case ALLEGRO_KEY_SPACE:

                    pulaPersonagem(
                        &( j -> personagem )
                    );

                    break;

                /* Faz o personagem deslizar. */
                case ALLEGRO_KEY_S:

                    deslizaPersonagem(
                        &( j -> personagem )
                    );

                    break;

                /* Sai do jogo durante a partida. */
                case ALLEGRO_KEY_ESCAPE:

                    j -> rodando = 0;

                    break;
            }

            break;

        case estadoVitoria:
        case estadoGameOver:

            /* Volta ao menu a partir das telas de fim de jogo. */
            if ( tecla == ALLEGRO_KEY_ENTER ) {
                j -> estado = estadoMenu;
            }

            break;
    }
}

/* Processa uma tecla solta, ou seja, que foi liberada pelo jogador. */
void processaTeclaSolta( jogo *j, int tecla ) {

    switch ( tecla ) {

        /* Para o movimento apenas se ainda estava indo para a esquerda. */
        case ALLEGRO_KEY_A:

            if ( j -> personagem.velocidadeX < 0 )
                j -> personagem.velocidadeX = 0;

            break;

        /* Para o movimento apenas se ainda estava indo para a direita. */
        case ALLEGRO_KEY_D:

            if ( j -> personagem.velocidadeX > 0 )
                j -> personagem.velocidadeX = 0;

            break;
    }
}

/* Desenha todos os elementos do jogo. */
void desenhaJogo( jogo *j ) {

    /* Limpa a tela antes de desenhar o frame atual. */
    al_clear_to_color(
        al_map_rgb( 0, 0, 0 )
    );

    /* Desenha conteúdo diferente de acordo com o estado do jogo. */
    switch ( j -> estado ) {

        case estadoMenu: {

            ALLEGRO_MOUSE_STATE mouse;

            int hoverJogar;
            int hoverSair;

            al_get_mouse_state(
                &mouse
            );

            /* Verifica se o mouse está sobre o botão "JOGAR". */
            hoverJogar =
                mouse.x >= BOTAO_JOGAR_X &&
                mouse.x <= BOTAO_JOGAR_X + BOTAO_JOGAR_W &&
                mouse.y >= BOTAO_JOGAR_Y &&
                mouse.y <= BOTAO_JOGAR_Y + BOTAO_JOGAR_H;

            /* Verifica se o mouse está sobre o botão "SAIR". */
            hoverSair =
                mouse.x >= BOTAO_SAIR_X &&
                mouse.x <= BOTAO_SAIR_X + BOTAO_SAIR_W &&
                mouse.y >= BOTAO_SAIR_Y &&
                mouse.y <= BOTAO_SAIR_Y + BOTAO_SAIR_H;

            desenhaMenu(
                hoverJogar,
                hoverSair
            );

            break;
        }

        case estadoJogando:

            desenhaMapa(
                &( j -> faseAtual ),
                j -> cameraX
            );

            desenhaPersonagem(
                &( j -> personagem ),
                j -> cameraX
            );

            desenhaVida(
                &( j -> personagem )
            );

            break;

        case estadoVitoria:

            desenhaTelaVitoria();

            break;

        case estadoGameOver:

            desenhaTelaGameOver();

            break;
    }

    /* Mostra o que foi desenhado na tela. */
    al_flip_display();
}

/* Responsável por atualizar o jogo. */
void atualizaJogo( jogo *j ) {

    /* Só atualiza a lógica do jogo enquanto estiver jogando. */
    if ( j -> estado != estadoJogando )
        return;

    atualizaPersonagem(
        &( j -> personagem ),
        &( j -> faseAtual )
    );

    /* Atualiza a posição da câmera. */
    j -> cameraX =
        j -> personagem.x - SCREEN_W / 2;

    /* Limita a câmera para não passar dos limites do mapa. */
    if ( j -> cameraX < CAMERA_MIN )
        j -> cameraX = CAMERA_MIN;

    if ( j -> cameraX > CAMERA_MAX )
        j -> cameraX = CAMERA_MAX;

    /* Verifica derrota. */
    if ( j -> personagem.vida <= 0 ) {
        j -> estado = estadoGameOver;
    }

    /* Verifica vitória. */
    if ( j -> personagem.venceu ) {
        j -> estado = estadoVitoria;
    }
}

void executaJogo( jogo *j ) {

    ALLEGRO_EVENT evento;

    while ( j -> rodando ) {

        /* Aguarda o próximo evento da fila. */
        al_wait_for_event(
            j -> filaEventos,
            &evento
        );

        switch ( evento.type ) {

            /* Evento do temporizador: atualiza o jogo a cada frame. */
            case ALLEGRO_EVENT_TIMER:

                atualizaJogo( j );

                j -> atualizarTela = 1;

                break;

            /* Usuário fechou a janela. */
            case ALLEGRO_EVENT_DISPLAY_CLOSE:

                j -> rodando = 0;

                break;

            /* Tecla pressionada. */
            case ALLEGRO_EVENT_KEY_DOWN:

                processaTeclaPressionada(
                    j,
                    evento.keyboard.keycode
                );

                break;

            /* Tecla solta. */
            case ALLEGRO_EVENT_KEY_UP:

                processaTeclaSolta(
                    j,
                    evento.keyboard.keycode
                );

                break;

            /* Clique do mouse, usado apenas no menu. */
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:

                if ( j -> estado == estadoMenu ) {

                    /* Clicou no botão "JOGAR". */
                    if ( evento.mouse.x >= BOTAO_JOGAR_X &&
                         evento.mouse.x <= BOTAO_JOGAR_X + BOTAO_JOGAR_W &&
                         evento.mouse.y >= BOTAO_JOGAR_Y &&
                         evento.mouse.y <= BOTAO_JOGAR_Y + BOTAO_JOGAR_H )

                        j -> estado = estadoJogando;

                    /* Clicou no botão "SAIR". */
                    if ( evento.mouse.x >= BOTAO_SAIR_X &&
                         evento.mouse.x <= BOTAO_SAIR_X + BOTAO_SAIR_W &&
                         evento.mouse.y >= BOTAO_SAIR_Y &&
                         evento.mouse.y <= BOTAO_SAIR_Y + BOTAO_SAIR_H )

                        j -> rodando = 0;
                }

                break;
        }

        /* Só redesenha a tela quando não há mais eventos pendentes na fila. */
        if ( j -> atualizarTela &&
             al_is_event_queue_empty(
                 j -> filaEventos ) ) {

            desenhaJogo( j );

            j -> atualizarTela = 0;
        }
    }
}

void finalizaJogo( jogo *j ) {

    finalizaInterface();

    finalizaPersonagem(
        &( j -> personagem )
    );

    finalizaMapa(
        &( j -> faseAtual )
    );

    /* Libera cada recurso somente se ele tiver sido criado. */
    if ( j -> temporizador != NULL )
        al_destroy_timer(
            j -> temporizador
        );

    if ( j -> filaEventos != NULL )
        al_destroy_event_queue(
            j -> filaEventos
        );

    if ( j -> display != NULL )
        al_destroy_display(
            j -> display
        );
}
