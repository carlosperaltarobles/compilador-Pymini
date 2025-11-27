# PyMini - Instrucciones Rápidas

## Para la Presentación/Exposición

### Antes de Empezar
```bash
cd /ruta/a/Compilador_Python
make clean && make
```

### Opción 1: Demostración Automática (Recomendada)
```bash
./demo_presentacion.sh
```

### Opción 2: Comandos Individuales

**Programa correcto:**
```bash
./pymini demo.pymini
```

**Error semántico:**
```bash
./pymini demo_error.pymini
```

**Error de tipos:**
```bash
./pymini demo_tipos.pymini
```

**Todos los tests:**
```bash
bash tests/run.sh
```

## Documentación

- `README.md` - Guía principal con ejemplos y demostración
- `GUIA_PRESENTACION.md` - Guía detallada para la exposición
- `README_FINAL.md` - Resumen técnico completo
- `docs/ARCHITECTURE.md` - Arquitectura interna

## Estado del Proyecto

- Fase 1: Análisis Léxico y Sintáctico ✓
- Fase 2: Análisis Semántico ✓
- Tests: 14/14 (100%)
- Líneas de código: ~2250

## Crear tu Propio Programa

```bash
nano mi_programa.pymini
```

Ejemplo:
```python
def suma(a, b): {
    return a + b
}

resultado = suma(10, 20)
print(resultado)
```

Compilar:
```bash
./pymini mi_programa.pymini
```

---

**Nota importante:** PyMini usa llaves `{}` para delimitar bloques, no indentación.
