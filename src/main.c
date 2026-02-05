#include <stdio.h>
#include <stdlib.h>
#include "lexico.h"
//#include "sintactico.c"

/*
 * Uso: ./main archivo.pas
 */ 
int main (int argc, char *argv[]) {
    if (argc != 2) {
        // Error al leer el archivo fuente
        fprintf(stderr, "Compilador ejecutado con %d programas.\n", argc - 1);
        fprintf(stderr, "Necesita exactamente un programa a compilar.\n");
        fprintf(stderr, "Uso: <%s archivo.pas>\n", argv[0]);
        exit(1);
    }
    
    // Se lee el archivo fuente con éxito
    char *archivo_fuente = argv[1];
    printf("[INFO] Archivo leído: %s\n", archivo_fuente);
    //analizar(archivo_fuente);
    return 0;
}
