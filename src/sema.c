/* sema.c - Implementación del Análisis Semántico (stub para fase 2) */

#include "sema.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Declarar strdup si no está disponible */
#ifndef _GNU_SOURCE
extern char *strdup(const char *s);
#endif

/* ========== Tabla de Símbolos ========== */

SymbolTable* symtab_new(SymbolTable* parent) {
    SymbolTable* table = (SymbolTable*)calloc(1, sizeof(SymbolTable));
    if (!table) {
        fprintf(stderr, "Error: no se pudo asignar memoria para la tabla de símbolos\n");
        exit(1);
    }
    table->symbols = NULL;
    table->count = 0;
    table->capacity = 0;
    table->parent = parent;
    return table;
}

void symtab_free(SymbolTable* table) {
    if (!table) return;
    
    for (size_t i = 0; i < table->count; i++) {
        free(table->symbols[i]->name);
        free(table->symbols[i]);
    }
    free(table->symbols);
    free(table);
}

bool symtab_add(SymbolTable* table, const char* name, SymbolKind kind, DataType type, Location loc) {
    if (!table || !name) return false;
    
    /* Verificar si el símbolo ya existe (stub simple) */
    for (size_t i = 0; i < table->count; i++) {
        if (strcmp(table->symbols[i]->name, name) == 0) {
            /* Ya existe - en fase 2 reportaremos error */
            return false;
        }
    }
    
    /* Expandir si es necesario */
    if (table->count >= table->capacity) {
        size_t new_cap = table->capacity == 0 ? 16 : table->capacity * 2;
        Symbol** new_syms = (Symbol**)realloc(table->symbols, new_cap * sizeof(Symbol*));
        if (!new_syms) {
            fprintf(stderr, "Error: no se pudo expandir la tabla de símbolos\n");
            exit(1);
        }
        table->symbols = new_syms;
        table->capacity = new_cap;
    }
    
    /* Crear el nuevo símbolo */
    Symbol* sym = (Symbol*)calloc(1, sizeof(Symbol));
    if (!sym) {
        fprintf(stderr, "Error: no se pudo asignar memoria para símbolo\n");
        exit(1);
    }
    sym->name = strdup(name);
    sym->kind = kind;
    sym->type = type;
    sym->loc = loc;
    
    table->symbols[table->count++] = sym;
    return true;
}

Symbol* symtab_lookup(SymbolTable* table, const char* name) {
    if (!table || !name) return NULL;
    
    /* Buscar en la tabla actual */
    for (size_t i = 0; i < table->count; i++) {
        if (strcmp(table->symbols[i]->name, name) == 0) {
            return table->symbols[i];
        }
    }
    
    /* Buscar en la tabla padre (para scopes anidados) */
    if (table->parent) {
        return symtab_lookup(table->parent, name);
    }
    
    return NULL;
}

/* ========== Análisis Semántico ========== */

void sema_error(Location loc, const char* msg) {
    fprintf(stderr, "Error semántico en línea %d, columna %d: %s\n", 
            loc.line, loc.column, msg);
}

bool sema_analyze(Ast* root) {
    /* Stub para fase 2
     * 
     * En la fase 2, esta función:
     * - Recorrerá el AST
     * - Construirá la tabla de símbolos
     * - Verificará que todas las variables estén declaradas
     * - Verificará tipos
     * - Validará que las funciones existan antes de llamarlas
     * - Verificará que los returns estén en funciones
     * etc.
     * 
     * Por ahora, simplemente retorna true para indicar éxito.
     */
    
    (void)root;  /* Evitar warning de parámetro no usado */
    
    /* En fase 1, no hacemos análisis semántico real */
    return true;
}

/* ========== Funciones Auxiliares (Stubs) ========== */

const char* datatype_to_string(DataType type) {
    switch (type) {
        case TYPE_INT: return "int";
        case TYPE_BOOL: return "bool";
        case TYPE_VOID: return "void";
        case TYPE_UNKNOWN: return "unknown";
        default: return "?";
    }
}

const char* symbolkind_to_string(SymbolKind kind) {
    switch (kind) {
        case SYM_VARIABLE: return "variable";
        case SYM_FUNCTION: return "function";
        case SYM_PARAMETER: return "parameter";
        default: return "?";
    }
}
