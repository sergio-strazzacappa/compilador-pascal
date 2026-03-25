#ifndef LEXICO_H
#define LEXICO_H

#include <stdio.h>
#include "token.h"

int inicializar_lexico(FILE *f);
int obtener_siguiente_token(tok_t *token);
int espacios(void);
int comentarios(void);
int digitos(tok_t *token);
int palabra(tok_t *token);
int especial(tok_t *token);
int es_caracter_especial(char c);

#endif /* LEXICO_H */
