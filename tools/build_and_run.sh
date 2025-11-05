#!/bin/bash
# build_and_run.sh - Helper para compilar y ejecutar tests e2e

set -e

if [ "$#" -ne 1 ]; then
    echo "Uso: $0 <archivo.pymini>"
    exit 1
fi

INPUT_FILE="$1"
GOLDEN_FILE="${INPUT_FILE}.golden"
COMPILER="./pymini"

# Verificar que el compilador existe
if [ ! -f "$COMPILER" ]; then
    echo "Error: No se encuentra el compilador '$COMPILER'"
    echo "Ejecuta 'make' primero"
    exit 1
fi

# Verificar que el archivo de entrada existe
if [ ! -f "$INPUT_FILE" ]; then
    echo "Error: No se encuentra el archivo '$INPUT_FILE'"
    exit 1
fi

# Ejecutar el programa y capturar la salida
ACTUAL_OUTPUT=$($COMPILER --run "$INPUT_FILE" 2>&1 || true)

# Si existe archivo golden, comparar
if [ -f "$GOLDEN_FILE" ]; then
    EXPECTED_OUTPUT=$(cat "$GOLDEN_FILE")
    
    if [ "$ACTUAL_OUTPUT" = "$EXPECTED_OUTPUT" ]; then
        echo "✓ Test PASSED: $INPUT_FILE"
        exit 0
    else
        echo "✗ Test FAILED: $INPUT_FILE"
        echo ""
        echo "Esperado:"
        echo "$EXPECTED_OUTPUT"
        echo ""
        echo "Obtenido:"
        echo "$ACTUAL_OUTPUT"
        exit 1
    fi
else
    # Sin archivo golden, solo mostrar salida
    echo "Output de $INPUT_FILE:"
    echo "$ACTUAL_OUTPUT"
    exit 0
fi
