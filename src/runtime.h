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
 * Imprime un string seguido de nueva línea
 */
void rt_print_string(const char* s);

/**
 * Lee un entero desde la entrada estándar
 * Si prompt != NULL, lo muestra antes de leer
 * Retorna el entero leído
 */
int rt_input_int(const char* prompt);

/**
 * Lee una línea desde la entrada estándar y retorna un string (malloc'd).
 * Si prompt != NULL, lo muestra antes de leer
 * El caller es responsable de no modificar el buffer si es `const char*` y
 * de liberarlo si corresponde en implementaciones futuras.
 */
char* rt_input_string(const char* prompt);

/**
 * Concatena dos strings y retorna un nuevo string (malloc'd)
 */
char* rt_str_concat(const char* a, const char* b);

/**
 * Convierte un string a int. Si la conversión falla, termina el programa con error.
 */
int rt_str_to_int(const char* s);

/**
 * Convierte un int a string (malloc'd)
 */
char* rt_int_to_str(int n);

/**
 * Convierte un bool a string (malloc'd)
 */
char* rt_bool_to_str(int b);

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
