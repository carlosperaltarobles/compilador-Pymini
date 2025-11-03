# Makefile para PyMini Compiler

CC = gcc
CFLAGS = -O2 -g -Wall -Wextra -std=c11 -Wno-unused-parameter
FLEX = flex
BISON = bison
BISON_FLAGS = -d -v

TARGET = pymini
SRC_DIR = src
TEST_DIR = tests

# Archivos fuente
LEX_SRC = $(SRC_DIR)/lexer.l
YACC_SRC = $(SRC_DIR)/parser.y
C_SOURCES = $(SRC_DIR)/ast.c $(SRC_DIR)/ast_print.c $(SRC_DIR)/sema.c $(SRC_DIR)/main.c

# Archivos generados
LEX_OUT = lex.yy.c
YACC_OUT = parser.tab.c
YACC_HEADER = parser.tab.h
YACC_OUTPUT = parser.output

# Todos los objetos
OBJS = lex.yy.o parser.tab.o ast.o ast_print.o sema.o main.o

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
ast.o: $(SRC_DIR)/ast.c $(SRC_DIR)/ast.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/ast.c -o ast.o

# Compilar AST printer
ast_print.o: $(SRC_DIR)/ast_print.c $(SRC_DIR)/ast_print.h $(SRC_DIR)/ast.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/ast_print.c -o ast_print.o

# Compilar análisis semántico (stub)
sema.o: $(SRC_DIR)/sema.c $(SRC_DIR)/sema.h $(SRC_DIR)/ast.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/sema.c -o sema.o

# Compilar main
main.o: $(SRC_DIR)/main.c $(SRC_DIR)/ast.h $(SRC_DIR)/ast_print.h $(YACC_HEADER)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o main.o

# Enlazar todo
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Ejecutar tests
test: $(TARGET)
	@echo "=== Ejecutando tests de PyMini ==="
	@for test_file in $(TEST_DIR)/*.pymini; do \
		echo ""; \
		echo ">>> Testeando $$test_file"; \
		./$(TARGET) $$test_file || exit 1; \
		echo "<<< $$test_file OK"; \
	done
	@echo ""
	@echo "=== Todos los tests pasaron correctamente ==="

# Limpiar archivos generados
clean:
	rm -f $(TARGET) $(OBJS) $(LEX_OUT) $(YACC_OUT) $(YACC_HEADER) $(YACC_OUTPUT)

# Limpiar todo incluyendo backups
distclean: clean
	rm -f *~ $(SRC_DIR)/*~ $(TEST_DIR)/*~
