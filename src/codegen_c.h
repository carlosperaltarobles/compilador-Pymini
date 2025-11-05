/**
 * codegen_c.h - Generador de código C desde AST anotado
 */
#ifndef CODEGEN_C_H
#define CODEGEN_C_H

#include "ast.h"
#include "symtab.h"
#include <stdio.h>
#include <stdbool.h>

/**
 * Opciones de generación de código
 */
typedef struct {
    bool emit_comments;      // Incluir comentarios en el código generado
    bool use_runtime_checks; // Usar rt_div/rt_mod para verificar división por cero
} CodegenOptions;

/**
 * Contexto de generación de código
 */
typedef struct {
    FILE* out;               // Stream de salida
    CodegenOptions opts;     // Opciones
    Scope* global_scope;     // Scope global para buscar funciones
    Symbol* current_func;    // Función actual (NULL si estamos en global)
    int indent_level;        // Nivel de indentación
    bool had_error;          // Flag de error
} CodegenCtx;

/**
 * Genera código C desde el AST anotado
 * Retorna 0 si OK, >0 si hay errores
 */
int codegen_emit_c(Ast* root, Scope* global_scope, const CodegenOptions* opts, FILE* out);

/**
 * Opciones por defecto
 */
CodegenOptions codegen_default_options(void);

#endif /* CODEGEN_C_H */
