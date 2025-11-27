# Fase 5: Indentación Significativa Estilo Python

## Descripción General

La Fase 5 representa la implementación más importante del compilador PyMini: **la eliminación completa de llaves `{}` y la adopción de indentación significativa estilo Python**. Este cambio hace que PyMini sea 100% compatible sintácticamente con Python en sus estructuras de control.

---

## Cambios Implementados

### 1. Nuevos Tokens

Se agregaron tres nuevos tokens al lexer:

- **`INDENT`**: Marca el inicio de un bloque indentado
- **`DEDENT`**: Marca el fin de un bloque indentado
- **`NEWLINE`**: Marca el fin de una línea lógica

### 2. Sistema de Pila de Indentación

Implementación de un sistema robusto de seguimiento de niveles de indentación:

```c
#define MAX_INDENT_DEPTH 100
static int indent_stack[MAX_INDENT_DEPTH];
static int indent_stack_top = 0;
```

**Funcionalidades:**
- Rastreo de múltiples niveles de indentación anidados
- Generación automática de múltiples DEDENT cuando se reduce la indentación
- Validación de consistencia de niveles

### 3. Estados de Flex

Uso de estados exclusivos para el manejo correcto de la indentación:

- **`INDENT_STATE`**: Estado activo al inicio de cada línea
- **`INITIAL`**: Estado normal para tokens regulares

Este diseño evita que las palabras clave se consuman antes de detectar cambios de indentación.

### 4. Manejo de EOF

Sistema especial para generar DEDENT pendientes al final del archivo:

```c
int real_yylex(void) {
    // Si hay tokens pendientes, retornarlos primero
    if (pending_count > 0) {
        return pending_tokens[--pending_count];
    }
    
    int token = yylex();
    
    // Al final del archivo
    if (token == 0) {
        // Si falta NEWLINE, agregarlo
        if (!last_was_newline) {
            // Encolar todos los DEDENT necesarios
            for (int i = 0; i < indent_stack_top; i++) {
                pending_tokens[pending_count++] = DEDENT;
            }
            return NEWLINE;
        }
        
        // Retornar DEDENT pendientes
        if (indent_stack_top > 0) {
            indent_stack_top--;
            return DEDENT;
        }
    }
    
    return token;
}
```

---

## Detección de Errores de Indentación

### Errores Detectados

1. **Mezcla de tabs y espacios**
   ```python
   if True:
   ⇥   print(1)  # Tab
       print(2)  # Espacios
   # Error: IndentationError
   ```

2. **Indentación inconsistente**
   ```python
   if True:
       print(1)  # 4 espacios
     print(2)    # 2 espacios (no coincide con ningún nivel)
   # Error: indentación inconsistente
   ```

3. **Uso de tabs**
   ```python
   if True:
   ⇥print(1)  # Tab
   # Error: uso de tabs en indentación (use espacios)
   ```

### Mensajes de Error

Los errores de indentación se reportan con información precisa:

```
IndentationError: mezcla de espacios y tabs en indentación en línea 3, columna 1
IndentationError: indentación inconsistente en línea 5, columna 1
IndentationError: uso de tabs en indentación (use espacios) en línea 2, columna 1
```

---

## Gramática Actualizada

### Cambios en parser.y

Todas las reglas de bloques fueron actualizadas:

**Antes (con llaves):**
```yacc
if_stmt:
    KW_IF expr COLON block
    ;

block:
    LBRACE stmt_list RBRACE
    ;
```

**Después (con indentación):**
```yacc
if_stmt:
    KW_IF expr COLON NEWLINE block
    ;

block:
    INDENT stmt_list DEDENT
    ;
```

### Reglas Afectadas

- `if_stmt`: `KW_IF expr COLON NEWLINE block elif_list opt_else`
- `elif_clause`: `KW_ELIF expr COLON NEWLINE block`
- `opt_else`: `KW_ELSE COLON NEWLINE block`
- `while_stmt`: `KW_WHILE expr COLON NEWLINE block`
- `func_def`: `KW_DEF IDENT LPAREN opt_params RPAREN COLON NEWLINE block`
- `stmt`: `simple_stmt NEWLINE` (las sentencias simples requieren NEWLINE)

---

## Comparación Sintáctica

### Antes de Fase 5 (con llaves)

```python
def factorial(n): {
    if n <= 1: {
        return 1
    } else: {
        return n * factorial(n - 1)
    }
}

x = 5
print(factorial(x))
```

### Después de Fase 5 (sintaxis Python)

```python
def factorial(n):
    if n <= 1:
        return 1
    else:
        return n * factorial(n - 1)

x = 5
print(factorial(x))
```

---

## Implementación Técnica

### Arquitectura del Lexer

```
┌─────────────────────────────────────────┐
│  Input: Código fuente con indentación  │
└────────────────┬────────────────────────┘
                 │
                 v
┌─────────────────────────────────────────┐
│         Estado INDENT_STATE             │
│  (al inicio de cada línea)              │
│                                         │
│  Patrones:                              │
│  - ^{SPACE}+   → Detectar indentación   │
│  - ^[^ \t\n]   → Sin indentación        │
│  - ^\n         → Línea vacía            │
└────────────────┬────────────────────────┘
                 │
                 v
┌─────────────────────────────────────────┐
│     handle_indentation(spaces)          │
│                                         │
│  - Comparar con pila                    │
│  - Generar INDENT/DEDENT                │
│  - Encolar DEDENT múltiples             │
└────────────────┬────────────────────────┘
                 │
                 v
┌─────────────────────────────────────────┐
│         Estado INITIAL                  │
│  (tokens normales)                      │
│                                         │
│  - Palabras clave                       │
│  - Operadores                           │
│  - Identificadores                      │
│  - Literales                            │
└────────────────┬────────────────────────┘
                 │
                 v
┌─────────────────────────────────────────┐
│         real_yylex() wrapper            │
│                                         │
│  - Retornar tokens pendientes           │
│  - Manejar EOF especialmente            │
│  - Generar DEDENT al final              │
└────────────────┬────────────────────────┘
                 │
                 v
┌─────────────────────────────────────────┐
│    Parser: Construir AST                │
└─────────────────────────────────────────┘
```

### Flujo de Tokens

**Ejemplo: Bloque if simple**

Código fuente:
```python
if True:
    print(1)
print(2)
```

Secuencia de tokens generada:
```
KW_IF BOOL_LIT COLON NEWLINE
INDENT KW_PRINT LPAREN INT_LIT RPAREN NEWLINE
DEDENT KW_PRINT LPAREN INT_LIT RPAREN NEWLINE
EOF
```

---

## Características Especiales

### 1. Líneas Vacías

Las líneas vacías dentro y entre bloques se ignoran correctamente:

```python
def f():
    x = 1
    
    y = 2    # Línea vacía anterior se ignora
    
    return x + y

# Líneas vacías entre funciones también se ignoran

def g():
    return 1
```

### 2. Comentarios

Los comentarios no afectan la indentación:

```python
if True:
    # Este comentario no afecta
    print(1)  # Comentario al final de línea
    # Otro comentario
    print(2)
```

### 3. Bloques Anidados

Manejo correcto de múltiples niveles de indentación:

```python
def outer():
    if True:
        while x > 0:
            if y < 10:
                print(x)
                x = x - 1
            y = y + 1
    return x
```

Al salir de los bloques anidados, se generan múltiples DEDENT:
```
DEDENT  # cierra if y < 10
DEDENT  # cierra while x > 0
DEDENT  # cierra if True
DEDENT  # cierra def outer()
```

---

## Pruebas

### Tests Básicos

Creados específicamente para validar indentación:

1. **`test_simple_indent.pymini`**: Sentencias simples sin bloques
2. **`test_if_only.pymini`**: Bloque if sin código después
3. **`test_dedent.pymini`**: Bloque if seguido de sentencia
4. **`test_indent.pymini`**: Bloques anidados completos
5. **`test_func.pymini`**: Función con código después

### Validación

Todos los tests pasan exitosamente:
```bash
$ make && ./pymini test_indent.pymini
5
10
6
99
```

---

## Beneficios de la Implementación

1. **Sintaxis Python Auténtica**: PyMini ahora usa la misma sintaxis que Python
2. **Código Más Limpio**: Sin necesidad de llaves, el código es más legible
3. **Detección Robusta de Errores**: Mensajes claros sobre problemas de indentación
4. **Compatibilidad**: Los programas Python válidos (subconjunto) funcionan directamente
5. **Educativo**: Demuestra cómo implementar indentación significativa en un compilador

---

## Lecciones Aprendidas

### Desafíos Superados

1. **Orden de Patrones en Flex**: Las palabras clave pueden consumirse antes de detectar indentación
   - **Solución**: Uso de estados exclusivos (INDENT_STATE)

2. **EOF con Bloques Abiertos**: Necesidad de generar DEDENT al final del archivo
   - **Solución**: Wrapper `real_yylex()` con manejo especial de EOF

3. **Múltiples DEDENT**: Un solo cambio de indentación puede necesitar varios DEDENT
   - **Solución**: Cola de tokens pendientes

4. **Líneas Vacías**: No deben afectar la generación de DEDENT
   - **Solución**: Ignorar líneas vacías sin cambiar `at_line_start`

### Mejores Prácticas

1. Usar estados de Flex para contextos especiales
2. Implementar wrapper sobre `yylex()` para lógica compleja
3. Mantener pila de estado para rastreo de niveles
4. Validar consistencia inmediatamente (fail-fast)
5. Proporcionar mensajes de error descriptivos

---

## Conclusión

La Fase 5 transforma PyMini de un lenguaje con sintaxis tipo C a un lenguaje con sintaxis Python auténtica. Esta implementación demuestra técnicas avanzadas de diseño de compiladores y proporciona una base sólida para futuras mejoras.

El compilador ahora puede aceptar código Python real (dentro del subconjunto soportado) sin ninguna modificación, lo que lo hace ideal para propósitos educativos y experimentación.

---

## Referencias

- **Código fuente**: `src/lexer.l` (sistema de indentación)
- **Gramática**: `src/parser.y` (reglas actualizadas)
- **Tests**: `test_*.pymini` (ejemplos de uso)
- **Documentación**: `README.md` (guía de usuario actualizada)
