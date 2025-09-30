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

.DEFAULT_GOAL := all
.PHONY: all clean test

all: $(BIN_SUDOKU)

# Main app (main.c at repo root)
$(BIN_SUDOKU): main.c $(OBJ)
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
	$(RM) -r $(OBJDIR) $(BIN_SUDOKU) $(BIN_CREATE) tests/$(BIN_TEST) testLogical


run: $(BIN_SUDOKU)
	./$(BIN_SUDOKU) input/txt9/9x9board101.txt 9 4

tests: tests/unit_tests.c $(OBJ)
	$(CC) $(CFLAGS) $(OFLAGS) $(INC) -o tests/$(BIN_TEST) $^ $(LDFLAGS) -lcunit
	./tests/$(BIN_TEST)	