# Tools - PyMini

Esta carpeta contiene herramientas de utilidad para el desarrollo y mantenimiento del compilador.

## Herramientas Disponibles

### `convert_syntax.py`
Convierte archivos `.pymini` de sintaxis antigua (con llaves `{}`) a sintaxis Python con indentación.

**Uso:**
```bash
python3 tools/convert_syntax.py
```

**Qué hace:**
- Busca recursivamente archivos `.pymini` en `tests/`, `demos/` y `examples/`
- Convierte sintaxis de `{}` a indentación Python (4 espacios)
- Crea backups con extensión `.bak`
- Maneja correctamente:
  * Bloques `if/elif/else`
  * Bucles `while`
  * Definiciones de funciones `def`
  * Bloques anidados

**Ejemplo de conversión:**

Antes:
```python
if x > 0: {
    print(x)
}
```

Después:
```python
if x > 0:
    print(x)
```

### `convert_to_indent.sh`
Script bash alternativo para conversión de sintaxis (versión anterior).

**Uso:**
```bash
bash tools/convert_to_indent.sh
```

## Cuándo usar estas herramientas

- Al migrar código antiguo a la nueva sintaxis con indentación
- Después de actualizar tests desde versiones anteriores
- Para convertir ejemplos de terceros a formato PyMini actual

## Notas

- ✅ Crea backups automáticos (`.bak`)
- ✅ No modifica archivos que ya usan indentación correcta
- ✅ Maneja múltiples niveles de anidación
- ⚠️ Revisa los archivos convertidos para verificar corrección
