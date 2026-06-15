#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "juego.h"
#include "mapas.h"

int main(){
    Jugador j = {0};
    j.fila    = 1;
    j.columna = 1;
    j.nivel   = 1;

    // calcular monedas del nivel 1
    int total_monedas = (int)contar_caracter((char*)nivel1, FILAS_MAPA * COLS_MAPA, 'M');

    char tecla;
    while(1) {
        system("cls");
        mostrar_hud(&j, total_monedas);
        imprimir_mapa(nivel1, &j);

        tecla = _getch();
        if (tecla == 'q' || tecla == 'Q') break;

        int resultado = mover_jugador(nivel1, &j, tecla);

        if (resultado == 1) {
            // nivel completado
            j.monedas_total += j.monedas_nivel;
            j.pasos_total   += j.pasos_nivel;
            printf("Nivel completado\n Monedas: %d/%d  Pasos: %d\n", j.monedas_nivel, total_monedas, j.pasos_nivel);
            printf("\tPresiona una tecla...\n");
            _getch();
            break;
        }
    }

    // puntaje final con nasm
    j.puntaje = (int)calcular_puntaje(j.monedas_total, j.pasos_total, j.nivel);

    system("cls");
    printf("\t------------------------------------\n");
    printf("\t  Juego completado\n");
    printf("\t  Monedas: %d\n", j.monedas_total);
    printf("\t  Pasos:   %d\n", j.pasos_total);
    printf("\t  Puntaje: %d\n", j.puntaje);
    printf("\t------------------------------------\n");

    system("pause");
    return 0;
}