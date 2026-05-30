
#include <stdio.h>

#include "juego.h"
//asm
int validar_objeto(char celda, Jugador* j){
    switch (celda){
        case MONEDA:
            j->monedas_nivel++;
            break;
        case SALIDA:
            j->nivel++;
            return 1;
            break;
        case LLAVE:
            j->llave = true;
            break;
        case PUERTA:
            j->llave = false;
            break;
    }

    return 0;

}

void limpiar_celda(char mapa[][COLS_MAPA], int f, int c){
    mapa[f][c] = CAMINO;
}


//hechas en c

//inicio_fila = jugador.fila - (FILAS_VISTA / 2)
//inicio_col  = jugador.columna - (COLS_VISTA / 2)

void imprimir_mapa(char mapa[FILAS_MAPA][COLS_MAPA], Jugador* jug){
    int inicio_fila = jug->fila - (FILAS_VISTA / 2); 
    int inicio_col = jug->columna - (COLS_VISTA / 2);

    if (inicio_fila < 0) inicio_fila = 0;
    if (inicio_col  < 0) inicio_col  = 0;
    if (inicio_fila + FILAS_VISTA > FILAS_MAPA) inicio_fila = FILAS_MAPA - FILAS_VISTA;
    if (inicio_col  + COLS_VISTA  > COLS_MAPA)  inicio_col  = COLS_MAPA  - COLS_VISTA;

    for (int i = inicio_fila; i < inicio_fila + 20; i++){
        printf("\t\t");
        for(int j = inicio_col; j < inicio_col + 20; j++){
            if (i == jug->fila && j == jug->columna) printf("%c", 'P'); 
            else printf("%c", mapa[i][j]);
        }

        printf("\n");
    }
}


int mover_jugador(char mapa[][COLS_MAPA], Jugador* j, char tecla){
    int nueva_fila = j->fila;
    int nueva_col = j->columna;

    // u = up, d = down, l = left, r = right

    if (tecla == 'W' || tecla == 'w'){
        nueva_fila--;
    }
    else if (tecla == 'S' || tecla == 's'){
        nueva_fila++;
    }
    else if (tecla == 'A' || tecla == 'a'){
        nueva_col--;
    }
    else if (tecla == 'D' || tecla == 'd'){
        nueva_col++;
    }

    char celda = mapa[nueva_fila][nueva_col];
    int n;
    
    if (celda == PUERTA && j->llave == false) return 0;
    
    else if (celda != PARED) {
        n =  validar_objeto(celda, j);

        if (celda == MONEDA || celda == LLAVE || celda == CAMINO)
            limpiar_celda(mapa, nueva_fila, nueva_col);

        // mover
        j->fila    = nueva_fila;
        j->columna = nueva_col;
        j->pasos_nivel++;

        return n;
        
    }

    return 0;
}