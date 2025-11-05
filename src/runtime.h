/**
 * runtime.h - Runtime robusto para programas PyMini compilados (Fase 5)
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
 * Lee un entero desde la entrada estándar
 * Retorna el entero leído
 */
int rt_input_int(void);

/**
 * División entera con verificación de división entre cero
 * Termina el programa con error formateado si b == 0
 */
int rt_div(int a, int b);

/**
 * Módulo con verificación de división entre cero
 * Termina el programa con error formateado si b == 0
 */
int rt_mod(int a, int b);

/**
 * Verificación de aserciones en runtime
 * Termina el programa si la condición es falsa
 */
int rt_assert(int condition, const char* message);

/**
 * Habilita el modo trace para depuración
 */
void rt_enable_trace(void);

/**
 * Registra entrada/salida de funciones (solo si trace está habilitado)
 * event debe ser "enter" o "exit"
 */
void rt_trace(const char* func_name, const char* event);

/**
 * Función principal generada por el codegen
 * Debe ser implementada por el código C generado
 */
int __pymini_main(void);

#endif /* RUNTIME_H */
