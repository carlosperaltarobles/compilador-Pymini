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

/* Helper portable para duplicar cadenas (evita dependencia de strdup explicita) */
static char* rt_strdup(const char* s) {
    if (!s) return NULL;
    size_t n = strlen(s) + 1;
    char* r = malloc(n);
    if (!r) return NULL;
    memcpy(r, s, n);
    return r;
}

void rt_print_int(int x) {
    printf("%d\n", x);
}

void rt_print_bool(int b) {
    printf("%s\n", b ? "True" : "False");
}

void rt_print_string(const char* s) {
    printf("%s\n", s);
}

int rt_input_int(const char* prompt) {
    if (prompt) {
        printf("%s", prompt);
        fflush(stdout);
    }
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

char* rt_input_string(const char* prompt) {
    if (prompt) {
        printf("%s", prompt);
        fflush(stdout);
    }
    /* Implementación portable usando fgets en un buffer razonable. */
    char buf[4096];
    if (!fgets(buf, sizeof(buf), stdin)) {
        /* EOF o error: devolver cadena vacía */
        return rt_strdup("");
    }
    /* Remover salto de línea final si existe */
    size_t l = strlen(buf);
    if (l > 0 && buf[l - 1] == '\n') buf[l - 1] = '\0';
    return rt_strdup(buf);
}

char* rt_str_concat(const char* a, const char* b) {
    if (!a) a = "";
    if (!b) b = "";
    size_t len_a = strlen(a);
    size_t len_b = strlen(b);
    char* result = malloc(len_a + len_b + 1);
    if (!result) {
        fprintf(stderr, "\n╔═══════════════════════════════════╗\n");
        fprintf(stderr, "║   Runtime Error                   ║\n");
        fprintf(stderr, "╠═══════════════════════════════════╣\n");
        fprintf(stderr, "║ Error de memoria al concatenar    ║\n");
        fprintf(stderr, "╚═══════════════════════════════════╝\n\n");
        exit(EXIT_FAILURE);
    }
    memcpy(result, a, len_a);
    memcpy(result + len_a, b, len_b + 1);
    return result;
}

int rt_str_to_int(const char* s) {
    if (!s || !*s) {
        fprintf(stderr, "\n╔═══════════════════════════════════╗\n");
        fprintf(stderr, "║   Runtime Error                   ║\n");
        fprintf(stderr, "╠═══════════════════════════════════╣\n");
        fprintf(stderr, "║ No se puede convertir string      ║\n");
        fprintf(stderr, "║ vacío a int                       ║\n");
        fprintf(stderr, "╚═══════════════════════════════════╝\n\n");
        exit(EXIT_FAILURE);
    }
    
    char* endptr;
    long val = strtol(s, &endptr, 10);
    
    if (*endptr != '\0') {
        fprintf(stderr, "\n╔═══════════════════════════════════╗\n");
        fprintf(stderr, "║   Runtime Error                   ║\n");
        fprintf(stderr, "╠═══════════════════════════════════╣\n");
        fprintf(stderr, "║ String inválido para conversión   ║\n");
        fprintf(stderr, "║ a int: '%s'                       ║\n", s);
        fprintf(stderr, "╚═══════════════════════════════════╝\n\n");
        exit(EXIT_FAILURE);
    }
    
    return (int)val;
}

char* rt_int_to_str(int n) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%d", n);
    return rt_strdup(buf);
}

char* rt_bool_to_str(int b) {
    return rt_strdup(b ? "True" : "False");
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
