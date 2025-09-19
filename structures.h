#ifndef MONTY_LANGUAGE
#define MONTY_LANGUAGE
#include <stdio.h>
#include <stdlib.h>
typedef struct stack_s
{
    int n;
    struct stack_s *prev;
    struct stack_s *next;
} stack_t;
void push(stack_t **stack, int value);
void pop(stack_t **stack);
void pall(stack_t *stack);
void swap(stack_t **stack);
void add(stack_t **stack);
#endif 
