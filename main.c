#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#include "juego.h"
#include "mapas.h"

void posicion_inicial(char mapa[][COLS_MAPA], Jugador *j) {
    srand(time(NULL));
    do {
        j->fila    = rand() % (FILAS_MAPA - 2) + 1;
        j->columna = rand() % (COLS_MAPA - 2) + 1;
    } while (mapa[j->fila][j->columna] != CAMINO);
}

int main() {
    //mostrar pantalla de inicio
    mostrar_pantalla_inicio();

    Jugador j = {0};
    j.nivel = 1;

    // apuntadores a los 4 niveles
    char (*mapas[4])[COLS_MAPA] = { nivel1, nivel2, nivel3, nivel4 };

    int total_monedas_global = 0;

    while (j.nivel <= 4) {
        char (*mapa_actual)[COLS_MAPA] = mapas[j.nivel - 1];

        // inicializando
        j.monedas_nivel = 0;
        j.pasos_nivel   = 0;
        j.llave         = false;

        // posición aleatoria en celda libre
        posicion_inicial(mapa_actual, &j);

        // contar monedas del nivel con nasm
        int total_monedas = (int)contar_caracter((char*)mapa_actual, FILAS_MAPA * COLS_MAPA, 'M');

        // contar celdas libres nasm
        int celdas_libres = (int)contar_celdas_libres((char*)mapa_actual, FILAS_MAPA * COLS_MAPA);

        // loop del nivel
        while (true) {
            system("cls");
            mostrar_hud(&j, total_monedas);
            printf("\t  Celdas libres: %d\n", celdas_libres);
            imprimir_mapa(mapa_actual, &j);

            char tecla = _getch();
            if (tecla == 'q' || tecla == 'Q') goto fin;

            int resultado = mover_jugador(mapa_actual, &j, tecla);

            if (resultado == 1) {
                // estadisticas acumuladas
                j.monedas_total += j.monedas_nivel;
                j.pasos_total += j.pasos_nivel;
                total_monedas_global += total_monedas;

                mostrar_resumen_nivel(&j, total_monedas);
                j.nivel++;
                break;
            }
        }
    }

    // puntaje final con nasm
    j.puntaje = (int)calcular_puntaje(j.monedas_total, j.pasos_total, 4);

    //mostrar resumen final
    mostrar_resumen_nivel(&j, total_monedas_global);

fin:
    return 0;
}
