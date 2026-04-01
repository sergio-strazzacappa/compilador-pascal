#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "error.h"

static const char *MENSAJES[] = {
    // Errores genericos
    "[ERROR] Se debe ingresar un solo archivo\n",
    "[ERROR] Uso <%s archivo.pas>\n",
    "[ERROR] Archivo %s no encontrado\n",

    // Errores léxicos
    "[ERROR] Comentario no cerrado en línea %zu\n",
    "[ERROR] Comentario no abierto en línea %zu\n",
    "[ERROR] Token %c no reconocido en línea %zu\n"
};

int mostrar_error(
    const cod_t codigo,
    const char *const archivo,
    const char *const lexema,
    const size_t *const linea) {

    size_t lon_mensajes = sizeof(MENSAJES) / sizeof(MENSAJES[0]);

    assert(codigo >= 0 && codigo < lon_mensajes);

    switch (codigo) {
        // recibe archivo
        case ERR_USO:
        case ERR_NO_ARCHIVO:
            assert(archivo != NULL);

            fprintf(stderr, MENSAJES[codigo], archivo);
            break;

        // recibe línea
        case ERR_COM_NO_CERRADO:
        case ERR_COM_NO_ABIERTO:
            assert(linea != NULL);

            fprintf(stderr, MENSAJES[codigo], *linea);
            break;

        // recibe lexema y línea
        case ERR_TOKEN:
            assert(lexema != NULL);
            assert(linea != NULL);

            fprintf(stderr, MENSAJES[codigo], *lexema, *linea);
            break;

        // no recibe parámetros
        case ERR_UN_ARCHIVO:
            fprintf(stderr, "%s", MENSAJES[codigo]);
            break;
        default:
            fprintf(stderr, "%s", MENSAJES[codigo]);
            break;
    }

    return EXIT_SUCCESS;
}
