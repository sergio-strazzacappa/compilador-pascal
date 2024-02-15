typedef struct Token {
    int tipo;       // 1 = Token, 2 = Numero, 3 = Palabra, 4 = Simbolo
    char *etiqueta; // Token
    long valor;     // Numero
    char *lexema;   // Palabra, Simbolo
} Token;

char* obtener_simbolo(Token t);
char* obtener_lexema(Token t);
char* mostrar_token(Token t);
