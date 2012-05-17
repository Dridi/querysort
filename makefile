CC=gcc
CFLAGS=-std=c99 -fPIC
EXEC=querysort querysort.so
SRC= $(wildcard src/*.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

querysort: $(OBJ)
	$(CC) -o $@ $^

querysort.so: src/querysort.o
	$(CC) -shared -o $@ $^

src/querysort_main.o: src/querysort_main.c

src/querysort.o: src/querysort.c

%*.o: %*.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm $(OBJ)

mrproper: clean
	@rm $(EXEC)

