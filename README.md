# 🚀 PyMini - Compilador en C

> **Un compilador completo para aprender cómo funcionan los compiladores desde cero**

PyMini es un compilador educativo para un subconjunto simple de Python, implementado en C usando Flex y Bison.

---

## Tabla de Contenidos

1. [¿Qué es PyMini?](#-qué-es-pymini)
2. [Instalación de Dependencias](#-instalación-de-dependencias-paso-a-paso)
3. [Compilación del Proyecto](#-compilación-del-proyecto)
4. [Cómo Usar PyMini](#-cómo-usar-pymini)
5. [Características del Lenguaje](#-características-del-lenguaje-pymini)
6. [Ejemplos de Código](#-ejemplos-de-código)
7. [Ejecutar las Pruebas](#-ejecutar-las-pruebas)
8. [Documentación Adicional](#-documentación-adicional)
9. [Resolución de Problemas](#-resolución-de-problemas)

---

## ¿Qué es PyMini?

PyMini es un **compilador en C** que procesa un subconjunto de Python. En esta **Fase 1**, el compilador puede:

 **Leer** tu código fuente  
 **Analizar** si la sintaxis es correcta  
 **Crear** un árbol de sintaxis (AST)  
 **Mostrar** la estructura del código  
 **Reportar** errores con número de línea y columna  

❌ **NO ejecuta** el código (eso será en fases futuras)  
❌ **NO genera** código máquina todavía  

**En resumen:** PyMini verifica que tu código esté bien escrito y te muestra cómo está estructurado internamente.

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

## cómo usar el compilador

ejecutar un archivo:

```bash
./pymini <archivo.pymini>
```

ejemplo rápido:

```bash
./pymini tests/t01_expr.pymini
```

esto mostrará si el parseo fue ok y luego imprimirá el ast.

---

## pruebas incluidas

el repositorio incluye 8 pruebas en la carpeta `tests/`. para ejecutar todas:

```bash
./run_tests.sh
```

para ejecutar una prueba individual:

```bash
./pymini tests/t01_expr.pymini
```

si todas las pruebas pasan, el script `run_tests.sh` indica resumen al final.

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

este proyecto fue preparado para la asignatura "compiladores" de la Universidad de Sonsonate. el README está pensado para que cualquier compañero, sin experiencia previa, pueda levantar el proyecto paso a paso.

al entregar la exposicion, muéstren los pasos en este orden:

1. instalar dependencias
2. compilar con `make`
3. ejecutar `./pymini tests/t01_expr.pymini` para mostrar el ast
4. ejecutar `./run_tests.sh` para demostrar que todas las pruebas pasan

---

## documentación adicional

para información más técnica y ejemplos avanzados:

1. `README_FINAL.md` — resumen técnico de la fase 1 (estadísticas, features completas)
2. `docs/INICIO_RAPIDO.md` — guía de inicio en 5 minutos (comandos directos)
3. `docs/ARCHITECTURE.md` — diseño interno del compilador (para entender el código)
4. `docs/EXAMPLES.md` — ejemplos avanzados de pymini (recursión, etc.)
5. `docs/ROADMAP.md` — próximas fases del proyecto
6. `docs/CHANGELOG.md` — historial de cambios y versiones




