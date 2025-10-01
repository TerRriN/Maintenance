# Compiler and flags
CC      = gcc
CFLAGS  = -Wall -Wextra -g -MMD -MP
OFLAGS  = -O3 -march=native -fopenmp
LDFLAGS = -lm

# Layout
SRC_DIR := logic
OBJDIR  := build
INC     := -I$(SRC_DIR)

# Sources from logic/
SRC := $(SRC_DIR)/common.c \
       $(SRC_DIR)/utils.c \
       $(SRC_DIR)/logical_solver.c \
       $(SRC_DIR)/set_board.c

# Objects & deps in build/
OBJ  := $(patsubst $(SRC_DIR)/%.c,$(OBJDIR)/%.o,$(SRC))
DEPS := $(OBJ:.o=.d)

# Binaries
BIN_SUDOKU := sudoku
BIN_CREATE := create_board
BIN_TEST   := unit_tests
BIN_DEMO   := demo

.DEFAULT_GOAL := all
.PHONY: all clean test

all: $(BIN_SUDOKU)

# Main app (main.c at repo root)
$(BIN_SUDOKU): main.c $(OBJ)
	$(CC) $(CFLAGS) $(OFLAGS) $(INC) -o $@ $^ $(LDFLAGS)

# Demo app
$(BIN_DEMO): demo.c $(OBJ)
	$(CC) $(CFLAGS) $(OFLAGS) $(INC) -o $@ $^ $(LDFLAGS)

# Standalone board creator
$(BIN_CREATE): $(SRC_DIR)/create_board.c $(OBJ)
	$(CC) $(CFLAGS) $(OFLAGS) $(INC) -o $@ $^ $(LDFLAGS)

# Pattern rule: build/%.o from logic/%.c
$(OBJDIR)/%.o: $(SRC_DIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(OFLAGS) $(INC) -c $< -o $@

# Ensure build/ exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Include auto-generated deps
-include $(DEPS)

clean:
	$(RM) -r $(OBJDIR) $(BIN_SUDOKU) $(BIN_CREATE) tests/$(BIN_TEST) $(BIN_DEMO) *.d tests/*.d

runDemo9: $(BIN_DEMO)
	./$(BIN_DEMO) input/txt9/9x9board1.txt 9

runDemo16: $(BIN_DEMO)
	./$(BIN_DEMO) input/txt16/16x16board1.txt 16

runDemo25: $(BIN_DEMO)
	./$(BIN_DEMO) input/txt25/6x25.txt 25

runDemo36: $(BIN_DEMO)
	./$(BIN_DEMO) input/36x36.txt 36

run: $(BIN_SUDOKU)
	./$(BIN_SUDOKU) input/txt25/6x25.txt 25 4

tests: tests/unit_tests.c $(OBJ)
	$(CC) $(CFLAGS) $(OFLAGS) $(INC) -o tests/$(BIN_TEST) $^ $(LDFLAGS) -lcunit
	./tests/$(BIN_TEST)	