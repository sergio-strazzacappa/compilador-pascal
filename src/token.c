#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "token.h"

void obtener_simbolo(Token t, char *str) {
    int index = -1;
    str[0] = '\0';

    if (t.etiqueta == NULL) {
        fprintf(stderr, "[ERROR] El token no tiene etiqueta asignada\n");
        return;
    }

    if (strcmp(t.etiqueta, "ASIGNACION") == 0)
        index = 0;
    else if (strcmp(t.etiqueta, "DOS_PUNTOS") == 0)
        index = 1;
    else if (strcmp(t.etiqueta, "PUNTO_Y_COMA") == 0)
        index = 2;
    else if (strcmp(t.etiqueta, "PUNTO") == 0)
        index = 3;
    else if (strcmp(t.etiqueta, "COMA") == 0)
        index = 4;
    else if (strcmp(t.etiqueta, "PARENTESIS_IZQUIERDO") == 0)
        index = 5;
    else if (strcmp(t.etiqueta, "PARENTESIS_DERECHO") == 0)
        index = 6;
    else if (t.lexema == NULL) {
        fprintf(stderr, "[ERROR] El token no tiene un lexema asignado\n");
        return;
    }

    if (strcmp(t.lexema, "MENOR_IGUAL") == 0)
        index = 7;
    else if (strcmp(t.lexema, "DISTINTO") == 0)
        index = 8;
    else if (strcmp(t.lexema, "MENOR") == 0)
        index = 9;
    else if (strcmp(t.lexema, "MAYOR_IGUAL") == 0)
        index = 10;
    else if (strcmp(t.lexema, "MAYOR") == 0)
        index = 11;
    else if (strcmp(t.lexema, "IGUAL") == 0)
        index = 12;
    else if (strcmp(t.lexema, "SUMA") == 0)
        index = 13;
    else if (strcmp(t.lexema, "RESTA") == 0)
        index = 14;
    else if (strcmp(t.lexema, "PRODUCTO") == 0)
        index = 15;
    else if (strcmp(t.lexema, "COCIENTE") == 0)
        index = 16;
    else {
        fprintf(stderr, "[ERROR] El token no tiene un símbolo asignado\n");
        return;
    }

    strcpy(str, SYMBOLS[index]);
}

void obtener_lexema(Token t, char *str) {
    switch (t.tipo) {
        case TOKEN:
        case SIMBOLO:
            obtener_simbolo(t, str);
            break;
        case NUMERO:
            sprintf(str, "%ld", *t.valor);
            break;
        case PALABRA:
            strcpy(str, t.lexema);
            break;
    }
}

void obtener_info_token(Token t, char *str) {
    str[0] = '\0';

    strcpy(str, "[ Etiqueta: ");
    strcat(str, t.etiqueta);

    if (t.valor != NULL) {
        char valor_s[100];
        sprintf(valor_s, "%ld", *t.valor);
        strcat(str, "\n  Valor: ");
        strcat(str, valor_s);
    }

    if (t.lexema != NULL) {
        strcat(str, "\n  Lexema: ");
        strcat(str, t.lexema);
    }

    strcat(str, " ]\n");
}
