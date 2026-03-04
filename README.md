# Compilador para Pascal

## Introducción

Se implementa un compilador escrito en _C_ para un subconjunto del lenguaje de
programación _Pascal_. Se va a ir ampliando la cantidad de constructores
soportados.

## Estructura del proyecto

```
./
├── bin/
├── build/
├── include/
│   ├── token.h
├── src/
│   ├── token.c
├── tests/
├── Makefile
└── README.md
```

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

- Identificador
    - Puntero a la TS
- Numero
    - Valor del entero
- Booleano
    - Valor del booleano
- Tipo
    - Entero
    - Booleano
- Program
- Función
- Procedimiento
- Begin
- End
- Var
- Write
- Read
- If
- Then
- Else
- While
- Do
- Asignación
- Or
- And
- Operador_relacional
    - Menor_igual
    - Menor
    - Mayor_igual
    - Igual
    - Distinto
- Algebraico_aditivo
    - Suma
    - Resta
- Algebraico_multiplicativo
    - Producto
    - Cociente
- Not
- Punto_y_coma
- Punto
- Coma
- Dos_puntos
- Parentesis_izquierdo
- Parentesis_derecho

### Palabras reservadas

- PROGRAM
- FUNCTION
- PROCEDURE
- BEGIN
- END
- VAR
- WRITE
- READ
- IF
- THEN
- ELSE
- WHILE
- DO
- OR
- AND
- NOT
- TRUE
- FALSE
- INTEGER
- TIPO

### Símbolos

- ASIGNACION
- DOS_PUNTOS
- &lt;"OPERADOR_RELACIONAL", "MENOR_IGUAL"&gt;
- &lt;"OPERADOR_RELACIONAL", "DISTINTO"&gt;
- &lt;"OPERADOR_RELACIONAL", "MENOR"&gt;
- &lt;"OPERADOR_RELACIONAL", "MAYOR_IGUAL"&gt;
- &lt;"OPERADOR_RELACIONAL", "MAYOR"6gt;
- &lt;"OPERADOR_RELACIONAL", "IGUAL"&gt;
- &lt;"ALGEBRAICO_ADITIVO", "SUMA"&gt;
- &lt;"ALGEBRAICO_ADITIVO", "RESTA"&gt;
- &lt;"ALGEBRAICO_MULTIPLICATIVO", "PRODUCTO"&gt;
- &lt;"ALGEBRAICO_MULTIPLICATIVO", "COCIENTE"&gt;
- PUNTO_Y_COMA
- PUNTO
- COMA
- PARENTESIS_IZQUIERDO
- PARENTESIS_DERECHO

## TODO

- Revisar los malloc y agregar los correspondiente free
- Ejemplo046
