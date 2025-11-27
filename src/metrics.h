/**
 * metrics.h - Sistema de métricas y estadísticas del compilador
 */
#ifndef METRICS_H
#define METRICS_H

#include <stddef.h>
#include <stdbool.h>
#include <sys/types.h>

/**
 * Estructura de métricas del compilador
 */
typedef struct {
    /* Métricas de parsing */
    size_t token_count;
    size_t ast_node_count;
    size_t line_count;
    
    /* Métricas semánticas */
    size_t function_count;
    size_t variable_count;
    size_t error_count;
    
    /* Métricas de optimización */
    size_t optimizations_applied;
    size_t constants_folded;
    size_t dead_code_removed;
    
    /* Tiempos de compilación (en segundos) */
    double parse_time;
    double sema_time;
    double opt_time;
    double codegen_time;
    double gcc_time;
    double total_time;
    
    /* Métricas de salida */
    size_t c_file_size;
    size_t binary_size;
    size_t c_line_count;
    
    /* Estado */
    bool enabled;
} CompilerMetrics;

/**
 * Inicializa el sistema de métricas
 */
void metrics_init(CompilerMetrics* m);

/**
 * Inicia un temporizador para una fase
 */
void metrics_start_timer(void);

/**
 * Detiene el temporizador y retorna el tiempo transcurrido
 */
double metrics_stop_timer(void);

/**
 * Incrementa el contador de tokens
 */
void metrics_inc_tokens(CompilerMetrics* m, size_t count);

/**
 * Incrementa el contador de nodos AST
 */
void metrics_inc_ast_nodes(CompilerMetrics* m, size_t count);

/**
 * Registra una optimización aplicada
 */
void metrics_record_optimization(CompilerMetrics* m, const char* opt_name);

/**
 * Obtiene el tamaño de un archivo
 */
size_t metrics_get_file_size(const char* filepath);

/**
 * Cuenta las líneas en un archivo
 */
size_t metrics_count_lines(const char* filepath);

/**
 * Imprime el reporte de métricas
 */
void metrics_print_report(const CompilerMetrics* m);

/**
 * Imprime un reporte resumido
 */
void metrics_print_summary(const CompilerMetrics* m);

#endif /* METRICS_H */
