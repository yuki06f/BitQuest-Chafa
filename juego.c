
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "juego.h"

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
        // actualizar llave y monedas
        if (celda == LLAVE) {
            j->llave = true;
            limpiar_celda(mapa, nueva_fila, nueva_col);
        }
        else if (celda == MONEDA) {
            j->monedas_nivel++;
            limpiar_celda(mapa, nueva_fila, nueva_col);
        }
        else if (celda == SALIDA) {
            j->fila    = nueva_fila;
            j->columna = nueva_col;
            j->pasos_nivel++;
            return 1;  // nivel completado
        }

        j->fila    = nueva_fila;
        j->columna = nueva_col;
        j->pasos_nivel++;
        return 0;
    }

    return 0;
}

//info hud del jugador
void mostrar_hud(Jugador* j, int total_monedas){
    printf("\n");
    printf("\t----------------------------------------\n");
    printf("\t               BIT QUEST                \n");
    printf("\t----------------------------------------\n");
    printf("\t  Nivel: %d\n", j->nivel);
    printf("\t  Llave: %s\n", j->llave ? "SI [K]" : "NO");
    printf("\t  Monedas: %d / %d\n", j->monedas_nivel, total_monedas);
    printf("\t  Pasos en nivel: %d\n", j->pasos_nivel);
    printf("\t----------------------------------------\n");
    printf("\t  [W,A,S,D] Moverse  |  [Q] Salir\n");
    printf("\t----------------------------------------\n");
}

void mostrar_resumen_nivel(Jugador* j, int total_monedas) {
    system("cls");
    printf("\t----------------------------------------\n");
    printf("\t         NIVEL %d COMPLETADO\n", j->nivel);
    printf("\t----------------------------------------\n");
    printf("\t  Monedas recolectadas: %d / %d\n", j->monedas_nivel, total_monedas);
    printf("\t  Pasos realizados: %d\n", j->pasos_nivel);
    printf("\t----------------------------------------\n");
    printf("\t  Presiona cualquier tecla...\n");
    _getch();
}

void mostrar_resumen_final(Jugador* j, int total_monedas_global) {
    printf("\t----------------------------------------\n");
    printf("\t           JUEGO COMPLETADO\n");
    printf("\t----------------------------------------\n");
    printf("\t  Monedas totales: %d / %d\n", j->monedas_total, total_monedas_global);
    printf("\t  Pasos totales: %d\n", j->pasos_total);
    printf("\t  Niveles completados: %d\n", j->nivel - 1);
    printf("\t  Puntaje final: %d\n", j->puntaje);
    printf("\t----------------------------------------\n");
}