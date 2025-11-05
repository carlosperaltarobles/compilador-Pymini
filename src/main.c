/* main.c - Punto de entrada del compilador PyMini */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ast.h"
#include "ast_print.h"
#include "sema.h"

/* Declaraciones externas del parser */
extern Ast* parse_file(const char* filename);
extern int parse_error_count;

/* ========== Función Principal ========== */

void print_usage(const char* program_name) {
    fprintf(stderr, "Uso: %s <archivo.pymini>\n", program_name);
    fprintf(stderr, "\n");
    fprintf(stderr, "Compilador PyMini - Fase 1: Front-end (Lexer + Parser + AST)\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Opciones:\n");
    fprintf(stderr, "  <archivo.pymini>   Archivo fuente de PyMini a parsear\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Ejemplo:\n");
    fprintf(stderr, "  %s test.pymini\n", program_name);
    fprintf(stderr, "\n");
}

int main(int argc, char** argv) {
    /* Verificar argumentos */
    if (argc != 2) {
        print_usage(argv[0]);
        return 1;
    }
    
    const char* filename = argv[1];
    
    /* Verificar extensión del archivo (opcional) */
    const char* ext = strrchr(filename, '.');
    if (ext && strcmp(ext, ".pymini") != 0) {
        fprintf(stderr, "Advertencia: el archivo no tiene extensión .pymini\n");
    }
    
    printf("========================================\n");
    printf("Compilador PyMini - Fase 1\n");
    printf("========================================\n");
    printf("Parseando: %s\n", filename);
    printf("========================================\n\n");
    
    /* Parsear el archivo */
    Ast* ast = parse_file(filename);
    
    if (!ast) {
        fprintf(stderr, "\n========================================\n");
        fprintf(stderr, "ERROR: Fallo el parseo del archivo\n");
        fprintf(stderr, "========================================\n");
        return 1;
    }
    
    /* Parseo exitoso */
    printf("========================================\n");
    printf("Parse OK\n");
    printf("========================================\n\n");
    
    /* Imprimir el AST */
    ast_print(ast);
    
    /* Análisis semántico (Fase 2) */
    printf("\n========================================\n");
    printf("Iniciando análisis semántico...\n");
    printf("========================================\n\n");
    
    int errors = sema_check(ast);
    
    if (errors > 0) {
        fprintf(stderr, "\n========================================\n");
        fprintf(stderr, "ERROR: Análisis semántico falló con %d error(es)\n", errors);
        fprintf(stderr, "========================================\n");
        ast_free(ast);
        return 1;
    }
    
    printf("\n========================================\n");
    printf("Semantic OK\n");
    printf("========================================\n");
    
    /* Liberar memoria */
    ast_free(ast);
    
    printf("\n========================================\n");
    printf("Compilación completada exitosamente\n");
    printf("========================================\n\n");
    
    return 0;
}
