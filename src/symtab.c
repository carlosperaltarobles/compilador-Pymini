/**
 * symtab.c - Implementación de tabla de símbolos
 */
#include "symtab.h"
#include <stdlib.h>
#include <string.h>

#ifndef _GNU_SOURCE
extern char *strdup(const char *s);
#endif

#define INITIAL_CAPACITY 16

// Hash simple para strings
static unsigned int hash(const char* str) {
    unsigned int h = 5381;
    int c;
    while ((c = *str++)) {
        h = ((h << 5) + h) + c;
    }
    return h;
}

Scope* scope_push(Scope* parent) {
    Scope* s = malloc(sizeof(Scope));
    s->parent = parent;
    s->capacity = INITIAL_CAPACITY;
    s->count = 0;
    s->symbols = calloc(s->capacity, sizeof(Symbol*));
    return s;
}

Scope* scope_pop(Scope* s) {
    if (!s) return NULL;
    Scope* parent = s->parent;
    
    // Liberar símbolos
    for (int i = 0; i < s->capacity; i++) {
        Symbol* sym = s->symbols[i];
        while (sym) {
            Symbol* next = sym->next;
            if (sym->kind == SYM_FUNC) {
                free(sym->param_types);
                if (sym->param_names) {
                    for (int j = 0; j < sym->arity; j++) {
                        free(sym->param_names[j]);
                    }
                    free(sym->param_names);
                }
            }
            free(sym);
            sym = next;
        }
    }
    
    free(s->symbols);
    free(s);
    return parent;
}

Symbol* sym_lookup_current(Scope* s, const char* name) {
    if (!s) return NULL;
    
    unsigned int idx = hash(name) % s->capacity;
    Symbol* sym = s->symbols[idx];
    
    while (sym) {
        if (strcmp(sym->name, name) == 0) {
            return sym;
        }
        sym = sym->next;
    }
    
    return NULL;
}

Symbol* sym_lookup(Scope* s, const char* name) {
    while (s) {
        Symbol* sym = sym_lookup_current(s, name);
        if (sym) return sym;
        s = s->parent;
    }
    return NULL;
}

Symbol* sym_insert(Scope* s, Symbol sym) {
    if (!s) return NULL;
    
    // Verificar si ya existe en el scope actual
    Symbol* existing = sym_lookup_current(s, sym.name);
    if (existing) {
        return existing; // Ya existe
    }
    
    unsigned int idx = hash(sym.name) % s->capacity;
    
    // Crear copia del símbolo
    Symbol* new_sym = malloc(sizeof(Symbol));
    *new_sym = sym;
    new_sym->name = strdup(sym.name);
    
    // Copiar arrays si es función
    if (sym.kind == SYM_FUNC && sym.arity > 0) {
        if (sym.param_types) {
            new_sym->param_types = malloc(sym.arity * sizeof(Type));
            memcpy(new_sym->param_types, sym.param_types, sym.arity * sizeof(Type));
        }
        if (sym.param_names) {
            new_sym->param_names = malloc(sym.arity * sizeof(char*));
            for (int i = 0; i < sym.arity; i++) {
                if (sym.param_names[i]) {
                    new_sym->param_names[i] = strdup(sym.param_names[i]);
                } else {
                    new_sym->param_names[i] = NULL;
                }
            }
        }
    }
    
    // Insertar al inicio de la lista
    new_sym->next = s->symbols[idx];
    s->symbols[idx] = new_sym;
    s->count++;
    
    return new_sym;
}

Symbol sym_make_var(const char* name, Type type) {
    Symbol sym;
    sym.name = name;
    sym.kind = SYM_VAR;
    sym.type = type;
    sym.return_type = TY_UNKNOWN;
    sym.arity = 0;
    sym.param_types = NULL;
    sym.param_names = NULL;
    sym.next = NULL;
    return sym;
}

Symbol sym_make_func(const char* name, int arity) {
    Symbol sym;
    sym.name = name;
    sym.kind = SYM_FUNC;
    sym.type = TY_UNKNOWN;
    sym.return_type = TY_UNKNOWN;
    sym.arity = arity;
    
    if (arity > 0) {
        sym.param_types = malloc(arity * sizeof(Type));
        sym.param_names = malloc(arity * sizeof(char*));
        for (int i = 0; i < arity; i++) {
            sym.param_types[i] = TY_UNKNOWN;
            sym.param_names[i] = NULL;
        }
    } else {
        sym.param_types = NULL;
        sym.param_names = NULL;
    }
    
    sym.next = NULL;
    return sym;
}

void scope_free(Scope* s) {
    while (s) {
        s = scope_pop(s);
    }
}
