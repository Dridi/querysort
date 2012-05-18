CC=gcc
CFLAGS=-std=c99 -pedantic -fPIC
EXEC=querysort querysort.so
SRC= $(wildcard src/*.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

build: $(EXEC)

querysort: $(OBJ)
	$(CC) -o $@ $^

querysort.so: src/querysort.o
	$(CC) -shared -o $@ $^

%*.o: %*.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm $(OBJ)

mrproper: clean
	@rm $(EXEC)

