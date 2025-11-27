/**
 * sema.h - Análisis semántico para PyMini
 */
#ifndef SEMA_H
#define SEMA_H

#include "ast.h"
#include "symtab.h"

/**
 * Contexto del análisis semántico
 */
typedef struct {
    Scope* scope;           // Scope actual
    Symbol* current_func;   // Función actual (NULL si estamos en global)
    int in_function;        // Flag: estamos dentro de una función
} SemaCtx;

/**
 * Resultado del análisis semántico
 */
typedef struct {
    int error_count;        // Número de errores encontrados
    Scope* global_scope;    // Scope global (debe ser liberado por el caller)
} SemaResult;

/**
 * Punto de entrada del análisis semántico
 * Retorna 0 si no hay errores, >0 si hay errores
 */
int sema_check(Ast* root);

/**
 * Versión extendida que retorna el scope global
 * El caller es responsable de liberar el scope con scope_free()
 */
SemaResult sema_check_ex(Ast* root);

#endif // SEMA_H
