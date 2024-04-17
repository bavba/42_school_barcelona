#include "push_swap.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 0;
    }

    // Parse input arguments into an array of integers
    int *stack_a = parse_arguments(argc - 1, argv + 1);

    // Read and execute instructions from stdin
    execute_instructions(stack_a);

    // Check if the stacks are sorted and print the result

    // Clean up allocated memory
    free(stack_a);

    return 0;
}

