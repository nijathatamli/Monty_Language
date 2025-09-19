#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
void push(stack_t **stack, int value)
{
    stack_t *new_node =malloc(sizeof(**stack));
    if (!new_node)
        printf('there is memory eror');
    new_node->n = value;
    new_node->prev = NULL;
    new_node->next = *stack;
    if (*stack != NULL)
        (*stack)->prev = new_node;
    *stack = new_node;
}