/**
 * runtime.c - Implementación del runtime para PyMini
 */
#include "runtime.h"
#include <stdio.h>
#include <stdlib.h>

void rt_print_int(int x) {
    printf("%d\n", x);
}

void rt_print_bool(int b) {
    printf("%s\n", b ? "True" : "False");
}

int rt_div(int a, int b) {
    if (b == 0) {
        fprintf(stderr, "Runtime Error: Division by zero\n");
        exit(1);
    }
    return a / b;
}

int rt_mod(int a, int b) {
    if (b == 0) {
        fprintf(stderr, "Runtime Error: Modulo by zero\n");
        exit(1);
    }
    return a % b;
}

/**
 * main real: llama a la función generada __pymini_main()
 */
int main(int argc, char** argv) {
    (void)argc;
    (void)argv;
    return __pymini_main();
}
