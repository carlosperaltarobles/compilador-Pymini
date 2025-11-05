/**
 * pipeline.c - Implementación del pipeline de compilación
 */
#define _POSIX_C_SOURCE 200809L
#include "pipeline.h"
#include "ast.h"
#include "sema.h"
#include "opt.h"
#include "codegen_c.h"
#include "diag.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/* Declaración externa del parser */
extern Ast* parse_file(const char* filename);

PipelineOptions pipeline_default_options(void) {
    PipelineOptions opts;
    opts.input_file = NULL;
    opts.output_file = NULL;
    opts.mode = PIPELINE_RUN;
    opts.opt_level = OPT_LEVEL_0;
    opts.verbose = false;
    opts.keep_temp = false;
    return opts;
}

/**
 * Genera un nombre de archivo temporal
 * Nota: usa dos buffers estáticos alternados para evitar problemas
 */
static char* gen_temp_filename(const char* suffix) {
    static char temp[2][256];
    static int idx = 0;
    idx = (idx + 1) % 2;
    snprintf(temp[idx], sizeof(temp[idx]), "/tmp/pymini_%d%s", getpid(), suffix);
    return temp[idx];
}

/**
 * Ejecuta gcc para compilar el código C generado
 */
static int run_gcc(const char* c_file, const char* output_file, bool verbose) {
    // Construir comando gcc
    char cmd[1024];
    char runtime_c_path[512];
    char runtime_h_path[512];
    char cwd[512];
    
    // Obtener directorio actual
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        fprintf(stderr, "Error: No se pudo obtener el directorio actual\n");
        return 1;
    }
    
    // Construir rutas absolutas a runtime
    snprintf(runtime_c_path, sizeof(runtime_c_path), "%s/src/runtime.c", cwd);
    snprintf(runtime_h_path, sizeof(runtime_h_path), "%s/src", cwd);
    
    // Verificar que runtime.c existe
    if (access(runtime_c_path, F_OK) != 0) {
        // Intentar con ruta relativa
        snprintf(runtime_c_path, sizeof(runtime_c_path), "src/runtime.c");
        if (access(runtime_c_path, F_OK) != 0) {
            fprintf(stderr, "Error: No se encuentra runtime.c\n");
            fprintf(stderr, "Asegúrate de ejecutar el compilador desde el directorio raíz del proyecto\n");
            return 1;
        }
        snprintf(runtime_h_path, sizeof(runtime_h_path), "src");
    }
    
    snprintf(cmd, sizeof(cmd), "gcc -O2 -std=c11 -I%s -o %s %s %s 2>&1",
             runtime_h_path, output_file, c_file, runtime_c_path);
    
    if (verbose) {
        printf("[Pipeline] Ejecutando: %s\n", cmd);
    }
    
    FILE* fp = popen(cmd, "r");
    if (!fp) {
        fprintf(stderr, "Error: No se pudo ejecutar gcc\n");
        return 1;
    }
    
    char buffer[256];
    bool had_output = false;
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        fprintf(stderr, "%s", buffer);
        had_output = true;
    }
    
    int status = pclose(fp);
    if (WIFEXITED(status)) {
        int exit_code = WEXITSTATUS(status);
        if (exit_code != 0 && verbose) {
            fprintf(stderr, "[Pipeline] gcc failed with exit code %d\n", exit_code);
        }
        return exit_code;
    }
    
    return 1;
}

/**
 * Ejecuta el binario generado
 */
static int run_binary(const char* binary_file, bool verbose) {
    if (verbose) {
        printf("[Pipeline] Ejecutando: %s\n", binary_file);
    }
    
    int status = system(binary_file);
    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }
    
    return 1;
}

PipelineResult pipeline_run(const PipelineOptions* opts) {
    PipelineResult result;
    result.exit_code = 0;
    result.error_msg = NULL;
    result.ast = NULL;
    result.global_scope = NULL;
    
    if (!opts || !opts->input_file) {
        result.exit_code = 1;
        result.error_msg = "Opciones de pipeline inválidas";
        return result;
    }
    
    if (opts->verbose) {
        printf("[Pipeline] Compilando: %s\n", opts->input_file);
        printf("[Pipeline] Modo: %s\n",
               opts->mode == PIPELINE_EMIT_C ? "emit-c" :
               opts->mode == PIPELINE_COMPILE ? "compile" : "run");
        printf("[Pipeline] Optimización: -O%d\n", opts->opt_level);
    }
    
    /* Paso 1: Parsear */
    if (opts->verbose) {
        printf("[Pipeline] Paso 1: Parsing...\n");
    }
    
    Ast* ast = parse_file(opts->input_file);
    if (!ast) {
        result.exit_code = 1;
        result.error_msg = "Error en el parsing";
        return result;
    }
    result.ast = ast;
    
    /* Paso 2: Análisis semántico */
    if (opts->verbose) {
        printf("[Pipeline] Paso 2: Análisis semántico...\n");
    }
    
    SemaResult sema_result = sema_check_ex(ast);
    if (sema_result.error_count > 0) {
        result.exit_code = 1;
        result.error_msg = "Errores semánticos";
        result.global_scope = sema_result.global_scope;
        return result;
    }
    result.global_scope = sema_result.global_scope;
    
    /* Paso 3: Optimizaciones */
    if (opts->opt_level > OPT_LEVEL_0) {
        if (opts->verbose) {
            printf("[Pipeline] Paso 3: Aplicando optimizaciones...\n");
        }
        optimize_ast(ast, opts->opt_level);
    }
    
    /* Paso 4: Generación de código C */
    if (opts->verbose) {
        printf("[Pipeline] Paso 4: Generando código C...\n");
    }
    
    const char* c_file = NULL;
    bool free_c_file = false;
    
    if (opts->mode == PIPELINE_EMIT_C) {
        c_file = opts->output_file ? opts->output_file : "out.c";
    } else {
        c_file = gen_temp_filename(".c");
        free_c_file = !opts->keep_temp;
    }
    
    FILE* out = fopen(c_file, "w");
    if (!out) {
        result.exit_code = 1;
        result.error_msg = "No se pudo crear archivo de salida";
        return result;
    }
    
    CodegenOptions codegen_opts = codegen_default_options();
    int codegen_err = codegen_emit_c(ast, result.global_scope, &codegen_opts, out);
    fclose(out);
    
    if (codegen_err != 0) {
        result.exit_code = 1;
        result.error_msg = "Error en la generación de código";
        if (free_c_file) unlink(c_file);
        return result;
    }
    
    if (opts->verbose) {
        printf("[Pipeline] Código C generado en: %s\n", c_file);
    }
    
    /* Si solo emitir C, terminamos aquí */
    if (opts->mode == PIPELINE_EMIT_C) {
        return result;
    }
    
    /* Paso 5: Compilar con gcc */
    if (opts->verbose) {
        printf("[Pipeline] Paso 5: Compilando con gcc...\n");
    }
    
    const char* binary_file = NULL;
    bool free_binary_file = false;
    
    if (opts->mode == PIPELINE_COMPILE) {
        binary_file = opts->output_file ? opts->output_file : "a.out";
    } else {
        binary_file = gen_temp_filename(".bin");
        free_binary_file = !opts->keep_temp;
    }
    
    int gcc_exit = run_gcc(c_file, binary_file, opts->verbose);
    
    if (free_c_file) {
        unlink(c_file);
    }
    
    if (gcc_exit != 0) {
        result.exit_code = 1;
        result.error_msg = "Error al compilar con gcc";
        if (free_binary_file) unlink(binary_file);
        return result;
    }
    
    if (opts->verbose) {
        printf("[Pipeline] Binario generado en: %s\n", binary_file);
    }
    
    /* Si solo compilar, terminamos aquí */
    if (opts->mode == PIPELINE_COMPILE) {
        return result;
    }
    
    /* Paso 6: Ejecutar */
    if (opts->verbose) {
        printf("[Pipeline] Paso 6: Ejecutando...\n");
        printf("========================================\n");
    }
    
    int run_exit = run_binary(binary_file, false);
    result.exit_code = run_exit;
    
    if (free_binary_file) {
        unlink(binary_file);
    }
    
    return result;
}

void pipeline_result_free(PipelineResult* result) {
    if (!result) return;
    
    if (result->ast) {
        ast_free(result->ast);
        result->ast = NULL;
    }
    
    if (result->global_scope) {
        scope_free(result->global_scope);
        result->global_scope = NULL;
    }
}
