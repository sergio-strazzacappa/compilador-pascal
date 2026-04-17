#ifndef SINTACTICO_H
#define SINTACTICO_H

#include <stdio.h>
#include "token.h"

int analizar(FILE *archivo_fuente);
int programa(void);
int lista_variables(void);
int lista_variables_1(void);
int lista_variables_2(void);
int tipo(void);
int declaracion_subprogramas(void);
int declaracion_subprogramas_1(void);
int funcion(void);
int procedimiento(void);
int parametros_formales(void);
int parametros_formales_1(void);
int parametros_formales_2(void);
int lista_sentencias(void);
int lista_sentencias_1(void);
int sentencia(void);
int sentencia_1(void);
int asignacion(void);
int alternativa(void);
int alternativa_1(void);
int repetitiva(void);
int sentencia_compuesta(void);
int escritura(void);
int lectura(void);
int expresion(void);
int expresion_1(void);
int termino_booleano(void);
int termino_booleano_1(void);
int factor_booleano(void);
int factor_booleano_1(void);
int expresion_simple(void);
int expresion_simple_1(void);
int termino(void);
int termino_1(void);
int factor(void);
int factor_1(void);
int factor_2(void);
int factor_3(void);
int factor_4(void);
int llamada_subprograma();
int lista_expresiones();
int lista_expresiones_1();
void to_upper_case(char *string, char *string_upper);
int match(tipo_t tok_t);
int match_palabra(char *lexema);
int match_simbolo(char *lexema);

#endif /* SINTACTICO_H */
