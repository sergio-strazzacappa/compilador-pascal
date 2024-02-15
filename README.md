# Compilador para Pascal

## Introducción

Se implementa un compilador escrito en _C_ para un subconjunto del lenguaje
de programación _Pascal_. Se va a ir ampliando la cantidad de constructores
soportados.

### Constructores a tener en cuenta

- Variables y subprogramas
- Tipos de datos: enteros y booleanos
- Constantes: true y false
- Subprogramas: procedimientos y funciones. Solo pasaje de parámetros por valor
- Estructuras de control: asignación, alternativa, repetitiva, compuesta (begin-end)
- Procedimientos de entrada/salida
- Expresiones aritméticas: +, - (unario y binario), *, /, (, )
- Expresiones booleanas: AND, OR, NOT, &gt;, &lt;, &equals;, &le;, &ge;, &ne;
- Comentarios encerrados entre llaves

## Tokens

- tipo
  - 1 = Token <etiqueta>
  - 2 = Numero <etiqueta=NUMERO, valor>
  - 3 = Palabra <etiqueta=PALABRA, lexema>
  - 4 = Simbolo <etiqueta=SIMBOLO, lexema>
- etiqueta

### Etiquetas

- ASIGNACIÓN
- DOS_PUNTOS
- PUNTO_Y_COMA
- PUNTO
- COMA
- PARENTESIS_IZQUIERDO
- PARENTESIS_DERECHO
