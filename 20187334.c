/****************************************************/
/* Programacion para mecatronicos                   */
/* Nombre: David Mireles Mateo                      */
/* Matricula: 2018-7334                              */
/* Seccion: Miercoles                                 */
/* Practica: Primer Parcial                         */
/* Fecha: 06/10/2026                                */
/* Link Practica: https://github.com/David030899/parcial-c-20187334 */
/****************************************************/

#include <stdio.h>

int main(void) {
    int N, M, L, U;
    int matriz[30][30];
    int eventosColumna[30] = {0};
    int eventosFila[30] = {0};
    int impactoFila[30] = {0};
    int rachaFila[30] = {0};
    int inicioFila[30] = {0};
    int i, j;
    int totalEventos = 0;
    int prioridad = -1;
    int columnaDestacada = -1;

    /* Lectura de dimensiones y limites */
    if (scanf("%d %d %d %d", &N, &M, &L, &U) != 4) {
        printf("ERROR\n");
        return 0;
    }

    /* Validacion de dimensiones y limites */
    if (N < 1 || N > 30 || M < 1 || M > 30 ||
        L < 0 || L > 1000 || U < 0 || U > 1000 || L > U) {
        printf("ERROR\n");
        return 0;
    }

    /* Lectura y validacion de la matriz */
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            if (scanf("%d", &matriz[i][j]) != 1 ||
                matriz[i][j] < 0 || matriz[i][j] > 1000) {
                printf("ERROR\n");
                return 0;
            }
        }
    }

    /* Analisis por fila y conteo por columna */
    for (i = 0; i < N; i++) {
        int rachaActual = 0;
        int inicioActual = 0;

        for (j = 0; j < M; j++) {
            int x = matriz[i][j];

            if (x < L || x > U) {
                int impacto = (x < L) ? (L - x) : (x - U);

                eventosFila[i]++;
                impactoFila[i] += impacto;
                eventosColumna[j]++;
                totalEventos++;

                if (rachaActual == 0) {
                    inicioActual = j + 1;
                }

                rachaActual++;

                /* Solo se actualiza si es mayor:
                   asi se conserva la racha maxima que inicio antes. */
                if (rachaActual > rachaFila[i]) {
                    rachaFila[i] = rachaActual;
                    inicioFila[i] = inicioActual;
                }
            } else {
                rachaActual = 0;
            }
        }
    }

    /* Seleccion de la fila prioritaria */
    if (totalEventos > 0) {
        for (i = 0; i < N; i++) {
            if (eventosFila[i] > 0) {
                if (prioridad == -1 ||
                    rachaFila[i] > rachaFila[prioridad] ||
                    (rachaFila[i] == rachaFila[prioridad] &&
                     impactoFila[i] > impactoFila[prioridad]) ||
                    (rachaFila[i] == rachaFila[prioridad] &&
                     impactoFila[i] == impactoFila[prioridad] &&
                     eventosFila[i] > eventosFila[prioridad])) {
                    prioridad = i;
                }
            }
        }

        /* Seleccion de la columna con mas eventos.
           En empate se conserva la primera (menor numero). */
        for (j = 0; j < M; j++) {
            if (columnaDestacada == -1 ||
                eventosColumna[j] > eventosColumna[columnaDestacada]) {
                columnaDestacada = j;
            }
        }
    }

    /* Salida exacta solicitada */
    for (i = 0; i < N; i++) {
        printf("FILA %d EVENTOS %d IMPACTO %d RACHA %d INICIO %d\n",
               i + 1, eventosFila[i], impactoFila[i],
               rachaFila[i], inicioFila[i]);
    }

    printf("COLUMNAS");
    for (j = 0; j < M; j++) {
        printf(" %d", eventosColumna[j]);
    }
    printf("\n");

    printf("PRIORIDAD %d\n", prioridad == -1 ? 0 : prioridad + 1);
    printf("COLUMNA %d\n", columnaDestacada == -1 ? 0 : columnaDestacada + 1);

    return 0;
}
