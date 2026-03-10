#include "structures.h"

/**
 * pall - prints all stack values from top to bottom
 * @stack: address of stack top
 * @line_number: current bytecode line number
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *current;

	(void)line_number;

	current = *stack;
	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}
