# Changelog - PyMini Compiler

Todos los cambios notables del proyecto se documentan en este archivo.

El formato está basado en [Keep a Changelog](https://keepachangelog.com/es-ES/1.0.0/),
y este proyecto sigue [Semantic Versioning](https://semver.org/lang/es/).

## [1.0.0] - 2025-11-03

### ✨ Añadido

#### Análisis Léxico
- Implementación completa del lexer con Flex
- Soporte para tokens: palabras clave, operadores, identificadores, literales
- Tracking de línea y columna para cada token
- Manejo de comentarios (#)
- Detección de caracteres inválidos

#### Análisis Sintáctico
- Parser LALR implementado con Bison
- Gramática completa para PyMini
- Precedencia y asociatividad correcta de operadores
- Construcción del AST durante el parsing
- Manejo de errores sintácticos con recuperación

#### AST (Árbol de Sintaxis Abstracta)
- 20+ tipos de nodos AST
- Gestión de memoria robusta
- Funciones de fábrica para todos los tipos de nodos
- Soporte para listas dinámicas (statements, parámetros, argumentos)
- Información de ubicación en cada nodo

#### Características del Lenguaje
- Tipos: `int`, `bool`
- Operadores aritméticos: `+`, `-`, `*`, `/`, `%`
- Operadores de comparación: `==`, `!=`, `<`, `<=`, `>`, `>=`
- Operadores lógicos: `and`, `or`, `not`
- Sentencias: asignación, `print`, `if`/`elif`/`else`, `while`
- Funciones: `def`, `return`, llamadas con argumentos
- Expresiones con precedencia correcta
- Comentarios de línea

#### Herramientas
- Pretty-printer del AST con formato de árbol
- Sistema de build con Makefile
- Script de tests automatizado (run_tests.sh)
- 8 archivos de prueba cubriendo diferentes características

#### Documentación
- README.md completo con características y uso
- QUICKSTART.md para inicio rápido
- EXAMPLES.md con 10+ ejemplos de código
- ARCHITECTURE.md con documentación técnica detallada
- ROADMAP.md con plan de desarrollo futuro
- INSTALL.md con instrucciones de instalación
- PROJECT_SUMMARY.md con resumen ejecutivo
- .gitignore configurado
- Changelog (este archivo)

#### Tests
- t01_expr.pymini - Expresiones aritméticas básicas
- t02_if.pymini - Condicional if-else
- t03_while.pymini - Bucle while
- t04_func.pymini - Definición y llamada de funciones
- t05_complex_expr.pymini - Expresiones complejas
- t06_elif.pymini - Condicionales con elif
- t07_recursion.pymini - Funciones recursivas
- t08_nested_loops.pymini - Bucles anidados

#### Infraestructura
- Sistema de build completo (Makefile)
- Script de pruebas automatizado
- Gestión de memoria sin leaks
- Manejo de errores robusto

### 📝 Stubs Implementados

#### Análisis Semántico
- Estructura básica de tabla de símbolos
- Tipos de símbolos (variable, función, parámetro)
- Funciones placeholder para fase 2
- Sistema de tipos básico (stub)

### 🔧 Detalles Técnicos

#### Compilador
- Lenguaje: C11
- Estándar: `-std=c11`
- Flags: `-O2 -g -Wall -Wextra`
- Sin warnings significativos

#### Lexer (Flex)
- ~150 líneas
- 25+ tokens definidos
- Opciones: noyywrap, nounput, noinput

#### Parser (Bison)
- ~350 líneas
- Modo verbose error
- Soporte de locations
- Parser LALR sin conflictos

#### AST
- ~450 líneas
- 20+ tipos de nodos
- Gestión de memoria completa

#### Pretty-Printer
- ~200 líneas
- Formato de árbol indentado
- Muestra ubicación de cada nodo

#### Total
- ~1,700 líneas de código
- 9 archivos fuente
- 8 archivos de prueba
- 7 archivos de documentación

### ✅ Validación

- ✅ Compila sin warnings con `-Wall -Wextra`
- ✅ Todos los tests pasan correctamente
- ✅ Sin memory leaks (verificable con valgrind)
- ✅ Manejo de errores robusto
- ✅ Código bien documentado
- ✅ Estructura extensible

### 🎯 Objetivos Cumplidos (Fase 1)

1. ✅ Implementar análisis léxico completo
2. ✅ Implementar análisis sintáctico con precedencia correcta
3. ✅ Construir AST bien formado
4. ✅ Pretty-printer funcional
5. ✅ Build reproducible (Makefile)
6. ✅ Tests mínimos ejecutables
7. ✅ Errores con línea y columna
8. ✅ Código portable y limpio
9. ✅ Documentación completa

### ⚠️ Limitaciones Conocidas

- No hay análisis semántico real (solo stubs)
- No hay verificación de tipos
- No genera código ejecutable
- Bloques usan `{ }` en lugar de indentación Python
- No soporta INDENT/DEDENT tokens
- Sin optimizaciones
- Sin generación de código

Estas limitaciones son esperadas para la Fase 1 y se abordarán en fases futuras.

### 📊 Estadísticas

```
Archivos de código fuente:      9
Archivos de prueba:             8
Archivos de documentación:      7
Total líneas de código:      ~1,700
Tipos de tokens:              25+
Tipos de nodos AST:           20+
Tests incluidos:                8
```

## [Unreleased]

### 🔮 Planeado para Fase 2

- Análisis semántico completo
- Tabla de símbolos funcional
- Verificación de tipos
- Resolución de nombres
- Verificación de scopes
- Más tests para casos semánticos

### 🔮 Planeado para Fase 3+

Ver [ROADMAP.md](ROADMAP.md) para detalles completos.

---

## Formato del Changelog

### Tipos de Cambios

- **Añadido** - Para nuevas características
- **Cambiado** - Para cambios en funcionalidad existente
- **Deprecado** - Para características que serán removidas
- **Removido** - Para características removidas
- **Corregido** - Para corrección de bugs
- **Seguridad** - Para vulnerabilidades

---

**Mantenido por**: Carlos  
**Última actualización**: 2025-11-03  
**Versión actual**: 1.0.0 (Fase 1 completa)
