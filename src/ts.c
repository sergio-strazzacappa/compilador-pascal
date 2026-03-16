#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ts.h"

static EntradaTS *TS; // Arreglo de entradas 
static size_t size = TS_SIZE_INICIAL; 
static size_t ocupado = 0;

static const char *palabras_reservadas[N_PALABRAS_RESERVADAS] = {
    "PROGRAM", "FUNCTION", "PROCEDURE", "BEGIN", "END",
    "VAR", "IF", "THEN", "ELSE", "WHILE", "DO", "OR",
    "AND", "NOT", "INTEGER", "BOOLEAN", "TRUE", "FALSE",
    "READ", "WRITE"
};

int inicializar_ts(void) {
    TS = (EntradaTS *)calloc(TS_SIZE_INICIAL, sizeof(EntradaTS));

    if (TS == NULL) {
        fprintf(stderr, "[ERROR] Fallo en asignar memoria para la TS en %s\n",
            "inicializar_ts()");
        return EXIT_FAILURE;
    }
    
    for (int i = 0; i < N_PALABRAS_RESERVADAS; i++) {
        // TODO: Añadir el tipo de token
        EntradaTS e;
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
    for (int i = 0; i < ocupado; i++) {
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
EntradaTS *buscar_ts_por_indice(const int indice) {
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
int insertar_ts(const EntradaTS entrada) {
    if (buscar_ts(entrada.lexema) != -1) {
        return EXIT_SUCCESS;
    }

    if (ocupado >= size) {
        if (redimensionar_ts() == EXIT_FAILURE) {
            return EXIT_FAILURE;
        }
    }

    TS[ocupado].lexema = (char *)malloc(MAX_LEXEMA_SIZE);

    if (TS[ocupado].lexema == NULL) {
        fprintf(stderr,
            "[ERROR] Fallo en asignar memoria para un lexema en %s\n",
            "insertar_ts(EntradaTS, int *)");
        return EXIT_FAILURE;
    }

    // TODO: Copiar el tipo de token
    strncpy(TS[ocupado].lexema, entrada.lexema, MAX_LEXEMA_SIZE - 1);
    TS[ocupado].lexema[MAX_LEXEMA_SIZE - 1] = '\0';

    ocupado++;

    return EXIT_SUCCESS;
}

int redimensionar_ts(void) {
    EntradaTS *ptr = realloc(TS, size * 2 * sizeof(EntradaTS));

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
    for (int i = 0; i < ocupado; i++)
        free(TS[i].lexema);
    free(TS);

    return EXIT_SUCCESS;
}

int mostrar_ts(void) {
    printf("[INFO] Tabla de símbolos. Tamaño máximo: %ld\n", size);

    for (int i = 0; i < ocupado; i++) {
        EntradaTS e = TS[i];

        printf("\t%s\n", e.lexema);
    }

    return EXIT_SUCCESS;
}
