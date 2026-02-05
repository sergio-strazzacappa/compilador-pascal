# Compilador para Pascal

## Introducción

Se implementa un compilador escrito en _C_ para un subconjunto del lenguaje de
programación _Pascal_. Se va a ir ampliando la cantidad de constructores
soportados.

## Constructores a tener en cuenta

- Variables y subprogramas
- Tipos de datos: `enteros` y `booleanos`
- Constantes: `true` y `false`
- Subprogramas: procedimientos y funciones. Solo pasaje de parámetros por valor
- Estructuras de control
    - asignación
    - alternativa: `if then else`
    - repetitiva: `while`
    - compuesta: `begin ... end`
- Procedimientos de entrada/salida
    - `read`
    - `write`
- Expresiones aritméticas: `+`, `-` (unario y binario), `*`, `/`, `(`, `)`
- Expresiones booleanas: `AND`, `OR`, `NOT`, `>`, `<`, `=`, <code>&leq;</code>,
  <code>&geq;</code>, <code>&ne;</code>
- Comentarios encerrados entre llaves

## Tokens

- tipo
    - TOKEN &lt;etiqueta&gt;
    - NUMERO &lt;etiqueta=NUMERO, valor&gt;
    - PALABRA &lt;etiqueta=IDENTIFICADOR, lexema&gt;
    - SIMBOLO &lt;etiqueta=SIMBOLO, lexema&gt;
- etiqueta
- valor
- lexema

### Palabras reservadas

tipo = 3 \
valor = 0

- <"PROGRAM", "PROGRAM">
- <"FUNCTION", "FUNCTION">
- <"PROCEDURE", "PROCEDURE">
- <"BEGIN", "BEGIN">
- <"END", "END">
- <"VAR", "VAR">
- <"WRITE", "WRITE">
- <"READ", "READ">
- <"IF", "IF">
- <"THEN", "THEN">
- <"ELSE", "ELSE">
- <"WHILE", "WHILE">
- <"DO", "DO">
- <"OR", "OR">
- <"AND", "AND">
- <"NOT", "NOT">
- <"BOOLEAN", "TRUE">
- <"BOOLEAN", "FALSE">
- <"TIPO", "INTEGER">
- <"TIPO", "BOOLEAN">

### Símbolos

- <"ASIGNACION", "">
- <"DOS_PUNTOS", "">
- <"OPERADOR_RELACIONAL", "MENOR_IGUAL">
- <"OPERADOR_RELACIONAL", "DISTINTO">
- <"OPERADOR_RELACIONAL", "MENOR">
- <"OPERADOR_RELACIONAL", "MAYOR_IGUAL">
- <"OPERADOR_RELACIONAL", "MAYOR">
- <"OPERADOR_RELACIONAL", "IGUAL">
- <"ALGEBRAICO_ADITIVO", "SUMA">
- <"ALGEBRAICO_ADITIVO", "RESTA">
- <"ALGEBRAICO_MULTIPLICATIVO", "PRODUCTO">
- <"ALGEBRAICO_MULTIPLICATIVO", "COCIENTE">
- <"PUNTO_Y_COMA", "">
- <"PUNTO", "">
- <"COMA", "">
- <"PARENTESIS_IZQUIERDO", "">
- <"PARENTESIS_DERECHO", "">

## TODO

- Revisar los malloc y agregar los correspondiente free
- Ejemplo046
