#ifndef SINTACTICO_H
#define SINTACTICO_H

#include <stdio.h>
#include "token.h"

int analizar(FILE *archivo_fuente);
int programa(void);
int lista_variables(void);
int lista_variables_1(void);
int lista_variables_2(void);
int tipo();
int declaracion_subprogramas();
int declaracion_subprogramas_1();
int funcion();
int procedimiento();
int parametros_formales();
int parametros_formales_1();
int parametros_formales_2();
int lista_sentencias();
int lista_sentencias_1();
int sentencia();
int sentencia_1();
int asignacion();
int alternativa();
int alternativa_1();
int repetitiva();
int sentencia_compuesta();
int escritura();
int lectura();
int expresion();
int expresion_1();
int termino_booleano();
int termino_booleano_1();
int factor_booleano();
int factor_booleano_1();
int expresion_simple();
int expresion_simple_1();
int termino();
int termino_1();
int factor();
int factor_1();
int factor_2();
int factor_4();
int factor_5();
int llamada_subprograma();
int lista_expresiones();
int lista_expresiones_1();
void to_upper_case(char *string, char *string_upper);
int match(tipo_t tok_t);
int match_palabra(char *lexema);
int match_simbolo(char *lexema);

#endif /* SINTACTICO_H */
