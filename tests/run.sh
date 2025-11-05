#!/bin/bash
# Script para ejecutar tests de análisis semántico

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

COMPILER="./pymini"
POS_DIR="tests/pos"
NEG_DIR="tests/neg"

total_tests=0
passed_tests=0
failed_tests=0

echo "========================================"
echo "  Tests de Análisis Semántico PyMini"
echo "========================================"
echo ""

# Verificar que el compilador existe
if [ ! -f "$COMPILER" ]; then
    echo -e "${RED}Error: Compilador '$COMPILER' no encontrado${NC}"
    echo "Por favor ejecuta 'make' primero"
    exit 1
fi

# Tests positivos (deben pasar)
echo "=== Tests Positivos (deben pasar sin errores) ==="
echo ""

for test_file in "$POS_DIR"/*.pymini; do
    if [ -f "$test_file" ]; then
        total_tests=$((total_tests + 1))
        filename=$(basename "$test_file")
        
        echo -n "  [TEST] $filename ... "
        
        # Ejecutar el compilador y capturar salida
        output=$("$COMPILER" "$test_file" 2>&1)
        exit_code=$?
        
        # Verificar que terminó con código 0 y contiene "Semantic OK"
        if [ $exit_code -eq 0 ] && echo "$output" | grep -q "Semantic OK"; then
            echo -e "${GREEN}OK${NC}"
            passed_tests=$((passed_tests + 1))
        else
            echo -e "${RED}FAIL${NC}"
            echo "     Esperado: código 0 y 'Semantic OK'"
            echo "     Obtenido: código $exit_code"
            echo "     Salida:"
            echo "$output" | sed 's/^/       /'
            failed_tests=$((failed_tests + 1))
        fi
    fi
done

echo ""

# Tests negativos (deben fallar)
echo "=== Tests Negativos (deben fallar con errores) ==="
echo ""

for test_file in "$NEG_DIR"/*.pymini; do
    if [ -f "$test_file" ]; then
        total_tests=$((total_tests + 1))
        filename=$(basename "$test_file")
        
        echo -n "  [TEST] $filename ... "
        
        # Ejecutar el compilador y capturar salida
        output=$("$COMPILER" "$test_file" 2>&1)
        exit_code=$?
        
        # Verificar que terminó con código distinto de 0 y contiene "error"
        if [ $exit_code -ne 0 ] && echo "$output" | grep -qi "error"; then
            echo -e "${GREEN}OK${NC}"
            passed_tests=$((passed_tests + 1))
        else
            echo -e "${RED}FAIL${NC}"
            echo "     Esperado: código != 0 y mensaje de error"
            echo "     Obtenido: código $exit_code"
            echo "     Salida:"
            echo "$output" | sed 's/^/       /'
            failed_tests=$((failed_tests + 1))
        fi
    fi
done

echo ""
echo "========================================"
echo "  Resultados"
echo "========================================"
echo "  Total:   $total_tests"
echo -e "  ${GREEN}Pasados: $passed_tests${NC}"

if [ $failed_tests -gt 0 ]; then
    echo -e "  ${RED}Fallados: $failed_tests${NC}"
    echo ""
    echo -e "${RED}Algunos tests fallaron${NC}"
    exit 1
else
    echo ""
    echo -e "${GREEN}¡Todos los tests pasaron!${NC}"
    exit 0
fi
