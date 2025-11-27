/**
 * metrics.c - Implementación del sistema de métricas
 */
#include "metrics.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

/* Variable estática para el temporizador */
static struct timespec timer_start;

void metrics_init(CompilerMetrics* m) {
    memset(m, 0, sizeof(CompilerMetrics));
    m->enabled = false;
}

void metrics_start_timer(void) {
    clock_gettime(CLOCK_MONOTONIC, &timer_start);
}

double metrics_stop_timer(void) {
    struct timespec timer_end;
    clock_gettime(CLOCK_MONOTONIC, &timer_end);
    
    double elapsed = (timer_end.tv_sec - timer_start.tv_sec);
    elapsed += (timer_end.tv_nsec - timer_start.tv_nsec) / 1000000000.0;
    
    return elapsed;
}

void metrics_inc_tokens(CompilerMetrics* m, size_t count) {
    if (m) m->token_count += count;
}

void metrics_inc_ast_nodes(CompilerMetrics* m, size_t count) {
    if (m) m->ast_node_count += count;
}

void metrics_record_optimization(CompilerMetrics* m, const char* opt_name) {
    if (!m) return;
    
    m->optimizations_applied++;
    
    if (strstr(opt_name, "constant")) {
        m->constants_folded++;
    } else if (strstr(opt_name, "dead")) {
        m->dead_code_removed++;
    }
}

size_t metrics_get_file_size(const char* filepath) {
    struct stat st;
    if (stat(filepath, &st) == 0) {
        return (size_t)st.st_size;
    }
    return 0;
}

size_t metrics_count_lines(const char* filepath) {
    FILE* f = fopen(filepath, "r");
    if (!f) return 0;
    
    size_t lines = 0;
    int ch;
    while ((ch = fgetc(f)) != EOF) {
        if (ch == '\n') lines++;
    }
    
    fclose(f);
    return lines;
}

void metrics_print_report(const CompilerMetrics* m) {
    if (!m || !m->enabled) return;
    
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║             PyMini Compiler Statistics                  ║\n");
    printf("╠══════════════════════════════════════════════════════════╣\n");
    printf("║ Parsing Metrics                                          ║\n");
    printf("║   Tokens processed:        %6zu                         ║\n", m->token_count);
    printf("║   AST nodes created:       %6zu                         ║\n", m->ast_node_count);
    printf("║   Source lines:            %6zu                         ║\n", m->line_count);
    printf("║                                                          ║\n");
    printf("║ Semantic Analysis                                        ║\n");
    printf("║   Functions defined:       %6zu                         ║\n", m->function_count);
    printf("║   Variables declared:      %6zu                         ║\n", m->variable_count);
    printf("║   Errors found:            %6zu                         ║\n", m->error_count);
    printf("║                                                          ║\n");
    printf("║ Optimizations                                            ║\n");
    printf("║   Total optimizations:     %6zu                         ║\n", m->optimizations_applied);
    printf("║   Constants folded:        %6zu                         ║\n", m->constants_folded);
    printf("║   Dead code removed:       %6zu                         ║\n", m->dead_code_removed);
    printf("║                                                          ║\n");
    printf("║ Compilation Times                                        ║\n");
    printf("║   Parsing:                 %6.3f s                      ║\n", m->parse_time);
    printf("║   Semantic analysis:       %6.3f s                      ║\n", m->sema_time);
    printf("║   Optimization:            %6.3f s                      ║\n", m->opt_time);
    printf("║   Code generation:         %6.3f s                      ║\n", m->codegen_time);
    printf("║   GCC compilation:         %6.3f s                      ║\n", m->gcc_time);
    printf("║   ─────────────────────────────────                     ║\n");
    printf("║   Total time:              %6.3f s                      ║\n", m->total_time);
    printf("║                                                          ║\n");
    printf("║ Output                                                   ║\n");
    printf("║   C file size:             %6zu bytes                   ║\n", m->c_file_size);
    printf("║   C lines generated:       %6zu                         ║\n", m->c_line_count);
    if (m->binary_size > 0) {
        printf("║   Binary size:             %6zu bytes                   ║\n", m->binary_size);
    }
    printf("╚══════════════════════════════════════════════════════════╝\n");
    printf("\n");
}

void metrics_print_summary(const CompilerMetrics* m) {
    if (!m || !m->enabled) return;
    
    printf("\n[Stats] ");
    printf("Tokens: %zu | ", m->token_count);
    printf("AST: %zu nodes | ", m->ast_node_count);
    printf("Functions: %zu | ", m->function_count);
    printf("Variables: %zu | ", m->variable_count);
    printf("Optimizations: %zu | ", m->optimizations_applied);
    printf("Time: %.3f s", m->total_time);
    
    if (m->binary_size > 0) {
        printf(" | Binary: %.1f KB", m->binary_size / 1024.0);
    }
    
    printf("\n\n");
}
