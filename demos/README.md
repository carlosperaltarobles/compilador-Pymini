# Demos - PyMini

Esta carpeta contiene archivos de demostración para presentaciones y pruebas rápidas del compilador PyMini.

## Archivos

### `demo.pymini`
Programa principal de demostración que calcula factoriales usando recursión.
```bash
./pymini demos/demo.pymini
```
**Salida:** `120` y `5040`

### `demo_error.pymini`
Ejemplo de error semántico (variable no declarada) para demostrar la detección de errores del compilador.
```bash
./pymini demos/demo_error.pymini
```
**Resultado:** Error detectado correctamente

### `demo_tipos.pymini`
Ejemplo de error de tipos (operaciones con tipos incompatibles) para demostrar el sistema de tipos.
```bash
./pymini demos/demo_tipos.pymini
```
**Resultado:** Error de tipos detectado

## Uso en Presentaciones

Estos archivos son útiles para:
- Demostrar las capacidades del compilador
- Mostrar detección de errores
- Explicar el sistema de tipos
- Validar el análisis semántico

Ver `scripts/demo_presentacion.sh` para una demostración automática completa.
