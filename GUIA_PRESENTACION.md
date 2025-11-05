# Guía Rápida para la Presentación/Exposición

## Preparación Previa

1. Asegúrate de tener el proyecto compilado:
   ```bash
   make clean && make
   ```

2. Verifica que todos los tests pasen:
   ```bash
   bash tests/run.sh
   ```

## Durante la Presentación

### Opción 1: Demostración Automática (Recomendada)

Ejecuta el script interactivo:
```bash
./demo_presentacion.sh
```

Esto mostrará todo el proceso paso a paso con pausas entre cada demostración.

### Opción 2: Demostración Manual

#### Paso 1: Mostrar Dependencias
```bash
gcc --version
flex --version
bison --version
```

#### Paso 2: Programa Correcto
```bash
cat demo.pymini
./pymini demo.pymini
```

#### Paso 3: Error Semántico (Variable no declarada)
```bash
cat demo_error.pymini
./pymini demo_error.pymini
```
Resultado esperado: Error en línea 3

#### Paso 4: Error de Tipos
```bash
cat demo_tipos.pymini
./pymini demo_tipos.pymini
```
Resultado esperado: Error de tipos incompatibles

#### Paso 5: Suite Completa de Tests
```bash
bash tests/run.sh
```
Resultado esperado: 14/14 tests pasan (100%)

## Puntos Clave a Mencionar

1. **Fase 1 Completa**: Análisis léxico y sintáctico
   - Tokenización con Flex
   - Parsing con Bison
   - Construcción de AST
   - Reportes de error con línea/columna

2. **Fase 2 Completa**: Análisis semántico
   - Sistema de tipos (int, bool)
   - Tabla de símbolos con scope
   - Verificación de variables declaradas
   - Validación de funciones
   - 8 tipos de errores semánticos detectados

3. **Estadísticas del Proyecto**:
   - ~2250 líneas de código C
   - 25+ tokens soportados
   - 20+ tipos de nodos AST
   - 14 tests (6 positivos, 8 negativos)
   - 100% de tests pasando

4. **Arquitectura Robusta**:
   - Análisis en dos pasadas
   - Manejo de errores completo
   - Código modular y bien organizado

## Respuestas a Preguntas Frecuentes

**P: ¿Por qué usa llaves {} en lugar de indentación?**
R: Para simplificar el parser. La indentación significativa requiere un lexer mucho más complejo.

**P: ¿Puede ejecutar el código?**
R: No todavía. Eso será en la Fase 3 (Generación de código). Actualmente verifica que el código esté correcto.

**P: ¿Qué pasa si hay múltiples errores?**
R: El compilador detecta y reporta todos los errores semánticos en una sola pasada.

**P: ¿Soporta otros tipos?**
R: Actualmente solo int y bool. Strings, listas, etc. serían extensiones futuras.

**P: ¿Cuánto tiempo tomó desarrollarlo?**
R: La Fase 1 tomó aproximadamente [X] horas, la Fase 2 tomó [Y] horas.

## Archivos de Documentación Adicional

Si te preguntan por detalles técnicos, puedes referirlos a:
- `README_FINAL.md` - Resumen técnico completo
- `docs/ARCHITECTURE.md` - Arquitectura interna
- `docs/EXAMPLES.md` - Ejemplos avanzados
- `docs/ROADMAP.md` - Plan de desarrollo futuro

## Checklist Final Antes de Presentar

- [ ] Proyecto compilado (`./pymini` existe)
- [ ] Todos los tests pasan (14/14)
- [ ] Script de demostración tiene permisos de ejecución
- [ ] Archivos demo creados (demo.pymini, demo_error.pymini, demo_tipos.pymini)
- [ ] Terminal configurado con fuente legible
- [ ] Navegador con documentación abierta (opcional)

## Contacto y Créditos

Proyecto desarrollado para la asignatura "Compiladores"
Universidad de Sonsonate
[Agregar nombres del equipo]

---

**¡Buena suerte con la presentación!**
