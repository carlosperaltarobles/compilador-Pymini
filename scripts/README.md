# Scripts - PyMini

Esta carpeta contiene scripts de utilidad para ejecutar tests, demostraciones y tareas automatizadas.

## Scripts Disponibles

### `run_tests.sh`
Ejecuta la suite completa de tests básicos del compilador.
```bash
bash scripts/run_tests.sh
```
**Descripción:** Ejecuta todos los archivos `.pymini` en `tests/` y reporta resultados.

### `demo_presentacion.sh`
Script de demostración en vivo para presentaciones.
```bash
bash scripts/demo_presentacion.sh
```
**Descripción:** 
- Muestra programas correctos y con errores
- Demuestra detección de errores semánticos
- Ejecuta suite de tests completa
- Pausas interactivas entre pasos

### `demo_fases_3_4.sh`
Demostración de las Fases 3 y 4 (generación de código y pipeline).
```bash
bash scripts/demo_fases_3_4.sh
```
**Descripción:**
- Muestra generación de código C
- Demuestra pipeline completo
- Ejemplos de optimizaciones
- Ejecución de programas compilados

## Uso

Todos los scripts deben ejecutarse desde el directorio raíz del proyecto:

```bash
# Desde la raíz del proyecto
bash scripts/nombre_del_script.sh
```

Los scripts automáticamente se posicionan en el directorio correcto.

## Requisitos

- Compilador PyMini compilado (`./pymini` debe existir)
- Permisos de ejecución en los scripts
- GCC instalado (para generación de código)
