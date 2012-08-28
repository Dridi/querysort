SRC=check_querysort.c ../src/querysort.c
CFLAGS=-std=c99 -pedantic -fPIC -D QS_VERSION=\"$(VERSION)\"
LDLIBS=-lcheck

all:

.PHONY: check
check: check_querysort
	./check_querysort

clean:
	$(RM) check_querysort

check_querysort: $(SRC)
	$(CC) $(CFLAGS) -o check_querysort $(SRC) $(LDLIBS)
