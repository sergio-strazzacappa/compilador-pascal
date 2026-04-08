#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "ts.h"
#include "sintactico.h"

/*
 * Uso: ./main archivo.pas
 */
int main(int argc, char **argv) {
    if (argc != 2) {
        // Cantidad de archivos incorrecto
        mostrar_error(ERR_UN_ARCHIVO, NULL, NULL, NULL);
        mostrar_error(ERR_USO, argv[0], NULL, NULL);

        return EXIT_FAILURE;
    }

    // Se lee el archivo fuente con éxito
    const char *archivo_fuente = argv[1];
    printf("[INFO] Archivo leído: %s\n", archivo_fuente);

    // Se inicializa la tabla de símbolos
    if (inicializar_ts() == EXIT_FAILURE) {
        fprintf(stderr, "[ERROR] No se pudo inicializar la TS en %s\n",
            "main(int, char**)");
        return EXIT_FAILURE;
    }

    FILE *f = fopen(archivo_fuente, "r");
    if (f == NULL) {
        mostrar_error(ERR_NO_ARCHIVO, archivo_fuente, NULL, NULL);

        return EXIT_FAILURE;
    }

    analizar(f);

    destruir_ts();
    fclose(f);

    return EXIT_SUCCESS;
}
