# Arquitectura del Compilador PyMini - Fases 1 y 2

## Visión General

PyMini es un compilador educativo que implementa un subconjunto de Python. Las Fases 1 y 2 cubren el **front-end** completo del compilador: análisis léxico, análisis sintáctico, construcción del AST y análisis semántico.

```
┌────────────────────────────────────────────────────────────────────┐
│                       Compilador PyMini                             │
│                                                                     │
│  archivo.pymini → [Lexer] → [Parser] → [AST] → [Sema] → ✓         │
│                     ↓         ↓          ↓        ↓                 │
│                  Tokens   Gramática   Árbol   Semántica            │
│                                                  ↓                  │
│                                            [Tabla Símbolos]         │
│                                            [Verificación Tipos]     │
└────────────────────────────────────────────────────────────────────┘
```

## Componentes Principales

### 1. Analizador Léxico (Lexer) - `lexer.l`

**Responsabilidad**: Convertir el texto fuente en tokens.

**Implementación**: Flex (generador de analizadores léxicos)

**Funcionalidad**:
- Lee el archivo fuente carácter por carácter
- Identifica patrones (palabras clave, identificadores, operadores, etc.)
- Genera tokens para el parser
- Mantiene registro de línea y columna para reportar errores
- Ignora comentarios y espacios en blanco

**Tokens Generados**:
- Palabras clave: `if`, `elif`, `else`, `while`, `def`, `return`, `print`, `True`, `False`
- Operadores: `+`, `-`, `*`, `/`, `%`, `==`, `!=`, `<`, `<=`, `>`, `>=`, `and`, `or`, `not`
- Símbolos: `=`, `(`, `)`, `{`, `}`, `:`, `,`
- Literales: números enteros, booleanos
- Identificadores: nombres de variables y funciones

**Ejemplo**:
```python
x = 5 + 3
```
Tokens generados: `IDENT(x)`, `ASSIGN`, `INT_LIT(5)`, `OP_PLUS`, `INT_LIT(3)`

### 2. Analizador Sintáctico (Parser) - `parser.y`

**Responsabilidad**: Verificar que los tokens siguen la gramática del lenguaje y construir el AST.

**Implementación**: Bison (generador de parsers LALR)

**Funcionalidad**:
- Lee tokens del lexer
- Verifica que la secuencia de tokens es sintácticamente válida
- Construye el árbol de sintaxis abstracta (AST)
- Reporta errores sintácticos con ubicación
- Implementa precedencia y asociatividad de operadores

**Gramática Simplificada**:
```
program     → stmt_list
stmt_list   → stmt*
stmt        → simple_stmt | compound_stmt
simple_stmt → assign_stmt | print_stmt | return_stmt
assign_stmt → IDENT '=' expr
print_stmt  → 'print' '(' expr ')'
compound_stmt → if_stmt | while_stmt | func_def
if_stmt     → 'if' expr ':' block elif_list opt_else
while_stmt  → 'while' expr ':' block
func_def    → 'def' IDENT '(' params ')' ':' block
expr        → or_expr
or_expr     → and_expr ('or' and_expr)*
and_expr    → not_expr ('and' not_expr)*
...
```

**Precedencia de Operadores** (de menor a mayor):
1. `or`
2. `and`
3. `not` (unario)
4. Comparaciones: `==`, `!=`, `<`, `<=`, `>`, `>=`
5. `+`, `-`
6. `*`, `/`, `%`
7. `-` unario

### 3. Árbol de Sintaxis Abstracta (AST) - `ast.h/c`

**Responsabilidad**: Representar la estructura del programa de manera jerárquica.

**Estructura**:
```c
typedef enum {
    AST_PROGRAM,
    AST_STMT_LIST,
    AST_ASSIGN,
    AST_PRINT,
    AST_IF,
    AST_WHILE,
    AST_FUNC_DEF,
    AST_BIN_OP,
    AST_CALL,
    AST_NAME,
    AST_INT_LIT,
    ...
} AstKind;

struct Ast {
    AstKind kind;
    Location loc;  // línea y columna
    union {
        // Datos específicos de cada tipo de nodo
    } data;
};
```

**Ventajas del AST**:
- Elimina detalles sintácticos innecesarios (paréntesis, llaves, etc.)
- Representa claramente la jerarquía del programa
- Facilita fases posteriores (análisis semántico, generación de código)
- Incluye información de ubicación para reportar errores

**Ejemplo**:
```python
x = 1 + 2 * 3
```

AST resultante:
```
Assign
  name: "x"
  value:
    BinOp '+'
      left: IntLit(1)
      right:
        BinOp '*'
          left: IntLit(2)
          right: IntLit(3)
```

### 4. Pretty-Printer - `ast_print.h/c`

**Responsabilidad**: Visualizar el AST de manera legible.

**Funcionalidad**:
- Recorre el AST recursivamente
- Imprime cada nodo con indentación apropiada
- Muestra información de ubicación (línea:columna)
- Ayuda a validar que el parsing fue correcto

### 5. Sistema de Tipos - `types.h/c`

**Responsabilidad**: Definir y manejar tipos del lenguaje.

**Implementación**: Enumeración de tipos básicos

**Funcionalidad**:
- Define tipos: `TY_INT`, `TY_BOOL`, `TY_UNKNOWN`, `TY_ERROR`
- Conversión de tipo a string (`type_name`)
- Verificación de compatibilidad (`types_compatible`)
- Propagación de errores de tipo

### 6. Sistema de Diagnóstico - `diag.h/c`

**Responsabilidad**: Reportar errores y advertencias semánticas.

**Funcionalidad**:
- Contador global de errores (`g_error_count`)
- Función `diag_error(line, col, formato, ...)` para reportar errores
- Función `diag_warn` para advertencias
- Función `diag_reset` para resetear contador
- Formato: `línea:columna: error: mensaje`

### 7. Tabla de Símbolos - `symtab.h/c`

**Responsabilidad**: Almacenar información sobre identificadores (variables y funciones).

**Implementación**: Hash table con scopes anidados

**Estructuras**:
```c
typedef enum {
    SYM_VAR,   // Variable
    SYM_FUNC   // Función
} SymbolKind;

typedef struct Symbol {
    char* name;
    SymbolKind kind;
    Type type;              // Tipo de variable o retorno
    Type return_type;       // Para funciones
    int arity;              // Número de parámetros
    Type* param_types;      // Tipos de parámetros
    char** param_names;     // Nombres de parámetros
    struct Symbol* next;    // Para colisiones en hash
} Symbol;

typedef struct Scope {
    struct Scope* parent;   // Scope padre
    Symbol** symbols;       // Hash table (16 buckets)
    int capacity;
    int count;
} Scope;
```

**Operaciones**:
- `scope_push(parent)`: Crear nuevo scope hijo
- `scope_pop(scope)`: Destruir scope y retornar al padre
- `sym_lookup(scope, name)`: Buscar símbolo (busca en cadena de scopes)
- `sym_lookup_current(scope, name)`: Buscar solo en scope actual
- `sym_insert(scope, symbol)`: Insertar símbolo en scope actual
- `sym_make_var(name, type)`: Constructor de símbolo variable
- `sym_make_func(name, arity)`: Constructor de símbolo función

### 8. Análisis Semántico - `sema.h/c`

**Responsabilidad**: Verificar reglas semánticas del lenguaje.

**Implementación**: Visitador de AST en dos pasadas

**Contexto Semántico**:
```c
typedef struct {
    Scope* scope;           // Scope actual
    Symbol* current_func;   // Función actual (NULL si global)
    int in_function;        // Flag: dentro de función?
} SemaCtx;
```

**Funcionalidad**:

**Pasada 0** - Recolección de firmas de funciones:
- Recorre el programa buscando definiciones de funciones
- Inserta símbolos de función en scope global
- Determina aridad de cada función

**Pasada 1** - Análisis semántico completo:
- Verifica declaración de variables antes de uso
- Verifica tipos en operadores (aritméticos requieren int, lógicos requieren bool)
- Verifica tipos en condiciones (if/while requieren bool)
- Verifica aridad de llamadas a funciones
- Verifica uso correcto de return (solo dentro de funciones)
- Detecta reasignaciones con tipo incompatible
- Gestiona scopes anidados (funciones, bloques)
- Propaga tipos en expresiones
- Reporta errores con ubicación precisa

**Reglas Semánticas Verificadas**:
1. Variable usada antes de ser asignada → ERROR
2. Tipos incompatibles en operadores → ERROR
3. Condición no booleana en if/while → ERROR
4. Aridad incorrecta en llamada a función → ERROR
5. Return fuera de función → ERROR
6. Reasignación con tipo incompatible → ERROR
7. Uso de función como variable → ERROR
8. Uso de variable como función → ERROR

### 9. Main - `main.c`

**Responsabilidad**: Punto de entrada del compilador.

**Funcionalidad**:
- Procesa argumentos de línea de comandos
- Abre el archivo fuente
- Invoca el parser
- Imprime el AST si el parsing fue exitoso
- Invoca el análisis semántico
- Reporta errores léxicos, sintácticos y semánticos
- Retorna código de salida apropiado
- Libera memoria

## Flujo de Compilación

```
┌────────────────────────────────────────────────────────────────┐
│ 1. ENTRADA: archivo.pymini                                     │
└────────────────────────────────────────────────────────────────┘
                           ↓
┌────────────────────────────────────────────────────────────────┐
│ 2. ANÁLISIS LÉXICO (lexer.l)                                   │
│    - Lee caracteres                                            │
│    - Genera tokens                                             │
│    - Rastrea línea y columna                                   │
└────────────────────────────────────────────────────────────────┘
                           ↓
                    [Stream de Tokens]
                           ↓
┌────────────────────────────────────────────────────────────────┐
│ 3. ANÁLISIS SINTÁCTICO (parser.y)                              │
│    - Verifica gramática                                        │
│    - Construye AST                                             │
│    - Reporta errores sintácticos                               │
└────────────────────────────────────────────────────────────────┘
                           ↓
                     [AST completo]
                           ↓
┌────────────────────────────────────────────────────────────────┐
│ 4. ANÁLISIS SEMÁNTICO (sema.c)                                 │
│    PASADA 0: Recolectar funciones                              │
│    - Construye tabla de símbolos de funciones                  │
│    - Verifica conflictos de nombres                            │
│    PASADA 1: Análisis completo                                 │
│    - Verifica tipos                                            │
│    - Valida uso de variables                                   │
│    - Comprueba retornos y llamadas                             │
│    - Reporta errores semánticos                                │
└────────────────────────────────────────────────────────────────┘
                           ↓
                [Validación semántica OK]
                           ↓
┌────────────────────────────────────────────────────────────────┐
│ 5. VISUALIZACIÓN (ast_print.c)                                 │
│    - Imprime el AST                                            │
│    - Muestra estructura del programa                           │
└────────────────────────────────────────────────────────────────┘
                           ↓
┌────────────────────────────────────────────────────────────────┐
│ 6. SALIDA: "Semantic OK" + AST impreso                         │
└────────────────────────────────────────────────────────────────┘
```

## Manejo de Errores

### Errores Léxicos
- **Causa**: Carácter inválido en el código fuente
- **Ejemplo**: `x = 5 @ 3` (@ no es válido)
- **Reporte**: `Error léxico en línea X, columna Y: carácter inválido '@'`
- **Recuperación**: Continúa parseando

### Errores Sintácticos
- **Causa**: Secuencia de tokens que no sigue la gramática
- **Ejemplo**: `if x > 5 { print(x) }` (falta ':')
- **Reporte**: `Error sintáctico en línea X, columna Y: syntax error, unexpected LBRACE, expecting COLON`
- **Recuperación**: Intenta sincronizar en el siguiente statement

### Errores Semánticos
- **Causa**: Código sintácticamente correcto pero semánticamente inválido
- **Ejemplos**:
  - Variable no declarada: `print(x)` sin definir `x`
  - Incompatibilidad de tipos: `x = 5; y = x and True`
  - Condición no booleana: `if 42: print("x")`
  - Error de aridad: `foo(1, 2)` cuando `foo` espera 1 parámetro
  - Conflicto de parámetros: `def foo(x, x): return x`
  - Retorno fuera de función: `return 5` en código global
- **Reporte**: `Error semántico en línea X, columna Y: [descripción del error]`
- **Comportamiento**: Acumula errores y reporta al final, retorna exit code 1

## Gestión de Memoria

### Estrategia:
1. **Lexer**: Usa buffers de Flex (manejados automáticamente)
2. **Strings**: Se duplican al crear nodos AST (`strdup`)
3. **AST**: Memoria asignada dinámicamente
4. **Liberación**: Función `ast_free()` recorre recursivamente el árbol

### Importante:
- Todo nodo AST creado debe ser liberado
- Los strings en los nodos se duplican para evitar referencias dangling
- El parser libera el AST en caso de error

## Herramientas Utilizadas

### Flex (Fast Lexical Analyzer)
- Generador de analizadores léxicos
- Lee especificación en formato `.l`
- Genera código C (`lex.yy.c`)
- Eficiente y ampliamente usado

### Bison (GNU Parser Generator)
- Generador de parsers LALR(1)
- Lee especificación en formato `.y`
- Genera código C (`y.tab.c` y `y.tab.h`)
- Soporta precedencia y asociatividad
- Modo de error verbose

## Diseño de la Gramática

### Decisiones de Diseño:

1. **Bloques con llaves**: En lugar de indentación Python, usamos `{ }` para simplificar el lexer (no necesitamos tokens INDENT/DEDENT)

2. **Precedencia explícita**: Definida en Bison para resolver conflictos shift/reduce

3. **Listas dinámicas**: Para statements, parámetros, argumentos, etc.

4. **Elif como lista**: Los elif se agrupan en una lista separada para facilitar el procesamiento

5. **Separación clara**: Simple statements vs compound statements

## Extensibilidad

La arquitectura está diseñada para ser extensible en fases futuras:

### Fase 2: Análisis Semántico
- Implementar tabla de símbolos completa
- Verificación de tipos
- Resolución de nombres
- Verificación de scopes

### Fase 3: Generación de Código Intermedio
- Añadir módulo de IR (Intermediate Representation)
- Traducir AST a IR
- Optimizaciones a nivel IR

### Fase 4: Generación de Código
- Backend para arquitectura objetivo
- Optimizaciones de código máquina

### Fase 5: Runtime
- Sistema de tipos en tiempo de ejecución
- Garbage collector (opcional)
- Biblioteca estándar mínima

## Métricas del Proyecto

- **Líneas de código** (aproximado):
  - Lexer: ~150 líneas
  - Parser: ~350 líneas
  - AST: ~450 líneas
  - Pretty-printer: ~200 líneas
  - Sistema de tipos: ~150 líneas
  - Diagnósticos: ~100 líneas
  - Tabla de símbolos: ~300 líneas
  - Analizador semántico: ~450 líneas
  - Main: ~100 líneas
  - **Total: ~2250 líneas**

- **Tokens soportados**: 25+
- **Tipos de nodos AST**: 20+
- **Tests incluidos**: 
  - 6 tests positivos (deben pasar)
  - 8 tests negativos (deben fallar con errores específicos)
  - **Total: 14 tests**

## Referencias y Recursos

- **Flex Manual**: https://westes.github.io/flex/manual/
- **Bison Manual**: https://www.gnu.org/software/bison/manual/
- **Dragon Book**: "Compilers: Principles, Techniques, and Tools" by Aho, Lam, Sethi, Ullman
- **Engineering a Compiler**: by Cooper and Torczon

## Limitaciones Conocidas

### Completado (Fases 1 y 2)
1. ✓ Análisis léxico completo
2. ✓ Análisis sintáctico completo
3. ✓ Construcción de AST
4. ✓ Verificación semántica (variables, tipos, funciones)
5. ✓ Tabla de símbolos con alcance (scope)
6. ✓ Sistema de tipos (int, bool)
7. ✓ Reportes de error con línea y columna

### Pendiente (Fases futuras)
1. ✗ No se genera código ejecutable (requiere Fase 3: Generación de código)
2. ✗ Soporte limitado para tipos (solo int y bool, sin strings, listas, etc.)
3. ✗ Sin optimizaciones de código
4. ✗ Sin inferencia de tipos avanzada
5. ✗ Sin manejo de excepciones
4. ✗ No hay optimizaciones
5. ✗ No hay soporte para indentación tipo Python
6. ✗ Sintaxis limitada a un subconjunto simple

Estas limitaciones se abordarán en fases futuras del proyecto.
