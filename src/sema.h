/* sema.h - Análisis Semántico para PyMini (stub para fase 2) */

#ifndef SEMA_H
#define SEMA_H

#include "ast.h"
#include <stdbool.h>

/* ========== Tabla de Símbolos (Stub) ========== */

typedef struct Symbol Symbol;
typedef struct SymbolTable SymbolTable;

/* Tipos de símbolos */
typedef enum {
    SYM_VARIABLE,
    SYM_FUNCTION,
    SYM_PARAMETER
} SymbolKind;

/* Tipos de datos */
typedef enum {
    TYPE_INT,
    TYPE_BOOL,
    TYPE_VOID,
    TYPE_UNKNOWN
} DataType;

/* Estructura de símbolo (stub) */
struct Symbol {
    char* name;
    SymbolKind kind;
    DataType type;
    Location loc;
};

/* Tabla de símbolos (stub) */
struct SymbolTable {
    Symbol** symbols;
    size_t count;
    size_t capacity;
    SymbolTable* parent;  /* Para soporte de scopes anidados en fase 2 */
};

/* ========== Funciones de la Tabla de Símbolos (Stubs) ========== */

/* Crear una nueva tabla de símbolos */
SymbolTable* symtab_new(SymbolTable* parent);

/* Liberar la tabla de símbolos */
void symtab_free(SymbolTable* table);

/* Agregar un símbolo (stub) */
bool symtab_add(SymbolTable* table, const char* name, SymbolKind kind, DataType type, Location loc);

/* Buscar un símbolo (stub) */
Symbol* symtab_lookup(SymbolTable* table, const char* name);

/* ========== Análisis Semántico (Stub) ========== */

/* Realizar análisis semántico en el AST (stub para fase 2) */
bool sema_analyze(Ast* root);

/* Imprimir errores semánticos (placeholder) */
void sema_error(Location loc, const char* msg);

#endif /* SEMA_H */
