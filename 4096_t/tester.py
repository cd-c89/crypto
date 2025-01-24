tester = r"""
#include <stdio.h>
#include <stdlib.h>
#include "4096_t.h"

/* hex string to  4096_t */
uint64_t bigh2i(char *h, uint64_t *n) {
	size_t l, i = 0, o; /* len, index, offset */
	memset(n, 0, BYTES);
	l = strlen(h);
	o = l - 16;
	while (l > o) {
		sscanf(h + o, "%lx", &n[i]);
		h[o] = 0;
		i++;
		o -= 16;
	}
	n[i] = strtol(h, NULL, 16);
	return 0;
}

uint64_t bigout(uint64_t *n) {
	size_t i = S - 1;
	for (; i < S; i--) {
		printf("%016lx", n[i]);
	}
	printf("\n");
	return 0;
}

int main(int argc, char **argv) {
	uint64_t a[S], b[S], c[S];
	if (argc != 4) {
		exit(1);
	}
	bigh2i(argv[1],a);
	bigh2i(argv[2],b);
	switch (argv[3][0]) {
		case 'A':
			bigadd(a,b,c);
			return bigout(c);
		case 'S':
			bigsub(a,b,c);
			return bigout(c);
		case 'M':
			bigmul(a,b,c);
			return bigout(c);
		case 'Q':
			bigquo(a,b,c);
			return bigout(c);
		case 'R':
			bigrem(a,b,c);
			return bigout(c);
	}
	return 0;
}
"""

if __name__ == "__main__":
    import subprocess, os

    ELF = "tester.out"

    if os.path.isfile(ELF):
        result = subprocess.run(["rm", ELF])
    open("tester.c", "w").write(tester)
    result = subprocess.run(["gcc", "tester.c", "4096_t.c", "-Wall", "-Wextra", "-Werror", "-Wpedantic", "-o", ELF])

    if not os.path.isfile(ELF):
        print("Compilation failed.")
        exit()
    result = subprocess.check_output(["head", "-c", "4", ELF])
    if not "ELF" in str(result)[1:]:
        print("Executable not valid.")
        exit()

    import random

    bigone = random.randint(2 ** 1024, 2 ** 2047)
    bigtwo = random.randint(2 ** 1024, 2 ** 2047)
    hexone = hex(bigone)
    hextwo = hex(bigtwo)

    from operator import add, sub, mul, floordiv as quo, mod as rem
    # We don't deal with negative results from sub, so, just don't test it.
    ops = {'ADD':add,'MUL':mul,'QUO':quo,'REM':rem} # 'SUB':sub,

    for op in ops:        
        result = int(subprocess.check_output(["./"+ELF, hexone, hextwo, op]),16)
        answer = ops[op](bigone,bigtwo)
        if result != answer:
            print("Operator", op, "failed.")
            print("Expected:")
            print(hex(answer))
            print("Received:")
            print(hex(result))
            exit()
        else:
            print(op, "passes.")