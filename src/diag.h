/**
 * diag.h - Sistema de diagnóstico (errores y warnings)
 */
#ifndef DIAG_H
#define DIAG_H

#include <stdarg.h>

// Contador global de errores
extern int g_error_count;
extern int g_warn_count;

/**
 * Emite un error con ubicación (línea:columna)
 */
void diag_error(int line, int col, const char* fmt, ...);

/**
 * Emite un warning con ubicación
 */
void diag_warn(int line, int col, const char* fmt, ...);

/**
 * Resetea los contadores de diagnóstico
 */
void diag_reset(void);

/**
 * Retorna si hay errores
 */
int diag_has_errors(void);

#endif // DIAG_H
