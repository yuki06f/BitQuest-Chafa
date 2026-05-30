#include <stdio.h>
#include <stdlib.h>

#include "juego.h"
#include "juego.c"
#include "mapas.h"

int main(){
    Jugador j;
    j.columna = 11;
    j.fila = 2;

    char tecla;
    while(true) {
        tecla = _getch();
        if (tecla == 'q' || tecla == 'Q') break;
        
        int resultado = mover_jugador(nivel1, &j, tecla);
        imprimir_mapa(nivel1, &j);
        
        if (resultado == 1) {
            printf("res: %d", resultado);
            break;
        }

    }
    return 0;
}