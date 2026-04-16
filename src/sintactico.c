#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "sintactico.h"
#include "lexico.h"
#include "error.h"
#include "ts.h"

static tok_t preanalisis;

int analizar(FILE *archivo_fuente) {
    inicializar_lexico(archivo_fuente);
    obtener_siguiente_token(&preanalisis);
    programa();
    printf("El programa no tiene errores sintácticos\n");

    return EXIT_SUCCESS;
}

int programa(void) {
    tipo_t t = preanalisis.tipo;

    match(TOK_PROGRAM);
    match(TOK_ID);
    match(TOK_PUNTO_Y_COMA);

    if (t == TOK_VAR) {
        match(TOK_VAR);
        lista_variables();
    }

    if (t == TOK_FUNCTION || t == TOK_PROCEDURE) {
        declaracion_subprogramas();
    }

    match(TOK_BEGIN);

    if (t == TOK_ID || t == TOK_IF || t == TOK_WHILE || t == TOK_WRITE ||
        t == TOK_READ || t == TOK_PUNTO_Y_COMA) {
        lista_sentencias();
    }

    match(TOK_END);
    match(TOK_PUNTO);

    // ERROR
    if (t == TOK_FIN) {
        // Tokens fuera del programa principal
        mostrar_error(ERR_TOK_SOBRANTE, NULL, NULL, &preanalisis.linea);

        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

int lista_variables(void) {
    match(TOK_ID);
    lista_variables_1();

    return EXIT_SUCCESS;
}

int lista_variables_1(void) {
    tipo_t t = preanalisis.tipo;

    if (t == TOK_COMA) {
        match(TOK_COMA);
        lista_variables();
    } else if (t == TOK_DOS_PUNTOS) {
        match(TOK_DOS_PUNTOS);
        tipo();
        match(TOK_PUNTO_Y_COMA);
        lista_variables_2();
    } else {
        // ERROR
        char *str = "Error en la declaración de variables."
                    "Se espera \",\" ó \":\"";
        mostrar_error(ERR_MATCH, NULL, str, NULL);
        
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

int lista_variables_2(void) {
    tipo_t t = preanalisis.tipo;

    if (t == TOK_ID) {
        lista_variables();
    }

    return EXIT_SUCCESS;
}

int tipo(void) {
    tipo_t t = preanalisis.tipo;
    const ts_entrada_t *e = buscar_ts_por_indice(preanalisis.data_u.ts_indice);

    if (t == TOK_T) {
        if (strcmp(e->lexema, "INTEGER") == 0) {
            match_palabra("INTEGER");
            match(TOK_T);
        } else if (strcmp(e->lexema, "BOOLEAN") == 0) {
            match_palabra("BOOLEAN");
            match(TOK_T);
        } else {
            assert(0);
        } 
    } else {
        // ERROR
        char *str = "Error en la declaración de variables. Se espera " 
                    "\"INTEGER\" ó \"BOOLEAN\"";

        mostrar_error(ERR_MATCH, NULL, str, NULL);

        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

int declaracion_subprogramas(void) {
    tipo_t t = preanalisis.tipo;

    if (t == TOK_FUNCTION) {
        funcion();
        declaracion_subprogramas_1();
    } else if (t == TOK_PROCEDURE) {
        procedimiento();
        declaracion_subprogramas_1();
    } else {
        // ERROR
        char *str = "Error sintáctico: error en definción de "
                    "función o procedimiento. "
                    "Se espera \"FUNCTION\" ó \"PROCEDURE\"";

        mostrar_error(ERR_MATCH, NULL, str, NULL);

        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

int declaracion_subprogramas_1(void) {
    tipo_t t = preanalisis.tipo;

    if (t == TOK_FUNCTION || t == TOK_PROCEDURE) {
        declaracion_subprogramas();
    }

    return EXIT_SUCCESS;
}

int funcion(void) {
    tipo_t t = preanalisis.tipo;

    match(TOK_FUNCTION);
    match(TOK_ID);

    if (t == TOK_PAR_IZQ) {
        match(TOK_PAR_IZQ);
        parametros_formales();
        match(TOK_PAR_DER);
    }

    match(TOK_DOS_PUNTOS);
    tipo();
    match(TOK_PUNTO_Y_COMA);

    if (t == TOK_VAR) {
        match(TOK_VAR);
        lista_variables();
    }

    if (t == TOK_FUNCTION || t == TOK_PROCEDURE) {
        declaracion_subprogramas();
    }

    match(TOK_BEGIN);

    if (t == TOK_ID || t == TOK_IF || t == TOK_WHILE || t == TOK_WRITE ||
        t == TOK_READ || t == TOK_PUNTO_Y_COMA) {
        lista_sentencias();
    }

    match(TOK_END);
    match(TOK_PUNTO_Y_COMA);

    return EXIT_SUCCESS;
}

int procedimiento(void) {
    tipo_t t = preanalisis.tipo;

    match(TOK_PROCEDURE);
    match(TOK_ID);

    if (t == TOK_PAR_IZQ) {
        match(TOK_PAR_IZQ);
        parametros_formales();
        match(TOK_PAR_DER);
    }

    match(TOK_PUNTO_Y_COMA);

    if (t == TOK_VAR) {
        match(TOK_VAR);
        lista_variables();
    }

    if (t == TOK_FUNCTION || t == TOK_PROCEDURE) {
        declaracion_subprogramas();
    }

    match(TOK_BEGIN);

    if (t == TOK_ID || t == TOK_IF || t == TOK_WHILE || t == TOK_WRITE ||
        t == TOK_READ || t == TOK_PUNTO_Y_COMA) {
        lista_sentencias();
    }

    match(TOK_END);
    match(TOK_PUNTO_Y_COMA);

    return EXIT_SUCCESS;
}

int parametros_formales(void) {
    match(TOK_ID);
    parametros_formales_1();

    return EXIT_SUCCESS;
}

int parametros_formales_1(void) {
    tipo_t t = preanalisis.tipo;

    if (t == TOK_COMA) {
        match(TOK_COMA);
        parametros_formales();
    } else if (t == TOK_DOS_PUNTOS) {
        match(TOK_DOS_PUNTOS);
        tipo();
        parametros_formales_2();
    } else {
        // ERROR
        char *str = "Error sintáctico: error en declaración de "
                    "variables. Se espera \",\" ó \":\"";

        mostrar_error(ERR_MATCH, NULL, str, NULL);

        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

int parametros_formales_2(void) {
    tipo_t t = preanalisis.tipo;

    if (t == TOK_PUNTO_Y_COMA) {
        match(TOK_PUNTO_Y_COMA);
        parametros_formales();
    }

    return EXIT_SUCCESS;
}

int lista_sentencias(void) {
    sentencia();
    lista_sentencias_1();

    return EXIT_SUCCESS;
}

int lista_sentencias_1(void) {
    tipo_t t = preanalisis.tipo;

    if (t == TOK_PUNTO_Y_COMA) {
        match(TOK_PUNTO_Y_COMA);
        lista_sentencias();
    }

    return EXIT_SUCCESS;
}

int sentencia() {
    tipo_t t = preanalisis.tipo;

    if (t == TOK_PUNTO_Y_COMA) {
        match(TOK_PUNTO_Y_COMA);
        sentencia();
    } else if (t == TOK_ID) {
        // Asignación o llamada a subprograma
        match(TOK_ID);
        sentencia_1();
    } else if (t == TOK_IF) {
        alternativa();
    } else if (t == TOK_WHILE) {
        repetitiva();
    } else if (t == TOK_WRITE) {
        escritura();
    } else if (t == TOK_READ) {
        lectura();
    }

    return EXIT_SUCCESS;
}

int sentencia_1(void) {
    tipo_t t = preanalisis.tipo;

    if (t == TOK_ASIG) {
        asignacion();
    } else if (t == TOK_PAR_IZQ) {
        match(TOK_PAR_IZQ);
        llamada_subprograma();
    } else if (t == TOK_PUNTO_Y_COMA) {
        match(TOK_PUNTO_Y_COMA);
    }

    return EXIT_SUCCESS;
}

int asignacion() {
    match(TOK_ASIG);
    expresion();

    return EXIT_SUCCESS;
}

int alternativa(void) {
    match(TOK_IF);
    expresion();
    match(TOK_THEN);
    sentencia_compuesta();
    alternativa_1();

    return EXIT_SUCCESS;
}

int alternativa_1(void) {
    tipo_t t = preanalisis.tipo;

    if (t == TOK_ELSE) {
        match(TOK_ELSE);
        sentencia_compuesta();
        match(TOK_PUNTO_Y_COMA);
    } else if (t == TOK_PUNTO_Y_COMA) {
        match(TOK_PUNTO_Y_COMA);
    } else {
        // ERROR
        char *str = "Error sintáctico: error en estructura "
                    "alternativa. Se espera \"ELSE\" ó \";\"";

        mostrar_error(ERR_MATCH, NULL, str, NULL);

        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

int repetitiva() {
    match("WHILE");
    expresion();
    match("DO");
    sentencia_compuesta();
    return 0;
}

int sentencia_compuesta() {
    if (strcmp(preanalisis.etiqueta, "IDENTIFICADOR") == 0
        || strcmp(preanalisis.etiqueta, "IF") == 0
        || strcmp(preanalisis.etiqueta, "WHILE") == 0
        || strcmp(preanalisis.etiqueta, "WRITE") == 0
        || strcmp(preanalisis.etiqueta, "READ") == 0) {

        sentencia();
    } else if (strcmp(preanalisis.etiqueta, "BEGIN") == 0) {
        match("BEGIN");
        sentencia();
        match("PUNTO_Y_COMA");
        lista_sentencias();
        match("END");
    } else {
        // ERROR
        printf("Error sintáctico: error en sentencia. ");
        printf("Se espera \"IDENTIFICADOR\", \"IF\", ");
        printf("\"WHILE\", \"WRITE\", \"READ\" ó \"BEGIN\"");

        if (strcmp(preanalisis.etiqueta, "NUMERO") == 0) {
            printf(" y se encontró \"%ld\"", preanalisis.valor);
        } else if (strcmp(preanalisis.lexema, "") != 0){
            printf(" y se encontró \"%s\"", preanalisis.lexema);
        }
        printf("\n");
        exit(1);

    }
    return 0;
}

int escritura() {
    match("WRITE");
    match("PARENTESIS_IZQUIERDO");
    expresion();
    match("PARENTESIS_DERECHO");
    return 0;
}

int lectura() {
    match("READ");
    match("PARENTESIS_IZQUIERDO");
    match("IDENTIFICADOR");
    match("PARENTESIS_DERECHO");
    return 0;
}

int expresion() {
    termino_booleano();
    expresion_1();
    return 0;
}

int expresion_1() {
    if (strcmp(preanalisis.etiqueta, "OR") == 0) {
        match("OR");
        termino_booleano();
        expresion_1();
    }
    return 0;
}

int termino_booleano() {
    factor_booleano();
    termino_booleano_1();
    return 0;
}

int termino_booleano_1() {
    if (strcmp(preanalisis.etiqueta, "AND") == 0) {
        match("AND");
        factor_booleano();
        termino_booleano_1();
    }
    return 0;
}

int factor_booleano() {
    expresion_simple();
    factor_booleano_1();
    return 0;
}

int factor_booleano_1() {
    if (strcmp(preanalisis.etiqueta, "OPERADOR_RELACIONAL") == 0) {
        if (strcmp(preanalisis.lexema, "MENOR") == 0) {
            match("OPERADOR_RELACIONAL");
            match_simbolo("MENOR");
            expresion_simple();
            factor_booleano_1();
        } else if (strcmp(preanalisis.lexema, "MENOR_IGUAL") == 0) {
            match("OPERADOR_RELACIONAL");
            match_simbolo("MENOR_IGUAL");
            expresion_simple();
            factor_booleano_1();
        } else if (strcmp(preanalisis.lexema, "DISTINTO") == 0) {
            match("OPERADOR_RELACIONAL");
            match_simbolo("DISTINTO");
            expresion_simple();
            factor_booleano_1();
        } else if (strcmp(preanalisis.lexema, "MAYOR") == 0) {
            match("OPERADOR_RELACIONAL");
            match_simbolo("MAYOR");
            expresion_simple();
            factor_booleano_1();
        } else if (strcmp(preanalisis.lexema, "MAYOR_IGUAL") == 0) {
            match("OPERADOR_RELACIONAL");
            match_simbolo("MAYOR_IGUAL");
            expresion_simple();
            factor_booleano_1();
        } else if (strcmp(preanalisis.lexema, "IGUAL") == 0) {
            match("OPERADOR_RELACIONAL");
            match_simbolo("IGUAL");
            expresion_simple();
            factor_booleano_1();
        }
    }
    return 0;
}

int expresion_simple() {
    termino();
    expresion_simple_1();
    return 0;
}

int expresion_simple_1() {
    if (strcmp(preanalisis.etiqueta, "ALGEBRAICO_ADITIVO") == 0 &&
        strcmp(preanalisis.lexema, "SUMA") == 0) {

        match("ALGEBRAICO_ADITIVO");
        match_simbolo("SUMA");
        termino();
        expresion_simple_1();
    } else if (strcmp(preanalisis.etiqueta, "ALGEBRAICO_ADITIVO") == 0 &&
            strcmp(preanalisis.lexema, "RESTA") == 0) {

        match("ALGEBRAICO_ADITIVO");
        match_simbolo("RESTA");
        termino();
        expresion_simple_1();
    }
    return 0;
}

int termino() {
    factor();
    termino_1();
    return 0;
}

int termino_1() {
    if (strcmp(preanalisis.etiqueta, "ALGEBRAICO_MULTIPLICATIVO") == 0 && 
        strcmp(preanalisis.lexema, "PRODUCTO") == 0) {
        
        match("ALGEBRAICO_MULTIPLICATIVO");
        match_simbolo("PRODUCTO");
        factor();
        termino_1();
    } else if (strcmp(preanalisis.etiqueta, "ALGEBRAICO_MULTIPLICATIVO") == 0 &&
            strcmp(preanalisis.lexema, "COCIENTE") == 0) {

        match("ALGEBRAICO_MULTIPLICATIVO");
        match_simbolo("COCIENTE");
        factor();
        termino_1();
    }
    return 0;
}

int factor() {
    if (strcmp(preanalisis.etiqueta, "ALGEBRAICO_ADITIVO") == 0 
        && strcmp(preanalisis.lexema, "RESTA") == 0) {
       
        match("ALGEBRAICO_ADITIVO");
        match_simbolo("RESTA");
        factor_();
    } if (strcmp(preanalisis.etiqueta, "NOT") == 0) {
        match("NOT");
        factor_5();
    } else if (strcmp(preanalisis.etiqueta, "NUMERO") == 0) {
        match("NUMERO");
    } else if (strcmp(preanalisis.etiqueta, "BOOLEAN") == 0) {
        match("BOOLEAN");
    } else if (strcmp(preanalisis.etiqueta, "IDENTIFICADOR") == 0) {
        match("IDENTIFICADOR");
        factor_1();
    } else if (strcmp(preanalisis.etiqueta, "PARENTESIS_IZQUIERDO") == 0) {
        match("PARENTESIS_IZQUIERDO");
        factor_2();
    } else {
        // ERROR
        printf("Error sintáctico: error en expresión. ");
        printf("Se espera \"NOT\", \"NÚMERO\", ");
        printf("\"BOOLEANO\", \"IDENTIFICADOR\" ó \"(\"");

        if (strcmp(preanalisis.etiqueta, "NUMERO") == 0) {
            printf(" y se encontró \"%ld\"", preanalisis.valor);
        } else if (strcmp(preanalisis.lexema, "") != 0){
            printf(" y se encontró \"%s\"", preanalisis.lexema);
        }
        printf("\n");
        exit(1);
    }
    return 0;
}

int factor_1() {
    if (strcmp(preanalisis.etiqueta, "PARENTESIS_IZQUIERDO") == 0) {
        match("PARENTESIS_IZQUIERDO");
        llamada_subprograma();
    }
    return 0;
}

int factor_2() {
    expresion();
    match("PARENTESIS_DERECHO");
    return 0;
}

int factor_4() {
    if (strcmp(preanalisis.etiqueta, "NUMERO") == 0 ) {
        match("NUMERO");
    } else if (strcmp(preanalisis.etiqueta, "IDENTIFICADOR") == 0) {
        match("IDENTIFICADOR");
    } else if (strcmp(preanalisis.etiqueta, "PARENTESIS_IZQUIERDO") == 0) {
        match("PARENTESIS_IZQUIERDO");
        factor_2();
    } else {
        // ERROR
        printf("Error sintáctico: error en expresión. ");
        printf("Se espera \"NÚMERO\", \"IDENTIFICADOR\" ó \"(\"");

        if (strcmp(preanalisis.etiqueta, "NUMERO") == 0) {
            printf(" y se encontró \"%ld\"", preanalisis.valor);
        } else if (strcmp(preanalisis.lexema, "") != 0){
            printf(" y se encontró \"%s\"", preanalisis.lexema);
        }
        printf("\n");
    }
    return 0;
}

int factor_5() {
    if (strcmp(preanalisis.etiqueta, "BOOLEAN") == 0) {
        match("BOOLEAN");
    } else if (strcmp(preanalisis.etiqueta, "IDENTIFICADOR") == 0) {
        match("IDENTIFICADOR");
    } else if (strcmp(preanalisis.etiqueta, "PARENTESIS_IZQUIERDO") == 0) {
        match("PARENTESIS_IZQUIERDO");
        //factor_1(); verificar
    } else {
        // ERROR
        printf("Error sintáctico: error en expresión. ");
        printf("Se espera \"BOOLEANO\", \"IDENTIFICADOR\" ó \"(\"");

        if (strcmp(preanalisis.etiqueta, "NUMERO") == 0) {
            printf(" y se encontró \"%ld\"", preanalisis.valor);
        } else if (strcmp(preanalisis.lexema, "") != 0){
            printf(" y se encontró \"%s\"", preanalisis.lexema);
        }
        printf("\n");
    }
    return 0;
}

int llamada_subprograma() {
    lista_expresiones();
    match("PARENTESIS_DERECHO");
    return 0;
}

int lista_expresiones() {
    expresion();
    lista_expresiones_1();
    return 0;
}

int lista_expresiones_1() {
    if (strcmp(preanalisis.etiqueta, "COMA") == 0) {
        match("COMA");
        lista_expresiones();
    }
    return 0;
}

void to_upper_case(char *string, char *string_upper) {
    char c = string[0];
    int i = 0;

    while (c != '\0') {
        string_upper[i] = toupper(c);
        i++;
        c = string[i];
    }
    while (i < strlen(string_upper)) {
        string_upper[i] = '\0';
        i++;
    }
}

// Match por tipo de token
int match(tipo_t tok_t) {
    // Compara el símbolo de prenálisis con el terminal esperado
    if (preanalisis.tipo == tok_t) {
        // Obtener siguiente token del análizador léxico
        obtener_siguiente_token(&preanalisis);
    } else {
        printf("Error sintáctico: se espera \"%s\"", etiqueta);
        if (strcmp(preanalisis.lexema, "") != 0) {
            printf(" y se encontró ");
            if (strcmp(preanalisis.etiqueta, "NUMERO") == 0) {
                printf("\"%ld\"", preanalisis.valor);
            } else {
                printf("\"%s\"", preanalisis.lexema);
            }
        }
        printf(" en linea %d\n", linea);
        exit(1);
    }
    return 0;
}

int match_palabra(char *lexema) {
    // Compara el símbolo de prenálisis con el terminal esperado
    if (strcmp(preanalisis.lexema, lexema) != 0) {
        printf("Error sintáctico: se espera \"%s\" y se encontró ", lexema);
        if (strcmp(preanalisis.etiqueta, "NUMERO") == 0) {
            printf("%ld", preanalisis.valor);
        } else {
            printf("%s", preanalisis.lexema);
        }
        printf(" en linea %d\n", linea);
        exit(1);
    }
    return 0;
}

int match_simbolo(char *lexema) {
    printf("Preanalisis: %s - %s - %ld\n", preanalisis.etiqueta, preanalisis.lexema, preanalisis.valor);
    printf("Lexema: %s\n", lexema);
    // Compara el símbolo de prenálisis con el terminal esperado
    if (strcmp(preanalisis.lexema, lexema) != 0) {
        printf("Error sintáctico: se espera \"%s\" y se encontró ", lexema);
        if (strcmp(preanalisis.etiqueta, "NUMERO") == 0) {
            printf("%ld", preanalisis.valor);
        } else {
            printf("%s", preanalisis.lexema);
        }
        printf(" en linea %d\n", linea);
        exit(1);
    }
    return 0;
}
