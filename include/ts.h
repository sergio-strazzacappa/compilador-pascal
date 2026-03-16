#ifndef TS_H
#define TS_H

#include <stdlib.h>
#include "token.h"

#define MAX_LEXEMA_SIZE 32
#define TS_SIZE_INICIAL 8
#define N_PALABRAS_RESERVADAS 20

/*
 * Inicialmente la TS se va a implementar como un simple array, con una
 * búsqueda de O(N) y inserción de O(1). Es un futuro se va a contemplar
 * la necesidad de implementarlo de forma mas eficiente
 *
 * El tamaño incial es de 8 y se va duplicando de forma dinamica en caso
 * de ser necesario
 */

typedef struct EntradaTS {
    // TODO: Completar con los campos faltantes
    enum tok_t tipo;
    char *lexema;
} EntradaTS;

int inicializar_ts(void);
int buscar_ts(const char *const lexema);
EntradaTS *buscar_ts_por_indice(const int indice);
int insertar_ts(const EntradaTS entrada);
int redimensionar_ts(void);
int destruir_ts(void);
int mostrar_ts(void);

#endif
