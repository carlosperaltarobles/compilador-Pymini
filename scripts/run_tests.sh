#!/bin/bash

# Script de pruebas para el compilador PyMini

echo "=========================================="
echo "Ejecutando tests de PyMini"
echo "=========================================="
echo ""

# Contador de tests
total_tests=0
passed_tests=0
failed_tests=0

# Ir al directorio raíz del proyecto
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR/.." || exit 1

# Verificar que el ejecutable existe
if [ ! -f "./bin/pymini" ]; then
    echo "ERROR: El ejecutable './bin/pymini' no existe."
    echo "Por favor, ejecute 'make' primero."
    exit 1
fi

# Buscar todos los archivos .pymini en tests/
for test_file in tests/*.pymini; do
    if [ ! -f "$test_file" ]; then
        echo "Advertencia: No se encontraron archivos de prueba en tests/"
        exit 1
    fi
    
    total_tests=$((total_tests + 1))
    test_name=$(basename "$test_file")
    
    echo "----------------------------------------"
    echo "Test $total_tests: $test_name"
    echo "----------------------------------------"
    
    # Ejecutar el test
    ./bin/pymini "$test_file" > /tmp/pymini_test_output.txt 2>&1
    exit_code=$?
    
    # Verificar el resultado
    # El compilador tiene éxito si retorna código 0 (sin errores de compilación)
    if [ $exit_code -eq 0 ]; then
        echo "✓ PASÓ: $test_name"
        passed_tests=$((passed_tests + 1))
        # Mostrar salida si hay
        if [ -s /tmp/pymini_test_output.txt ]; then
            echo "Salida:"
            cat /tmp/pymini_test_output.txt
        fi
    else
        echo "✗ FALLÓ: $test_name (código de salida: $exit_code)"
        failed_tests=$((failed_tests + 1))
        echo "Salida:"
        cat /tmp/pymini_test_output.txt
    fi
    
    echo ""
done

# Limpiar archivo temporal
rm -f /tmp/pymini_test_output.txt

# Resumen
echo "=========================================="
echo "Resumen de Tests"
echo "=========================================="
echo "Total:   $total_tests"
echo "Pasaron: $passed_tests"
echo "Fallaron: $failed_tests"
echo "=========================================="
echo ""

# Retornar código de salida apropiado
if [ $failed_tests -eq 0 ]; then
    echo "✓ Todos los tests pasaron correctamente"
    exit 0
else
    echo "✗ Algunos tests fallaron"
    exit 1
fi
