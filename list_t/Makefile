CC = gcc # or clang
CFLAGS = -std=c89 -Wall -Wextra -Werror -Wpedantic -O
OUTPUT = -o tester

all: list_t.c list_t.h tester.c
	$(CC) list_t.c list_t.h tester.c $(CFLAGS) $(OUTPUT)	

check: all
	./tester

noflag: list_t.c list_t.h tester.c
	$(CC) list_t.c list_t.h tester.c $(OUTPUT)	

clean:
	rm tester *.gch
