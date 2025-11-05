/**
 * cli.c - Implementación de la interfaz de línea de comandos
 */
#include "cli.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cli_print_version(void) {
    printf("PyMini Compiler v0.4.0\n");
    printf("Fases 1-4: Lexer, Parser, Semantic, Codegen, Optimization\n");
}

void cli_print_help(const char* program_name) {
    printf("Uso: %s [opciones] <archivo.pymini>\n", program_name);
    printf("\n");
    printf("Compilador PyMini - Subset educativo de Python\n");
    printf("\n");
    printf("Opciones:\n");
    printf("  --help              Muestra este mensaje de ayuda\n");
    printf("  --version           Muestra la versión del compilador\n");
    printf("  --emit-c            Solo genera código C (no compila)\n");
    printf("  --compile           Compila a binario ejecutable\n");
    printf("  --run               Compila y ejecuta (por defecto)\n");
    printf("  -o <archivo>        Especifica el archivo de salida\n");
    printf("  -O0                 Sin optimizaciones (por defecto)\n");
    printf("  -O1                 Optimizaciones básicas\n");
    printf("  -v, --verbose       Modo verbose (muestra pasos del pipeline)\n");
    printf("  --keep-temp         Mantiene archivos temporales\n");
    printf("\n");
    printf("Ejemplos:\n");
    printf("  %s programa.pymini                    # Compila y ejecuta\n", program_name);
    printf("  %s --emit-c -o out.c prog.pymini      # Solo genera C\n", program_name);
    printf("  %s --compile -o prog prog.pymini      # Compila a binario\n", program_name);
    printf("  %s -O1 --run prog.pymini              # Optimiza y ejecuta\n", program_name);
    printf("\n");
}

int cli_parse_args(int argc, char** argv, CliOptions* opts) {
    if (!opts) return 1;
    
    // Inicializar con valores por defecto
    opts->pipeline_opts = pipeline_default_options();
    opts->show_help = false;
    opts->show_version = false;
    
    // Si no hay argumentos, mostrar ayuda
    if (argc < 2) {
        opts->show_help = true;
        return 0;
    }
    
    int i = 1;
    while (i < argc) {
        const char* arg = argv[i];
        
        if (strcmp(arg, "--help") == 0 || strcmp(arg, "-h") == 0) {
            opts->show_help = true;
            return 0;
        }
        else if (strcmp(arg, "--version") == 0) {
            opts->show_version = true;
            return 0;
        }
        else if (strcmp(arg, "--emit-c") == 0) {
            opts->pipeline_opts.mode = PIPELINE_EMIT_C;
        }
        else if (strcmp(arg, "--compile") == 0) {
            opts->pipeline_opts.mode = PIPELINE_COMPILE;
        }
        else if (strcmp(arg, "--run") == 0) {
            opts->pipeline_opts.mode = PIPELINE_RUN;
        }
        else if (strcmp(arg, "-o") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Error: -o requiere un argumento\n");
                return 1;
            }
            opts->pipeline_opts.output_file = argv[++i];
        }
        else if (strcmp(arg, "-O0") == 0) {
            opts->pipeline_opts.opt_level = OPT_LEVEL_0;
        }
        else if (strcmp(arg, "-O1") == 0) {
            opts->pipeline_opts.opt_level = OPT_LEVEL_1;
        }
        else if (strcmp(arg, "-v") == 0 || strcmp(arg, "--verbose") == 0) {
            opts->pipeline_opts.verbose = true;
        }
        else if (strcmp(arg, "--keep-temp") == 0) {
            opts->pipeline_opts.keep_temp = true;
        }
        else if (arg[0] == '-') {
            fprintf(stderr, "Error: Opción desconocida: %s\n", arg);
            fprintf(stderr, "Usa --help para ver las opciones disponibles\n");
            return 1;
        }
        else {
            // Archivo de entrada
            if (opts->pipeline_opts.input_file) {
                fprintf(stderr, "Error: Solo se puede especificar un archivo de entrada\n");
                return 1;
            }
            opts->pipeline_opts.input_file = arg;
        }
        
        i++;
    }
    
    // Verificar que se especificó un archivo de entrada
    if (!opts->show_help && !opts->show_version && !opts->pipeline_opts.input_file) {
        fprintf(stderr, "Error: No se especificó archivo de entrada\n");
        fprintf(stderr, "Usa --help para ver las opciones disponibles\n");
        return 1;
    }
    
    return 0;
}
