#include <stdio.h>
#include <stdlib.h>
#include "error.h"

static const char *MENSAJES[] = {
    // Errores genericos
    "[ERROR] Se debe ingresar un solo archivo\n",
    "[ERROR] Uso <%s archivo.pas>\n",
    "[ERROR] Archivo %s no encontrado\n",

    // Errores léxicos
    "[ERROR] Comentario no cerrado en línea %zu\n",
    "[ERROR] Comentario no abierto en línea %zu\n",
    "[ERROR] Token no reconocido\n"
};

/* TODO: Comprobar que linea no sea NULL en los casos necesarios
 * Ir agregado cases para cada caso. Falta completar el caso en que recibe
 * una linea o los dos argumentos
 */
int mostrar_error(
    const cod_t codigo,
    const char *const archivo,
    const size_t *const linea) {

    size_t lon_mensajes = sizeof(MENSAJES) / sizeof(MENSAJES[0]);

    if (codigo < 0 || codigo >= lon_mensajes) {
        fprintf(stderr, "[ERROR] Código de error desconocido en %s\n",
            "mostrar_error(CodigoError, char *)");
        return EXIT_FAILURE;
    }

    switch (codigo) {
        // recibe archivo
        case ERR_USO:
        case ERR_NO_ARCHIVO:
            fprintf(stderr, MENSAJES[codigo], archivo);
            break;
        // recibe línea
        case ERR_COM_NO_CERRADO:
        case ERR_COM_NO_ABIERTO:
            fprintf(stderr, MENSAJES[codigo], *linea);
            break;
        // no recibe parámetros
        case ERR_UN_ARCHIVO:
        case ERR_TOKEN:
            fprintf(stderr, "%s", MENSAJES[codigo]);
            break;
        default:
            fprintf(stderr, "%s", MENSAJES[codigo]);
            break;
    }

    return EXIT_SUCCESS;
}
