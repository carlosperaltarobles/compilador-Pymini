# Makefile para PyMini Compiler

CC = gcc
CFLAGS = -O2 -g -Wall -Wextra -std=c11 -Wno-unused-parameter -Wno-unused-function
FLEX = flex
BISON = bison
BISON_FLAGS = -d -v

TARGET = pymini
SRC_DIR = src
TEST_DIR = tests

# Archivos fuente
LEX_SRC = $(SRC_DIR)/lexer.l
YACC_SRC = $(SRC_DIR)/parser.y
C_SOURCES = $(SRC_DIR)/ast.c $(SRC_DIR)/ast_print.c $(SRC_DIR)/types.c $(SRC_DIR)/diag.c \
            $(SRC_DIR)/symtab.c $(SRC_DIR)/sema.c $(SRC_DIR)/codegen_c.c $(SRC_DIR)/opt.c \
            $(SRC_DIR)/pipeline.c $(SRC_DIR)/cli.c $(SRC_DIR)/main.c

# Archivos generados
LEX_OUT = lex.yy.c
YACC_OUT = parser.tab.c
YACC_HEADER = parser.tab.h
YACC_OUTPUT = parser.output

# Todos los objetos
OBJS = lex.yy.o parser.tab.o ast.o ast_print.o types.o diag.o symtab.o sema.o \
       codegen_c.o opt.o pipeline.o cli.o main.o

.PHONY: all clean test

all: $(TARGET)

# Generar el lexer
$(LEX_OUT): $(LEX_SRC)
	$(FLEX) $(LEX_SRC)

# Generar el parser
$(YACC_OUT) $(YACC_HEADER): $(YACC_SRC)
	$(BISON) $(BISON_FLAGS) $(YACC_SRC)

# Compilar el parser primero (genera parser.tab.h que necesita el lexer)
parser.tab.o: $(YACC_OUT) $(YACC_HEADER)
	$(CC) $(CFLAGS) -I. -c $(YACC_OUT) -o parser.tab.o

# Compilar el lexer (depende de y.tab.h)
lex.yy.o: $(LEX_OUT) $(YACC_HEADER)
	$(CC) $(CFLAGS) -I. -c $(LEX_OUT) -o lex.yy.o

# Compilar AST
ast.o: $(SRC_DIR)/ast.c $(SRC_DIR)/ast.h $(SRC_DIR)/types.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/ast.c -o ast.o

# Compilar AST printer
ast_print.o: $(SRC_DIR)/ast_print.c $(SRC_DIR)/ast_print.h $(SRC_DIR)/ast.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/ast_print.c -o ast_print.o

# Compilar tipos
types.o: $(SRC_DIR)/types.c $(SRC_DIR)/types.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/types.c -o types.o

# Compilar diagnóstico
diag.o: $(SRC_DIR)/diag.c $(SRC_DIR)/diag.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/diag.c -o diag.o

# Compilar tabla de símbolos
symtab.o: $(SRC_DIR)/symtab.c $(SRC_DIR)/symtab.h $(SRC_DIR)/types.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/symtab.c -o symtab.o

# Compilar análisis semántico
sema.o: $(SRC_DIR)/sema.c $(SRC_DIR)/sema.h $(SRC_DIR)/ast.h $(SRC_DIR)/types.h $(SRC_DIR)/diag.h $(SRC_DIR)/symtab.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/sema.c -o sema.o

# Compilar generación de código
codegen_c.o: $(SRC_DIR)/codegen_c.c $(SRC_DIR)/codegen_c.h $(SRC_DIR)/ast.h $(SRC_DIR)/types.h $(SRC_DIR)/symtab.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/codegen_c.c -o codegen_c.o

# Compilar optimizaciones
opt.o: $(SRC_DIR)/opt.c $(SRC_DIR)/opt.h $(SRC_DIR)/ast.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/opt.c -o opt.o

# Compilar pipeline
pipeline.o: $(SRC_DIR)/pipeline.c $(SRC_DIR)/pipeline.h $(SRC_DIR)/ast.h $(SRC_DIR)/sema.h $(SRC_DIR)/opt.h $(SRC_DIR)/codegen_c.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/pipeline.c -o pipeline.o

# Compilar CLI
cli.o: $(SRC_DIR)/cli.c $(SRC_DIR)/cli.h $(SRC_DIR)/pipeline.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/cli.c -o cli.o

# Compilar main
main.o: $(SRC_DIR)/main.c $(SRC_DIR)/cli.h $(SRC_DIR)/pipeline.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o main.o

# Enlazar todo
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Ejecutar tests semánticos (usando el script)
test: $(TARGET)
	@./tests/run.sh

# Ejecutar tests end-to-end
test-e2e: $(TARGET)
	@echo "=== Ejecutando tests end-to-end ==="
	@echo ""
	@echo "Tests positivos:"
	@for test_file in tests/e2e/pos/*.pymini; do \
		./tools/build_and_run.sh $$test_file || exit 1; \
	done
	@echo ""
	@echo "Tests negativos (deben fallar en runtime):"
	@for test_file in tests/e2e/neg/*.pymini; do \
		echo "Testing $$test_file (debe fallar)..."; \
		./$(TARGET) --run $$test_file 2>&1 | grep -i "error" > /dev/null && echo "✓ Falló correctamente" || (echo "✗ Debió fallar"; exit 1); \
	done
	@echo ""
	@echo "=== Todos los tests e2e pasaron ==="

# Ejecutar solo tests positivos
test-pos: $(TARGET)
	@echo "=== Ejecutando tests positivos ==="
	@for test_file in tests/pos/*.pymini; do \
		echo ""; \
		echo ">>> Testeando $$test_file"; \
		./$(TARGET) $$test_file || exit 1; \
		echo "<<< $$test_file OK"; \
	done
	@echo ""
	@echo "=== Todos los tests positivos pasaron ==="

# Ejecutar solo tests negativos
test-neg: $(TARGET)
	@echo "=== Ejecutando tests negativos ==="
	@echo "(Estos deben FALLAR con errores)"
	@for test_file in tests/neg/*.pymini; do \
		echo ""; \
		echo ">>> Testeando $$test_file"; \
		./$(TARGET) $$test_file 2>&1 | grep -i "error" > /dev/null && echo "<<< $$test_file OK (falló como se esperaba)" || (echo "<<< $$test_file FAIL (debió fallar)"; exit 1); \
	done
	@echo ""
	@echo "=== Todos los tests negativos fallaron correctamente ==="

# Limpiar archivos generados
clean:
	rm -f $(TARGET) $(OBJS) $(LEX_OUT) $(YACC_OUT) $(YACC_HEADER) $(YACC_OUTPUT)

# Limpiar todo incluyendo backups
distclean: clean
	rm -f *~ $(SRC_DIR)/*~ $(TEST_DIR)/*~
