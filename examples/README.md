# Examples - PyMini

Esta carpeta contiene ejemplos de programas interactivos que usan la función `input()` para leer datos del usuario.

## Archivos

### `test_input.pymini`
Ejemplo básico: suma de dos números ingresados por el usuario.
```bash
echo -e "5\n3" | ./pymini examples/test_input.pymini
```
**Salida:** `8`

### `test_input_factorial.pymini`
Calcula el factorial de un número ingresado por el usuario.
```bash
echo "7" | ./pymini examples/test_input_factorial.pymini
```
**Salida:** `5040`

### `test_calculator.pymini`
Calculadora simple que realiza operaciones básicas (suma, resta, multiplicación, división).
```bash
echo -e "10\n3" | ./pymini examples/test_calculator.pymini
```
**Salida:** Resultados de las operaciones

### `test_par_impar.pymini`
Determina si un número es par (imprime `1`) o impar (imprime `0`).
```bash
echo "10" | ./pymini examples/test_par_impar.pymini
```
**Salida:** `1` (par)

## Características

Estos ejemplos demuestran:
- ✨ Función `input()` para interactividad
- Lectura de enteros desde stdin
- Combinación con operadores aritméticos
- Uso en funciones recursivas
- Condicionales con entrada de usuario

## Uso Interactivo

Para probar de forma interactiva (sin `echo`):
```bash
./pymini examples/test_input_factorial.pymini
# Escribe un número y presiona ENTER
```
