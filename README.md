# PyMini - Compilador en C


> **Compilador Python (subconjunto) en C - Versión 2.0.0**

PyMini es un compilador educativo para un subconjunto simple de Python, implementado en C usando Flex y Bison.

---

## Tabla de Contenidos

1. [¿Qué es PyMini?](#-qué-es-pymini)
2. [Instalación de Dependencias](#-instalación-de-dependencias-paso-a-paso)
3. [Compilación del Proyecto](#-compilación-del-proyecto)
4. [Demostración en Vivo](#-demostración-en-vivo)
5. [Cómo Usar PyMini](#-cómo-usar-pymini)
6. [Características del Lenguaje](#-características-del-lenguaje-pymini)
7. [Ejemplos de Código](#-ejemplos-de-código)
8. [Ejecutar las Pruebas](#-ejecutar-las-pruebas)
9. [Documentación Adicional](#-documentación-adicional)
10. [Resolución de Problemas](#-resolución-de-problemas)

---

## ¿Qué es PyMini?

PyMini es un **compilador completo en C** que procesa un subconjunto de Python. Actualmente en **Fase Final (Fase 5)**, el compilador incluye:

**Fase 1 - Análisis Léxico y Sintáctico:**
- **Leer** tu código fuente  
- **Analizar** si la sintaxis es correcta  
- **Crear** un árbol de sintaxis (AST)  
- **Reportar** errores léxicos y sintácticos con número de línea y columna  

**Fase 2 - Análisis Semántico:**
- **Verificar** que las variables estén declaradas antes de usarse
- **Comprobar** que los tipos sean compatibles (int, bool)
- **Validar** llamadas a funciones (aridad, existencia)
- **Detectar** errores semánticos (retornos fuera de funciones, conflictos de parámetros)
- **Construir** tabla de símbolos con alcance (scope)
- **Reportar** errores semánticos detallados

**Fase 3 - Generación de Código:**
- **Generar** código C a partir del AST validado
- **Compilar** con GCC para producir ejecutables nativos
- **Runtime** con funciones de impresión y verificación de errores
- **Protección** contra división por cero en tiempo de ejecución

**Fase 4 - Pipeline y Optimizaciones:**
- **CLI completo** con múltiples modos de operación
- **Pipeline** de compilación automatizado
- **Optimizaciones** básicas (constant folding, dead code elimination)
- **Ejecución** directa de programas PyMini

**Fase 5 - Sintaxis Python con Indentación:**
- **Indentación significativa** estilo Python (sin llaves `{}`)
- **Tokens INDENT/DEDENT/NEWLINE** para bloques de código
- **Detección de errores** de indentación (tabs mezclados, niveles inconsistentes)
- **Sintaxis 100% compatible** con Python para estructuras de control
- **Manejo robusto** de bloques anidados y múltiples niveles de dedent

**En resumen:** PyMini es un compilador completo que acepta sintaxis Python con indentación, genera ejecutables nativos optimizados y proporciona mensajes de error detallados.

---

## Instalación de dependencias (PASO A PASO)

### ¿Qué necesitas instalar?

Para compilar y usar PyMini, necesitas estas herramientas en tu computadora:

| Herramienta | ¿Para qué sirve? | Obligatorio |
|------------|------------------|-------------|
| **GCC** | Compilador de C que convierte el código fuente en ejecutable |  Sí |
| **Make** | Automatiza el proceso de compilación |  Sí |
| **Flex** | Generador de analizadores léxicos (tokenización) |  Sí |
| **Bison** | Generador de analizadores sintácticos (parsing) |  Sí |
| **GDB** | Debugger para encontrar errores (opcional pero útil) | Recomendado |

---

### 📦 Instalación en Ubuntu/Debian/WSL

Si usas **Ubuntu**, **Debian** o **WSL** (Windows Subsystem for Linux), ejecuta estos comandos:

#### 1️⃣ Actualizar el sistema (recomendado)

```bash
sudo apt update
```

**¿Qué hace?** Actualiza la lista de paquetes disponibles.

#### 2️⃣ Instalar todas las dependencias básicas

```bash
sudo apt install -y build-essential flex bison make
```

**¿Qué instala?**
- `build-essential`: Incluye GCC, Make y otras herramientas de compilación
- `flex`: Generador de analizadores léxicos
- `bison`: Generador de analizadores sintácticos

#### 3️⃣ Instalar GDB (opcional pero recomendado)

```bash
sudo apt install -y gdb
```


comprobación rápida:

```bash
gcc --version
make --version
flex --version
bison --version
gdb --version   # si lo instalaste
```

otras plataformas:

- fedora/rhel/centos:

```bash
sudo dnf install -y gcc flex bison make gdb
```

- macos (requiere homebrew y xcode command line tools):

```bash
xcode-select --install
brew install flex bison
```

---

## cómo compilar el proyecto

1) entrar al directorio del proyecto:

```bash
cd /ruta/a/Compilador_Python
```

2) limpiar compilaciones previas (opcional pero recomendado si tuvo errores antes):

```bash
make clean
```

3) compilar todo:

```bash
make
```

qué hace `make`:

- ejecuta flex sobre `src/lexer.l`
- ejecuta bison sobre `src/parser.y`
- compila los `.c` a `.o`
- enlaza y genera el ejecutable `pymini`

salida esperada: verás las invocaciones de flex y bison y al final el binario `pymini`.

nota: bison puede imprimir una advertencia "1 shift/reduce conflict". es una advertencia menor y no impide el uso.

---

## Demostración

### Opción Rápida: script automático

Para una demostración automatizada durante la presentación, ejecuta el siguiente script:

```bash
./demo_presentacion.sh
```

Este script ejecutará todos los pasos de demostración automáticamente, mostrando:
1. Verificación de dependencias
2. Compilación exitosa de un programa
3. Detección de error semántico (variable no declarada)
4. Detección de error de tipos incompatibles
5. Ejecución de suite completa de tests

### Crear tu primer programa PyMini (Paso a Paso)

Vamos a crear un archivo `.pymini` desde cero y compilarlo paso a paso.

#### Paso 1: Crear el archivo

```bash
cat > demo.pymini << 'EOF'
# Programa de demostración PyMini
# Calcula el factorial de un número
```bash
nano demo.pymini
```

O usando `cat` directamente:

```bash
cat > demo.pymini << 'EOF'
# Programa de demostración PyMini
# Calcula el factorial de un número

def factorial(n):
    if n <= 1:
        return 1
    else:
        return n * factorial(n - 1)

x = 5
result = factorial(x)
print(result)
EOF
```

#### Paso 2: Compilar el archivo

```bash
./pymini demo.pymini
```

#### Paso 3: Verificar la salida

Si todo está correcto, verás:

```
Semantic OK
Program
  FuncDef: factorial
    Params: n
    Body:
      If
        Condition: (n <= 1)
        Then:
          Return: 1
        Else:
          Return: (n * factorial(n - 1))
  Assign: x = 5
  Assign: result = factorial(x)
  Print: result
```

### Ejemplo con Error Semántico

Ahora probemos un archivo con un error intencional:

```bash
cat > demo_error.pymini << 'EOF'
# Este programa tiene un error semántico
x = 5
print(y)  # Error: 'y' no está declarada
EOF
```

Compilar:

```bash
./pymini demo_error.pymini
```

Salida esperada:

```
Error semántico en línea 3, columna 7: variable 'y' no declarada
```

### Ejemplo de Verificación de Tipos

```bash
cat > demo_tipos.pymini << 'EOF'
# Verificación de tipos
x = 5
y = True
z = x and y  # Error: no se puede usar 'and' con int y bool
EOF
```

Compilar:

```bash
./pymini demo_tipos.pymini
```

Salida esperada:

```
Error semántico en línea 3, columna 5: tipos incompatibles en operación 'and': int y bool
```

---

## Cómo usar el compilador

PyMini ahora soporta múltiples modos de operación:

### Modo 1: Compilar y ejecutar (por defecto)

```bash
./pymini programa.pymini
```

O explícitamente:

```bash
./pymini --run programa.pymini
```

Esto compila el programa y lo ejecuta inmediatamente, mostrando la salida.

### Modo 2: Solo generar código C

```bash
./pymini --emit-c -o programa.c programa.pymini
```

Genera código C en `programa.c` sin compilarlo a binario.

### Modo 3: Compilar a ejecutable

```bash
./pymini --compile -o programa programa.pymini
```

Genera un ejecutable nativo llamado `programa`.

### Opciones de optimización

```bash
./pymini -O0 programa.pymini    # Sin optimizaciones (por defecto)
./pymini -O1 programa.pymini    # Optimizaciones básicas
```

Las optimizaciones `-O1` incluyen:
- Constant folding (evalúa `1+2*3` → `7` en tiempo de compilación)
- Dead code elimination (elimina código inalcanzable)

### Opciones adicionales

```bash
./pymini --help              # Muestra ayuda
./pymini --version           # Muestra versión
./pymini -v programa.pymini  # Modo verbose (muestra pasos del pipeline)
```

### Ejemplos completos

```bash
# Compilar y ejecutar con optimizaciones
./pymini -O1 tests/e2e/pos/e02_arith.pymini

# Generar código C y ver el resultado
./pymini --emit-c -o temp.c tests/e2e/pos/e04_funcs.pymini
cat temp.c

# Compilar a ejecutable y ejecutarlo manualmente
./pymini --compile -o mi_programa tests/e2e/pos/e03_if_while.pymini
./mi_programa
```

---

## características del lenguaje pymini

PyMini soporta un subconjunto de Python con las siguientes características:

### Tipos de Datos
- **Enteros**: `42`, `-10`, `0`
- **Booleanos**: `True`, `False`

### Operadores

**Aritméticos**:
- `+` (suma), `-` (resta), `*` (multiplicación), `/` (división), `%` (módulo)
- Operadores unarios: `-` (negación)

**Relacionales**:
- `<`, `<=`, `>`, `>=`, `==`, `!=`

**Lógicos**:
- `and`, `or`, `not`

### Estructuras de Control

**Condicionales**:
```python
if condicion:
    # código
elif otra_condicion:
    # código
else:
    # código
```

**Bucles**:
```python
while condicion:
    # código
```

### Funciones

**Definición**:
```python
def nombre_funcion(param1, param2):
    # código
    return valor
```

**Llamada**:
```python
resultado = nombre_funcion(arg1, arg2)
```

### Variables
- Asignación: `x = expresion`
- Deben declararse antes de usarse
- Tipo inferido en la primera asignación
- No se puede cambiar el tipo después

### Comentarios
```python
# Esto es un comentario de una línea
```

### Funciones Built-in
- `print(expresion)` - Imprime una expresión (int o bool)
- `input()` - Lee un entero desde la entrada estándar ✨ **NUEVO**

---

## ejemplos de código

### Ejemplo 1: Expresiones Básicas

```python
# Operaciones aritméticas
x = 10
y = 20
z = x + y * 2
print(z)  # Imprime: 50
```

### Ejemplo 2: Condicionales

```python
# Verificar si un número es positivo, negativo o cero
num = -5

if num > 0:
    print(1)  # Positivo
elif num < 0:
    print(-1)  # Negativo
else:
    print(0)  # Cero
```

### Ejemplo 3: Bucles

```python
# Suma de los primeros 10 números
suma = 0
i = 1

while i <= 10:
    suma = suma + i
    i = i + 1

print(suma)  # Imprime: 55
```

### Ejemplo 4: Funciones

```python
# Función que calcula el máximo de dos números
def max(a, b):
    if a > b:
        return a
    else:
        return b

resultado = max(15, 23)
print(resultado)  # Imprime: 23
```

### Ejemplo 5: Recursión (Factorial)

```python
# Cálculo recursivo del factorial
def factorial(n):
    if n <= 1:
        return 1
    else:
        return n * factorial(n - 1)

f5 = factorial(5)
print(f5)  # Imprime: 120
```

### Ejemplo 6: Fibonacci

```python
# Fibonacci recursivo
def fib(n):
    if n <= 1:
        return n
    else:
        return fib(n - 1) + fib(n - 2)

resultado = fib(7)
print(resultado)  # Imprime: 13
```

### Ejemplo 7: Programa Completo

```python
# Programa que calcula si un número es primo
def es_primo(n):
    if n <= 1:
        return False
    if n == 2:
        return True
    
    i = 2
    while i * i <= n:
        if n % i == 0:
            return False
        i = i + 1
    
    return True

# Probar con varios números
num = 17
if es_primo(num):
    print(1)  # Es primo
else:
    print(0)  # No es primo
```

### Ejemplo 7: Programa Interactivo ✨ **NUEVO**

```python
# Calculadora simple que lee dos números
# y muestra su suma

x = input()  # Lee el primer número
y = input()  # Lee el segundo número
suma = x + y
print(suma)

# Uso:
# $ echo -e "5\n3" | ./pymini programa.pymini
# 8
```

### Ejemplo 8: Factorial Interactivo ✨ **NUEVO**

```python
# Calcula el factorial de un número ingresado por el usuario

def factorial(n):
    if n <= 1:
        return 1
    else:
        return n * factorial(n - 1)

n = input()
resultado = factorial(n)
print(resultado)

# Uso:
# $ echo "5" | ./pymini factorial.pymini
# 120
```

Para más ejemplos avanzados, consulta `docs/EXAMPLES.md`.

---

## Herramientas Incluidas

### Convertir Código Antiguo (con llaves `{}`)

Si tienes código PyMini antiguo que usa llaves `{}` en lugar de indentación, puedes convertirlo automáticamente:

```bash
# Convertir todos los archivos .pymini en el proyecto
python3 convert_syntax.py
```

**¿Qué hace el script?**
- Encuentra todos los archivos `.pymini` en el proyecto
- Convierte la sintaxis de `{}` a indentación Python
- Crea copias de seguridad con extensión `.bak`
- Maneja correctamente: `if/elif/else`, `while`, `def`, bloques anidados

**Ejemplo de conversión:**

Antes (sintaxis antigua con `{}`):
```python
if x > 0: {
  print(x)
}
```

Después (sintaxis Python con indentación):
```python
if x > 0:
    print(x)
```

**Nota:** Todos los archivos de ejemplo y tests ya están actualizados a la nueva sintaxis.

---

## Pruebas incluidas

El repositorio incluye múltiples suites de pruebas:

### Tests Semánticos (Fases 1-2)

**Tests Positivos** - Ubicados en `tests/pos/`:
- `p01_simple.pymini` - Asignaciones y expresiones básicas
- `p02_if.pymini` - Condicionales if/else
- `p03_while.pymini` - Bucles while
- `p04_func.pymini` - Definición y llamada de funciones
- `p05_recursion.pymini` - Funciones recursivas (factorial)
- `p06_complex.pymini` - Programa completo con múltiples funciones

**Tests Negativos** - Ubicados en `tests/neg/`:
- `n01_undeclared_var.pymini` - Variable no declarada
- `n02_type_incompatible.pymini` - Tipos incompatibles
- `n03_if_not_bool.pymini` - Condición if no booleana
- `n04_wrong_arity.pymini` - Llamada con número incorrecto de argumentos
- `n05_param_conflict.pymini` - Parámetros duplicados
- `n06_reassign_type.pymini` - Reasignación con tipo diferente
- `n07_return_outside.pymini` - Return fuera de función
- `n08_while_not_bool.pymini` - Condición while no booleana

### Tests End-to-End (Fases 3-4)

**Tests Positivos** - Ubicados en `tests/e2e/pos/`:
- `e01_hello.pymini` - Impresión básica de int y bool
- `e02_arith.pymini` - Expresiones aritméticas
- `e03_if_while.pymini` - Control de flujo (while)
- `e04_funcs.pymini` - Llamadas a funciones
- `e05_bool.pymini` - Operadores booleanos y lógica

**Tests Negativos** - Ubicados en `tests/e2e/neg/`:
- `e06_divzero.pymini` - División por cero (debe fallar en runtime)

### Ejecutar todas las pruebas

**Tests semánticos:**
```bash
bash tests/run.sh
```

**Tests end-to-end:**
```bash
make test-e2e
```

**Ambos:**
```bash
bash tests/run.sh && make test-e2e
```

### Ejecutar una prueba individual

```bash
# Test semántico
./pymini tests/pos/p01_simple.pymini

# Test e2e (compila y ejecuta)
./pymini --run tests/e2e/pos/e02_arith.pymini

# Usando el helper script
./tools/build_and_run.sh tests/e2e/pos/e01_hello.pymini
```

Si todas las pruebas pasan, verás mensajes de éxito para cada una.

---

## estructura del repositorio y documentación detallada

archivos principales:

- `src/`: código fuente en c, lexer y parser
- `tests/`: archivos de prueba (.pymini)
- `Makefile`: instrucciones de compilación
- `run_tests.sh`: script para ejecutar las pruebas
- `README.md`: este archivo (guía principal)
- `README_FINAL.md`: resumen técnico de la fase 1
- `docs/`: documentación detallada organizada

contenido de `docs/`:

- `INICIO_RAPIDO.md`: guía de inicio rápido (5 minutos)
- `ARCHITECTURE.md`: arquitectura interna del compilador
- `EXAMPLES.md`: ejemplos de código pymini avanzados
- `ROADMAP.md`: plan de desarrollo futuro (fases 2-5)
- `CHANGELOG.md`: historial de cambios

recomendación: si un compañero quiere más detalle técnico, abrir `README_FINAL.md` o los archivos en `docs/`.

---

## problemas comunes y soluciones rápidas

1) "command not found: flex" o "bison"

solución: instalar las herramientas indicadas más arriba.

2) error: no se pudo abrir el archivo

solución: verificar que la ruta es correcta y que se está en el directorio del proyecto.

3) segmentation fault al ejecutar `./pymini` después de compilar

solución:

- recompilar desde cero: `make clean && make`
- si persiste, usar gdb: `sudo apt install -y gdb` y luego `gdb ./pymini` para obtener backtrace

4) advertencia "1 shift/reduce conflict"

esto es normal en esta gramática y no impide el funcionamiento.

---

## Nota para la exposición

Este proyecto fue preparado para la asignatura "Compiladores" de la Universidad de Sonsonate.

### Demostración Recomendada (Fases 1-4)

Al presentar la exposición, sigue estos pasos:

#### 1. Verificar dependencias
```bash
gcc --version && flex --version && bison --version
```

#### 2. Compilar el proyecto
```bash
make clean && make
```

#### 3. Demostración del CLI
```bash
# Mostrar ayuda
./pymini --help

# Mostrar versión
./pymini --version
```

#### 4. Compilar y ejecutar un programa simple
```bash
# Ejecutar directamente
./pymini tests/e2e/pos/e01_hello.pymini

# Output esperado:
# 1
# True
```

#### 5. Mostrar generación de código C
```bash
# Generar código C sin compilar
./pymini --emit-c -o demo.c tests/e2e/pos/e02_arith.pymini

# Ver el código generado
cat demo.c
```

#### 6. Demostrar optimizaciones
```bash
# Sin optimización
./pymini -O0 --emit-c -o demo_O0.c tests/e2e/pos/e02_arith.pymini

# Con optimización (constant folding)
./pymini -O1 --emit-c -o demo_O1.c tests/e2e/pos/e02_arith.pymini

# Comparar (O1 debe mostrar x = 7 directamente)
diff demo_O0.c demo_O1.c
```

#### 7. Mostrar recursión funcional
```bash
# Fibonacci recursivo
./pymini --run tests/e2e/pos/e06_recursion.pymini

# Output esperado: 13
```

#### 8. Demostrar detección de errores semánticos
```bash
# Variable no declarada
./pymini tests/neg/n01_undeclared.pymini

# Error de tipos
./pymini tests/neg/n02_type_op.pymini
```

#### 9. Demostrar detección de errores en runtime
```bash
# División por cero
./pymini --run tests/e2e/neg/e06_divzero.pymini

# Output esperado: Runtime Error: Division by zero
```

#### 10. Ejecutar suite completa de tests
```bash
# Tests end-to-end (compilación + ejecución)
make test-e2e

# Output esperado: Todos los tests pasan (7/7)
```

#### 11. Compilar a ejecutable standalone
```bash
# Generar ejecutable
./pymini --compile -o mi_programa tests/e2e/pos/e04_funcs.pymini

# Ejecutar el binario generado
./mi_programa

# Output esperado: 5
```

### Puntos Clave para Mencionar

✅ **4 Fases Completas**: Lexer, Parser, Semántica, Codegen
✅ **Genera código C nativo**: No interpretado, ejecutables reales
✅ **Optimizaciones funcionales**: Constant folding, dead code elimination
✅ **Runtime robusto**: Detección de división por cero
✅ **CLI profesional**: Múltiples modos de operación
✅ **Tests exhaustivos**: 21 tests (14 semánticos + 7 e2e)
✅ **Recursión soportada**: Fibonacci, factorial funcionan correctamente

---

## documentación adicional

para información más técnica y ejemplos avanzados:

1. `README_FINAL.md` — resumen técnico completo de las Fases 1 y 2 (estadísticas, features, tabla de tests)
2. `docs/INICIO_RAPIDO.md` — guía de inicio en 5 minutos (comandos directos)
3. `docs/ARCHITECTURE.md` — diseño interno del compilador con análisis semántico (para entender el código)
4. `docs/EXAMPLES.md` — ejemplos avanzados de pymini (recursión, etc.)
5. `docs/ROADMAP.md` — próximas fases del proyecto
6. `docs/CHANGELOG.md` — historial de cambios y versiones

## Características implementadas

### Fase 1 - Análisis Léxico y Sintáctico
- Tokenización completa con seguimiento de línea/columna
- Parsing de expresiones aritméticas y booleanas
- Soporte para if/elif/else, while, funciones
- Construcción de AST completo
- Reportes de error precisos

### Fase 2 - Análisis Semántico
- Sistema de tipos (int, bool)
- Tabla de símbolos con scope
- Verificación de declaración de variables
- Compatibilidad de tipos en expresiones
- Validación de funciones (existencia, aridad, parámetros)
- Detección de 8 tipos de errores semánticos
- Análisis en dos pasadas (firmas de funciones + cuerpo completo)

### Fase 3 - Generación de Código
- Traducción de AST a código C válido
- Runtime mínimo con funciones de impresión (int/bool)
- Verificación de división por cero en runtime
- Generación de función `__pymini_main` para código top-level
- Short-circuit evaluation para operadores lógicos
- Compilación automática con GCC

### Fase 4 - Pipeline y Optimizaciones
- CLI completo con múltiples banderas
- Pipeline automatizado: parse → sema → opt → codegen → gcc → run
- Constant folding (plegado de constantes)
- Dead code elimination (eliminación de código muerto)
- Tests end-to-end con verificación de salida
- Modo verbose para debugging del compilador

### Fase 5 - Indentación Pythonica **NUEVO**
- **Indentación significativa**: Los bloques se delimitan con indentación en lugar de llaves `{}`
- **100% compatible con Python**: La sintaxis es ahora idéntica a Python real
- **Tokens especiales**: INDENT, DEDENT, NEWLINE para manejar la estructura
- **Detección de errores**: Detecta mezcla de tabs/espacios, indentación inconsistente
- **Conversión automática**: Script incluido para convertir código antiguo con `{}`
- **Documentación completa**: Ver `docs/FASE_5_INDENTACION.md` para detalles técnicos




