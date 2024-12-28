unsigned choice(unsigned a, unsigned b, unsigned c) {
    asm (
        "andl %0, %1;"
        "notl %0;"
        "andl %2, %0;"
        "orl  %1, %0;"
        : "+r" (a), "+r" (b)
        : "r" (c)
    );
    return a;
}

unsigned median(unsigned a, unsigned b, unsigned c)  {
    unsigned d;
    asm (
        "movl %0, %3;"
        "andl %2, %3;"
        "andl %1, %2;"
        "andl %0, %1;" 
        "orl  %3, %2;"
        "orl  %2, %1;"
        : "+r" (a), "+r" (b), "+r" (c), "+r" (d)
    );
    return b;
}

unsigned rotate(unsigned a, unsigned b) {
    asm("rorl %%cl, %0" : "+r" (a) : "c" (b));
    return a;
}

int main() {
    /* Various Variables*/
    unsigned a[3], i, buf[8] = {0, 1, 2, 4, 8, 16, 24, 32};

    /* Random values from memory address... */
    /* use "-Wno-pointer-to-int-cast" */
    a[0] = (unsigned)(&a) | ((long)(&a) >> 32) * (unsigned)(&a) + 1;
    a[1] = (unsigned)(&a) ^ ((long)(&a) >> 32) * (unsigned)(&a) + 2;
    a[2] = (unsigned)(&a) & ((long)(&a) >> 32) * (unsigned)(&a) + 3;

    /* CHOICE */
    for (i = 0; i < 3; i++) {
        if (CHOICE(a[(i+0)%3],a[(i+1)%3],a[(i+2)%3]) !=
            choice(a[(i+0)%3],a[(i+1)%3],a[(i+2)%3])) {
            return 1;
        }
    }

    /* MEDIAN */
    for (i = 0; i < 3; i++) {
        if (MEDIAN(a[(i+0)%3],a[(i+1)%3],a[(i+2)%3]) !=
            median(a[(i+0)%3],a[(i+1)%3],a[(i+2)%3])) {
            return 2;
        }
        a[i] = ~a[i];
    }

    /* ROTATE */
    for (i = 0; i < 8; i++) {
        if (ROTATE(a[0], buf[i]) != rotate(a[0], buf[i]) &&
            ROTATE(a[1], buf[i]) != rotate(a[1], buf[i]) &&
            ROTATE(a[2], buf[i]) != rotate(a[2], buf[i])) {
            return 3;
        }
    }
    return 0;
}
