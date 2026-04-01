#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include "lexico.h"
#include "ts.h"
#include "error.h"

static FILE *programa_fuente;
static size_t linea;
static char siguiente_caracter;

int inicializar_lexico(FILE *f) {
    assert(f != NULL);

    programa_fuente = f;
    linea = 1;
    siguiente_caracter = fgetc(f);

    return EXIT_SUCCESS;
}

int obtener_siguiente_token(tok_t *token) {
    char c = siguiente_caracter;
    int token_encontrado = 0;

    assert(token != NULL);

    while (!token_encontrado && c != EOF) {
        if (isdigit(c)) {
            digitos(token);
            token_encontrado = 1;
        } else if (isalpha(c) || c == '_') {
            palabra(token);
            token_encontrado = 1;
        } else if (es_caracter_especial(c)) {
            especial(token);
            token_encontrado = 1;
        } else {
            // espacios, comentarios, saltos de línea
            switch (c) {
                case ' ':
                case '\t':
                case '\r':
                case '\n':
                    espacios();
                    break;
                case '{':
                    comentarios();
                    break;
                case '}':
                    mostrar_error(ERR_COM_NO_ABIERTO, NULL, NULL, &linea);
                    siguiente_caracter = fgetc(programa_fuente);
                    break;
                default:
                    mostrar_error(ERR_TOKEN, NULL, &c, &linea);
                    siguiente_caracter = fgetc(programa_fuente);
                    break;
            }
        }
        c = siguiente_caracter;
    }

    if (c == EOF) {
        token->tipo = TOK_FIN;
        token->linea = linea;
    }

    return EXIT_SUCCESS;    
}

// Elimina los espacios en blanco y saltos de línea
int espacios(void) {
    char c = siguiente_caracter;

    while (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
        if (c == '\n') {
            linea++;
        }
        siguiente_caracter = fgetc(programa_fuente);
        c = siguiente_caracter;
    }
    return EXIT_SUCCESS;
}

// Elimina los comentarios
int comentarios(void) {
    char c = siguiente_caracter;
    size_t linea_actual = linea;

    while (c != '}' && c != EOF) {
        siguiente_caracter = fgetc(programa_fuente);
        c = siguiente_caracter;

        if (c == '\n') {
            linea++;
        }

        if (c == EOF) {
            mostrar_error(ERR_COM_NO_CERRADO, NULL, NULL, &linea_actual); 
            return EXIT_SUCCESS;
        }
    }
    siguiente_caracter = fgetc(programa_fuente);
    return EXIT_SUCCESS;
}

// Lee digítos
int digitos(tok_t *token) {
    __int128_t valor = 0;
    char c = siguiente_caracter;
    int error = 0;

    do {
        if (!error)
            valor = (10 * valor) + (c - '0');

        if (valor >= (__int128_t)LONG_MAX + 1 && !error) {
            fprintf(stderr, "[ERROR] Número fuera de rango. Overflow\n");
            error = 1;
        }

        siguiente_caracter = fgetc(programa_fuente);
        c = siguiente_caracter;
    } while (isdigit(c));

    token->tipo = TOK_NUM;
    token->linea = linea;

    if (!error) {
        token->data_u.valor = (unsigned long)valor;
    } else {
        token->data_u.valor = 0;
    }

    return EXIT_SUCCESS;
}

// Lee palabras
int palabra(tok_t *token) {
    char palabra[MAX_LEXEMA_SIZE];
    char c = siguiente_caracter;
    size_t i = 0;
    int error = 0;

    // formar el lexema
    do {
        // checkeo de identificador demasiado largo, máximo 32 bits
        if (i >= MAX_LEXEMA_SIZE && !error) {
            fprintf(stderr,
                "[ERROR] Identificado muy largo. Máximo permitido %d\n",
                MAX_LEXEMA_SIZE);
            error = 1;
        }

        if (!error)
            palabra[i++] = toupper(siguiente_caracter);
        siguiente_caracter = fgetc(programa_fuente);
        c = siguiente_caracter;
    } while (isalpha(c) || isdigit(c) || c == '_');

    palabra[i] = '\0';

    // buscar el lexema en la tabla de símbolos
    int indice = buscar_ts(palabra);

    if (indice == -1) {
        // lexema no encontrado
        // almacenar lexema en la TS
        ts_entrada_t entrada;
        entrada.tipo = TOK_ID;
        entrada.lexema = (char *)malloc(MAX_LEXEMA_SIZE * sizeof(char));
        strncpy(entrada.lexema, palabra, MAX_LEXEMA_SIZE);
        indice = insertar_ts(entrada);

        // crear el token
        token->tipo = TOK_ID;
        token->linea = linea;
        token->data_u.ts_indice = indice;

        free(entrada.lexema);
    } else {
        // obtener la entrada de la TS
        const ts_entrada_t *e = buscar_ts_por_indice(indice);
        token->tipo = e->tipo;
        token->linea = linea;
        token->data_u.ts_indice = indice;
    }

    return EXIT_SUCCESS;
}

// Lee caracteres especiales
int especial(tok_t *token) {
    char c = siguiente_caracter;
    token->linea = linea;
    
    switch (c) {
        case ':':
            siguiente_caracter = fgetc(programa_fuente);
            c = siguiente_caracter;
            if (c == '=') {
                // Asignación
                token->tipo = TOK_ASIG;
                siguiente_caracter = fgetc(programa_fuente);
            } else {
                // Dos puntos
                token->tipo = TOK_DOS_PUNTOS;
            }
            break;
        case '<':
            siguiente_caracter = fgetc(programa_fuente);
            c = siguiente_caracter;
            if (c == '=') {
                // Menor igual
                token->tipo = TOK_OP_REL;
                token->data_u.subtipo = MENOR_IGUAL;
                siguiente_caracter = fgetc(programa_fuente);
            } else if (c == '>') {
                // Distinto
                token->tipo = TOK_OP_REL;
                token->data_u.subtipo = DISTINTO;
                siguiente_caracter = fgetc(programa_fuente);
            } else {
                // Menor
                token->tipo = TOK_OP_REL;
                token->data_u.subtipo = MENOR;
            }
            break;
        case '>':
            siguiente_caracter = fgetc(programa_fuente);
            c = siguiente_caracter;
            if (c == '=') {
                // Mayor igual
                token->tipo = TOK_OP_REL;
                token->data_u.subtipo = MAYOR_IGUAL;
                siguiente_caracter = fgetc(programa_fuente);
            } else {
                // Mayor
                token->tipo = TOK_OP_REL;
                token->data_u.subtipo = MAYOR;
            }
            break;
        case '=':
            // Igual
            siguiente_caracter = fgetc(programa_fuente);
            token->tipo = TOK_OP_REL;
            token->data_u.subtipo = IGUAL;
            break;
        case '+':
            // Suma
            siguiente_caracter = fgetc(programa_fuente);
            token->tipo = TOK_ALG_AD;
            token->data_u.subtipo = SUMA;
            break;
        case '-':
            // Resta
            siguiente_caracter = fgetc(programa_fuente);
            token->tipo = TOK_ALG_AD;
            token->data_u.subtipo = RESTA;
            break;
        case '*':
            // Producto
            siguiente_caracter = fgetc(programa_fuente);
            token->tipo = TOK_ALG_MUL;
            token->data_u.subtipo = PRODUCTO;
            break;
        case '/':
            // Cociente
            siguiente_caracter = fgetc(programa_fuente);
            token->tipo = TOK_ALG_MUL;
            token->data_u.subtipo = COCIENTE;
            break;
        case ';':
            // Punto y coma
            siguiente_caracter = fgetc(programa_fuente);
            token->tipo = TOK_PUNTO_Y_COMA;
            break;
        case '.':
            // Punto
            siguiente_caracter = fgetc(programa_fuente);
            token->tipo = TOK_PUNTO;
            break;
        case ',':
            // Coma
            siguiente_caracter = fgetc(programa_fuente);
            token->tipo = TOK_COMA;
            break;
        case '(':
            // Parentesis izquierdo
            siguiente_caracter = fgetc(programa_fuente);
            token->tipo = TOK_PAR_IZQ;
            break;
        case ')':
            // Parentesis derecho
            siguiente_caracter = fgetc(programa_fuente);
            token->tipo = TOK_PAR_DER;
            break;
        default:
            fprintf(stderr, "[ERROR] Símbolo no reconocido en %s\n",
                "especial()");
            break;
    }

    return EXIT_SUCCESS;
}

int es_caracter_especial(char c) {
    const char simbolos[13] = {
        ':', '<', '>', '=', '+', '-', '*', '/', ';', '.', ',', '(', ')'
    };

    for (int i = 0; i < 13; i++) {
        if (c == simbolos[i])
            return 1;
    }
    return 0;
}
