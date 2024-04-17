#include "push_swap.h"

void execute_instruction(int *stack, int size, char *instruction) {
    if (strcmp(instruction, "sa") == 0) {
        swap(&stack[0], &stack[1]);
    }
    // Implement other instruction cases similarly
}

void execute_instructions(int *stack_a, int size) {
    char instruction[4]; // Assuming instructions are max 3 characters + '\0'

    while (scanf("%s", instruction) != EOF) {
        execute_instruction(stack_a, size, instruction);
    }
}

