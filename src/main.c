/* main.c - Punto de entrada del compilador PyMini */

#include <stdio.h>
#include <stdlib.h>
#include "cli.h"
#include "pipeline.h"

int main(int argc, char** argv) {
    CliOptions opts;
    
    /* Parsear argumentos de línea de comandos */
    if (cli_parse_args(argc, argv, &opts) != 0) {
        return 1;
    }
    
    /* Mostrar ayuda o versión si se solicitó */
    if (opts.show_help) {
        cli_print_help(argv[0]);
        return 0;
    }
    
    if (opts.show_version) {
        cli_print_version();
        return 0;
    }
    
    /* Ejecutar el pipeline de compilación */
    PipelineResult result = pipeline_run(&opts.pipeline_opts);
    
    /* Mostrar mensaje de error si hubo alguno */
    if (result.error_msg) {
        fprintf(stderr, "Error: %s\n", result.error_msg);
    }
    
    /* Liberar recursos */
    int exit_code = result.exit_code;
    pipeline_result_free(&result);
    
    return exit_code;
}
