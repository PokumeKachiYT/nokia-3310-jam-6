CC=gcc
BIN_FLAGS=-o main `sdl2-config --cflags --libs` -lm
OBJECT_FLAGS =-c

CLEAN_OBJECT_FILES=find . -name "*.o" -type f -delete

all: main.o
	$(CC) main.o $(BIN_FLAGS)
	$(CLEAN_OBJECT_FILES)


main.o: src/main.c
	$(CC) src/main.c $(OBJECT_FLAGS)
