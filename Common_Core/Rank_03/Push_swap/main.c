#include "push_swap.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 0;
    }

    int *stack_a = parse_arguments(argc - 1, argv + 1);
    execute_instructions(stack_a, argc - 1);
    sort_stack(stack_a, argc - 1);
    free(stack_a);

    return 0;
}

