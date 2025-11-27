# Compilador PyMini - Fase 2 Completada

Resumen técnico del proyecto para la asignatura "Compiladores" de la Universidad de Sonsonate.

Este documento contiene información técnica condensada sobre la implementación.

## Estado del Proyecto

### Fase 1 (Front-end) - COMPLETADA
- Analizador léxico (Flex)
- Analizador sintáctico (Bison)
- Construcción de AST
- Pretty-printer del AST
- Reporte de errores con línea y columna
- 8 archivos de prueba funcionando

### Fase 2 (Análisis Semántico) - COMPLETADA
- Sistema de tipos (int, bool, unknown, error)
- Tabla de símbolos con scopes anidados
- Resolución de identificadores (variables y funciones)
- Verificación de tipos en operadores y asignaciones
- Validación de reglas semánticas
- Reporte de errores semánticos con ubicación precisa
- Suite de 14 tests (6 positivos + 8 negativos) - 100% exitoso

## Compilación

```bash
make clean
make
```

El ejecutable `pymini` se generará en el directorio raíz.

## Uso Básico

```bash
./pymini <archivo.pymini>
```

Ejemplos:
```bash
# Archivo sin errores
./pymini tests/pos/p01_vars.pymini

# Archivo con errores semánticos (para demostración)
./pymini tests/neg/n01_undeclared.pymini
```

## Ejecutar Tests

```bash
# Todos los tests (positivos y negativos)
make test

# Ver solo resumen
./tests/run.sh | tail -10
```

**Resultado actual: 14/14 tests pasando**

## Características Implementadas

### Tipos de Datos
- Enteros (`int`)
- Booleanos (`True`, `False`)
- Inferencia de tipos
- Detección de tipos incompatibles

### Operadores
- **Aritméticos**: `+`, `-`, `*`, `/`, `%` (requieren int)
- **Comparación**: `==`, `!=`, `<`, `>`, `<=`, `>=`
- **Lógicos**: `and`, `or`, `not` (requieren bool)

### Estructuras de Control
- **Condicionales**: `if`, `elif`, `else` (condición debe ser bool)
- **Bucles**: `while` (condición debe ser bool)

### Funciones
- Definición con `def`
- Parámetros tipados (inferencia de tipos)
- Retorno con `return`
- Llamadas a funciones con verificación de aridad
- Detección de return fuera de función

### Análisis Semántico
Las siguientes reglas semánticas son verificadas y generan errores:

1. Variables usadas antes de asignar
2. Tipos incompatibles en operadores
3. Condiciones no booleanas en if/while
4. Aridad incorrecta en llamadas a funciones
5. Reasignación con tipo incompatible
6. Return fuera de función
7. Uso de nombre de función como variable
8. Uso de nombre de variable como función

### Otras Características
- Asignación de variables con inferencia de tipos
- Función `print()` (acepta int o bool)
- Comentarios con `#`
- Scopes anidados (funciones, bloques)

## Estructura del Proyecto

```
Compilador_Python/
├── src/                   # Código fuente
│   ├── lexer.l            # Analizador léxico (Flex)
│   ├── parser.y           # Analizador sintáctico (Bison)
│   ├── ast.h/c            # Definición e implementación del AST
│   ├── ast_print.h/c      # Pretty-printer del AST
│   ├── types.h/c          # Sistema de tipos [FASE 2]
│   ├── diag.h/c           # Sistema de diagnóstico [FASE 2]
│   ├── symtab.h/c         # Tabla de símbolos [FASE 2]
│   ├── sema.h/c           # Análisis semántico completo [FASE 2]
│   └── main.c             # Punto de entrada
├── tests/                 # Archivos de prueba
│   ├── pos/               # Tests positivos (deben pasar) [FASE 2]
│   │   ├── p01_vars.pymini         # Variables básicas
│   │   ├── p02_cond.pymini         # Condicionales
│   │   ├── p03_func.pymini         # Funciones
│   │   ├── p04_types.pymini        # Inferencia de tipos
│   │   ├── p05_while.pymini        # Bucles while
│   │   └── p06_logic.pymini        # Operadores lógicos
│   ├── neg/               # Tests negativos (deben fallar) [FASE 2]
│   │   ├── n01_undeclared.pymini   # Variable no declarada
│   │   ├── n02_type_op.pymini      # Tipo incompatible en operador
│   │   ├── n03_if_bool.pymini      # Condición if no booleana
│   │   ├── n04_arity.pymini        # Aridad incorrecta
│   │   ├── n05_param_conflict.pymini # Conflicto de tipos en parámetro
│   │   ├── n06_reassign_type.pymini  # Reasignación con tipo diferente
│   │   ├── n07_return_outside.pymini # Return fuera de función
│   │   └── n08_while_bool.pymini     # Condición while no booleana
│   ├── run.sh             # Script automatizado de tests [FASE 2]
│   └── t*.pymini          # Tests originales de Fase 1
├── docs/                  # Documentación
│   ├── ARCHITECTURE.md
│   ├── EXAMPLES.md
│   ├── INICIO_RAPIDO.md
│   └── ROADMAP.md
├── Makefile               # Sistema de compilación (actualizado)
├── run_tests.sh           # Script de pruebas Fase 1
└── README_FINAL.md        # Este archivo
```

## Ejemplos de Uso

### Ejemplo 1: Código válido
```python
# tests/pos/p01_vars.pymini
x = 5
y = x + 10
print(y)
```

**Salida:**
```
========================================
Semantic OK
========================================
Compilación completada exitosamente
```

### Ejemplo 2: Error - Variable no declarada
```python
# tests/neg/n01_undeclared.pymini
x = y + 1
```

**Salida:**
```
2:7: error: variable 'y' no declarada o usada antes de asignar
ERROR: Análisis semántico falló con 1 error(es)
```

### Ejemplo 3: Error - Tipo incompatible
```python
# tests/neg/n02_type_op.pymini
x = True + 1
```

**Salida:**
```
2:13: error: operador aritmético '+' requiere int (encontrado bool y int)
ERROR: Análisis semántico falló con 1 error(es)
```

### Ejemplo 4: Error - Aridad incorrecta
```python
# tests/neg/n04_arity.pymini
def suma(a, b):
{
  return a + b
}
print(suma(5))  # Error: se esperan 2 argumentos
```

**Salida:**
```
6:10: error: función 'suma' espera 2 argumento(s), pero se le pasaron 1
ERROR: Análisis semántico falló con 1 error(es)
```

## Tests Negativos - Casos de Error

Los tests negativos verifican que el compilador detecta correctamente errores semánticos:

| Test | Error Detectado | Mensaje Esperado |
|------|----------------|------------------|
| n01_undeclared.pymini | Variable usada antes de ser asignada | variable 'y' no declarada o usada antes de asignar |
| n02_type_op.pymini | Operador aritmético con tipos incompatibles | operador aritmético '+' requiere int |
| n03_if_bool.pymini | Condición de if no es booleana | condición de 'if' debe ser bool |
| n04_arity.pymini | Número incorrecto de argumentos en llamada | función 'a' espera 2 argumento(s), pero se le pasaron 1 |
| n05_param_conflict.pymini | Conflicto de tipos en parámetro | condición de 'if' debe ser bool |
| n06_reassign_type.pymini | Reasignación con tipo diferente | reasignación de 'x' con tipo incompatible |
| n07_return_outside.pymini | Return fuera de función | return fuera de función |
| n08_while_bool.pymini | Condición de while no es booleana | condición de 'while' debe ser bool |

**Todos estos tests fallan correctamente**, demostrando que el análisis semántico funciona.

## Arquitectura del Análisis Semántico

### Sistema de Tipos
```c
typedef enum {
    TY_INT,       // Tipo entero
    TY_BOOL,      // Tipo booleano
    TY_UNKNOWN,   // Para inferencia
    TY_ERROR      // Para propagación de errores
} Type;
```

### Tabla de Símbolos
- Implementada con **hash table** (16 buckets)
- **Scopes anidados** con punteros al scope padre
- Soporte para **variables** y **funciones**
- Operaciones: `sym_lookup`, `sym_insert`, `scope_push`, `scope_pop`

### Símbolo
```c
typedef struct Symbol {
    char* name;              // Nombre del símbolo
    SymbolKind kind;         // SYM_VAR o SYM_FUNC
    Type type;               // Tipo de la variable
    Type return_type;        // Tipo de retorno (funciones)
    int arity;               // Número de parámetros (funciones)
    Type* param_types;       // Tipos de parámetros
    char** param_names;      // Nombres de parámetros
    struct Symbol* next;     // Para colisiones en hash table
} Symbol;
```

### Visitador de AST
- **Patrón Visitor** para recorrer el árbol
- **Dos pasadas**:
  1. Recolección de firmas de funciones
  2. Análisis semántico completo
- Propagación de tipos hacia arriba
- Inserción de símbolos hacia abajo

### Contexto Semántico
```c
typedef struct {
    Scope* scope;            // Scope actual
    Symbol* current_func;    // Función actual (NULL si global)
    int in_function;         // Flag: estamos dentro de una función?
} SemaCtx;
```

## Estadísticas del Proyecto

- **Archivos de código**: 18 archivos (.h/.c)
- **Líneas de código**: ~3000 líneas
- **Tests**: 14 tests (100% exitosos)
- **Reglas semánticas**: 8 validaciones principales
- **Tipos soportados**: 2 tipos básicos + 2 meta-tipos
- **Operadores**: 15 operadores con validación de tipos

## Requisitos del Sistema

- GCC o Clang
- Flex 2.6+
- Bison 3.0+
- Make
- Sistema Unix/Linux (probado en Ubuntu)

## Instalación de Dependencias (Ubuntu/Debian)

```bash
sudo apt install flex bison gcc make
```

## Próximos Pasos (Fase 3)

- [ ] Generación de código intermedio (IR)
- [ ] Representación de tres direcciones
- [ ] Gestión de memoria y activación de funciones
- [ ] Generación de código assembly o bytecode
- [ ] Optimizaciones básicas (opcional)

## Documentación Adicional

Ver la carpeta `docs/` para más información:
- `ARCHITECTURE.md` - Arquitectura del compilador
- `INICIO_RAPIDO.md` - Guía rápida de inicio
- `EXAMPLES.md` - Más ejemplos de código PyMini
- `ROADMAP.md` - Roadmap completo de desarrollo

## Aspectos Educativos

Este proyecto demuestra:
- **Diseño e implementación de compiladores**
- **Análisis léxico y sintáctico** con Flex/Bison
- **Construcción de AST** con tipos suma
- **Análisis semántico** con tabla de símbolos
- **Sistema de tipos** y verificación
- **Gestión de errores** con ubicación precisa
- **Testing sistemático** con casos positivos y negativos

## Resolución de Problemas

### Error: "command not found: flex" o "command not found: bison"
```bash
sudo apt install flex bison gcc make
```

### Error al compilar: "undefined reference to sym_lookup"
```bash
make clean
make
```

### Los tests no se ejecutan
```bash
chmod +x tests/run.sh
./tests/run.sh
```

## Licencia

Proyecto educativo - Uso libre para aprendizaje.

---

## Resumen de Logros

- Fase 1 completada: Front-end funcional
- Fase 2 completada: Análisis semántico robusto
- 14/14 tests pasando: Calidad verificada
- Arquitectura extensible: Lista para Fase 3

**El compilador PyMini evoluciona.**
