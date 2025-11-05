/* ast_print.c - Implementación del Pretty-printer para el AST de PyMini */

#include "ast_print.h"
#include <stdio.h>
#include <string.h>

/* ========== Utilidades de Indentación ========== */

static void print_indent(int level) {
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
}

/* ========== Impresión Recursiva del AST ========== */

void ast_print_indent(const Ast* node, int indent) {
    if (!node) {
        print_indent(indent);
        printf("(null)\n");
        return;
    }
    
    print_indent(indent);
    
    switch (node->kind) {
        case AST_PROGRAM:
            printf("Program [%d:%d]\n", node->loc.line, node->loc.column);
            ast_print_indent(node->data.program.body, indent + 1);
            break;
            
        case AST_STMT_LIST:
            printf("StmtList (%zu statements)\n", node->data.stmt_list.count);
            for (size_t i = 0; i < node->data.stmt_list.count; i++) {
                ast_print_indent(node->data.stmt_list.stmts[i], indent + 1);
            }
            break;
            
        case AST_ASSIGN:
            printf("Assign [%d:%d] name='%s'\n", 
                   node->loc.line, node->loc.column, node->data.assign.name);
            print_indent(indent + 1);
            printf("value:\n");
            ast_print_indent(node->data.assign.value, indent + 2);
            break;
            
        case AST_PRINT:
            printf("Print [%d:%d]\n", node->loc.line, node->loc.column);
            ast_print_indent(node->data.print.expr, indent + 1);
            break;
            
        case AST_RETURN:
            printf("Return [%d:%d]\n", node->loc.line, node->loc.column);
            if (node->data.ret.expr) {
                ast_print_indent(node->data.ret.expr, indent + 1);
            } else {
                print_indent(indent + 1);
                printf("(no value)\n");
            }
            break;
            
        case AST_IF:
            printf("If [%d:%d]\n", node->loc.line, node->loc.column);
            print_indent(indent + 1);
            printf("condition:\n");
            ast_print_indent(node->data.if_stmt.condition, indent + 2);
            print_indent(indent + 1);
            printf("then:\n");
            ast_print_indent(node->data.if_stmt.then_block, indent + 2);
            if (node->data.if_stmt.elif_list) {
                print_indent(indent + 1);
                printf("elifs:\n");
                ast_print_indent(node->data.if_stmt.elif_list, indent + 2);
            }
            if (node->data.if_stmt.else_block) {
                print_indent(indent + 1);
                printf("else:\n");
                ast_print_indent(node->data.if_stmt.else_block, indent + 2);
            }
            break;
            
        case AST_ELIF:
            printf("Elif [%d:%d]\n", node->loc.line, node->loc.column);
            print_indent(indent + 1);
            printf("condition:\n");
            ast_print_indent(node->data.elif.condition, indent + 2);
            print_indent(indent + 1);
            printf("block:\n");
            ast_print_indent(node->data.elif.block, indent + 2);
            break;
            
        case AST_ELIF_LIST:
            printf("ElifList (%zu items)\n", node->data.elif_list.count);
            for (size_t i = 0; i < node->data.elif_list.count; i++) {
                ast_print_indent(node->data.elif_list.elifs[i], indent + 1);
            }
            break;
            
        case AST_ELSE:
            printf("Else [%d:%d]\n", node->loc.line, node->loc.column);
            ast_print_indent(node->data.else_stmt.block, indent + 1);
            break;
            
        case AST_WHILE:
            printf("While [%d:%d]\n", node->loc.line, node->loc.column);
            print_indent(indent + 1);
            printf("condition:\n");
            ast_print_indent(node->data.while_stmt.condition, indent + 2);
            print_indent(indent + 1);
            printf("body:\n");
            ast_print_indent(node->data.while_stmt.body, indent + 2);
            break;
            
        case AST_FUNC_DEF:
            printf("FuncDef [%d:%d] name='%s'\n", 
                   node->loc.line, node->loc.column, node->data.func_def.name);
            if (node->data.func_def.params) {
                print_indent(indent + 1);
                printf("params:\n");
                ast_print_indent(node->data.func_def.params, indent + 2);
            }
            print_indent(indent + 1);
            printf("body:\n");
            ast_print_indent(node->data.func_def.body, indent + 2);
            break;
            
        case AST_BLOCK:
            printf("Block [%d:%d]\n", node->loc.line, node->loc.column);
            ast_print_indent(node->data.block.stmts, indent + 1);
            break;
            
        case AST_BIN_OP:
            printf("BinOp [%d:%d] op='%s'\n", 
                   node->loc.line, node->loc.column, 
                   op_kind_to_string(node->data.bin_op.op));
            print_indent(indent + 1);
            printf("left:\n");
            ast_print_indent(node->data.bin_op.left, indent + 2);
            print_indent(indent + 1);
            printf("right:\n");
            ast_print_indent(node->data.bin_op.right, indent + 2);
            break;
            
        case AST_UN_OP:
            printf("UnOp [%d:%d] op='%s'\n", 
                   node->loc.line, node->loc.column, 
                   op_kind_to_string(node->data.un_op.op));
            print_indent(indent + 1);
            printf("operand:\n");
            ast_print_indent(node->data.un_op.operand, indent + 2);
            break;
            
        case AST_CALL:
            printf("Call [%d:%d] name='%s'\n", 
                   node->loc.line, node->loc.column, node->data.call.name);
            if (node->data.call.args) {
                print_indent(indent + 1);
                printf("args:\n");
                ast_print_indent(node->data.call.args, indent + 2);
            } else {
                print_indent(indent + 1);
                printf("(no arguments)\n");
            }
            break;
        
        case AST_INPUT:
            printf("Input [%d:%d]\n", node->loc.line, node->loc.column);
            break;
            
        case AST_NAME:
            printf("Name [%d:%d] id='%s'\n", 
                   node->loc.line, node->loc.column, node->data.name.id);
            break;
            
        case AST_INT_LIT:
            printf("IntLit [%d:%d] value=%d\n", 
                   node->loc.line, node->loc.column, node->data.int_lit.value);
            break;
            
        case AST_BOOL_LIT:
            printf("BoolLit [%d:%d] value=%s\n", 
                   node->loc.line, node->loc.column, 
                   node->data.bool_lit.value ? "True" : "False");
            break;
        
        case AST_STRING_LIT:
            printf("StringLit [%d:%d] value=\"%s\"\n", 
                   node->loc.line, node->loc.column, 
                   node->data.string_lit.value);
            break;
            
        case AST_PARAM_LIST:
            printf("ParamList (%zu params)\n", node->data.list.count);
            for (size_t i = 0; i < node->data.list.count; i++) {
                print_indent(indent + 1);
                printf("- %s\n", node->data.list.names[i]);
            }
            break;
            
        case AST_ARG_LIST:
            printf("ArgList (%zu args)\n", node->data.list.count);
            for (size_t i = 0; i < node->data.list.count; i++) {
                ast_print_indent(node->data.list.exprs[i], indent + 1);
            }
            break;
            
        default:
            printf("Unknown [%d:%d] kind=%d\n", 
                   node->loc.line, node->loc.column, node->kind);
            break;
    }
}

/* ========== Función Principal de Impresión ========== */

void ast_print(const Ast* root) {
    if (!root) {
        printf("(AST vacío)\n");
        return;
    }
    printf("\n========== AST ==========\n\n");
    ast_print_indent(root, 0);
    printf("\n=========================\n\n");
}
