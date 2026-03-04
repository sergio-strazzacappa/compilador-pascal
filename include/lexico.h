#include "token.c"

#define MAX_PALABRAS_RESERVADAS (2048)

void inicializar_lexico(char *archivo_fuente);
Token obtener_siguiente_token();
void espacios();
void comentarios();
Token numero();
Token palabra();
Token especial();
Token buscar_lexema(char *lexema);
void mostrar_palabras_reservadas();
