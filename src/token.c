#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "token.h"

/*
 * Recibe un puntero a un Token y devuelve un string que identifica a que tipo
 * de Token se refiere
 */
int obtener_token(const Token *tok, char *str) {
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
int obtener_numero(const Token *tok, char *str, size_t len) {
    str[0] = '\0';

    if (tok->tipo == TOK_NUM) {
        snprintf(str, len, "%ld", tok->data.valor);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

/*
 * Recibe un puntero a un Token y devuelve el lexema correspondiente a los
 * símbolos
 */
int obtener_lexema(const Token *tok, char *str) {
    const char *SYMBOLS[17] = {
        ":=", ":", ";", ".", ",", "(", ")",
        "<=", "<", ">=", ">", "=", "<>", "+", "-", "*", "/"
    };
    int index = -1;
    str[0] = '\0';

    switch (tok->tipo) {
        case TOK_ASIG:          index = 0;  break;
        case TOK_DOS_PUNTOS:    index = 1;  break;
        case TOK_PUNTO_Y_COMA:  index = 2;  break;
        case TOK_PUNTO:         index = 3;  break;
        case TOK_COMA:          index = 4;  break;
        case TOK_PAR_IZQ:       index = 5;  break;
        case TOK_PAR_DER:       index = 6;  break;
        case TOK_OP_REL:
            switch (tok->data.lexema) {
                case MENOR_IGUAL:   index = 7;  break;
                case MENOR:         index = 8;  break;
                case MAYOR_IGUAL:   index = 9;  break;
                case MAYOR:         index = 10; break;
                case IGUAL:         index = 11; break;
                case DISTINTO:      index = 12; break;
                default:
                    fprintf(stderr,
                        "[ERROR] Subtipo incorrecto para token %d\n",
                        tok->tipo);
                    return EXIT_FAILURE;
            }
            break;
        case TOK_ALG_AD:
            switch (tok->data.lexema) {
                case SUMA:  index = 13; break;
                case RESTA: index = 14; break;
                default:
                    fprintf(stderr,
                        "[ERROR] Subtipo incorrecto para token %d\n",
                        tok->tipo);
                    return EXIT_FAILURE;
            }
            break;
        case TOK_ALG_MUL:
            switch (tok->data.lexema) {
                case PRODUCTO:  index = 15; break;
                case COCIENTE:  index = 16; break;
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
    strcpy(str, SYMBOLS[index]);
    return EXIT_SUCCESS;
}

int obtener_info_token(const Token *tok, char *str, size_t len) {
    char buffer[256];
    char tipo_str[64];
    char detalle_str[512] = "";
    str[0] = '\0';

    if (obtener_token(tok, tipo_str) != EXIT_SUCCESS)
        tipo_str[0] = '\0';

    switch (tok->tipo) {
        case TOK_ID:
            // TODO
            break;
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
            if (obtener_lexema(tok, buffer) == EXIT_SUCCESS) {
                snprintf(detalle_str, sizeof(detalle_str), "\n Lexema: %s", buffer);
            }
            break;
        default:
            // TODO: Gestionar las palabras reservadas, incluyendo booleano y
            // tipo. Obtener sus correspondientes valores de la tabla de
            // símbolos
            break;
    }

    snprintf(str, len, "[ TIPO: %s%s\n Línea: %d ]",
        tipo_str, detalle_str, tok->linea);
    return EXIT_SUCCESS;
}
