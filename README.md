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
│   ├── error.h
│   ├── lexico.h
│   ├── token.h
│   ├── ts.h
├── src/
│   ├── error.c
│   ├── lexico.c
│   ├── token.c
│   ├── ts.c
├── tests/
├── Dockerfile
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

## Especificación técnica

### Mensajes de errores (error.h y error.c)

#### API

```c
typedef enum cod_e {
    ERR_UN_ARCHIVO
    ERR_USO
    ERR_NO_ARCHIVO
} cod_t;

int mostrar_error(
    const cod_t codigo,
    const char *const archivo,
    const size_t *const linea);
```

### Tokens (token.h y token.c)

#### Palabras reservadas

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

#### Símbolos

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

#### API

```c
typedef enum tipo_e {
    TOK_ID, TOK_NUM, TOK_BOOL, TOK_T, TOK_PROGRAM, TOK_FUNCTION,
    TOK_PROCEDURE, TOK_BEGIN, TOK_END, TOK_VAR, TOK_WRITE, TOK_READ,
    TOK_IF, TOK_THEN, TOK_ELSE, TOK_WHILE, TOK_DO, TOK_ASIG, TOK_OR,
    TOK_AND, TOK_OP_REL, TOK_ALG_AD, TOK_ALG_MUL, TOK_NOT, TOK_PUNTO_Y_COMA,
    TOK_PUNTO, TOK_COMA, TOK_DOS_PUNTOS, TOK_PAR_IZQ, TOK_PAR_DER
} tipo_t;

typedef enum subtipo_e {
    MENOR_IGUAL, MENOR, MAYOR_IGUAL, MAYOR, IGUAL, DISTINTO,
    SUMA, RESTA, PRODUCTO, COCIENTE
} subtipo_t;

typedef struct token_s {
    tipo_t tipo;
    int linea;

    union {
        long valor;         // valor si el token es un TOK_NUM
        subtipo_t subtipo;  // subtipo de token si es un símbolo
        int ts_indice;      // indice donde el token esta almacenado en la TS
    } data_u;
} tok_t;

extern const tipo_t TOKENS[];

int obtener_lexema(const tok_t *const tok, char *str);
int obtener_numero(const tok_t *const tok, char *str, const size_t len);
int obtener_lexema_sin(const tok_t *const tok, char *str);
int obtener_info_token(const tok_t *const tok, char *str, const size_t len);
```

### Tabla de símbolos (ts.h t ts.c)

#### API

```c
typedef struct ts_entrada_s {
    // TODO: Completar con los campos faltantes
    tipo_t tipo;
    char *lexema;
} ts_entrada_t;


int inicializar_ts(void);
int buscar_ts(const char *const lexema);
ts_entrada_t *buscar_ts_por_indice(const size_t indice);
int insertar_ts(const ts_entrada_t entrada);
int redimensionar_ts(void);
int destruir_ts(void);
int mostrar_ts(void);
```

## TODO

- Revisar los malloc y agregar los correspondiente free
- Ejemplo046
