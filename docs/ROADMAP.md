# Plan de Desarrollo de PyMini

Este documento describe el plan para las fases futuras del compilador PyMini.

## Estado Actual: Fase 1 ✓

**Completado**: Front-end (Lexer + Parser + AST)

**Funcionalidades**:
- ✓ Análisis léxico completo
- ✓ Análisis sintáctico con gramática LR
- ✓ Construcción del AST
- ✓ Pretty-printer del AST
- ✓ Reporte de errores con línea y columna
- ✓ Tests básicos

**Limitaciones**:
- No hay análisis semántico
- No hay generación de código
- No se pueden ejecutar programas

---

## Fase 2: Análisis Semántico (Próxima)

**Objetivo**: Verificar la corrección semántica del programa.

### Tareas:

#### 2.1 Tabla de Símbolos
- [ ] Implementar tabla de símbolos con scopes
- [ ] Soporte para scopes anidados (funciones, bloques)
- [ ] Registrar variables con su tipo
- [ ] Registrar funciones con sus firmas

#### 2.2 Verificación de Nombres
- [ ] Verificar que las variables están declaradas antes de usarse
- [ ] Verificar que las funciones existen antes de llamarlas
- [ ] Detectar redeclaraciones en el mismo scope
- [ ] Reportar variables no usadas (warning)

#### 2.3 Sistema de Tipos
- [ ] Inferencia de tipos para expresiones
- [ ] Verificación de tipos en asignaciones
- [ ] Verificación de tipos en operaciones binarias
- [ ] Verificación de tipos en llamadas a funciones
- [ ] Verificación de tipos de retorno

#### 2.4 Verificaciones Adicionales
- [ ] Return solo dentro de funciones
- [ ] Verificar número y tipos de argumentos en llamadas
- [ ] Verificar que todas las ramas de control retornan valor (si es necesario)
- [ ] Detectar código inalcanzable

#### 2.5 Tests
- [ ] Tests para variables no declaradas
- [ ] Tests para errores de tipos
- [ ] Tests para redeclaraciones
- [ ] Tests para funciones no definidas

**Entregables**:
- Tabla de símbolos funcional
- Sistema de tipos básico
- Reportes de errores semánticos detallados
- Suite de tests ampliada

---

## Fase 3: Generación de Código Intermedio

**Objetivo**: Traducir el AST a una representación intermedia (IR).

### Tareas:

#### 3.1 Diseño del IR
- [ ] Definir formato del IR (3-address code, SSA, o bytecode)
- [ ] Diseñar conjunto de instrucciones
- [ ] Implementar estructuras de datos para IR

#### 3.2 Traducción AST → IR
- [ ] Traducir expresiones aritméticas
- [ ] Traducir expresiones lógicas
- [ ] Traducir asignaciones
- [ ] Traducir condicionales (if/elif/else)
- [ ] Traducir bucles (while)
- [ ] Traducir funciones y llamadas
- [ ] Manejar returns

#### 3.3 Optimizaciones Básicas
- [ ] Constant folding (evaluar constantes en compile-time)
- [ ] Dead code elimination
- [ ] Copy propagation
- [ ] Common subexpression elimination

#### 3.4 Tests
- [ ] Tests de generación de IR
- [ ] Tests de optimizaciones
- [ ] Validación de corrección del IR

**Entregables**:
- Generador de IR completo
- Optimizador básico
- Herramienta para visualizar IR
- Documentación del formato IR

---

## Fase 4: Generación de Código Backend

**Objetivo**: Generar código ejecutable a partir del IR.

### Opción A: Bytecode + VM

#### 4A.1 Diseño de Bytecode
- [ ] Definir set de instrucciones de la VM
- [ ] Diseñar formato de bytecode
- [ ] Implementar serialización de bytecode

#### 4A.2 Máquina Virtual
- [ ] Implementar VM stack-based
- [ ] Implementar dispatcher de instrucciones
- [ ] Implementar runtime para operaciones básicas
- [ ] Soporte para llamadas a funciones

#### 4A.3 Runtime
- [ ] Sistema de objetos simple (int, bool)
- [ ] Gestión de memoria (stack + heap)
- [ ] Garbage collector opcional

### Opción B: Código Nativo (x86-64 o LLVM)

#### 4B.1 Backend LLVM
- [ ] Integrar LLVM IR generator
- [ ] Traducir IR de PyMini a LLVM IR
- [ ] Generar código objeto
- [ ] Linker con runtime

#### 4B.2 Backend x86-64
- [ ] Selección de instrucciones
- [ ] Asignación de registros
- [ ] Generación de código assembly
- [ ] Integración con assembler/linker

**Entregables**:
- Generador de código funcional
- Runtime básico
- Ejecutables que funcionan
- Benchmarks de rendimiento

---

## Fase 5: Características Avanzadas

**Objetivo**: Añadir características más complejas al lenguaje.

### 5.1 Extensiones del Lenguaje
- [ ] Listas y tuplas
- [ ] Diccionarios
- [ ] Strings (literales y operaciones)
- [ ] For loops (for x in range(...))
- [ ] Break y continue
- [ ] Operador ternario
- [ ] Lambdas / funciones anónimas
- [ ] Closures

### 5.2 Sistema de Tipos Avanzado
- [ ] Type hints opcionales
- [ ] Verificación estática de tipos
- [ ] Generics / polimorfismo

### 5.3 Biblioteca Estándar
- [ ] Módulo de I/O (lectura/escritura archivos)
- [ ] Módulo de matemáticas
- [ ] Módulo de strings
- [ ] Módulo de listas

### 5.4 Optimizaciones Avanzadas
- [ ] Inlining de funciones
- [ ] Loop unrolling
- [ ] Strength reduction
- [ ] Profile-guided optimization

### 5.5 Herramientas de Desarrollo
- [ ] Debugger integrado
- [ ] Profiler
- [ ] REPL (Read-Eval-Print Loop)
- [ ] Language Server Protocol (LSP) para IDEs

**Entregables**:
- Lenguaje más expresivo
- Biblioteca estándar mínima
- Herramientas de desarrollo
- Documentación completa

---

## Fase 6: Características Experimentales

**Objetivo**: Explorar características avanzadas y experimentales.

### 6.1 Características del Lenguaje
- [ ] Decoradores
- [ ] Generators / yield
- [ ] Async/await
- [ ] Pattern matching
- [ ] Comprehensions (list, dict, set)
- [ ] Context managers (with statement)

### 6.2 Sistema de Módulos
- [ ] Import/export de módulos
- [ ] Paquetes
- [ ] Gestión de dependencias

### 6.3 Metaprogramación
- [ ] Reflection básica
- [ ] Macros en compile-time
- [ ] AST transformations

### 6.4 Interoperabilidad
- [ ] FFI (Foreign Function Interface) para C
- [ ] Embedding PyMini en otros programas
- [ ] Extensiones en C/C++

**Entregables**:
- Características experimentales
- Sistema de módulos
- FFI funcional
- Ejemplos de interoperabilidad

---

## Roadmap Temporal (Estimado)

```
┌─────────────┬─────────────────────────────────────────┐
│ Fase        │ Duración Estimada                       │
├─────────────┼─────────────────────────────────────────┤
│ Fase 1 ✓    │ 2-3 semanas (COMPLETADO)               │
│ Fase 2      │ 3-4 semanas                            │
│ Fase 3      │ 3-4 semanas                            │
│ Fase 4      │ 4-6 semanas                            │
│ Fase 5      │ 6-8 semanas                            │
│ Fase 6      │ 8-12 semanas (opcional)                │
├─────────────┼─────────────────────────────────────────┤
│ TOTAL       │ 6-10 meses (completo)                  │
└─────────────┴─────────────────────────────────────────┘
```

---

## Decisiones de Arquitectura Pendientes

### Gestión de Memoria
- ¿Reference counting o Garbage Collection?
- ¿Stack-based o register-based VM?

### Formato de Distribución
- ¿Bytecode compilado o código fuente interpretado?
- ¿AOT (Ahead-of-Time) o JIT (Just-in-Time) compilation?

### Compatibilidad
- ¿Mantener compatibilidad con Python real?
- ¿O divergir para simplificar la implementación?

### Performance vs Simplicidad
- ¿Optimizar al máximo o mantener código educativo simple?

---

## Recursos Necesarios

### Conocimientos
- Algoritmos de análisis semántico
- Generación de código intermedio
- Arquitectura de VM
- Assembly x86-64 (si se elige código nativo)
- LLVM (si se usa como backend)
- Garbage collection algorithms

### Herramientas
- LLVM toolkit (opcional)
- Profilers (valgrind, perf, gprof)
- Debuggers (gdb)
- Testing frameworks

### Referencias
- "Crafting Interpreters" by Robert Nystrom
- "Modern Compiler Implementation in C" by Andrew Appel
- "Engineering a Compiler" by Cooper & Torczon
- LLVM documentation
- Python implementation (CPython source)

---

## Métricas de Éxito

### Fase 2
- ✓ Detecta todos los errores semánticos básicos
- ✓ Suite de tests con 100% de cobertura de features

### Fase 3
- ✓ IR bien formado para todos los tests
- ✓ Optimizaciones demuestran mejora medible

### Fase 4
- ✓ Programas se ejecutan correctamente
- ✓ Performance aceptable para programas pequeños

### Fase 5
- ✓ Puede ejecutar programas "reales" simples
- ✓ Biblioteca estándar útil

### Fase 6
- ✓ Feature parity con un subconjunto significativo de Python
- ✓ Herramientas de desarrollo funcionales

---

## Contribuciones Futuras

Si este proyecto se hace público, áreas donde la comunidad puede contribuir:

1. **Tests**: Más casos de prueba, edge cases
2. **Optimizaciones**: Nuevas optimizaciones
3. **Backends**: Soporte para nuevas arquitecturas
4. **Biblioteca estándar**: Más módulos
5. **Documentación**: Tutoriales, ejemplos
6. **Herramientas**: Editor syntax highlighting, linters
7. **Benchmarks**: Suite de benchmarks para medir performance

---

## Conclusión

El desarrollo de PyMini es un viaje educativo ambicioso. Cada fase añade complejidad y funcionalidad, llevando el proyecto desde un simple parser hasta un compilador completo y funcional.

La Fase 1 establece una base sólida con un front-end robusto. Las fases futuras construirán sobre esta base para crear un compilador real y útil.

**Estado actual**: Fase 1 completada ✓
**Próximo paso**: Iniciar Fase 2 (Análisis Semántico)
