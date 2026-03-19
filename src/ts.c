#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "ts.h"

static ts_entrada_t *TS; // Arreglo de entradas
static size_t size = TS_SIZE_INICIAL;
static size_t ocupado = 0;

static const char *palabras_reservadas[N_PALABRAS_RESERVADAS] = {
    "PROGRAM", "FUNCTION", "PROCEDURE", "BEGIN", "END",
    "VAR", "IF", "THEN", "ELSE", "WHILE", "DO", "OR",
    "AND", "NOT", "INTEGER", "BOOLEAN", "TRUE", "FALSE",
    "READ", "WRITE"
};

/*
 * Carga en la TS las palabras reservadas
 */
int inicializar_ts(void) {
    TS = (ts_entrada_t *)calloc(TS_SIZE_INICIAL, sizeof(ts_entrada_t));

    if (TS == NULL) {
        fprintf(stderr, "[ERROR] Fallo en asignar memoria para la TS en %s\n",
            "inicializar_ts()");
        return EXIT_FAILURE;
    }


    for (size_t i = 0; i < N_PALABRAS_RESERVADAS; i++) {
        ts_entrada_t e;
        e.tipo = TOKENS[i];
        e.lexema = (char *)palabras_reservadas[i];

        if (insertar_ts(e)) {
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

/*
 * Busca el lexema pasado por parametro en la TS y devuelve su indice o -1 si
 * no se encuentra
 */
int buscar_ts(const char *const lexema) {
    for (size_t i = 0; i < ocupado; i++) {
        if (strcmp(lexema, TS[i].lexema) == 0) {
            return i;
        }
    }
    return -1 ;
}

/*
 * Devuelve el lexema y el tipo de token del indice pasado por parametro.
 * El puntero devuelto puede quedar invalido si se redimensiona la TS y se
 * hace un realloc()
 */
ts_entrada_t *buscar_ts_por_indice(const size_t indice) {
    if (indice >= ocupado) {
        fprintf(stderr, "[ERROR] Indice fuera de rango en %s\n",
            "buscar_ts_por_indice(int)");
        return NULL;
    }

    return &TS[indice];
}

/*
 * Inserta una entrada en la TS y devuelve el indice correspondiente
 */
int insertar_ts(const ts_entrada_t entrada) {
    size_t indice = buscar_ts(entrada.lexema);

    if (indice != -1) {
        return indice;
    }

    if (ocupado >= size) {
        if (redimensionar_ts() == EXIT_FAILURE) {
            return -1;
        }
    }

    TS[ocupado].lexema = (char *)malloc(MAX_LEXEMA_SIZE);

    if (TS[ocupado].lexema == NULL) {
        fprintf(stderr,
            "[ERROR] Fallo en asignar memoria para un lexema en %s\n",
            "insertar_ts(EntradaTS, int *)");
        return -1;
    }

    TS[ocupado].tipo = entrada.tipo;
    strncpy(TS[ocupado].lexema, entrada.lexema, MAX_LEXEMA_SIZE - 1);
    TS[ocupado].lexema[MAX_LEXEMA_SIZE - 1] = '\0';

    ocupado++;
    return ocupado - 1;
}

int redimensionar_ts(void) {
    ts_entrada_t *ptr = realloc(TS, size * 2 * sizeof(ts_entrada_t));

    if (ptr == NULL) {
        fprintf(stderr, "[ERROR] Fallo en redimensionar la TS en %s\n",
            "redimensionar_ts()");
        return EXIT_FAILURE;
    }

    TS = ptr;
    size *= 2;

    return EXIT_SUCCESS;
}

int destruir_ts(void) {
    for (size_t i = 0; i < ocupado; i++)
        free(TS[i].lexema);
    free(TS);

    return EXIT_SUCCESS;
}

int mostrar_ts(void) {
    printf("[INFO] Tabla de símbolos. Tamaño máximo: %ld\n", size);

    for (size_t i = 0; i < ocupado; i++) {
        ts_entrada_t e = TS[i];

        printf("\t%s\n", e.lexema);
    }
    return EXIT_SUCCESS;
}
