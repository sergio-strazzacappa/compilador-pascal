#ifndef ERROR_H
#define ERROR_H

/*
 * Archivo para manejar los errores durante todas las fases de compilación.
 *
 * Errores Genericos
 * -----------------
 * 0. Se debe ingresar un solo archivo
 * 1. Uso correcto del programa
 * 2. Archivo no encontrado
 *
 * Errores Léxicos
 * ---------------
 * 3. Comentario no cerrado
 * 4. Comentario no abierto
 * 5. Token no reconocido
 *
 * Errores Sintácticos
 * 6. Token fuera del programa
 * 7. Error match
 */

#include <stddef.h>

typedef enum cod_e {
    // Errores genericos
    ERR_UN_ARCHIVO      = 0,
    ERR_USO             = 1,
    ERR_NO_ARCHIVO      = 2,

    // Errores léxicos
    ERR_COM_NO_CERRADO  = 3,
    ERR_COM_NO_ABIERTO  = 4,
    ERR_TOKEN           = 5,

    // Errores sintácticos
    ERR_TOK_SOBRANTE    = 6,
    ERR_MATCH           = 7
} cod_t;

int mostrar_error(
    const cod_t codigo,
    const char *const archivo,
    const char *const lexema,
    const size_t *const linea);

#endif
