#include <stdio.h>
#include <stdlib.h>

#include "juego.h"
#include "juego.c"
#include "mapas.h"

void mostrar(){
    for (int i = 0; i < FILAS_MAPA; i++){
        for (int j = 0; j < COLS_MAPA; j++){
            printf("%c", nivel1[i][j]);
            if (j == 59) printf("\n");
        }
    }
}

int main(){
    mostrar();
    system("pause");
}