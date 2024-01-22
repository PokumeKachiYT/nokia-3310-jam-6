CC=gcc
SRC_DIR=src

BIN_FLAGS=`sdl2-config --cflags --libs` -lm
OBJECT_FLAGS=-c -lm

CLEAN_OBJECT_FILES=find . -name "*.o" -type f -delete

all: main.o
	$(CC) main.o $(BIN_FLAGS) -omain
	$(CLEAN_OBJECT_FILES)

main.o:
	$(CC) $(SRC_DIR)/main.c $(OBJECT_FLAGS)

