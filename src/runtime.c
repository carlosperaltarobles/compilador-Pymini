/**
 * runtime.c - Implementación del runtime robusto para PyMini (Fase 5)
 */
#include "runtime.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Variables globales para tracing */
static int rt_trace_enabled = 0;
static int rt_trace_depth = 0;

void rt_enable_trace(void) {
    rt_trace_enabled = 1;
}

void rt_trace(const char* func_name, const char* event) {
    if (!rt_trace_enabled) return;
    
    for (int i = 0; i < rt_trace_depth; i++) {
        fprintf(stderr, "  ");
    }
    
    if (strcmp(event, "enter") == 0) {
        fprintf(stderr, "→ %s()\n", func_name);
        rt_trace_depth++;
    } else if (strcmp(event, "exit") == 0) {
        rt_trace_depth--;
        for (int i = 0; i < rt_trace_depth; i++) {
            fprintf(stderr, "  ");
        }
        fprintf(stderr, "← %s()\n", func_name);
    }
}

void rt_print_int(int x) {
    printf("%d\n", x);
}

void rt_print_bool(int b) {
    printf("%s\n", b ? "True" : "False");
}

int rt_input_int(void) {
    int value;
    if (scanf("%d", &value) != 1) {
        fprintf(stderr, "\n╔═══════════════════════════════════╗\n");
        fprintf(stderr, "║   Input Error                     ║\n");
        fprintf(stderr, "╠═══════════════════════════════════╣\n");
        fprintf(stderr, "║ No se pudo leer un entero válido  ║\n");
        fprintf(stderr, "╚═══════════════════════════════════╝\n\n");
        exit(EXIT_FAILURE);
    }
    return value;
}

int rt_div(int a, int b) {
    if (b == 0) {
        fprintf(stderr, "\n╔═══════════════════════════════════╗\n");
        fprintf(stderr, "║   Runtime Error                   ║\n");
        fprintf(stderr, "╠═══════════════════════════════════╣\n");
        fprintf(stderr, "║ División por cero detectada       ║\n");
        fprintf(stderr, "║ Operación: %d / %d                ║\n", a, b);
        fprintf(stderr, "╚═══════════════════════════════════╝\n\n");
        exit(EXIT_FAILURE);
    }
    return a / b;
}

int rt_mod(int a, int b) {
    if (b == 0) {
        fprintf(stderr, "\n╔═══════════════════════════════════╗\n");
        fprintf(stderr, "║   Runtime Error                   ║\n");
        fprintf(stderr, "╠═══════════════════════════════════╣\n");
        fprintf(stderr, "║ Módulo por cero detectado         ║\n");
        fprintf(stderr, "║ Operación: %d %% %d               ║\n", a, b);
        fprintf(stderr, "╚═══════════════════════════════════╝\n\n");
        exit(EXIT_FAILURE);
    }
    return a % b;
}

int rt_assert(int condition, const char* message) {
    if (!condition) {
        fprintf(stderr, "\n╔═══════════════════════════════════╗\n");
        fprintf(stderr, "║   Assertion Failed                ║\n");
        fprintf(stderr, "╠═══════════════════════════════════╣\n");
        fprintf(stderr, "║ %s\n", message);
        fprintf(stderr, "╚═══════════════════════════════════╝\n\n");
        exit(EXIT_FAILURE);
    }
    return 1;
}

/**
 * main real: llama a la función generada __pymini_main()
 */
int main(int argc, char** argv) {
    (void)argc;
    (void)argv;
    
    /* Verificar si se habilitó trace mediante variable de entorno */
    if (getenv("PYMINI_TRACE")) {
        rt_enable_trace();
    }
    
    return __pymini_main();
}
