#include <stdio.h>
#include "jogo.h"

int main() {

    jogo Deu_a_Louca_no_Papai_Noel;

    if ( !inicializaJogo( &Deu_a_Louca_no_Papai_Noel ) ) {
        printf( "Erro ao inicializar o jogo.\n" );
        
        return 1;
    }

    executaJogo( &Deu_a_Louca_no_Papai_Noel );

    finalizaJogo( &Deu_a_Louca_no_Papai_Noel );

    return 0;
}