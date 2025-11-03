# Guía Rápida de Inicio - PyMini

## Instalación Rápida (Ubuntu/Debian/WSL)

```bash
# Instalar dependencias
sudo apt update
sudo apt install build-essential flex bison

# Compilar el proyecto
cd /ruta/a/Compilador_Python
make

# Ejecutar tests
./run_tests.sh
```

## Uso Básico

```bash
# Parsear un archivo
./pymini archivo.pymini

# Ejemplo
./pymini tests/t01_expr.pymini
```

## Estructura del Proyecto

```
Compilador_Python/
├── src/                # Código fuente del compilador
│   ├── lexer.l        # Analizador léxico (Flex)
│   ├── parser.y       # Analizador sintáctico (Bison)
│   ├── ast.h/c        # Árbol de sintaxis abstracta
│   ├── ast_print.h/c  # Pretty-printer del AST
│   ├── sema.h/c       # Análisis semántico (stub)
│   └── main.c         # Punto de entrada
├── tests/             # Archivos de prueba
├── Makefile          # Sistema de build
├── run_tests.sh      # Script de pruebas
├── README.md         # Documentación principal
├── INSTALL.md        # Guía de instalación
└── EXAMPLES.md       # Ejemplos de código
```

## Comandos Make

```bash
make           # Compilar el proyecto
make clean     # Limpiar archivos generados
make test      # Ejecutar todos los tests
```

## Sintaxis Básica de PyMini

```python
# Variables y expresiones
x = 10 + 5 * 2
print(x)

# Condicionales
if x > 15:
{
  print(True)
}
else:
{
  print(False)
}

# Bucles
i = 0
while i < 5:
{
  print(i)
  i = i + 1
}

# Funciones
def suma(a, b):
{
  return a + b
}

resultado = suma(3, 4)
print(resultado)
```

## Verificar que Todo Funciona

```bash
# 1. Compilar
make

# 2. Probar un archivo simple
echo 'x = 5
print(x)' > test_simple.pymini
./pymini test_simple.pymini

# 3. Ejecutar todos los tests
./run_tests.sh
```

Si ves "Parse OK" y el AST impreso, ¡todo está funcionando correctamente!

## Solución de Problemas Comunes

### Error: "Command 'make' not found"
```bash
sudo apt install build-essential
```

### Error: "flex: not found"
```bash
sudo apt install flex
```

### Error: "bison: not found"
```bash
sudo apt install bison
```

### Error: "./run_tests.sh: Permission denied"
```bash
chmod +x run_tests.sh
```

## Más Información

- Ver `README.md` para documentación completa
- Ver `EXAMPLES.md` para más ejemplos de código
- Ver `INSTALL.md` para instrucciones de instalación en otros sistemas
