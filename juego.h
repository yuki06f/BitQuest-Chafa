
#include <stdbool.h>

#ifndef JUEGO_H  
#define JUEGO_H 

// tamaño del mapa
#define FILAS_MAPA  60
#define COLS_MAPA   60

// tamaño solo de la ventana
#define FILAS_VISTA 20
#define COLS_VISTA  20

// simbolos
#define PARED    '#'
#define CAMINO   '.'
#define JUGADOR  'P'
#define MONEDA   'M'
#define LLAVE    'K'
#define PUERTA   'D'
#define SALIDA   'E'

typedef struct {
    int fila;           // posicion actual
    int columna;

    bool llave;    // 0 = no, 1 = si

    int monedas_nivel;        // en el nivel 
    int pasos_nivel;          // en el nivel actual

    int monedas_total;  // de todos los niveles
    int pasos_total;    // de todos los niveles

    int nivel;          // 1,2,3
    int puntaje;        
} Jugador;

void mostrar_hud(Jugador* j, int total_monedas);
void mostrar_resumen_nivel(Jugador* j, int total_monedas);
void mostrar_resumen_final(Jugador* j, int total_monedas_global);
void iniciar_nivel(char mapa[][COLS_MAPA], Jugador* j);

//prototipos de las nasm
extern long long contar_caracter(char *mapa, int total_celdas, char caracter);
extern long long validar_movimiento(char *mapa, int columnas, int fila, int columna);
extern long long calcular_puntaje(int monedas, int pasos, int niveles);
extern long long detectar_objeto(char *mapa, int columnas, int fila, int columna, char objeto);
extern long long contar_celdas_libres(char *mapa, int total_celdas);



///////
void imprimir_mapa(char mapa[][COLS_MAPA], Jugador* j);
int mover_jugador(char mapa[][COLS_MAPA], Jugador* j, char tecla);
void limpiar_celda(char mapa[][COLS_MAPA], int f, int c);
#endif