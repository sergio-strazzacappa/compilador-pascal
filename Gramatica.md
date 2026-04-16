# Gramatica

## Programa

programa -> `PROGRAM` IDENTIFICADOR `;` [`VAR` lista_variables]
[declaracion_subprogramas] `BEGIN` lista_sentencias `END` `.`

## Lista de variables

lista_variables -> `IDENTIFICADOR` lista_variables_1

lista_variables_1 -> `,` lista_variables | `:` tipo `;` lista_variables_2

lista_variables_2 -> lista_variables | $\lambda$

## Tipo

tipo -> `INTEGER` | `BOOLEAN`

## Declaración de subprogramas

declaracion_subprogramas -> funcion declaracion_subprograma_1 |
 procedimiento declaracion_subprograma_1

declaracion_subprogramas_1 -> declaracion_subprogramas | $\lambda$

## Función

funcion -> `FUNCTION` `IDENTIFICADOR` [`(` parametros_formales `)`] `:` tipo
 `;` [`VAR` lista_variables] [declaracion_subprogramas] `BEGIN`
  [lista_sentencias] `END` `;`

## Procedimiento

procedimiento -> `PROCEDURE` `IDENTIFICADOR` [`(` parametros_formales `)`] `;`
 [`VAR` lista_variables] [declaracion_subprogramas] `BEGIN` [lista_sentencias]
 `END` `;`

## Parametros formales

parametros_formales -> `IDENTIFICADOR` parametros_formales_1

parametros_formales_1 -> `,` parametros_formales |
 `:` tipo parametros_formales_2

parametros_formales_2 -> `;` parametros_formales | $\lambda$

## Lista sentencias

lista_sentencias -> sentencia lista_sentencias_1

lista_sentencias_1 -> `;` lista_sentencias | $\lambda$

## Sentencia

sentencia -> `;` sentencia | `IDENTIFICADOR` sentencia_1 | alternativa |
 repetitiva | escritura | lectura | $\lambda$

sentencia_1 -> asignacion | `(` llamada_subprograma | `;` | $\lambda$

## Asignación

asignacion -> `:=` expresion

## Alternativa

alternativa -> `IF` expresion `THEN` sentencia_compuesta alternativa_1

alternativa_1 -> `ELSE` sentencia_compuesta `;` | `;`

repetitiva -> "WHILE" expresion "DO" sentencia_compuesta

sentencia_compuesta -> sentencia | "BEGIN" sentencia ";" lista_sentencias "END"

escritura -> "WRITE" "(" expresion ")"

lectura -> "READ" "(" "IDENTIFICADOR" ")"

expresion -> termino_booleano expresion_1

expresion_1 -> "OR" termino_booleano expresion_1 | \lambda

termino_booleano -> factor_booleano termino_booleano_1

termino_booleano_1 -> "AND" factor_booleano termino_booleano_1 | \lambda

factor_booleano -> expresion_simple factor_booleano_1

factor_booleano_1 -> "&lt;" expresion_simple factor_booleano_1 |
                     "&le;" expresion_simple factor_booleano_1 | 
                     "&lt; &gt;" expresion_simple factor_booleano_1 |
                     "&gt;" expresion_simple factor_booleano_1 |
                     "&ge;" expresion_simple factor_booleano_1 |
                     "=" expresion_simple factor_booleano_1 |
                     \lambda

expresion_simple -> termino expresion_simple_1

expresion_simple_1 -> "+" termino expresion_simple_1 |
                      "-" termino expresion_simple_1 | \lambda

termino -> factor termino_1

termino_1 -> "*" factor termino_1 | "/" factor termino_1 | \lambda

factor -> "-" factor_4 | "NOT" factor_5 | "NUMERO" | "BOOLEANO" | 
          "IDENTIFICADOR" factor_1 | "(" factor_2

factor_1 -> "(" llamada_subprograma | \lambda

factor_2 -> expresion ")"

factor_4 -> "NUMERO" | "IDENTIFICADOR" | "(" factor_1

factor_5 -> "BOOLEANO" | "IDENTIFICADOR" | "(" factor_1

llamada_subprograma -> lista_expresiones ")"

lista_expresiones -> expresion lista_expresiones_1

lista_expresiones_1 -> "," lista_expresiones | \lambda
