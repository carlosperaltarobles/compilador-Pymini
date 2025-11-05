/**
 * types.c - Implementación del sistema de tipos
 */
#include "types.h"
#include <string.h>

const char* type_name(Type t) {
    switch (t) {
        case TY_INT:     return "int";
        case TY_BOOL:    return "bool";
        case TY_STRING:  return "str";
        case TY_UNKNOWN: return "<unknown>";
        case TY_ERROR:   return "<error>";
        default:         return "<invalid>";
    }
}

int types_compatible(Type t1, Type t2) {
    // TY_ERROR es compatible con todo (para evitar cascada de errores)
    if (t1 == TY_ERROR || t2 == TY_ERROR) {
        return 1;
    }
    
    // TY_UNKNOWN puede ser compatible dependiendo del contexto
    if (t1 == TY_UNKNOWN || t2 == TY_UNKNOWN) {
        return 1;
    }
    
    return t1 == t2;
}
