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
 */

#include <stddef.h>

typedef enum cod_e {
    ERR_UN_ARCHIVO      = 0,
    ERR_USO             = 1,
    ERR_NO_ARCHIVO      = 2,
    ERR_COM_NO_CERRADO  = 3,
    ERR_COM_NO_ABIERTO  = 4,
    ERR_TOKEN           = 5,
} cod_t;

int mostrar_error(
    const cod_t codigo,
    const char *const archivo,
    const size_t *const linea);

#endif
