# Tests Manuales - PyMini

Esta carpeta contiene tests manuales utilizados durante el desarrollo del compilador, especialmente para la implementación de la Fase 5 (indentación significativa).

## Contenido

### Tests de Indentación
- `test_indent.pymini` - Test básico de indentación
- `test_dedent.pymini` - Test de múltiples DEDENT
- `test_dedent2.pymini` - Test adicional de DEDENT
- `test_if_only.pymini` - Test de condicionales con indentación
- `test_if_only2.pymini` - Variante de test condicional
- `test_if_simple.pymini` - If simple
- `test_simple_indent.pymini` - Programa simple con indentación
- `test_two_lines.pymini` - Test de dos líneas

### Tests de Funciones
- `test_func.pymini` - Test de definición de funciones

### Tests Finales
- `test_final.pymini` - Test final de integración
- `test_minimal.pymini` - Programa mínimo
- `test_simple.pymini` - Programa simple

### Archivos C Generados
- `*.c` - Archivos de código C generados durante pruebas de codegen

## Propósito

Estos archivos fueron creados durante el desarrollo para:
- Validar el sistema de indentación (tokens INDENT/DEDENT/NEWLINE)
- Probar casos edge del lexer
- Verificar múltiples niveles de anidación
- Debugging del parser con indentación

## Nota

Para tests automatizados y organizados, ver:
- `tests/pos/` - Tests positivos (semántica correcta)
- `tests/neg/` - Tests negativos (errores esperados)  
- `tests/e2e/` - Tests end-to-end (ejecución completa)
- `tests/t01-t08.pymini` - Suite de tests básicos

Estos tests manuales se mantienen por razones históricas y de referencia.
