/**
 * types.h - Sistema de tipos para PyMini
 */
#ifndef TYPES_H
#define TYPES_H

typedef enum {
    TY_INT,      // Tipo entero
    TY_BOOL,     // Tipo booleano
    TY_STRING,   // Tipo string (cadena de texto)
    TY_UNKNOWN,  // Tipo aún no determinado
    TY_ERROR     // Tipo con error (para propagar errores sin cascada)
} Type;

/**
 * Convierte un tipo a su representación en string
 */
const char* type_name(Type t);

/**
 * Verifica si dos tipos son compatibles
 */
int types_compatible(Type t1, Type t2);

#endif // TYPES_H
