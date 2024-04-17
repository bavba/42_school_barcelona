#include "push_swap.h"

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void push(int *dest, int *src, int *size_dest, int *size_src) {
    if (*size_src > 0) {
        dest[*size_dest] = src[*size_src - 1];
        (*size_dest)++;
        (*size_src)--;
    }
}

void rotate(int *stack, int size) {
    int first = stack[0];
    for (int i = 0; i < size - 1; i++) {
        stack[i] = stack[i + 1];
    }
    stack[size - 1] = first;
}

void reverse_rotate(int *stack, int size) {
    int last = stack[size - 1];
    for (int i = size - 1; i > 0; i--) {
        stack[i] = stack[i - 1];
    }
    stack[0] = last;
}

void sort_stack(int *stack_a, int size) {
    int stack_b[size]; // Temporary stack for sorting

    int size_a = size;
    int size_b = 0;

    while (size_a > 1) {
        int min_index = 0;
        for (int i = 1; i < size_a; i++) {
            if (stack_a[i] < stack_a[min_index]) {
                min_index = i;
            }
        }

        if (min_index == 0) {
            rotate(stack_a, size_a);
            // Print instruction: ra
        } else if (min_index <= size_a / 2) {
            while (min_index-- > 0) {
                rotate(stack_a, size_a);
                // Print instruction: ra
            }
        } else {
            min_index = size_a - min_index;
            while (min_index-- > 0) {
                reverse_rotate(stack_a, size_a);
                // Print instruction: rra
            }
        }

        push(stack_b, stack_a, &size_b, &size_a);
        // Print instruction: pb
    }

    while (size_b > 0) {
        push(stack_a, stack_b, &size_a, &size_b);
        // Print instruction: pa
    }
}

