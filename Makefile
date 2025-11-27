# Makefile para PyMini Compiler

CC = gcc
CFLAGS = -O2 -g -Wall -Wextra -std=c11 -Wno-unused-parameter -Wno-unused-function -I./src
FLEX = flex
BISON = bison
BISON_FLAGS = -d -v

# Directorios
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build
BIN_DIR = bin

# Ejecutable
TARGET = $(BIN_DIR)/pymini

# Archivos fuente
LEX_SRC = $(SRC_DIR)/lexer.l
YACC_SRC = $(SRC_DIR)/parser.y
C_SOURCES = $(SRC_DIR)/ast.c $(SRC_DIR)/ast_print.c $(SRC_DIR)/types.c $(SRC_DIR)/diag.c \
            $(SRC_DIR)/symtab.c $(SRC_DIR)/sema.c $(SRC_DIR)/codegen_c.c $(SRC_DIR)/opt.c \
            $(SRC_DIR)/pipeline.c $(SRC_DIR)/cli.c $(SRC_DIR)/main.c

# Archivos generados
LEX_OUT = $(BUILD_DIR)/lex.yy.c
YACC_OUT = $(BUILD_DIR)/parser.tab.c
YACC_HEADER = $(BUILD_DIR)/parser.tab.h
YACC_OUTPUT = $(BUILD_DIR)/parser.output

# Todos los objetos
OBJS = $(BUILD_DIR)/lex.yy.o $(BUILD_DIR)/parser.tab.o $(BUILD_DIR)/ast.o $(BUILD_DIR)/ast_print.o \
       $(BUILD_DIR)/types.o $(BUILD_DIR)/diag.o $(BUILD_DIR)/symtab.o $(BUILD_DIR)/sema.o \
       $(BUILD_DIR)/codegen_c.o $(BUILD_DIR)/opt.o $(BUILD_DIR)/pipeline.o $(BUILD_DIR)/cli.o $(BUILD_DIR)/main.o

.PHONY: all clean test

all: $(BUILD_DIR) $(BIN_DIR) $(TARGET)

# Crear directorios necesarios
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Generar el lexer
$(LEX_OUT): $(LEX_SRC) | $(BUILD_DIR)
	$(FLEX) -o $(LEX_OUT) $(LEX_SRC)

# Generar el parser
$(YACC_OUT) $(YACC_HEADER): $(YACC_SRC) | $(BUILD_DIR)
	$(BISON) $(BISON_FLAGS) -o $(YACC_OUT) $(YACC_SRC)

# Compilar el parser primero (genera parser.tab.h que necesita el lexer)
$(BUILD_DIR)/parser.tab.o: $(YACC_OUT) $(YACC_HEADER)
	$(CC) $(CFLAGS) -I$(BUILD_DIR) -c $(YACC_OUT) -o $(BUILD_DIR)/parser.tab.o

# Compilar el lexer (depende de y.tab.h)
$(BUILD_DIR)/lex.yy.o: $(LEX_OUT) $(YACC_HEADER)
	$(CC) $(CFLAGS) -I$(BUILD_DIR) -c $(LEX_OUT) -o $(BUILD_DIR)/lex.yy.o

# Compilar AST
$(BUILD_DIR)/ast.o: $(SRC_DIR)/ast.c $(SRC_DIR)/ast.h $(SRC_DIR)/types.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/ast.c -o $(BUILD_DIR)/ast.o

# Compilar AST printer
$(BUILD_DIR)/ast_print.o: $(SRC_DIR)/ast_print.c $(SRC_DIR)/ast_print.h $(SRC_DIR)/ast.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/ast_print.c -o $(BUILD_DIR)/ast_print.o

# Compilar tipos
$(BUILD_DIR)/types.o: $(SRC_DIR)/types.c $(SRC_DIR)/types.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/types.c -o $(BUILD_DIR)/types.o

# Compilar diagnóstico
$(BUILD_DIR)/diag.o: $(SRC_DIR)/diag.c $(SRC_DIR)/diag.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/diag.c -o $(BUILD_DIR)/diag.o

# Compilar tabla de símbolos
$(BUILD_DIR)/symtab.o: $(SRC_DIR)/symtab.c $(SRC_DIR)/symtab.h $(SRC_DIR)/types.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/symtab.c -o $(BUILD_DIR)/symtab.o

# Compilar análisis semántico
$(BUILD_DIR)/sema.o: $(SRC_DIR)/sema.c $(SRC_DIR)/sema.h $(SRC_DIR)/ast.h $(SRC_DIR)/types.h $(SRC_DIR)/diag.h $(SRC_DIR)/symtab.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/sema.c -o $(BUILD_DIR)/sema.o

# Compilar generación de código
$(BUILD_DIR)/codegen_c.o: $(SRC_DIR)/codegen_c.c $(SRC_DIR)/codegen_c.h $(SRC_DIR)/ast.h $(SRC_DIR)/types.h $(SRC_DIR)/symtab.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/codegen_c.c -o $(BUILD_DIR)/codegen_c.o

# Compilar optimizaciones
$(BUILD_DIR)/opt.o: $(SRC_DIR)/opt.c $(SRC_DIR)/opt.h $(SRC_DIR)/ast.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/opt.c -o $(BUILD_DIR)/opt.o

# Compilar pipeline
$(BUILD_DIR)/pipeline.o: $(SRC_DIR)/pipeline.c $(SRC_DIR)/pipeline.h $(SRC_DIR)/ast.h $(SRC_DIR)/sema.h $(SRC_DIR)/opt.h $(SRC_DIR)/codegen_c.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/pipeline.c -o $(BUILD_DIR)/pipeline.o

# Compilar CLI
$(BUILD_DIR)/cli.o: $(SRC_DIR)/cli.c $(SRC_DIR)/cli.h $(SRC_DIR)/pipeline.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/cli.c -o $(BUILD_DIR)/cli.o

# Compilar main
$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c $(SRC_DIR)/cli.h $(SRC_DIR)/pipeline.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $(BUILD_DIR)/main.o

# Enlazar todo
$(TARGET): $(OBJS) | $(BIN_DIR)
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
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Limpiar todo incluyendo backups
distclean: clean
	rm -f *~ $(SRC_DIR)/*~ $(TEST_DIR)/*~
