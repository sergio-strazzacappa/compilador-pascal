#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ts.h>
#include "token.h"

tipo_t const TOKENS[N_PALABRAS_RESERVADAS] = {
    TOK_PROGRAM, TOK_FUNCTION, TOK_PROCEDURE, TOK_BEGIN, TOK_END, TOK_VAR,
    TOK_IF, TOK_THEN, TOK_ELSE, TOK_WHILE, TOK_DO, TOK_OR, TOK_AND,
    TOK_NOT, TOK_T, TOK_T, TOK_BOOL, TOK_BOOL, TOK_READ, TOK_WRITE
};

/*
 * Recibe un puntero a un Token y devuelve un string que identifica a que tipo
 * de Token se refiere
 */
int obtener_lexema(const tok_t *const tok, char *str) {
    str[0] = '\0';

    switch (tok->tipo) {
        case TOK_ID:            strcpy(str, "IDENTIFICADOR");               break;
        case TOK_NUM:           strcpy(str, "NUMERO");                      break;
        case TOK_BOOL:          strcpy(str, "BOOLEANO");                    break;
        case TOK_T:             strcpy(str, "TIPO");                        break;
        case TOK_PROGRAM:       strcpy(str, "PROGRAM");                     break;
        case TOK_FUNCTION:      strcpy(str, "FUNCTION");                    break;
        case TOK_PROCEDURE:     strcpy(str, "PROCEDURE");                   break;
        case TOK_BEGIN:         strcpy(str, "BEGIN");                       break;
        case TOK_END:           strcpy(str, "END");                         break;
        case TOK_VAR:           strcpy(str, "VAR");                         break;
        case TOK_WRITE:         strcpy(str, "WRITE");                       break;
        case TOK_READ:          strcpy(str, "READ");                        break;
        case TOK_IF:            strcpy(str, "IF");                          break;
        case TOK_THEN:          strcpy(str, "THEN");                        break;
        case TOK_ELSE:          strcpy(str, "ELSE");                        break;
        case TOK_WHILE:         strcpy(str, "WHILE");                       break;
        case TOK_DO:            strcpy(str, "DO");                          break;
        case TOK_ASIG:          strcpy(str, "ASIGNACIÓN");                  break;
        case TOK_OR:            strcpy(str, "OR");                          break;
        case TOK_AND:           strcpy(str, "AND");                         break;
        case TOK_OP_REL:        strcpy(str, "OPERADOR RELACIONAL");         break;
        case TOK_ALG_AD:        strcpy(str, "ALGEBRAICO ADITIVO");          break;
        case TOK_ALG_MUL:       strcpy(str, "ALGEBRAICO_MULTIPLICATIVO");   break;
        case TOK_NOT:           strcpy(str, "NOT");                         break;
        case TOK_PUNTO_Y_COMA:  strcpy(str, "PUNTO_Y_COMA");                break;
        case TOK_PUNTO:         strcpy(str, "PUNTO");                       break;
        case TOK_COMA:          strcpy(str, "COMA");                        break;
        case TOK_DOS_PUNTOS:    strcpy(str, "DOS_PUNTOS");                  break;
        case TOK_PAR_IZQ:       strcpy(str, "PARENTESIS_IZQUIERDO");        break;
        case TOK_PAR_DER:       strcpy(str, "PARENTESIS_DERECHO");          break;
        default:
            fprintf(stderr,
                "[ERROR] Token %d no tiene un tipo válido\n",
                tok->tipo);
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/*
 * Recibe un puntero a un token y devuelve un string con el valor númerico del
 * token
 */
int obtener_numero(const tok_t *const tok, char *str, const size_t len) {
    str[0] = '\0';

    if (tok->tipo == TOK_NUM) {
        snprintf(str, len, "%ld", tok->data_u.valor);
        return EXIT_SUCCESS;
    }

    fprintf(stderr, "[ERROR] El token no es un número\n");
    return EXIT_FAILURE;
}

/*
 * Recibe un puntero a un Token y devuelve el lexema correspondiente a los
 * símbolos
 */
int obtener_lexema_sim(const tok_t *const tok, char *str) {
    const char *SIMBOLOS[17] = {
        ":=", ":", ";", ".", ",", "(", ")",
        "<=", "<", ">=", ">", "=", "<>", "+", "-", "*", "/"
    };
    int indice = -1;
    str[0] = '\0';

    switch (tok->tipo) {
        case TOK_ASIG:          indice = 0;  break;
        case TOK_DOS_PUNTOS:    indice = 1;  break;
        case TOK_PUNTO_Y_COMA:  indice = 2;  break;
        case TOK_PUNTO:         indice = 3;  break;
        case TOK_COMA:          indice = 4;  break;
        case TOK_PAR_IZQ:       indice = 5;  break;
        case TOK_PAR_DER:       indice = 6;  break;
        case TOK_OP_REL:
            switch (tok->data_u.subtipo) {
                case MENOR_IGUAL:   indice = 7;  break;
                case MENOR:         indice = 8;  break;
                case MAYOR_IGUAL:   indice = 9;  break;
                case MAYOR:         indice = 10; break;
                case IGUAL:         indice = 11; break;
                case DISTINTO:      indice = 12; break;
                default:
                    fprintf(stderr,
                        "[ERROR] Subtipo incorrecto para token %d\n",
                        tok->tipo);
                    return EXIT_FAILURE;
            }
            break;
        case TOK_ALG_AD:
            switch (tok->data_u.subtipo) {
                case SUMA:  indice = 13; break;
                case RESTA: indice = 14; break;
                default:
                    fprintf(stderr,
                        "[ERROR] Subtipo incorrecto para token %d\n",
                        tok->tipo);
                    return EXIT_FAILURE;
            }
            break;
        case TOK_ALG_MUL:
            switch (tok->data_u.subtipo) {
                case PRODUCTO:  indice = 15; break;
                case COCIENTE:  indice = 16; break;
                default:
                    fprintf(stderr,
                        "[ERROR] Subtipo incorrecto para token %d\n",
                        tok->tipo);
                    return EXIT_FAILURE;
            }
            break;
        default:
            fprintf(stderr,
                    "[ERROR] El token %d no tiene un símbolo válido\n",
                    tok->tipo);
            return EXIT_FAILURE;
    }

    strcpy(str, SIMBOLOS[indice]);
    return EXIT_SUCCESS;
}

int obtener_info_token(const tok_t *const tok, char *str, const size_t len) {
    char buffer[256];
    char tipo_str[64];
    char detalle_str[512] = "";
    str[0] = '\0';

    if (obtener_lexema(tok, tipo_str) != EXIT_SUCCESS)
        tipo_str[0] = '\0';

    switch (tok->tipo) {
        case TOK_NUM:
            obtener_numero(tok, buffer, sizeof(buffer));
            snprintf(detalle_str, sizeof(detalle_str), "\n Valor: %s", buffer);
            break;
        case TOK_ASIG:
        case TOK_OP_REL:
        case TOK_ALG_AD:
        case TOK_ALG_MUL:
        case TOK_PUNTO_Y_COMA:
        case TOK_PUNTO:
        case TOK_COMA:
        case TOK_DOS_PUNTOS:
        case TOK_PAR_IZQ:
        case TOK_PAR_DER:
            if (obtener_lexema_sim(tok, buffer) == EXIT_SUCCESS) {
                snprintf(detalle_str, sizeof(detalle_str), "\n Lexema: %s", buffer);
            }
            break;
        default:
            {
                ts_entrada_t *e = buscar_ts_por_indice(tok->data_u.ts_indice);

                if (e == NULL) {
                    fprintf(stderr, "[ERROR] Token no encontrado\n");
                    return EXIT_FAILURE;
                }

                snprintf(
                    detalle_str, sizeof(detalle_str), "\n Lexema: %s", e->lexema);
                break;
            }
    }

    snprintf(str, len, "[ TIPO: %s%s\n Línea: %d ]",
        tipo_str, detalle_str, tok->linea);
    return EXIT_SUCCESS;
}
