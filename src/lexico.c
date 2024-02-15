#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "lexico.h"

FILE *programa;
int linea;
char siguiente_caracter;
Token palabras_reservadas[MAX_PALABRAS_RESERVADAS];
int cant_palabras_reservadas;

void inicializar_lexico(char *archivo_fuente) {
    cant_palabras_reservadas = 20;
    Token tokens[cant_palabras_reservadas];

    tokens[0].etiqueta  = "PROGRAM\0";
    tokens[1].etiqueta  = "FUNCTION\0";
    tokens[2].etiqueta  = "PROCEDURE\0";
    tokens[3].etiqueta  = "BEGIN\0";
    tokens[4].etiqueta  = "END\0";
    tokens[5].etiqueta  = "VAR\0";
    tokens[6].etiqueta  = "WRITE\0";
    tokens[7].etiqueta  = "READ\0";
    tokens[8].etiqueta  = "IF\0";
    tokens[9].etiqueta  = "THEN\0";
    tokens[10].etiqueta = "ELSE\0";
    tokens[11].etiqueta = "WHILE\0";
    tokens[12].etiqueta = "DO\0";
    tokens[13].etiqueta = "OR\0";
    tokens[14].etiqueta = "AND\0";
    tokens[15].etiqueta = "NOT\0";
    tokens[16].etiqueta = "TRUE\0";
    tokens[17].etiqueta = "FALSE\0";
    tokens[18].etiqueta = "INTEGER\0";
    tokens[19].etiqueta = "BOOLEAN\0";

    for (int i = 0; i < cant_palabras_reservadas; i++) {
        tokens[i].tipo = 3;
        tokens[i].valor = 0;
        tokens[i].lexema = tokens[i].etiqueta;
        palabras_reservadas[i] = tokens[i];
    }

    programa = fopen(archivo_fuente, "r");
    linea = 1;
    siguiente_caracter = ' ';

    if (programa == NULL) {
        printf("Error al leer el archivo fuente.\n");
        exit(1);
    }
    siguiente_caracter = fgetc(programa);
}

Token obtener_siguiente_token() {
    Token token;
    bool token_encontrado;
    bool caracter_extranio;

    token.tipo = -1;
    token.etiqueta = "\0";
    token.valor = 0;
    token.lexema = "\0";
    token_encontrado = false;
    caracter_extranio = true;

    while (siguiente_caracter == ' ' || siguiente_caracter == '\t' ||
            siguiente_caracter == '\n' || siguiente_caracter == '{' ||
            siguiente_caracter == '}') {
        // Caracteres ignorados
        if (siguiente_caracter == ' ' || siguiente_caracter == '\t' ||
                siguiente_caracter == '\n') {
            // Espacios y saltos de linea
            espacios();
        } else if (siguiente_caracter == '{') {
            // Comentarios
            comentarios();
        } else if (siguiente_caracter == '}') {
            printf("Error léxico: comentario no abierto en linea %d\n", linea);
            exit(1);
        }
    }
    while (!token_encontrado && siguiente_caracter != EOF) {
        if (!token_encontrado && siguiente_caracter >= '0' && 
                siguiente_caracter <= '9') {
            token = numero();
            token_encontrado = true;
            caracter_extranio = false;
        } else if (!token_encontrado && 
                (siguiente_caracter >= 'A' && siguiente_caracter <= 'Z') ||
                (siguiente_caracter == '_') || 
                (siguiente_caracter >= 'a' && siguiente_caracter <= 'z')) {
            token = palabra();
            token_encontrado = true;
            caracter_extranio = false;
        } else if (!token_encontrado &&
                (siguiente_caracter == ':' || siguiente_caracter == '<' ||
                 siguiente_caracter == '>' || siguiente_caracter == '=' ||
                 siguiente_caracter == '+' || siguiente_caracter == '-' ||
                 siguiente_caracter == '*' || siguiente_caracter == '/' ||
                 siguiente_caracter == ';' || siguiente_caracter == '.' ||
                 siguiente_caracter == ',' || siguiente_caracter == '(' ||
                 siguiente_caracter == ')')) {
            token = especial();
            token_encontrado = true;
            caracter_extranio = false;
        }
        if (caracter_extranio) {
            printf("Error léxico: token no reconocido en linea %d\n", linea);
            exit(1);
        }
    }
    printf("Token devuelto: %s, %s\n", token.etiqueta, token.lexema);
    return token;
}

void espacios() {
    while (siguiente_caracter == ' ' || siguiente_caracter == '\t' ||
            siguiente_caracter == '\n') {
        if (siguiente_caracter == '\n') {
            linea++;
        }
        siguiente_caracter = fgetc(programa);
    }
}

void comentarios() {
    while (siguiente_caracter != '}') {
        siguiente_caracter = fgetc(programa);
        if (siguiente_caracter == '\n') {
            linea++;
        }
        if (siguiente_caracter == EOF) {
            printf("Error léxico: comentario no cerrado en linea %d\n", linea);
            exit(1);
        }
    }
    siguiente_caracter = fgetc(programa);
}

Token numero() {
    Token token;
    int valor = 0;

    do {
        valor = (10 * valor) + (siguiente_caracter - 48);
        siguiente_caracter = fgetc(programa);
    } while (siguiente_caracter >= '0' && siguiente_caracter <= '9');

    token.tipo = 2;
    token.etiqueta = "Numero";
    token.valor = valor;
    token.lexema = "";

    return token;
}

Token palabra() {
    char *palabra = malloc(1024 * sizeof(char));
    char *palabra_mayuscula = malloc(1024 + sizeof(char));
    int i;
    Token token;
    // Formar el lexema
    i = 0;
    do {
        palabra[i] = siguiente_caracter;
        palabra_mayuscula[i] = toupper(siguiente_caracter);
        siguiente_caracter = fgetc(programa);
        i++;
    } while ((siguiente_caracter >= '0' && siguiente_caracter <= '9') ||
            (siguiente_caracter >= 'A' && siguiente_caracter <= 'Z') ||
            (siguiente_caracter >= 'a' && siguiente_caracter <= 'z') ||
            siguiente_caracter == '_'); 
    palabra[i] = '\0';
    palabra_mayuscula[i] = '\0';
    // Buscar lexema en la tabla de símbolos
    token = buscar_lexema(palabra_mayuscula);

    if (token.tipo == -1) {
        token.tipo = 3;
        token.etiqueta = "Identificador";
        token.valor = 0;
        token.lexema = palabra;
        palabras_reservadas[cant_palabras_reservadas] = token;
        cant_palabras_reservadas++;
    }   
    return token;
}

Token especial() {
    Token token;
    
    token.tipo = 4;
    token.valor = 0;

    if (siguiente_caracter == ':') {
        siguiente_caracter = fgetc(programa);
        if (siguiente_caracter == '=') {
            // Asignación
            token.etiqueta = "ASIGNACION\0";
            token.lexema = "\0";
            siguiente_caracter = fgetc(programa);
        } else {
            // Dos puntos
            token.etiqueta = "DOS_PUNTOS\0";
            token.lexema = "\0";
        }
    } else if (siguiente_caracter == '<') {
        siguiente_caracter = fgetc(programa);
        if (siguiente_caracter == '=') {
            // Menor igual
            token.etiqueta = "OPERADOR_RELACIONAL\0";
            token.lexema = "MENOR_IGUAL\0";
            siguiente_caracter = fgetc(programa);
        } else if (siguiente_caracter == '>') {
            // Distinto
            token.etiqueta = "OPERADOR_RELACIONAL\0";
            token.lexema = "DISTINTO\0";
            siguiente_caracter = fgetc(programa);
        } else {
            // Menor
            token.etiqueta = "OPERADOR_RELACIONAL\0";
            token.lexema = "MENOR\0";
        }
    } else if (siguiente_caracter == '>') {
        siguiente_caracter = fgetc(programa);
        if (siguiente_caracter == '=') {
            // Mayor igual
            token.etiqueta = "OPERADOR_RELACIONAL\0";
            token.lexema = "MAYOR_IGUAL\0";
            siguiente_caracter = fgetc(programa);
        } else {
            // Mayor
            token.etiqueta = "OPERADOR_RELACIONAL\0";
            token.lexema = "MAYOR\0";
        }
    } else if (siguiente_caracter == '=') {
        // Igual
        siguiente_caracter = fgetc(programa);
        token.etiqueta = "OPERADOR_RELACIONAL\0";
        token.lexema = "IGUAL\0";
    } else if (siguiente_caracter == '+') {
        // Suma
        siguiente_caracter = fgetc(programa);
        token.etiqueta = "ALGEBRAICO_ADITIVO\0";
        token.lexema = "SUMA\0";
    } else if (siguiente_caracter == '-') {
        // Resta
        siguiente_caracter = fgetc(programa);
        token.etiqueta = "ALGEBRAICO_ADITIVO\0";
        token.lexema = "RESTA\0";
    } else if (siguiente_caracter == '*') {
        // Producto
        siguiente_caracter = fgetc(programa);
        token.etiqueta = "ALGEBRAICO_MULTIPLICATIVO\0";
        token.lexema = "PRODUCTO\0";
    } else if (siguiente_caracter == '/') {
        // Cociente
        siguiente_caracter = fgetc(programa);
        token.etiqueta = "ALGEBRAICO_MULTIPLICATIVO\0";
        token.lexema = "COCIENTE\0";
    } else if (siguiente_caracter == ';') {
        // Punto y coma
        siguiente_caracter = fgetc(programa);
        token.etiqueta = "PUNTO_Y_COMA\0";
        token.lexema = "\0";
    } else if (siguiente_caracter == '.') {
        // Punto
        siguiente_caracter = fgetc(programa);
        token.etiqueta = "PUNTO\0";
        token.lexema = "\0";
    } else if (siguiente_caracter == ',') {
        // Coma
        siguiente_caracter = fgetc(programa);
        token.etiqueta = "COMA\0";
        token.lexema = "\0";
    } else if (siguiente_caracter == '(') {
        // Parentesis izquierdo
        siguiente_caracter = fgetc(programa);
        token.etiqueta = "PARENTESIS_IZQUIERDO\0";
        token.lexema = "\0";
    } else if (siguiente_caracter == ')') {
        // Parentesis derecho
        siguiente_caracter = fgetc(programa);
        token.etiqueta = "PARENTESIS_DERECHO\0";
        token.lexema = "\0";
    }
    return token;
}

Token buscar_lexema(char *lexema) {
    Token token;
    token.tipo = -1;

    for (int i = 0; i < cant_palabras_reservadas; i++) {
        char *palabra = malloc(1024 * sizeof(char));
        for (int j = 0; j < 1024; j++) {
            palabra[j] = toupper(palabras_reservadas[i].lexema[j]);
        }
        if (!strcmp(palabras_reservadas[i].lexema, lexema) ||
            !strcmp(palabra, lexema)) {
            // Lexema encontrado
            return palabras_reservadas[i];
        }
    }
    // Lexema no encontrado
    return token;
}

void mostrar_palabras_reservadas() {
    printf("Palabras reservadas:\n");
    printf("TOTAL= %d\n", cant_palabras_reservadas);
    for (int i = 0; i < cant_palabras_reservadas; i++) {
        printf("[ %s - ", palabras_reservadas[i].etiqueta);
        printf("%s ]\n", palabras_reservadas[i].lexema);
    }
}
