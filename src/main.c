#include <stdio.h>
#include <stdlib.h>
#include <token.h>
//#include "lexico.h"
//#include "sintactico.h"

int test_tokens() {
    printf("[INFO] Comenzando debug de Tokens\n");

    char info[542];

    // Test de número
    Token t1 = { .tipo = TOK_NUM, .linea = 10, .data.valor = 542 };

    // Test de operador relacional
    Token t2 = { .tipo = TOK_OP_REL, .linea = 11, .data.lexema = MENOR_IGUAL };

    // Test de palabra reservada
    Token t3 = { .tipo = TOK_BEGIN, .linea = 12 };

    // Test de identificador
    struct Entrada {
        char nombre[33];
    };

    struct Entrada mi_var = (struct Entrada){"contador_global"};
    Token t4 = { .tipo = TOK_ID, .linea = 13, .data.ptr_TS = (char *)&mi_var };

    // Test desconocido
    Token t5 = { .tipo = 999, .linea = 999 };

    // Test subtipo
    Token t6 = { .tipo = TOK_OP_REL, .linea = 7, .data.lexema = SUMA };

    Token *pruebas[] = {&t1, &t2, &t3, &t4, &t5, &t6};
    for (int i = 0; i < 6; i++) {
        if (obtener_info_token(pruebas[i], info, sizeof(info)) == EXIT_SUCCESS)
            printf("\tToken %d: \n%s\n", i + 1, info);
    }

    printf("[INFO] Finalizado debug de Tokens\n");

    return EXIT_SUCCESS;
}

/*
 * Uso: ./main archivo.pas
 */
int main (int argc, char **argv) {
    if (argc != 2) {
        // Error al leer el archivo fuente
        fprintf(stderr,
            "[ERROR] Compilador ejecutado con %d programas.\n", argc - 1);
        fprintf(stderr,
            "[ERROR] Necesita exactamente un programa a compilar.\n");
        fprintf(stderr,
            "[ERROR] Uso: <%s archivo.pas>\n", argv[0]);
        return EXIT_FAILURE;
    }
  
    // Se lee el archivo fuente con éxito
    char *archivo_fuente = argv[1];
    printf("[INFO] Archivo leído: %s\n", archivo_fuente);
    //analizar(archivo_fuente);
  
   test_tokens();

    return EXIT_SUCCESS;
}
