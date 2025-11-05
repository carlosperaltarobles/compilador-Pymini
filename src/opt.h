/**
 * opt.h - Optimizaciones básicas para PyMini
 */
#ifndef OPT_H
#define OPT_H

#include "ast.h"
#include <stdbool.h>

/**
 * Niveles de optimización
 */
typedef enum {
    OPT_LEVEL_0,  // Sin optimizaciones
    OPT_LEVEL_1   // Optimizaciones básicas
} OptLevel;

/**
 * Aplica optimizaciones al AST según el nivel especificado
 * Retorna true si hubo cambios
 */
bool optimize_ast(Ast* root, OptLevel level);

/**
 * Constant folding: evalúa expresiones constantes en tiempo de compilación
 */
Ast* opt_constant_folding(Ast* node);

/**
 * Dead code elimination: elimina código inalcanzable
 */
bool opt_dead_code_elimination(Ast* node);

/**
 * Copy propagation: propaga copias simples
 */
bool opt_copy_propagation(Ast* node);

#endif /* OPT_H */
