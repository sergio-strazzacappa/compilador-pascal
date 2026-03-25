#ifndef TOKEN_H
#define TOKEN_H

/*
 * Archivo para manejar los tokens
 *
 * Los tokens pueden ser:
 *      1. Identificador (TOK_ID)
 *      2. Número (TOK_NUM)
 *      3. Booleano (TOK_BOOL)
 *      4. Tipo (TOK_T)
 *      5. PROGRAM (TOK_PROGRAM)
 *      6. FUNCTION (TOK_FUNCTION)
 *      7. PROCEDURE (TOK_PROCEDURE)
 *      8. BEGIN (TOK_BEGIN)
 *      9. END (TOK_END)
 *      10. VAR (TOK_VAR)
 *      11. WRITE (TOK_WRITE)
 *      12. READ (TOK_READ)
 *      13. IF (TOK_IF)
 *      14. THEN (TOK_THEN)
 *      15. ELSE (TOK_ELSE)
 *      16. WHILE (TOK_WHILE)
 *      17. DO (TOK_DO)
 *      18. ASIGNACIÓN (TOK_ASIG)
 *      19. OR (TOK_OR)
 *      20. AND (TOK_AND)
 *      21. Operador relacional (TOK_OP_REL)
 *      22. Algebraico aditivo (TOK_ALG_AD)
 *      23. Algebraico multiplicativo (TOK_ALG_MUL)
 *      24. NOT (TOK_NOT)
 *      25. ; (TOK_PUNTO_Y_COMA)
 *      26. . (TOK_PUNTO)
 *      27. , (TOK_COMA)
 *      28. : (TOK_DOS_PUNTOS)
 *      29. ( (TOK_PAR_IZQ)
 *      30. ) (TOK_PAR_DER)
 *
 * Cada token esta compuesto por:
 *      1. Tipo
 *      2. Linea
 *      2. Valor - Solo números
 *      3. Lexema - Algunos símbolos o palabras reservadas
 *      4. Puntero a la TS - Identificadores
 */

#include <stddef.h>

typedef enum tipo_e {
    TOK_ID, TOK_NUM, TOK_BOOL, TOK_T, TOK_PROGRAM, TOK_FUNCTION,
    TOK_PROCEDURE, TOK_BEGIN, TOK_END, TOK_VAR, TOK_WRITE, TOK_READ,
    TOK_IF, TOK_THEN, TOK_ELSE, TOK_WHILE, TOK_DO, TOK_ASIG, TOK_OR,
    TOK_AND, TOK_OP_REL, TOK_ALG_AD, TOK_ALG_MUL, TOK_NOT, TOK_PUNTO_Y_COMA,
    TOK_PUNTO, TOK_COMA, TOK_DOS_PUNTOS, TOK_PAR_IZQ, TOK_PAR_DER, TOK_FIN
} tipo_t;

typedef enum subtipo_e {
    MENOR_IGUAL, MENOR, MAYOR_IGUAL, MAYOR, IGUAL, DISTINTO,
    SUMA, RESTA, PRODUCTO, COCIENTE
} subtipo_t;

typedef struct token_s {
    tipo_t tipo;
    int linea;

    union {
        long valor;
        subtipo_t subtipo;
        int ts_indice;
    } data_u;
} tok_t;

extern const tipo_t TOKENS[];

int obtener_lexema(const tok_t *const tok, char *str);
int obtener_numero(const tok_t *const tok, char *str, const size_t len);
int obtener_lexema_sim(const tok_t *const tok, char *str);
int obtener_info_token(const tok_t *const tok, char *str, const size_t len);

#endif
