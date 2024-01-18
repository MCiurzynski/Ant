CC = gcc
CFLAGS = -Wall

SRC_FILES = main.c ant.c
OBJ_FILES = $(SRC_FILES:.c=.o)
EXE_FILE = main.out
BOARDS_DIR = boards

all: $(EXE_FILE)

$(EXE_FILE): $(OBJ_FILES) | $(BOARDS_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_FILES): $(SRC_FILES)

clean:
	rm -f $(EXE_FILE) $(OBJ_FILES)

$(BOARDS_DIR):
	mkdir -p $(BOARDS_DIR)
