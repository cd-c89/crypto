#include "heap_t.h"
#include <stdio.h>
#include <stdint.h>

#define HEAP_SIZE 6

bool gt_uint8_t(void *a, void *b) {
    return (*(uint8_t *)a > *(uint8_t *)b);
}

int main() {
    uint8_t vals[HEAP_SIZE] = {128, 64, 192, 96, 160, 224}, i, j, *ptr;
    heap_t h = heap(sizeof(uint8_t), gt_uint8_t);

    
    printf("Printing array:\n[");
    ptr = (uint8_t *)h.eles;
    for (i = 0; i < HEAP_SIZE - 1; i++) {
        printf("%u, ", vals[i]);
    }
    printf("%u]\n", vals[HEAP_SIZE - 1]);
    
    for (i = 0; i < HEAP_SIZE; i++) {
        insert(&h, &vals[i]);
        printf("Printing heap after add no. %u:\n[", i);
        ptr = (uint8_t *)h.eles;
        for (j = 0; j < HEAP_SIZE - 1; j++) {
            printf("%u, ", ptr[j]);
        }
        printf("%u]\n", ptr[HEAP_SIZE - 1]);
        printf("heap_ptr: %p\n", h);
        printf("ele_size: %ld\n", h.ele_size);
        printf("capacity: %ld\n", h.capacity);
        printf("num_eles: %ld\n", h.num_eles);
        printf("eles_loc: %p\n\n", h.eles);
    }

    printf("Printing heap:\n[");
    ptr = (uint8_t *)h.eles;
    for (i = 0; i < HEAP_SIZE - 1; i++) {
        printf("%u, ", ptr[i]);
    }
    printf("%u]\n", ptr[HEAP_SIZE - 1]);

    for (i = 0; i < HEAP_SIZE; i++) {
        //ptr = maxpop(h);
        vals[i] = *ptr;
        free(ptr);
    }

    printf("Printing heapsorted array:\n[");
    for (i = 0; i < HEAP_SIZE - 1; i++) {
        printf("%u, ", vals[i]);
    }
    printf("%u]\n", vals[HEAP_SIZE - 1]);
    
    for (i = 0; i < HEAP_SIZE - 1; i++) {
        if (vals[i] < vals[i+1]) {
            exit(1);
        }
    }

    return 0;
}