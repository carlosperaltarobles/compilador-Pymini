# Ejemplos de Uso de PyMini

Este documento muestra ejemplos de código PyMini y cómo usar el compilador.

## Compilación del Proyecto

```bash
# Asegúrate de tener las dependencias instaladas (ver INSTALL.md)
make

# Limpiar archivos generados
make clean
```

## Ejecutar el Compilador

```bash
# Sintaxis básica
./pymini <archivo.pymini>

# Ejemplo
./pymini tests/t01_expr.pymini
```

## Ejecutar Todos los Tests

```bash
# Opción 1: Usando el script de bash
./run_tests.sh

# Opción 2: Usando make
make test
```

## Ejemplos de Código PyMini

### 1. Expresiones Aritméticas

```python
# Operaciones básicas
x = 10 + 5 * 2
y = x / 3
z = y % 2

print(x)
print(y)
print(z)
```

### 2. Variables y Asignaciones

```python
# Asignaciones múltiples
a = 5
b = a + 3
c = b * 2

print(c)
```

### 3. Operadores Lógicos

```python
# Operadores and, or, not
x = True
y = False

result1 = x and y    # False
result2 = x or y     # True
result3 = not x      # False

print(result1)
print(result2)
print(result3)
```

### 4. Comparaciones

```python
# Operadores de comparación
a = 10
b = 5

print(a > b)    # True
print(a < b)    # False
print(a == b)   # False
print(a != b)   # True
print(a >= 10)  # True
print(b <= 5)   # True
```

### 5. Condicionales (if-elif-else)

```python
# Condicional simple
x = 10
if x > 5:
{
  print(True)
}
else:
{
  print(False)
}

# Condicional con elif
score = 85
if score >= 90:
{
  print(True)  # A
}
elif score >= 80:
{
  print(True)  # B
}
elif score >= 70:
{
  print(False) # C
}
else:
{
  print(False) # F
}
```

### 6. Bucles While

```python
# Bucle simple
counter = 0
while counter < 5:
{
  print(counter)
  counter = counter + 1
}

# Bucles anidados
i = 0
while i < 3:
{
  j = 0
  while j < 3:
  {
    print(i * 10 + j)
    j = j + 1
  }
  i = i + 1
}
```

### 7. Funciones

```python
# Función simple
def suma(a, b):
{
  return a + b
}

resultado = suma(5, 3)
print(resultado)

# Función con múltiples parámetros
def calcular(x, y, z):
{
  return x + y * z
}

print(calcular(1, 2, 3))

# Función sin parámetros
def saludar():
{
  print(True)
  return 42
}

x = saludar()
print(x)
```

### 8. Recursión

```python
# Factorial recursivo
def factorial(n):
{
  if n <= 1:
  {
    return 1
  }
  else:
  {
    return n * factorial(n - 1)
  }
}

print(factorial(5))  # 120

# Fibonacci recursivo
def fib(n):
{
  if n <= 1:
  {
    return n
  }
  else:
  {
    return fib(n - 1) + fib(n - 2)
  }
}

print(fib(7))  # 13
```

### 9. Expresiones Complejas

```python
# Combinación de operadores
a = 10
b = 5
c = 2

# Precedencia de operadores
result1 = a + b * c      # 20 (no 30)
result2 = (a + b) * c    # 30
result3 = a / b + c      # 4
result4 = a % b + c * b  # 10

print(result1)
print(result2)
print(result3)
print(result4)

# Expresiones lógicas complejas
x = True
y = False
z = True

complex1 = x and y or z           # True
complex2 = x and (y or z)         # True
complex3 = not x or y and z       # False
complex4 = (not x or y) and z     # False

print(complex1)
print(complex2)
print(complex3)
print(complex4)
```

### 10. Programa Completo

```python
# Programa que calcula números primos (aproximación)
def es_divisible(n, d):
{
  return n % d == 0
}

def verificar_primo(n):
{
  if n <= 1:
  {
    return False
  }
  else:
  {
    i = 2
    while i < n:
    {
      if es_divisible(n, i):
      {
        return False
      }
      else:
      {
        i = i + 1
      }
    }
    return True
  }
}

# Probar algunos números
print(verificar_primo(2))   # True
print(verificar_primo(7))   # True
print(verificar_primo(9))   # False
print(verificar_primo(11))  # True
```

## Salida del Compilador

Cuando ejecutas el compilador sobre un archivo válido, la salida incluye:

1. **Header informativo**: Indica que el archivo está siendo parseado
2. **"Parse OK"**: Confirma que el parseo fue exitoso
3. **AST impreso**: Muestra el árbol de sintaxis abstracta con formato de árbol
4. **Confirmación final**: Indica que la compilación fue exitosa

Ejemplo de salida:

```
==========================================
Compilador PyMini - Fase 1
==========================================
Parseando: tests/t01_expr.pymini
==========================================

==========================================
Parse OK
==========================================

========== AST ==========

Program [1:1]
  StmtList (2 statements)
    Assign [2:1] name='x'
      value:
        BinOp [2:5] op='+'
          left:
            IntLit [2:5] value=1
          right:
            BinOp [2:9] op='*'
              left:
                IntLit [2:9] value=2
              right:
                IntLit [2:13] value=3
    Print [3:1]
      Name [3:7] id='x'

=========================

==========================================
Compilación completada exitosamente
==========================================
```

## Manejo de Errores

El compilador reporta errores con línea y columna:

### Error Léxico

```python
x = 5 @ 3  # '@' no es un carácter válido
```

Salida:
```
Error léxico en línea 1, columna 7: carácter inválido '@'
```

### Error Sintáctico

```python
if x > 5
{
  print(x)
}
```

Salida:
```
Error sintáctico en línea 1, columna 9: syntax error, unexpected LBRACE, expecting COLON
```

## Limitaciones de la Fase 1

Esta es la Fase 1 del compilador, que solo implementa el front-end. Por lo tanto:

- ✅ El código se parsea y se construye el AST
- ❌ NO se verifica semántica (variables no declaradas, tipos, etc.)
- ❌ NO se genera código ejecutable
- ❌ NO se ejecuta el programa

Las fases futuras añadirán:
- **Fase 2**: Análisis semántico completo
- **Fase 3**: Generación de código intermedio
- **Fase 4**: Optimización
- **Fase 5**: Generación de código máquina/bytecode y runtime
