#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "sintactico.h"
#include "lexico.h"
#include "error.h"
#include "ts.h"
#include "token.h"

static tok_t preanalisis;

int analizar(FILE *archivo_fuente) {
    inicializar_lexico(archivo_fuente);
    obtener_siguiente_token(&preanalisis);
    programa();
    printf("El programa no tiene errores sintácticos\n");

    return EXIT_SUCCESS;
}

int programa(void) {
    match(TOK_PROGRAM);
    match(TOK_ID);
    match(TOK_PUNTO_Y_COMA);

    if (preanalisis.tipo == TOK_VAR) {
        match(TOK_VAR);
        lista_variables();
    }

    if (preanalisis.tipo == TOK_FUNCTION || preanalisis.tipo == TOK_PROCEDURE) {
        declaracion_subprogramas();
    }

    match(TOK_BEGIN);

    if (preanalisis.tipo == TOK_ID || preanalisis.tipo == TOK_IF ||
        preanalisis.tipo == TOK_WHILE || preanalisis.tipo == TOK_WRITE ||
        preanalisis.tipo == TOK_READ || preanalisis.tipo == TOK_PUNTO_Y_COMA) {
        lista_sentencias();
    }

    match(TOK_END);
    match(TOK_PUNTO);

    // ERROR
    if (preanalisis.tipo != TOK_FIN) {
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
    if (preanalisis.tipo == TOK_COMA) {
        match(TOK_COMA);
        lista_variables();
    } else if (preanalisis.tipo == TOK_DOS_PUNTOS) {
        match(TOK_DOS_PUNTOS);
        tipo();
        match(TOK_PUNTO_Y_COMA);
        lista_variables_2();
    } else {
        // ERROR
        char *str = "Error en la declaración de variables. "
                    "Se espera \",\" ó \":\"";
        mostrar_error(ERR_MATCH, NULL, str, &preanalisis.linea);
        
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

int lista_variables_2(void) {
    if (preanalisis.tipo == TOK_ID)
        lista_variables();

    return EXIT_SUCCESS;
}

int tipo(void) {
    const ts_entrada_t *e = buscar_ts_por_indice(preanalisis.data_u.ts_indice);

    if (preanalisis.tipo == TOK_T && (strcmp(e->lexema, "INTEGER") == 0 || 
        strcmp(e->lexema, "BOOLEAN") == 0)) {

        match(TOK_T);
    } else {
        // ERROR
        char *str = "Error en la declaración de variables. Se espera " 
                    "\"INTEGER\" ó \"BOOLEAN\"";

        mostrar_error(ERR_MATCH, NULL, str, &preanalisis.linea);

        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

int declaracion_subprogramas(void) {
    if (preanalisis.tipo == TOK_FUNCTION) {
        funcion();
        declaracion_subprogramas_1();
    } else if (preanalisis.tipo == TOK_PROCEDURE) {
        procedimiento();
        declaracion_subprogramas_1();
    } else {
        // ERROR
        char *str = "Error sintáctico: error en definción de "
                    "función o procedimiento. "
                    "Se espera \"FUNCTION\" ó \"PROCEDURE\"";

        mostrar_error(ERR_MATCH, NULL, str, &preanalisis.linea);

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
    match(TOK_FUNCTION);
    match(TOK_ID);

    if (preanalisis.tipo == TOK_PAR_IZQ) {
        match(TOK_PAR_IZQ);
        parametros_formales();
        match(TOK_PAR_DER);
    }

    match(TOK_DOS_PUNTOS);
    tipo();
    match(TOK_PUNTO_Y_COMA);

    if (preanalisis.tipo == TOK_VAR) {
        match(TOK_VAR);
        lista_variables();
    }

    if (preanalisis.tipo == TOK_FUNCTION || preanalisis.tipo == TOK_PROCEDURE) {
        declaracion_subprogramas();
    }

    match(TOK_BEGIN);

    if (preanalisis.tipo == TOK_ID || preanalisis.tipo == TOK_IF ||
        preanalisis.tipo == TOK_WHILE || preanalisis.tipo == TOK_WRITE ||
        preanalisis.tipo == TOK_READ || preanalisis.tipo == TOK_PUNTO_Y_COMA) {
        lista_sentencias();
    }

    match(TOK_END);
    match(TOK_PUNTO_Y_COMA);

    return EXIT_SUCCESS;
}

int procedimiento(void) {
    match(TOK_PROCEDURE);
    match(TOK_ID);

    if (preanalisis.tipo == TOK_PAR_IZQ) {
        match(TOK_PAR_IZQ);
        parametros_formales();
        match(TOK_PAR_DER);
    }

    match(TOK_PUNTO_Y_COMA);

    if (preanalisis.tipo == TOK_VAR) {
        match(TOK_VAR);
        lista_variables();
    }

    if (preanalisis.tipo == TOK_FUNCTION || preanalisis.tipo == TOK_PROCEDURE) {
        declaracion_subprogramas();
    }

    match(TOK_BEGIN);

    if (preanalisis.tipo == TOK_ID || preanalisis.tipo == TOK_IF ||
        preanalisis.tipo == TOK_WHILE || preanalisis.tipo == TOK_WRITE ||
        preanalisis.tipo == TOK_READ || preanalisis.tipo == TOK_PUNTO_Y_COMA) {
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
    if (preanalisis.tipo == TOK_COMA) {
        match(TOK_COMA);
        parametros_formales();
    } else if (preanalisis.tipo == TOK_DOS_PUNTOS) {
        match(TOK_DOS_PUNTOS);
        tipo();
        parametros_formales_2();
    } else {
        // ERROR
        char *str = "Error sintáctico: error en declaración de "
                    "variables. Se espera \",\" ó \":\"";

        mostrar_error(ERR_MATCH, NULL, str, &preanalisis.linea);

        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

int parametros_formales_2(void) {
    if (preanalisis.tipo == TOK_PUNTO_Y_COMA) {
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
    if (preanalisis.tipo == TOK_PUNTO_Y_COMA) {
        match(TOK_PUNTO_Y_COMA);
        lista_sentencias();
    }

    return EXIT_SUCCESS;
}

int sentencia() {
    if (preanalisis.tipo == TOK_PUNTO_Y_COMA) {
        match(TOK_PUNTO_Y_COMA);
        sentencia();
    } else if (preanalisis.tipo == TOK_ID) {
        // Asignación o llamada a subprograma
        match(TOK_ID);
        sentencia_1();
    } else if (preanalisis.tipo == TOK_IF) {
        alternativa();
    } else if (preanalisis.tipo == TOK_WHILE) {
        repetitiva();
    } else if (preanalisis.tipo == TOK_WRITE) {
        escritura();
    } else if (preanalisis.tipo == TOK_READ) {
        lectura();
    }

    return EXIT_SUCCESS;
}

int sentencia_1(void) {
    if (preanalisis.tipo == TOK_ASIG) {
        asignacion();
    } else if (preanalisis.tipo == TOK_PAR_IZQ) {
        match(TOK_PAR_IZQ);
        llamada_subprograma();
    } else if (preanalisis.tipo == TOK_PUNTO_Y_COMA) {
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
    if (preanalisis.tipo == TOK_ELSE) {
        match(TOK_ELSE);
        sentencia_compuesta();
        match(TOK_PUNTO_Y_COMA);
    } else if (preanalisis.tipo == TOK_PUNTO_Y_COMA) {
        match(TOK_PUNTO_Y_COMA);
    } else {
        // ERROR
        char *str = "Error sintáctico: error en estructura "
                    "alternativa. Se espera \"ELSE\" ó \";\"";

        mostrar_error(ERR_MATCH, NULL, str, &preanalisis.linea);

        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

int repetitiva(void) {
    match(TOK_WHILE);
    expresion();
    match(TOK_DO);
    sentencia_compuesta();

    return EXIT_SUCCESS;
}

int sentencia_compuesta(void) {
    if (preanalisis.tipo == TOK_ID || preanalisis.tipo == TOK_IF ||
        preanalisis.tipo == TOK_WHILE || preanalisis.tipo == TOK_WRITE ||
        preanalisis.tipo == TOK_READ) {
        sentencia();
    } else if (preanalisis.tipo == TOK_BEGIN) {
        match(TOK_BEGIN);
        sentencia();
        match(TOK_PUNTO_Y_COMA);
        lista_sentencias();
        match(TOK_END);
    } else {
        // ERROR
        char *str = "Error sintáctico: error en sentencia. "
                    "Se espera \"IDENTIFICADOR\", \"IF\", "
                    "\"WHILE\", \"WRITE\", \"READ\" ó \"BEGIN\"";

        mostrar_error(ERR_MATCH, NULL, str, &preanalisis.linea);

        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

int escritura(void) {
    match(TOK_WRITE);
    match(TOK_PAR_IZQ);
    expresion();
    match(TOK_PAR_DER);

    return EXIT_SUCCESS;
}

int lectura(void) {
    match(TOK_READ);
    match(TOK_PAR_IZQ);
    match(TOK_ID);
    match(TOK_PAR_DER);

    return EXIT_SUCCESS;
}

int expresion(void) {
    termino_booleano();
    expresion_1();

    return EXIT_SUCCESS;
}

int expresion_1(void) {
    if (preanalisis.tipo == TOK_OR) {
        match(TOK_OR);
        termino_booleano();
        expresion_1();
    }

    return EXIT_SUCCESS;
}

int termino_booleano(void) {
    factor_booleano();
    termino_booleano_1();

    return EXIT_SUCCESS;
}

int termino_booleano_1(void) {
    if (preanalisis.tipo == TOK_AND) {
        match(TOK_AND);
        factor_booleano();
        termino_booleano_1();
    }

    return EXIT_SUCCESS;
}

int factor_booleano(void) {
    expresion_simple();
    factor_booleano_1();

    return EXIT_SUCCESS;
}

int factor_booleano_1(void) {
    if (preanalisis.tipo == TOK_OP_REL) {
        const ts_entrada_t *e = buscar_ts_por_indice(preanalisis.data_u.ts_indice);

        if (strcmp(e->lexema, "MENOR") == 0 ||
            strcmp(e->lexema, "MENOR_IGUAL") == 0 ||
            strcmp(e->lexema, "DISTINTO") == 0 ||
            strcmp(e->lexema, "MAYOR") == 0 ||
            strcmp(e->lexema, "MAYOR_IGUAL") == 0 ||
            strcmp(e->lexema, "IGUAL") == 0) {

            match(TOK_OP_REL);
            expresion_simple();
            factor_booleano_1();
        }
    }

    return EXIT_SUCCESS;
}

int expresion_simple(void) {
    termino();
    expresion_simple_1();

    return EXIT_SUCCESS;
}

int expresion_simple_1(void) {
    const ts_entrada_t *e = buscar_ts_por_indice(preanalisis.data_u.ts_indice);

    if (preanalisis.tipo == TOK_ALG_AD && (strcmp(e->lexema, "SUMA") == 0 ||
        strcmp(e->lexema, "RESTA") == 0)) {

        match(TOK_ALG_AD);
        termino();
        expresion_simple_1();
    }

    return EXIT_SUCCESS;
}

int termino(void) {
    factor();
    termino_1();

    return EXIT_SUCCESS;
}

int termino_1(void) {
    const ts_entrada_t *e = buscar_ts_por_indice(preanalisis.data_u.ts_indice);

    if (preanalisis.tipo == TOK_ALG_MUL && (strcmp(e->lexema, "PRODUCTO") == 0 ||
        strcmp(e->lexema, "COCIENTE") == 0)) {

        match(TOK_ALG_MUL);
        factor();
        termino_1();
    }

    return EXIT_SUCCESS;
}

int factor(void) {
    const ts_entrada_t *e = buscar_ts_por_indice(preanalisis.data_u.ts_indice);

    if (preanalisis.tipo == TOK_ALG_AD && strcmp(e->lexema, "RESTA") == 0) {
        match(TOK_ALG_AD);
        factor_3();
    } else if (preanalisis.tipo == TOK_NOT) {
        match(TOK_NOT);
        factor_4();
    } else if (preanalisis.tipo == TOK_NUM) {
        match(TOK_NUM);
    } else if (preanalisis.tipo == TOK_BOOL) {
        match(TOK_BOOL);
    } else if (preanalisis.tipo == TOK_ID) {
        match(TOK_ID);
        factor_1();
    } else if (preanalisis.tipo == TOK_PAR_IZQ) {
        match(TOK_PAR_IZQ);
        factor_2();
    } else {
        // ERROR
        char *str = "Error sintáctico: error en expresión. "
                    "Se espera \"NOT\", \"NÚMERO\", "
                    "\"BOOLEANO\", \"IDENTIFICADOR\" ó \"(\"";

        mostrar_error(ERR_MATCH, NULL, str, &preanalisis.linea);

        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

int factor_1(void) {
    if (preanalisis.tipo == TOK_PAR_IZQ) {
        match(TOK_PAR_IZQ);
        llamada_subprograma();
    }

    return EXIT_SUCCESS;
}

int factor_2(void) {
    expresion();
    match(TOK_PAR_DER);

    return EXIT_SUCCESS;
}

int factor_3(void) {
    if (preanalisis.tipo == TOK_NUM) {
        match(TOK_NUM);
    } else if (preanalisis.tipo == TOK_ID) {
        match(TOK_ID);
    } else if (preanalisis.tipo == TOK_PAR_IZQ) {
        match(TOK_PAR_IZQ);
        factor_2();
    } else {
        // ERROR
        char *str = "Error sintáctico: error en expresión. "
                    "Se espera \"NÚMERO\", \"IDENTIFICADOR\" ó \"(\"";

        mostrar_error(ERR_MATCH, NULL, str, &preanalisis.linea);

        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

int factor_4(void) {
    if (preanalisis.tipo == TOK_BOOL) {
        match(TOK_BOOL);
    } else if (preanalisis.tipo == TOK_ID) {
        match(TOK_ID);
    } else if (preanalisis.tipo == TOK_PAR_IZQ) {
        match(TOK_PAR_IZQ);
        factor_1(); 
    } else {
        // ERROR
        char *str = "Error sintáctico: error en expresión. "
                    "Se espera \"BOOLEANO\", \"IDENTIFICADOR\" ó \"(\"";

        mostrar_error(ERR_MATCH, NULL, str, &preanalisis.linea);

        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

int llamada_subprograma(void) {
    lista_expresiones();
    match(TOK_PAR_DER);

    return EXIT_SUCCESS;
}

int lista_expresiones(void) {
    expresion();
    lista_expresiones_1();

    return EXIT_SUCCESS;
}

int lista_expresiones_1(void) {
    if (preanalisis.tipo == TOK_COMA) {
        match(TOK_COMA);
        lista_expresiones();
    }

    return EXIT_SUCCESS;
}

// Match por tipo de token
int match(tipo_t tok_tipo) {
    char lexema[32];
    tok_t tmp = {0};
    tmp.tipo = tok_tipo;
    obtener_lexema(&tmp, lexema);
    fprintf(stderr, "[INFO] Token esperado %s\n", lexema);
    // Compara el símbolo de prenálisis con el terminal esperado
    if (preanalisis.tipo == tok_tipo) {
        // Obtener siguiente token del análizador léxico
        obtener_siguiente_token(&preanalisis);
        char str[512];
        obtener_info_token(&preanalisis, str, 512);
        fprintf(stderr, "[INFO] %s\n", str);
    } else {
        char str[256] = "Error sintáctico: se espera ";
        strcat(str, lexema);

        mostrar_error(ERR_MATCH, NULL, str, &preanalisis.linea);

        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
