/* ast_print.h - Pretty-printer del AST para PyMini */

#ifndef AST_PRINT_H
#define AST_PRINT_H

#include "ast.h"

/* Imprime el AST con formato de árbol indentado */
void ast_print(const Ast* root);

/* Imprime el AST con nivel de indentación específico (uso interno) */
void ast_print_indent(const Ast* node, int indent);

#endif /* AST_PRINT_H */
