#include <stdio.h>
#include "lexico.c"

int main (int argc, char *argv[]) {
    if (argc != 2) {
        // Error al leer el archivo fuente
        printf("Falta el archivo fuente. \n");
        printf("Uso: <%s archivo.pas>\n", argv[0]);
        exit(1);
    }
    
    // Se lee el archivo fuente con éxito
    char *archivo_fuente = argv[1];

    inicializar_lexico(archivo_fuente);

    for (int i = 0; i < 100; i++) {
        obtener_siguiente_token();
    }

    mostrar_palabras_reservadas();
    return 0;
}
