
#include <stdio.h>
#include <stdlib.h>
#include "4096_t.h"

/* hex string to  4096_t */
uint64_t bigh2i(char *h, uint64_t *n) {
	size_t l, i = 0, o; /* len, index, offset */
	memset(n, 0, BYTES);
	h += 2;
	l = strlen(h);
	o = l - 16;
	while (l > o) {
		sscanf(h + o, "%lx", &n[i]);
		h[o] = 0;
		i++;
		o -= 16;
	}
	sscanf(h, "%lx", &n[i]);
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
