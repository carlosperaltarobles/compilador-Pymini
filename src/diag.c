/**
 * diag.c - Implementación del sistema de diagnóstico
 */
#include "diag.h"
#include <stdio.h>
#include <stdarg.h>

int g_error_count = 0;
int g_warn_count = 0;

void diag_error(int line, int col, const char* fmt, ...) {
    fprintf(stderr, "%d:%d: error: ", line, col);
    
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    
    fprintf(stderr, "\n");
    g_error_count++;
}

void diag_warn(int line, int col, const char* fmt, ...) {
    fprintf(stderr, "%d:%d: warning: ", line, col);
    
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    
    fprintf(stderr, "\n");
    g_warn_count++;
}

void diag_reset(void) {
    g_error_count = 0;
    g_warn_count = 0;
}

int diag_has_errors(void) {
    return g_error_count > 0;
}
