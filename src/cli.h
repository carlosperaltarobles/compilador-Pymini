/**
 * cli.h - Interfaz de línea de comandos para PyMini
 */
#ifndef CLI_H
#define CLI_H

#include "pipeline.h"

/**
 * Opciones parseadas de la línea de comandos
 */
typedef struct {
    PipelineOptions pipeline_opts;  // Opciones del pipeline
    bool show_help;                 // Mostrar ayuda
    bool show_version;              // Mostrar versión
} CliOptions;

/**
 * Parsea los argumentos de línea de comandos
 * Retorna 0 si OK, >0 si hay errores
 */
int cli_parse_args(int argc, char** argv, CliOptions* opts);

/**
 * Muestra el mensaje de ayuda
 */
void cli_print_help(const char* program_name);

/**
 * Muestra la versión
 */
void cli_print_version(void);

#endif /* CLI_H */
