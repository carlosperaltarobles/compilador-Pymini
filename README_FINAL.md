# Compilador pymini - fase 1 completada

Resumen técnico del proyecto para la asignatura "compiladores" de la Universidad de Sonsonate.

este documento contiene información técnica condensada sobre la implementación.

## Estado del proyecto

Fase 1 (front-end) completada:
- analizador léxico (Flex)
- analizador sintáctico (Bison)
- construcción de ast
- pretty-printer del ast
- reporte de errores con línea y columna
- 8 archivos de prueba funcionando (100% de éxito)

## Compilación

```bash
make clean
make
```

el ejecutable `pymini` se generará en el directorio raíz.

## Uso básico

```bash
./pymini <archivo.pymini>
```

ejemplo:
```bash
./pymini tests/t01_expr.pymini
```

## Ejecutar Tests

```bash
./run_tests.sh
```

Esto ejecutará los 8 archivos de prueba y mostrará un resumen de resultados.

## Características implementadas

### Tipos de datos
- Enteros (`int`)
- Booleanos (`True`, `False`)

### Operadores
- Aritméticos: `+`, `-`, `*`, `/`, `%`
- Comparación: `==`, `!=`, `<`, `>`, `<=`, `>=`
- Lógicos: `and`, `or`, `not`

### Estructuras de Control
- Condicionales: `if`, `elif`, `else`
- Bucles: `while`

### Funciones
- Definición con `def`
- Parámetros
- Retorno con `return`
- Llamadas a funciones

### Otras Características
- Asignación de variables
- Función `print()`
- Comentarios con `#`

## Estructura del Proyecto

```
Compilador_Python/
├── src/               # Código fuente
│   ├── lexer.l        # Analizador léxico (Flex)
│   ├── parser.y       # Analizador sintáctico (Bison)
│   ├── ast.h/c        # Definición e implementación del AST
│   ├── ast_print.h/c  # Pretty-printer del AST
│   ├── sema.h/c       # Análisis semántico (stub)
│   └── main.c         # Punto de entrada
├── tests/             # Archivos de prueba
│   ├── t01_expr.pymini           # Expresiones aritméticas
│   ├── t02_if.pymini             # Condicionales
│   ├── t03_while.pymini          # Bucles
│   ├── t04_func.pymini           # Funciones
│   ├── t05_complex_expr.pymini   # Expresiones complejas
│   ├── t06_elif.pymini           # Elif
│   ├── t07_recursion.pymini      # Recursión
│   └── t08_nested_loops.pymini   # Bucles anidados
├── docs/              # Documentación
├── Makefile           # Sistema de compilación
├── run_tests.sh       # Script de pruebas
└── README_FINAL.md    # Este archivo
```

## 🎯 Ejemplo de salida

```bash
$ ./pymini tests/t01_expr.pymini
========================================
Compilador PyMini - Fase 1
========================================
Parseando: tests/t01_expr.pymini
========================================

========================================
Parse OK
========================================

========== AST ==========

Program [3:9]
  StmtList (2 statements)
    Assign [3:1] name='x'
      value:
        BinOp [3:1] op='+'
          left:
            IntLit [2:5] value=1
          right:
            BinOp [2:13] op='*'
              left:
                IntLit [2:9] value=2
              right:
                IntLit [2:13] value=3
    Print [3:8]
      Name [3:8] id='x'

=========================

========================================
Compilación completada exitosamente
========================================
```

## 🛠️ Requisitos

- GCC o Clang
- Flex 2.6+
- Bison 3.0+
- Make

## ⚙️ Instalación de dependencias (Ubuntu/Debian)

```bash
sudo apt install flex bison gcc make
```

## 🔍 Resolución de Problemas

### Error: "command not found: flex" o "command not found: bison"
Instala las dependencias con el comando mostrado arriba.

### Error: "strdup implicitly declared"
Este proyecto incluye declaraciones explícitas de `strdup` para compatibilidad.

### Advertencia: "1 shift/reduce conflict"
Es una advertencia esperada en la gramática y no afecta el funcionamiento.

## 📚 Documentación Adicional

Ver la carpeta `docs/` para:
- `ARCHITECTURE.md` - Arquitectura del compilador
- `GRAMMAR.md` - Gramática formal de PyMini
- `QUICKSTART.md` - Guía rápida de inicio
- `EXAMPLES.md` - Ejemplos de código PyMini
- `ROADMAP.md` - Roadmap de desarrollo

## 🚦 Próximos pasos (Fase 2)

- [ ] Análisis semántico completo
- [ ] Tabla de símbolos
- [ ] Verificación de tipos
- [ ] Generación de código intermedio
- [ ] Optimizaciones básicas

## 👨‍💻 Desarrollo

Este es un proyecto educativo para aprender sobre:
- Diseño de compiladores
- Análisis léxico y sintáctico
- Construcción de AST
- Procesamiento de lenguajes

## 📄 Licencia

Proyecto educativo - Uso libre para aprendizaje.

---

**¡El compilador PyMini Fase 1!**
