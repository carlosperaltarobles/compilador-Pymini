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
 * Punto de entrada del análisis semántico
 * Retorna 0 si no hay errores, >0 si hay errores
 */
int sema_check(Ast* root);

#endif // SEMA_H
