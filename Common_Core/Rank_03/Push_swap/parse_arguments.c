#include "push_swap.h"

int *parse_arguments(int count, char *args[]) {
    int *stack = malloc(sizeof(int) * count);
    if (!stack) {
        // Handle memory allocation error
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < count; i++) {
        char *endptr;
        long num = strtol(args[i], &endptr, 10);

        if (*endptr != '\0' || num < INT_MIN || num > INT_MAX) {
            // Handle invalid input
            exit(EXIT_FAILURE);
        }

        stack[i] = (int)num;
    }

    return stack;
}

