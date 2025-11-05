# PyMini - Compilador en C

> **Un compilador completo para aprender cómo funcionan los compiladores desde cero**

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

PyMini es un **compilador completo en C** que procesa un subconjunto de Python. Actualmente en **Fases 1 y 2**, el compilador puede:

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

**Mostrar** la estructura del código completo y validado

**NO ejecuta** el código (eso será en Fase 3: Generación de código)  
**NO genera** código máquina todavía  

**En resumen:** PyMini verifica que tu código esté bien escrito sintáctica y semánticamente, y te muestra cómo está estructurado internamente.

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

## Demostración en Vivo

### Opción Rápida: Script Automático

Para una demostración automatizada durante la presentación:

```bash
./demo_presentacion.sh
```

Este script ejecutará todos los pasos de demostración automáticamente, mostrando:
1. Verificación de dependencias
2. Compilación exitosa de un programa
3. Detección de error semántico (variable no declarada)
4. Detección de error de tipos incompatibles
5. Ejecución de suite completa de tests

### Crear tu Primer Programa PyMini (Paso a Paso)

Vamos a crear un archivo `.pymini` desde cero y compilarlo paso a paso.

#### Paso 1: Crear el archivo

```bash
nano demo.pymini
```

O usando `cat` directamente:

```bash
cat > demo.pymini << 'EOF'
# Programa de demostración PyMini
# Calcula el factorial de un número

def factorial(n): {
    if n <= 1: {
        return 1
    } else: {
        return n * factorial(n - 1)
    }
}

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

## cómo usar el compilador

ejecutar un archivo:

```bash
./pymini <archivo.pymini>
```

ejemplo rápido:

```bash
./pymini tests/pos/p01_simple.pymini
```

esto mostrará si el análisis fue exitoso y luego imprimirá el ast.

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
if condicion: {
    # código
} elif otra_condicion: {
    # código
} else: {
    # código
}
```

**Bucles**:
```python
while condicion: {
    # código
}
```

### Funciones

**Definición**:
```python
def nombre_funcion(param1, param2): {
    # código
    return valor
}
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
- `print(expresion)` - Imprime una expresión

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

if num > 0: {
    print(1)  # Positivo
} elif num < 0: {
    print(-1)  # Negativo
} else: {
    print(0)  # Cero
}
```

### Ejemplo 3: Bucles

```python
# Suma de los primeros 10 números
suma = 0
i = 1

while i <= 10: {
    suma = suma + i
    i = i + 1
}

print(suma)  # Imprime: 55
```

### Ejemplo 4: Funciones

```python
# Función que calcula el máximo de dos números
def max(a, b): {
    if a > b: {
        return a
    } else: {
        return b
    }
}

resultado = max(15, 23)
print(resultado)  # Imprime: 23
```

### Ejemplo 5: Recursión (Factorial)

```python
# Cálculo recursivo del factorial
def factorial(n): {
    if n <= 1: {
        return 1
    } else: {
        return n * factorial(n - 1)
    }
}

f5 = factorial(5)
print(f5)  # Imprime: 120
```

### Ejemplo 6: Fibonacci

```python
# Fibonacci recursivo
def fib(n): {
    if n <= 1: {
        return n
    } else: {
        return fib(n - 1) + fib(n - 2)
    }
}

resultado = fib(7)
print(resultado)  # Imprime: 13
```

### Ejemplo 7: Programa Completo

```python
# Programa que calcula si un número es primo
def es_primo(n): {
    if n <= 1: {
        return False
    }
    if n == 2: {
        return True
    }
    
    i = 2
    while i * i <= n: {
        if n % i == 0: {
            return False
        }
        i = i + 1
    }
    
    return True
}

# Probar con varios números
num = 17
if es_primo(num): {
    print(1)  # Es primo
} else: {
    print(0)  # No es primo
}
```

Para más ejemplos avanzados, consulta `docs/EXAMPLES.md`.

---

## pruebas incluidas

el repositorio incluye 14 pruebas organizadas en dos categorías:

### Tests Positivos (deben pasar)
Ubicados en `tests/pos/`:
- `p01_simple.pymini` - Asignaciones y expresiones básicas
- `p02_if.pymini` - Condicionales if/else
- `p03_while.pymini` - Bucles while
- `p04_func.pymini` - Definición y llamada de funciones
- `p05_recursion.pymini` - Funciones recursivas (factorial)
- `p06_complex.pymini` - Programa completo con múltiples funciones

### Tests Negativos (deben fallar)
Ubicados en `tests/neg/`:
- `n01_undeclared_var.pymini` - Variable no declarada
- `n02_type_incompatible.pymini` - Tipos incompatibles
- `n03_if_not_bool.pymini` - Condición if no booleana
- `n04_wrong_arity.pymini` - Llamada con número incorrecto de argumentos
- `n05_param_conflict.pymini` - Parámetros duplicados
- `n06_reassign_type.pymini` - Reasignación con tipo diferente
- `n07_return_outside.pymini` - Return fuera de función
- `n08_while_not_bool.pymini` - Condición while no booleana

### Ejecutar todas las pruebas

```bash
bash tests/run.sh
```

### Ejecutar una prueba individual

```bash
./pymini tests/pos/p01_simple.pymini
./pymini tests/neg/n01_undeclared_var.pymini
```

si todas las pruebas pasan, el script mostrará un resumen con el estado de cada una.

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

## nota para la exposicion

este proyecto fue preparado para la asignatura "compiladores" de la Universidad de Sonsonate.

al entregar la exposicion, muéstren los pasos en este orden:

1. **Verificar dependencias instaladas**: `gcc --version && flex --version && bison --version`
2. **Compilar el proyecto**: `make clean && make`
3. **Demostración en vivo**: Crear un archivo `demo.pymini` y compilarlo (ver sección anterior)
4. **Mostrar programa correcto**: `./pymini tests/pos/p01_simple.pymini`
5. **Mostrar detección de errores**: `./pymini tests/neg/n01_undeclared_var.pymini`
6. **Ejecutar suite completa**: `bash tests/run.sh` (14/14 tests pasan)
7. **Explicar arquitectura**: Mostrar el flujo desde código fuente hasta AST validado

---

## documentación adicional

para información más técnica y ejemplos avanzados:

1. `README_FINAL.md` — resumen técnico completo de las Fases 1 y 2 (estadísticas, features, tabla de tests)
2. `docs/INICIO_RAPIDO.md` — guía de inicio en 5 minutos (comandos directos)
3. `docs/ARCHITECTURE.md` — diseño interno del compilador con análisis semántico (para entender el código)
4. `docs/EXAMPLES.md` — ejemplos avanzados de pymini (recursión, etc.)
5. `docs/ROADMAP.md` — próximas fases del proyecto
6. `docs/CHANGELOG.md` — historial de cambios y versiones

## características implementadas

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




