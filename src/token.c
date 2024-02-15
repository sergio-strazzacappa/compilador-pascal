#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <err.h>
#include "token.h"

char* obtener_simbolo(Token t) {
    char* simbolo = "";
    int e = -1;

    if (!strcmp(t.etiqueta, "ASIGNACION")) {
        e = 1;
    } else if (!strcmp(t.etiqueta, "DOS_PUNTOS")) {
        e = 2;
    } else if (!strcmp(t.etiqueta, "PUNTO_Y_COMA")) {
        e = 3;
    } else if (!strcmp(t.etiqueta, "PUNTO")) {
        e = 4;
    } else if (!strcmp(t.etiqueta, "COMA")) {
        e = 5;
    } else if (!strcmp(t.etiqueta, "PARENTESIS_IZQUIERDO")) {
        e = 6;
    } else if (!strcmp(t.etiqueta, "PARENTESIS_DERECHO")) {
        e = 7;
    } else if (!strcmp(t.lexema, "MENOR_IGUAL")) {
        e = 8;
    } else if (!strcmp(t.lexema, "DISTINTO")) {
        e = 9;
    } else if (!strcmp(t.lexema, "MENOR")) {
        e = 10;
    } else if (!strcmp(t.lexema, "MAYOR_IGUAL")) {
        e = 11;
    } else if (!strcmp(t.lexema, "MAYOR")) {
        e = 12;
    } else if (!strcmp(t.lexema, "IGUAL")) {
        e = 13;
    } else if (!strcmp(t.lexema, "SUMA")) {
        e = 14;
    } else if (!strcmp(t.lexema, "RESTA")) {
        e = 15;
    } else if (!strcmp(t.lexema, "PRODUCTO")) {
        e = 16;
    } else if (!strcmp(t.lexema, "COCIENTE")) {
        e = 17;
    }

    switch(e) {
        case 1:
            simbolo = ":=";
            break;
        case 2:
            simbolo = ":";
            break;
        case 3:
            simbolo = ";";
            break;
        case 4:
            simbolo = ".";
            break;
        case 5:
            simbolo = ",";
            break;
        case 6:
            simbolo = "(";
            break;
        case 7:
            simbolo = ")";
            break;
        case 8:
            simbolo = "<=";
            break;
        case 9:
            simbolo = "<>";
            break;
        case 10:
            simbolo = "<";
            break;
        case 11:
            simbolo = ">=";
            break;
        case 12:
            simbolo = ">";
            break;
        case 13:
            simbolo = "=";
            break;
        case 14:
            simbolo = "+";
            break;
        case 15:
            simbolo = "-";
            break;
        case 16:
            simbolo = "*";
            break;
        case 17:
            simbolo = "/";
            break;
    }
    return simbolo;
}

// Liberar el espacio de memoria alocado a lexema en la función
// llamadora
char* obtener_lexema(Token t) {
    char *lexema;
    size_t max_size;

    max_size = sizeof(t.etiqueta) + sizeof(t.valor) + 1;
    lexema = malloc(sizeof(*lexema) + max_size);

    if (lexema == NULL) {
        err(EXIT_FAILURE, "malloc()");
    }

    switch (t.tipo) {
        case 1:
        case 4:
            lexema = obtener_simbolo(t);
            break;
        case 2:
            sprintf(lexema, "%ld", t.valor);
            break;
        case 3:
            strcpy(lexema, t.lexema);
            break;
    }
    return lexema;
}

// Liberar el espacio de memoria alocado a mensaje en la función
// llamadora
char* mostrar_token(Token t) {
    char *mensaje;
    size_t max_size;
    size_t valor_size;
    char *valor_s;

    max_size = strlen("[ Etiqueta: ") + sizeof(t.etiqueta) +
        strlen("\n  Valor: ") + sizeof(t.valor) +
        strlen("\n  Lexema: ") + sizeof(t.lexema) + strlen(" ]") + 1;
    mensaje = malloc(sizeof(*mensaje) + max_size);

    if (mensaje == NULL) {
        err(EXIT_FAILURE, "malloc()");
    }

    valor_size = sizeof(t.valor) + 1;
    valor_s = malloc(sizeof(*valor_s) + valor_size);

    if (valor_s == NULL) {
        err(EXIT_FAILURE, "malloc()");
    }

    strcpy(mensaje, "[ Etiqueta: ");
    strcat(mensaje, t.etiqueta);

    switch(t.tipo) {
        case 2:
            sprintf(valor_s, "%ld", t.valor);
            strcat(mensaje, "\n  Valor: ");
            strcat(mensaje, valor_s);
            free(valor_s);
            break;
        case 3:
        case 4:
            strcat(mensaje, "\n  Lexema: ");
            strcat(mensaje, t.lexema);
            break;
    }

    strcat(mensaje, " ]");

    return mensaje;
}
