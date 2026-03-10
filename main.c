#include <ctype.h>
#include <string.h>
#include "structures.h"

int g_push_value;

/**
 * free_stack - frees an entire stack
 * @stack: top of stack
 */
void free_stack(stack_t *stack)
{
	stack_t *current = stack;
	stack_t *next;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

/**
 * is_integer - checks whether a string is a valid integer
 * @str: string to validate
 *
 * Return: 1 if valid, 0 otherwise
 */
int is_integer(const char *str)
{
	int index = 0;

	if (str == NULL || str[0] == '\0')
		return (0);

	if (str[index] == '-' || str[index] == '+')
		index++;

	if (str[index] == '\0')
		return (0);

	while (str[index] != '\0')
	{
		if (!isdigit((unsigned char)str[index]))
			return (0);
		index++;
	}

	return (1);
}

/**
 * get_instruction - finds the function for an opcode
 * @opcode: opcode name
 *
 * Return: matching function pointer or NULL
 */
static void (*get_instruction(char *opcode))(stack_t **stack,
	unsigned int line_number)
{
	instruction_t instructions[] = {
		{"push", push},
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"swap", swap},
		{"add", add},
		{NULL, NULL}
	};
	int index = 0;

	while (instructions[index].opcode != NULL)
	{
		if (strcmp(opcode, instructions[index].opcode) == 0)
			return (instructions[index].f);
		index++;
	}

	return (NULL);
}

/**
 * main - entry point for the Monty interpreter
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int main(int argc, char **argv)
{
	FILE *file;
	char *line = NULL;
	size_t capacity = 0;
	size_t bytes_read;
	unsigned int line_number = 0;
	stack_t *stack = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		return (EXIT_FAILURE);
	}

	while ((bytes_read = getline(&line, &capacity, file)) != -1)
	{
		char *opcode;
		char *value;
		void (*instruction)(stack_t **stack, unsigned int line_number);

		(void)bytes_read;
		line_number++;
		opcode = strtok(line, " \t\n");
		if (opcode == NULL || opcode[0] == '#')
			continue;

		if (strcmp(opcode, "push") == 0)
		{
			value = strtok(NULL, " \t\n");
			if (!is_integer(value))
			{
				fprintf(stderr, "L%u: usage: push integer\n", line_number);
				free(line);
				free_stack(stack);
				fclose(file);
				return (EXIT_FAILURE);
			}
			g_push_value = atoi(value);
		}

		instruction = get_instruction(opcode);
		if (instruction == NULL)
		{
			fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
			free(line);
			free_stack(stack);
			fclose(file);
			return (EXIT_FAILURE);
		}

		instruction(&stack, line_number);
	}

	free(line);
	free_stack(stack);
	fclose(file);
	return (EXIT_SUCCESS);
}
