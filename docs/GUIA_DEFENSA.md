# Guia para defensa del proyecto - Compilador PyMini

Esta guia conecta las **preguntas tipicas de defensa** con el **codigo real implementado** en PyMini.

---

## 1. Estructura general del compilador

### Pregunta: ¿Cuales son las fases principales y donde estan en tu codigo?

**Respuesta:**
PyMini implementa las fases clasicas de compilacion:

1. **Analisis lexico** → `src/lexer.l`
    - Convierte texto en tokens (IDENT, NUMBER, KW_IF, etc.)
    - Genera: `build/lex.yy.c`

2. **Analisis sintactico** → `src/parser.y`
    - Construye el AST desde los tokens
    - Genera: `build/parser.tab.c` y `build/parser.tab.h`

3. **Analisis semantico** → `src/sema.c` + `src/symtab.c` + `src/types.c`
    - Valida tipos, variables y funciones
    - Usa tabla de simbolos jerarquica

4. **Generacion de codigo** → `src/codegen_c.c`
    - Traduce AST a codigo C
    - Salida: archivo `.c` intermedio

5. **Pipeline completo** → `src/pipeline.c`
    - Orquesta todas las fases
    - Invoca GCC para compilar el C generado

**Archivos clave para mostrar:**
```
src/main.c         # Punto de entrada
src/pipeline.c     # Coordinacion de fases
src/cli.c          # Interfaz de usuario
```

---

## 2. Analisis lexico (Flex)

### Pregunta: ¿Como reconoces tokens y manejas errores?

**Respuesta:**
Uso Flex con expresiones regulares en `src/lexer.l`:

**Ejemplos de patrones:**
```c
// Linea 134-142 en lexer.l
"if"        { return KW_IF; }
"while"     { return KW_WHILE; }
"print"     { return KW_PRINT; }
"input"     { return KW_INPUT; }
"int"       { return KW_INT; }
"str"       { return KW_STR; }

// Linea 160-170: Identificadores
[a-zA-Z_][a-zA-Z0-9_]* {
     yylval.str_val = strdup(yytext);
     return IDENT;
}

// Linea 175-180: Numeros
[0-9]+ {
     yylval.int_val = atoi(yytext);
     return INT_LIT;
}

// Linea 186-198: Strings
\"([^\"\\\n]|\\.)*\" {
     // Copiar sin comillas
     char* str = malloc(len + 1);
     strncpy(str, yytext + 1, len);
     yylval.str_val = str;
     return STRING_LIT;
}
```

**Manejo de errores lexicos:**
```c
// Linea 330-340 en lexer.l
.   {
     fprintf(stderr, "Error lexico: caracter inesperado '%c' en linea %d\n",
                yytext[0], yyline);
     // Continuar parseando
}
```

**Demostrar con:**
- Crear un archivo con error: `x = @123;` → Error lexico
- Mostrar mensaje de error con linea exacta

---

## 3. Analisis sintactico (Bison)

### Pregunta: ¿Que tipo de parser usas y como resuelves conflictos?

**Respuesta:**
Implemente un parser LR(1) con Bison en `src/parser.y`.

**Gramatica ejemplo:**
```yacc
// Linea 108-115: Programa principal
program:
     stmt_list NEWLINE
          { 
                parse_result = ast_new_program($1, LOC);
          }
     ;

// Linea 265-275: Expresiones OR (asociatividad izquierda)
or_expr:
     and_expr
          { $$ = $1; }
     | or_expr TOK_OR and_expr
          { $$ = ast_new_bin_op(OP_OR, $1, $3, LOC); }
     ;

// Linea 310-320: Operaciones aritmeticas
add_expr:
     mult_expr
          { $$ = $1; }
     | add_expr TOK_PLUS mult_expr
          { $$ = ast_new_bin_op(OP_ADD, $1, $3, LOC); }
     | add_expr TOK_MINUS mult_expr
          { $$ = ast_new_bin_op(OP_SUB, $1, $3, LOC); }
     ;
```

**Precedencia y asociatividad:**
```yacc
// Linea 89-95 en parser.y
%left TOK_OR                    // Menor precedencia
%left TOK_AND
%right TOK_NOT
%left TOK_EQ TOK_NE TOK_LT TOK_LE TOK_GT TOK_GE
%left TOK_PLUS TOK_MINUS
%left TOK_STAR TOK_SLASH TOK_MOD
%right UNARY                    // Mayor precedencia
```

**Resolucion de conflictos:**
- Shift/Reduce en expresiones → Resuelto con `%left` y `%right`
- Dangling else → Resuelto con precedencia implicita
- Ver: `build/parser.output` para analisis detallado

**Resultado: AST**
```c
// src/ast.h linea 74-204
struct Ast {
     AstKind kind;        // Tipo de nodo
     Location loc;        // Linea y columna
     Type type;           // Tipo inferido (semantico)
     union { ... } data;  // Datos especificos del nodo
};
```

---

## 4. Analisis semantico

### Pregunta: ¿Que validas y como manejas tipos y ambitos?

**Respuesta:**
El analisis semantico esta en `src/sema.c` y valida:

**1. Variables no declaradas:**
```c
// src/sema.c linea 185-198
case AST_NAME: {
     char* name = node->data.name.id;
     Symbol* sym = sym_lookup(ctx->scope, name);
     
     if (!sym) {
          diag_error(node->loc.line, node->loc.column,
                "variable '%s' no declarada o usada antes de asignar", name);
          node->type = TY_ERROR;
          return TY_ERROR;
     }
     // ...
}
```

**2. Compatibilidad de tipos:**
```c
// src/sema.c linea 24-42
static Type check_bin_op_types(SemaCtx* ctx, Ast* node, Type left_ty, Type right_ty) {
     OpKind op = node->data.bin_op.op;
     
     if (op == OP_ADD || op == OP_SUB || op == OP_MUL || op == OP_DIV || op == OP_MOD) {
          // Caso especial: + entre strings es concatenacion
          if (op == OP_ADD && left_ty == TY_STRING && right_ty == TY_STRING) {
                return TY_STRING;
          }
          
          if (left_ty != TY_INT || right_ty != TY_INT) {
                diag_error(node->loc.line, node->loc.column,
                     "operador aritmetico '%s' requiere int (encontrado %s y %s)",
                     op_kind_to_string(op), type_name(left_ty), type_name(right_ty));
                return TY_ERROR;
          }
          return TY_INT;
     }
     // ...
}
```

**3. Tabla de simbolos jerarquica:**
```c
// src/symtab.c linea 20-45
typedef struct Scope {
     struct Scope* parent;    // Ambito padre
     Symbol* symbols;         // Lista de simbolos
     size_t count;
     size_t capacity;
} Scope;

// Busqueda recursiva en ambitos
Symbol* sym_lookup(Scope* scope, const char* name) {
     while (scope) {
          Symbol* sym = sym_lookup_current(scope, name);
          if (sym) return sym;
          scope = scope->parent;  // Subir al ambito padre
     }
     return NULL;
}
```

**4. Validacion de funciones:**
```c
// src/sema.c linea 220-245
case AST_CALL: {
     // Verificar que existe
     Symbol* sym = sym_lookup(ctx->scope, name);
     if (!sym) {
          diag_error(..., "funcion '%s' no declarada", name);
     }
     
     // Verificar aridad (numero de parametros)
     if (arg_count != sym->arity) {
          diag_error(..., "funcion '%s' espera %d argumento(s), pero se le pasaron %d",
                         name, sym->arity, arg_count);
     }
}
```

**Sistema de tipos:**
```c
// src/types.h linea 8-15
typedef enum {
     TY_UNKNOWN,   // No inferido aun
     TY_INT,       // Entero
     TY_BOOL,      // Booleano
     TY_STRING,    // String
     TY_ERROR      // Error de tipo
} Type;
```

**Demostrar con archivos de prueba:**
- `tests/neg/n01_undeclared.pymini` → Variable no declarada
- `tests/neg/n02_type_op.pymini` → Operador con tipos incorrectos
- `tests/neg/n04_arity.pymini` → Funcion con aridad incorrecta

---

## 5. Generacion de codigo

### Pregunta: ¿Como traduces PyMini a C?

**Respuesta:**
`src/codegen_c.c` recorre el AST y emite codigo C.

**Ejemplo: if-elif-else**
```c
// src/codegen_c.c linea 250-285
static void codegen_if(CodegenCtx* ctx, Ast* node) {
     // if
     emit_indent(ctx);
     emit_raw(ctx, "if (");
     codegen_expr(ctx, node->data.if_stmt.condition);
     emit_raw(ctx, ") {\n");
     
     ctx->indent_level++;
     codegen_stmt_list(ctx, node->data.if_stmt.then_block->data.block.stmts);
     ctx->indent_level--;
     emit_line(ctx, "}");
     
     // elif
     if (node->data.if_stmt.elif_list) {
          for (size_t i = 0; i < elif_list->data.elif_list.count; i++) {
                emit_raw(ctx, "else if (");
                codegen_expr(ctx, elif->data.elif.condition);
                emit_raw(ctx, ") {\n");
                // ...
          }
     }
     
     // else
     if (node->data.if_stmt.else_block) {
          emit_line(ctx, "else {");
          codegen_stmt_list(ctx, ...);
          emit_line(ctx, "}");
     }
}
```

**Ejemplo: while**
```c
// src/codegen_c.c linea 290-300
static void codegen_while(CodegenCtx* ctx, Ast* node) {
     emit_indent(ctx);
     emit_raw(ctx, "while (");
     codegen_expr(ctx, node->data.while_stmt.condition);
     emit_raw(ctx, ") {\n");
     
     ctx->indent_level++;
     codegen_stmt_list(ctx, node->data.while_stmt.body->data.block.stmts);
     ctx->indent_level--;
     emit_line(ctx, "}");
}
```

**Mapeo de tipos:**
```c
// src/codegen_c.c linea 70-78
static const char* type_to_c(Type t) {
     switch (t) {
          case TY_INT:
          case TY_BOOL:
                return "int";       // bool se mapea a int (0/1)
          case TY_STRING:
                return "const char*";
          default:
                return "int";
     }
}
```

**Runtime para operaciones especiales:**
```c
// src/runtime.h linea 12-50
void rt_print_int(int x);
void rt_print_bool(int b);
void rt_print_string(const char* s);
int rt_input_int(const char* prompt);
char* rt_input_string(const char* prompt);
char* rt_str_concat(const char* a, const char* b);
int rt_str_to_int(const char* s);
char* rt_int_to_str(int n);
int rt_div(int a, int b);      // Con verificacion de /0
int rt_mod(int a, int b);      // Con verificacion de %0
```

**¿Por que C y no ensamblador?**
- Portabilidad entre arquitecturas
- Facilita depuracion
- Aprovecha optimizaciones de GCC
- Codigo legible para aprendizaje

**Ver codigo generado:**
```bash
./bin/pymini -emit-c programa.pymini -o salida.c
cat salida.c  # Ver el codigo C generado
```

---

## 6. Optimizaciones

### Pregunta: ¿Que optimizaciones implementaste?

**Respuesta:**
Implemente optimizaciones basicas en `src/opt.c`:

**1. Constant folding (plegado de constantes):**
```c
// src/opt.c linea 25-55
static Ast* opt_fold_binary(Ast* node) {
     if (node->data.bin_op.left->kind == AST_INT_LIT &&
          node->data.bin_op.right->kind == AST_INT_LIT) {
          
          int left = node->data.bin_op.left->data.int_lit.value;
          int right = node->data.bin_op.right->data.int_lit.value;
          int result;
          
          switch (node->data.bin_op.op) {
                case OP_ADD: result = left + right; break;
                case OP_SUB: result = left - right; break;
                case OP_MUL: result = left * right; break;
                // ...
          }
          
          // Reemplazar nodo por literal
          ast_free(node->data.bin_op.left);
          ast_free(node->data.bin_op.right);
          node->kind = AST_INT_LIT;
          node->data.int_lit.value = result;
     }
     return node;
}
```

**Ejemplo:**
```python
# Antes de optimizar
x = 5 + 3 * 2

# Despues de constant folding
x = 11
```

**2. Dead code elimination:**
```c
// src/opt.c linea 80-95
static Ast* opt_dead_code(Ast* node) {
     if (node->kind == AST_IF) {
          // if True: ... → ejecutar solo then
          if (node->data.if_stmt.condition->kind == AST_BOOL_LIT &&
                node->data.if_stmt.condition->data.bool_lit.value) {
                return node->data.if_stmt.then_block;
          }
          // if False: ... → ejecutar solo else o eliminar
          if (node->data.if_stmt.condition->kind == AST_BOOL_LIT &&
                !node->data.if_stmt.condition->data.bool_lit.value) {
                return node->data.if_stmt.else_block;
          }
     }
}
```

**Activar con:**
```bash
./bin/pymini -O programa.pymini
```

---

## 7. Manejo de errores

### Pregunta: ¿Como manejas errores en cada fase?

**Respuesta:**
Sistema unificado de diagnosticos en `src/diag.c`:

```c
// src/diag.c linea 10-30
void diag_error(int line, int col, const char* fmt, ...) {
     fprintf(stderr, "%d:%d: error: ", line, col);
     
     va_list args;
     va_start(args, fmt);
     vfprintf(stderr, fmt, args);
     va_end(args);
     
     fprintf(stderr, "\n");
     g_error_count++;
}

void diag_warning(int line, int col, const char* fmt, ...) {
     fprintf(stderr, "%d:%d: warning: ", line, col);
     // ...
}
```

**Ejemplos de errores por fase:**

**Lexico:**
```c
// src/lexer.l
Error lexico: caracter inesperado '@' en linea 5
```

**Sintactico:**
```c
// parser.y
syntax error, unexpected IDENT, expecting COLON at line 10
```

**Semantico:**
```c
// src/sema.c
5:16: error: operador aritmetico '+' requiere int (encontrado str y str)
7:12: error: variable 'suma' no declarada o usada antes de asignar
```

**Runtime:**
```c
// src/runtime.c linea 105-120
int rt_div(int a, int b) {
     if (b == 0) {
          fprintf(stderr, "\n╔═══════════════════════════════════╗\n");
          fprintf(stderr, "║   Runtime Error                   ║\n");
          fprintf(stderr, "╠═══════════════════════════════════╣\n");
          fprintf(stderr, "║ Division por cero detectada       ║\n");
          fprintf(stderr, "║ Operacion: %d / %d                ║\n", a, b);
          fprintf(stderr, "╚═══════════════════════════════════╝\n\n");
          exit(EXIT_FAILURE);
     }
     return a / b;
}
```

**Pipeline:**
```c
// src/pipeline.c linea 40-60
if (lex_errors > 0) {
     return 1;  // Detener compilacion
}
if (parse_errors > 0) {
     return 1;  // No continuar al semantico
}
if (sema_errors > 0) {
     return 1;  // No generar codigo
}
```

---

## 8. Pruebas y validacion

### Pregunta: ¿Como probaste el compilador?

**Respuesta:**
Suite completa de tests en `tests/`:

**Tests positivos (deben compilar y ejecutar):**
```
tests/t01_expr.pymini         # Expresiones aritmeticas
tests/t02_if.pymini           # Condicionales
tests/t03_while.pymini        # Bucles
tests/t04_func.pymini         # Funciones
tests/t05_complex_expr.pymini # Expresiones complejas
tests/t06_elif.pymini         # If-elif-else
tests/t07_recursion.pymini    # Recursion
tests/t08_nested_loops.pymini # Bucles anidados
```

**Tests negativos (deben detectar errores):**
```
tests/neg/n01_undeclared.pymini    # Variable no declarada
tests/neg/n02_type_op.pymini       # Tipo incorrecto en operador
tests/neg/n03_if_bool.pymini       # If con tipo no-bool
tests/neg/n04_arity.pymini         # Funcion con aridad incorrecta
tests/neg/n05_param_conflict.pymini # Conflicto de parametros
tests/neg/n06_reassign_type.pymini  # Reasignacion con tipo diferente
tests/neg/n07_return_outside.pymini # Return fuera de funcion
tests/neg/n08_while_bool.pymini    # While con tipo no-bool
```

**Script de tests:**
```bash
# tests/run.sh
for test in tests/t*.pymini; do
     ./bin/pymini "$test" && echo "✓ $test PASS" || echo "✗ $test FAIL"
done

for test in tests/neg/*.pymini; do
     ./bin/pymini "$test" 2>&1 | grep -q "error" && echo "✓ $test PASS" || echo "✗ $test FAIL"
done
```

**Ejecutar tests:**
```bash
cd tests && bash run.sh
```

**Ejemplos interactivos:**
```
examples/test_input.pymini           # Input basico
examples/test_calculator.pymini      # Calculadora
examples/test_input_factorial.pymini # Factorial interactivo
```

---

## 9. Aspectos de implementacion

### Pregunta: ¿Que herramientas usaste y por que?

**Respuesta:**

**Herramientas principales:**
- Flex 2.6+ → Generador de lexer (analisis lexico)
- Bison 3.0+ → Generador de parser LR(1)
- GCC → Compilador de backend
- Make → Sistema de construccion
- VS Code → IDE de desarrollo

**¿Por que Flex y Bison?**
- Estandar de la industria
- Generan codigo C eficiente
- Manejo automatico de precedencia y ambiguedades
- Integracion perfecta con GCC
- Amplia documentacion

**Arquitectura del proyecto:**
```
Compilador_Python/
├── src/              # Codigo fuente C
│   ├── lexer.l       # Especificacion lexica (Flex)
│   ├── parser.y      # Gramatica (Bison)
│   ├── ast.{c,h}     # Arbol sintactico abstracto
│   ├── sema.{c,h}    # Analisis semantico
│   ├── types.{c,h}   # Sistema de tipos
│   ├── symtab.{c,h}  # Tabla de simbolos
│   ├── codegen_c.{c,h} # Generador de codigo C
│   ├── pipeline.{c,h}  # Orquestador
│   ├── runtime.{c,h}   # Runtime del lenguaje
│   └── main.c        # Punto de entrada
├── build/            # Archivos generados (.o, lex.yy.c, etc.)
├── bin/              # Ejecutable pymini
├── tests/            # Suite de pruebas
├── examples/         # Ejemplos de uso
├── docs/             # Documentacion
└── Makefile          # Sistema de construccion
```

**Compilacion:**
```bash
make clean    # Limpiar archivos generados
make -j       # Compilar en paralelo
make test     # Ejecutar tests
make install  # Instalar (opcional)
```

**Uso:**
```bash
# Compilar y ejecutar
./bin/pymini programa.pymini

# Solo verificar sintaxis
./bin/pymini -check programa.pymini

# Generar codigo C intermedio
./bin/pymini -emit-c programa.pymini -o salida.c

# Con optimizaciones
./bin/pymini -O programa.pymini

# Ver AST
./bin/pymini -dump-ast programa.pymini
```

**Compatibilidad:**
- Linux (Ubuntu, Fedora, Arch)
- macOS (con Homebrew)
- WSL (Windows Subsystem for Linux)

---

## 10. Preguntas conceptuales

### ¿Que es una gramatica libre de contexto?

**Respuesta:**
Una gramatica que define la sintaxis de un lenguaje mediante reglas de produccion.

**Ejemplo en PyMini:**
```yacc
// parser.y linea 108-130
program → stmt_list
stmt_list → stmt | stmt_list stmt
stmt → assign_stmt | print_stmt | if_stmt | while_stmt
expr → expr + term | expr - term | term
term → term * factor | term / factor | factor
factor → NUMBER | IDENT | ( expr )
```

**Caracteristicas:**
- Lado izquierdo: un solo no-terminal
- Lado derecho: cualquier combinacion de terminales y no-terminales
- No depende del contexto circundante

---

### ¿Diferencia entre lenguaje regular y libre de contexto?

**Lenguajes regulares:**
- Reconocibles por automatas finitos
- Expresables con expresiones regulares
- Ejemplo en PyMini: tokens del lexer

```c
// lexer.l
[0-9]+              → NUMBER
[a-zA-Z_][a-zA-Z0-9_]* → IDENT
"if"|"while"        → KEYWORDS
```

**Lenguajes libres de contexto:**
- Reconocibles por automatas de pila
- Expresables con gramaticas (Bison)
- Ejemplo en PyMini: estructura del programa

```python
# Requiere pila para balancear
if x > 0:
     if y > 0:
          print(x)  # Dos niveles de anidacion
```

---

### ¿Que es una reduccion?

**Respuesta:**
Proceso inverso a una derivacion. El parser reduce una secuencia de tokens/no-terminales a un no-terminal segun las reglas.

**Ejemplo:**
```
Entrada: x = 5 + 3

Tokens:  IDENT ASSIGN NUMBER PLUS NUMBER

Reducciones:
5        → factor (reducir)
factor   → term
3        → factor
factor   → term
term + term → expr (reducir)
x = expr → assign_stmt (reducir)
```

Ver en: `build/parser.output` (estados y reducciones del parser)

---

### ¿Que papel cumple el AST?

**Respuesta:**
El AST (abstract syntax tree) es la representacion estructurada del codigo despues del parseo.

**Ventajas:**
- Elimina detalles sintacticos innecesarios (parentesis, punto y coma)
- Facilita analisis semantico (visitas recursivas)
- Base para generacion de codigo
- Permite optimizaciones

**Estructura en PyMini:**
```c
// src/ast.h
typedef enum {
     AST_PROGRAM,
     AST_IF, AST_WHILE, AST_FUNC_DEF,
     AST_BIN_OP, AST_CALL, AST_ASSIGN,
     // ...
} AstKind;

struct Ast {
     AstKind kind;
     Location loc;        // Para mensajes de error
     Type type;           // Inferido por semantico
     union { ... } data;  // Datos especificos
};
```

**Ver AST:**
```bash
./bin/pymini -dump-ast programa.pymini
```

---

### ¿Compilador vs interprete?

**Compilador (PyMini):**
- Traduce todo el codigo antes de ejecutar
- Genera codigo ejecutable (a traves de C)
- Mas rapido en ejecucion
- Detecta errores antes de ejecutar

**Interprete (Python estandar):**
- Ejecuta linea por linea
- No genera ejecutable
- Mas lento pero mas flexible
- Errores se detectan al ejecutar esa linea

PyMini es un compilador porque genera codigo C que luego GCC compila a ejecutable nativo.

---

## 11. Preguntas de reflexion final

### ¿Cual fue la parte mas dificil?

**Respuesta sugerida:**
> La parte mas compleja fue el analisis semantico, especificamente manejar los ambitos de variables en funciones anidadas y validar la compatibilidad de tipos en expresiones complejas.
> 
> Implementar la tabla de simbolos jerarquica (`src/symtab.c`) con busqueda recursiva hacia ambitos padres fue un desafio, especialmente al manejar funciones dentro de funciones.
> 
> Otro reto fue el manejo de strings, ya que agregue soporte tardio y tuve que modificar el lexer, parser, sistema de tipos, codegen y runtime (`rt_str_concat`, `rt_input_string`).

### ¿Que aprendiste?

**Respuesta sugerida:**
> - Como funcionan realmente los compiladores mas alla de la teoria
> - La importancia de un buen diseno de errores para ayudar al programador
> - Como las fases se comunican a traves de estructuras de datos (tokens → AST → codigo)
> - El balance entre simplicidad y expresividad del lenguaje
> - Debugging con herramientas como gdb y valgrind

### ¿Que mejorarias con mas tiempo?

**Respuestas honestas:**
- F-strings completos (actualmente se usan `str()` + concatenacion)
- Mas tipos: listas, diccionarios, tuplas
- Clases y objetos (POO basica)
- Mejor sistema de modulos (import)
- Optimizaciones avanzadas: loop unrolling, inline de funciones
- Mensajes de error mas informativos (mostrar snippet de codigo)
- Generador de codigo LLVM en lugar de C (mas portable)

### ¿Limitaciones actuales?

**Respuestas honestas:**
- No soporta f-strings completos con `{expr}` embebidas
- No hay tipos compuestos (listas, tuplas, dicts)
- No hay clases ni herencia
- No hay excepciones (try/except)
- No hay modulos/imports
- Variables globales y locales comparten namespace en algunos casos
- Sin garbage collection (memoria de strings puede crecer)

---

## 12. Demo para la defensa

### Script de demostracion recomendado:

**1. Ejemplo simple (hello world + input):**
```python
# demo_basico.pymini
nombre = input('Como te llamas? ')
print('Hola ' + nombre + '!')
```

```bash
./bin/pymini demo_basico.pymini
```

**2. Ejemplo con logica (factorial):**
```python
# demo_factorial.pymini
def factorial(n):
     if n <= 1:
          return 1
     else:
          return n * factorial(n - 1)

n = int(input('Numero: '))
print('Factorial: ' + str(factorial(n)))
```

```bash
./bin/pymini demo_factorial.pymini
```

**3. Mostrar error semantico:**
```python
# demo_error.pymini
x = 5
y = 'hola'
z = x + y  # Error: tipos incompatibles
```

```bash
./bin/pymini demo_error.pymini
# Salida: error: operador aritmetico '+' requiere int (encontrado int y str)
```

**4. Mostrar codigo C generado:**
```bash
./bin/pymini -emit-c demo_factorial.pymini -o factorial.c
cat factorial.c  # Mostrar el codigo C
```

**5. Ver AST:**
```bash
./bin/pymini -dump-ast demo_basico.pymini
```

---



## Archivos clave por tema

| Tema | Archivos a revisar |
|------|-------------------|
| Lexico | `src/lexer.l` |
| Sintactico | `src/parser.y`, `build/parser.output` |
| AST | `src/ast.h`, `src/ast.c` |
| Semantico | `src/sema.c`, `src/symtab.c`, `src/types.c` |
| Codegen | `src/codegen_c.c`, `src/runtime.c` |
| Pipeline | `src/pipeline.c`, `src/main.c` |
| Tests | `tests/*.pymini`, `tests/neg/*.pymini` |
| Ejemplos | `examples/*.pymini` |

---

## Checklist final

Antes de la defensa, asegurar:

- [ ] Compilar el proyecto sin errores
- [ ] Ejecutar todos los tests (deben pasar)
- [ ] Preparar 2-3 ejemplos de demo
- [ ] Revisar `build/parser.output` (entender conflictos resueltos)
- [ ] Poder explicar cada fase con un archivo especifico
- [ ] Conocer las limitaciones del compilador
- [ ] Tener respuestas preparadas para las 10 categorias de preguntas
- [ ] Practicar explicacion del flujo completo (3-5 minutos)

---
