CC = gcc # or clang
CFLAGS = -std=c89 -Wall -Wextra -Werror -Wpedantic -O2

all: list_t.c list_t.h tester.c
	$(CC) list_t.c list_t.h tester.c $(CFLAGS)
	
noflag: list_t.c list_t.h tester.c
	$(CC) list_t.c list_t.h tester.c
	
