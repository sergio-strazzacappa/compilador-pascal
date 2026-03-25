#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "token.h"
#include "error.h"
#include "ts.h"
#include "lexico.h"
//#include "sintactico.h"

/*
 * Uso: ./main archivo.pas
 */
int main(int argc, char **argv) {
    if (argc != 2) {
        // Cantidad de archivos incorrecto
        mostrar_error(ERR_UN_ARCHIVO, NULL, NULL);
        mostrar_error(ERR_USO, argv[0], NULL);
        return EXIT_FAILURE;
    }

    // Se lee el archivo fuente con éxito
    char *archivo_fuente = argv[1];
    printf("[INFO] Archivo leído: %s\n", archivo_fuente);

    // Se inicializa la tabla de símbolos
    if (inicializar_ts() == EXIT_FAILURE) {
        fprintf(stderr, "[ERROR] No se pudo inicializar la TS en %s\n",
            "main(int, char**)");
        return EXIT_FAILURE;
    }

    mostrar_ts();

    FILE *f = fopen(archivo_fuente, "r");
    if (f == NULL) {
        mostrar_error(ERR_NO_ARCHIVO, archivo_fuente, NULL);
        return EXIT_FAILURE;
    }

    inicializar_lexico(f);

    tok_t *t = (tok_t *)malloc(sizeof(tok_t));

    while (t->tipo != TOK_FIN) {
       obtener_siguiente_token(t);
    }
    //analizar(archivo_fuente);

    destruir_ts();
    return EXIT_SUCCESS;
}
