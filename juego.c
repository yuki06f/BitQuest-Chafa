
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h> //para los colores en la consola
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

    //para los colores
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = inicio_fila; i < inicio_fila + 20; i++){
        printf("\t\t");
        for(int j = inicio_col; j < inicio_col + 20; j++){

            if (i == jug->fila && j == jug->columna){
                SetConsoleTextAttribute(hConsole, 11); // color cyan para el jugador
                printf("%c", 'P'); 
            }else{
                char celda = mapa[i][j];
                if (celda == MONEDA) {
                    SetConsoleTextAttribute(hConsole, 14); // color amarillo para monedas                    
                    printf("%c", celda);
                } else if (celda == LLAVE) {
                    SetConsoleTextAttribute(hConsole, 13); // color magenta para llave
                    printf("%c", celda);
                } else if (celda == PUERTA) {
                    SetConsoleTextAttribute(hConsole, 12); // color rojo para puerta
                    printf("%c", celda);
                } else if (celda == SALIDA) {
                    SetConsoleTextAttribute(hConsole, 10); // color verde para salida
                    printf("%c", celda);
                } else if (celda == PARED) {
                    SetConsoleTextAttribute(hConsole, 8); // color gris para paredes
                    printf("%c", celda);
                } else {
                    SetConsoleTextAttribute(hConsole, 15); // color blanco para caminos
                    printf("%c", celda);
                }
            }
        }

        //regresa al color normal después de imprimir cada línea
        SetConsoleTextAttribute(hConsole, 7);
        printf("\n");
    }
    SetConsoleTextAttribute(hConsole, 7); // color blanco para el resto del texto
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

//pantalla de inicio
void mostrar_pantalla_inicio(){
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    SetConsoleTextAttribute(hConsole, 11); // Color Cyan
    printf("\n\n\n\n");
    printf("\t\t=========================================================\n");
    printf("\t\t  ____   ___  _____   ___    _   _   _____   ____    _____\n");
    printf("\t\t | __ ) |_ _||_   _| / _ \\  | | | | | ___|  / ___| |_   _|\n");
    printf("\t\t |  _\\\\  | |   | |  | | | | | | | | | |___  \\___\\    | | \n");
    printf("\t\t | |_) | | |   | |  | |_| | | | | | | |___   ___)|   | | \n");
    printf("\t\t |____/ |___|  |_|   \\__/\\\\  \\___/  |_____| |____/   |_| \n");
    printf("\t\t                                                         \n");
    printf("\t\t=========================================================\n\n");

    SetConsoleTextAttribute(hConsole, 14); // Color amarillo
    printf("\t\t         Presiona cualquier tecla para INICIAR...\n");
    
    SetConsoleTextAttribute(hConsole, 7); // Regresar al color normal
    _getch(); // Espera a que el jugador presione una tecla
}

//pantalla de victoria
void mostrar_pantalla_victoria(Jugador* j, int total_monedas_global){
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    SetConsoleTextAttribute(hConsole, 14); // Color amarillo
    printf("\n\n\n\n");
    printf("\t\t==========================================================\n");
    printf("\t\t   ____     _     _   _     _     ____   _____   _____ \n");
    printf("\t\t  / ___|   / \\   | \\ | |   / \\   / ___| |_   _| |  ___|\n");
    printf("\t\t | |  _   / _ \\  |  \\| |  / _ \\  \\__ _\\   | |   | |___ \n");
    printf("\t\t | |_| | / ___ \\ | |\\  | / ___ \\  ___) |  | |   | |___ \n");
    printf("\t\t  \\____//_/  \\_\\\\|_| \\_//_/  \\\\_\\|____/   |_|   |_____|\n");
    printf("\t\t                                                          \n");
    printf("\t\t==========================================================\n\n");

    // Mostramos las estadísticas finales aquí mismo en amarillo
    SetConsoleTextAttribute(hConsole, 14); 
    printf("\t\t       Monedas totales: %d / %d\n", j->monedas_total, total_monedas_global);
    printf("\t\t       Pasos totales: %d\n", j->pasos_total);
    printf("\t\t       Niveles completados: %d\n", j->nivel - 1);
    printf("\t\t       Puntaje final: %d\n", j->puntaje);
    printf("\t\t=======================================================\n\n");

    SetConsoleTextAttribute(hConsole, 15); // Blanco Brillante
    printf("\t\t         Presiona cualquier tecla para SALIR...\n");

    SetConsoleTextAttribute(hConsole, 7); // Regresar al color normal
    _getch();
}
