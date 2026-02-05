#ifndef TOKEN_H
#define TOKEN_H

/*
 * Archivo para manejar los tokens
 *
 * Cada token esta compuesto por:
 *      1. Tipo
 *      2. Etiqueta
 *      3. Valor
 *      4. Lexema
 *
 * El tipo puede ser:
 *      1. TOKEN
 *      2. NUMERO
 *      3. PALABRA
 *      4. SIMBOLO
 *
 * El tipo TOKEN corresponde a los signos de puntuación: asignación,
 * dos puntos, punto y coma, coma y los parentesís. El campo Etiqueta, Valor, y
 * Lexema se setean a NULL.
 *
 * El tipo NUMERO corresponde a constantes númericas enteras. El campo valor
 * tiene asignado la magnitud del número. El campo lexema se setean a NULL.
 *
 * El tipo PALABRA corresponde con los identificadores. El campo lexema tiene
 * asignado el string correspondiente al identificador. El campo valor se setea
 * a NULL.
 *
 * TODO: Los identificadores tienen que tener un puntero a la tabla de símbolos
 * y almacenar el lexema en dicha tabla.
 *
 * El tipo SIMBOLO tiene el resto de los operadores. El campo lexema tiene
 * asignado el string correspondiete. EL campo valor se setea a NULL.
 */

enum Tipo {
    TOKEN,
    NUMERO,
    PALABRA,
    SIMBOLO
};

typedef struct Token {
    enum Tipo tipo;
    char *etiqueta;
    long *valor;
    char *lexema;
} Token;

const char *SYMBOLS[17] = {
    ":=", ":", ";", ".", ",", "(", ")",
    "<=", "<>", "<", ">=", ">", "=", "+", "-", "*", "/"  
};

void obtener_simbolo(Token t, char *str);
void obtener_lexema(Token t, char *str);
void obtener_info_token(Token t, char *str);

#endif
