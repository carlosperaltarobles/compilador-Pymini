/**
 * runtime.h - Runtime mínimo para programas PyMini compilados
 */
#ifndef RUNTIME_H
#define RUNTIME_H

/**
 * Imprime un entero seguido de nueva línea
 */
void rt_print_int(int x);

/**
 * Imprime un booleano como True/False seguido de nueva línea
 */
void rt_print_bool(int b);

/**
 * División entera con verificación de división entre cero
 * Termina el programa con error si b == 0
 */
int rt_div(int a, int b);

/**
 * Módulo con verificación de división entre cero
 * Termina el programa con error si b == 0
 */
int rt_mod(int a, int b);

/**
 * Función principal generada por el codegen
 * Debe ser implementada por el código C generado
 */
int __pymini_main(void);

#endif /* RUNTIME_H */
