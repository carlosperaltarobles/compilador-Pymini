/**
 * opt.c - Implementación de optimizaciones básicas
 */
#include "opt.h"
#include "ast.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* ========== Constant Folding ========== */

static bool is_literal(Ast* node) {
    return node && (node->kind == AST_INT_LIT || node->kind == AST_BOOL_LIT);
}

static int get_int_value(Ast* node) {
    if (node->kind == AST_INT_LIT) return node->data.int_lit.value;
    if (node->kind == AST_BOOL_LIT) return node->data.bool_lit.value ? 1 : 0;
    return 0;
}

static bool get_bool_value(Ast* node) {
    if (node->kind == AST_BOOL_LIT) return node->data.bool_lit.value;
    if (node->kind == AST_INT_LIT) return node->data.int_lit.value != 0;
    return false;
}

static Ast* fold_binary(Ast* node) {
    if (node->kind != AST_BIN_OP) return node;
    
    Ast* left = opt_constant_folding(node->data.bin_op.left);
    Ast* right = opt_constant_folding(node->data.bin_op.right);
    
    node->data.bin_op.left = left;
    node->data.bin_op.right = right;
    
    if (!is_literal(left) || !is_literal(right)) {
        return node;
    }
    
    int lval = get_int_value(left);
    int rval = get_int_value(right);
    bool lbool = get_bool_value(left);
    bool rbool = get_bool_value(right);
    
    Location loc = node->loc;
    OpKind op = node->data.bin_op.op;
    
    switch (op) {
        case OP_ADD:
            return ast_new_int_lit(lval + rval, loc);
        case OP_SUB:
            return ast_new_int_lit(lval - rval, loc);
        case OP_MUL:
            return ast_new_int_lit(lval * rval, loc);
        case OP_DIV:
            if (rval != 0) return ast_new_int_lit(lval / rval, loc);
            break;
        case OP_MOD:
            if (rval != 0) return ast_new_int_lit(lval % rval, loc);
            break;
        case OP_EQ:
            return ast_new_bool_lit(lval == rval, loc);
        case OP_NE:
            return ast_new_bool_lit(lval != rval, loc);
        case OP_LT:
            return ast_new_bool_lit(lval < rval, loc);
        case OP_LE:
            return ast_new_bool_lit(lval <= rval, loc);
        case OP_GT:
            return ast_new_bool_lit(lval > rval, loc);
        case OP_GE:
            return ast_new_bool_lit(lval >= rval, loc);
        case OP_AND:
            return ast_new_bool_lit(lbool && rbool, loc);
        case OP_OR:
            return ast_new_bool_lit(lbool || rbool, loc);
        default:
            break;
    }
    
    return node;
}

static Ast* fold_unary(Ast* node) {
    if (node->kind != AST_UN_OP) return node;
    
    Ast* operand = opt_constant_folding(node->data.un_op.operand);
    node->data.un_op.operand = operand;
    
    if (!is_literal(operand)) return node;
    
    Location loc = node->loc;
    OpKind op = node->data.un_op.op;
    
    if (op == OP_NEG) {
        int val = get_int_value(operand);
        return ast_new_int_lit(-val, loc);
    } else if (op == OP_NOT) {
        bool val = get_bool_value(operand);
        return ast_new_bool_lit(!val, loc);
    }
    
    return node;
}

Ast* opt_constant_folding(Ast* node) {
    if (!node) return NULL;
    
    switch (node->kind) {
        case AST_BIN_OP:
            return fold_binary(node);
        case AST_UN_OP:
            return fold_unary(node);
        case AST_CALL:
            // Fold argumentos
            if (node->data.call.args) {
                Ast* args = node->data.call.args;
                for (size_t i = 0; i < args->data.list.count; i++) {
                    args->data.list.exprs[i] = opt_constant_folding(args->data.list.exprs[i]);
                }
            }
            return node;
        default:
            return node;
    }
}

/* ========== Dead Code Elimination ========== */

static bool dce_stmt_list(Ast* node) {
    if (!node || node->kind != AST_STMT_LIST) return false;
    
    bool changed = false;
    bool found_return = false;
    size_t new_count = 0;
    
    for (size_t i = 0; i < node->data.stmt_list.count; i++) {
        Ast* stmt = node->data.stmt_list.stmts[i];
        
        if (found_return) {
            // Código inalcanzable después de return
            changed = true;
            continue;
        }
        
        // Aplicar DCE recursivamente
        changed |= opt_dead_code_elimination(stmt);
        
        node->data.stmt_list.stmts[new_count++] = stmt;
        
        if (stmt->kind == AST_RETURN) {
            found_return = true;
        }
    }
    
    if (new_count < node->data.stmt_list.count) {
        node->data.stmt_list.count = new_count;
        changed = true;
    }
    
    return changed;
}

bool opt_dead_code_elimination(Ast* node) {
    if (!node) return false;
    
    bool changed = false;
    
    switch (node->kind) {
        case AST_PROGRAM:
            changed |= opt_dead_code_elimination(node->data.program.body);
            break;
            
        case AST_STMT_LIST:
            changed |= dce_stmt_list(node);
            break;
            
        case AST_FUNC_DEF:
            changed |= opt_dead_code_elimination(node->data.func_def.body);
            break;
            
        case AST_BLOCK:
            changed |= opt_dead_code_elimination(node->data.block.stmts);
            break;
            
        case AST_IF: {
            Ast* cond = node->data.if_stmt.condition;
            
            // Si la condición es un literal constante
            if (is_literal(cond)) {
                bool cond_val = get_bool_value(cond);
                if (cond_val) {
                    // if True { A } else { B } -> A
                    // Simplificado: mantenemos la estructura pero marcamos el cambio
                    changed = true;
                } else {
                    // if False { A } else { B } -> B o nada
                    changed = true;
                }
            }
            
            changed |= opt_dead_code_elimination(node->data.if_stmt.then_block);
            if (node->data.if_stmt.elif_list) {
                Ast* elif_list = node->data.if_stmt.elif_list;
                for (size_t i = 0; i < elif_list->data.elif_list.count; i++) {
                    changed |= opt_dead_code_elimination(elif_list->data.elif_list.elifs[i]->data.elif.block);
                }
            }
            if (node->data.if_stmt.else_block) {
                changed |= opt_dead_code_elimination(node->data.if_stmt.else_block->data.else_stmt.block);
            }
            break;
        }
            
        case AST_WHILE:
            changed |= opt_dead_code_elimination(node->data.while_stmt.body);
            break;
            
        case AST_ASSIGN:
            node->data.assign.value = opt_constant_folding(node->data.assign.value);
            break;
            
        case AST_PRINT:
            node->data.print.expr = opt_constant_folding(node->data.print.expr);
            break;
            
        case AST_RETURN:
            if (node->data.ret.expr) {
                node->data.ret.expr = opt_constant_folding(node->data.ret.expr);
            }
            break;
            
        default:
            break;
    }
    
    return changed;
}

/* ========== Copy Propagation (Simplificada) ========== */

bool opt_copy_propagation(Ast* node) {
    // Implementación básica: por ahora solo retornamos false
    // Una implementación completa requeriría análisis de flujo de datos
    (void)node;
    return false;
}

/* ========== Función Principal de Optimización ========== */

bool optimize_ast(Ast* root, OptLevel level) {
    if (!root || level == OPT_LEVEL_0) return false;
    
    bool changed = false;
    
    // Aplicar constant folding a todas las expresiones
    opt_dead_code_elimination(root);
    
    // Dead code elimination
    changed |= opt_dead_code_elimination(root);
    
    // Copy propagation (limitada)
    changed |= opt_copy_propagation(root);
    
    return changed;
}
