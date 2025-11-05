/**
 * symtab.h - Tabla de símbolos y gestión de ámbitos
 */
#ifndef SYMTAB_H
#define SYMTAB_H

#include "types.h"

typedef enum {
    SYM_VAR,   // Variable
    SYM_FUNC   // Función
} SymKind;

typedef struct Symbol {
    const char* name;
    SymKind kind;
    Type type;           // Para variables: tipo actual
    
    // Para funciones:
    Type return_type;    // Tipo de retorno (inicialmente TY_UNKNOWN)
    int arity;           // Número de parámetros
    Type* param_types;   // Array dinámico de tipos de parámetros
    char** param_names;  // Nombres de parámetros (para debugging)
    
    struct Symbol* next; // Para listas enlazadas en hash table
} Symbol;

typedef struct Scope {
    struct Scope* parent;  // Scope padre (NULL para global)
    Symbol** symbols;      // Hash table simple
    int capacity;
    int count;
} Scope;

/**
 * Crea un nuevo scope con el scope padre dado
 */
Scope* scope_push(Scope* parent);

/**
 * Destruye el scope actual y retorna el padre
 */
Scope* scope_pop(Scope* s);

/**
 * Busca un símbolo en la cadena de scopes (actual y padres)
 */
Symbol* sym_lookup(Scope* s, const char* name);

/**
 * Busca un símbolo solo en el scope actual
 */
Symbol* sym_lookup_current(Scope* s, const char* name);

/**
 * Inserta un nuevo símbolo en el scope actual
 * Copia el símbolo y retorna el puntero al símbolo insertado
 */
Symbol* sym_insert(Scope* s, Symbol sym);

/**
 * Crea un símbolo de variable
 */
Symbol sym_make_var(const char* name, Type type);

/**
 * Crea un símbolo de función
 */
Symbol sym_make_func(const char* name, int arity);

/**
 * Libera memoria del scope (recursivamente si se desea)
 */
void scope_free(Scope* s);

#endif // SYMTAB_H
