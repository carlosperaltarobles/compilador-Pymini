/**
 * pipeline.h - Pipeline de compilación para PyMini
 */
#ifndef PIPELINE_H
#define PIPELINE_H

#include "ast.h"
#include "symtab.h"
#include "opt.h"
#include "codegen_c.h"
#include <stdbool.h>

/**
 * Modo de compilación
 */
typedef enum {
    PIPELINE_EMIT_C,    // Solo emitir código C
    PIPELINE_COMPILE,   // Compilar a binario
    PIPELINE_RUN        // Compilar y ejecutar
} PipelineMode;

/**
 * Opciones del pipeline
 */
typedef struct {
    const char* input_file;    // Archivo fuente .pymini
    const char* output_file;   // Archivo de salida (NULL = automático)
    PipelineMode mode;         // Modo de operación
    OptLevel opt_level;        // Nivel de optimización
    bool verbose;              // Mostrar información detallada
    bool keep_temp;            // Mantener archivos temporales
} PipelineOptions;

/**
 * Resultado del pipeline
 */
typedef struct {
    int exit_code;             // Código de salida (0 = éxito)
    const char* error_msg;     // Mensaje de error (NULL si OK)
    Ast* ast;                  // AST generado (puede ser NULL)
    Scope* global_scope;       // Scope global (puede ser NULL)
} PipelineResult;

/**
 * Ejecuta el pipeline completo de compilación
 */
PipelineResult pipeline_run(const PipelineOptions* opts);

/**
 * Libera recursos del resultado
 */
void pipeline_result_free(PipelineResult* result);

/**
 * Opciones por defecto del pipeline
 */
PipelineOptions pipeline_default_options(void);

#endif /* PIPELINE_H */
