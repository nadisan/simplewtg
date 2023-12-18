#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

/**
  * prompt - simple_shell program
  * Return: 0 (program successful)
  */

int prompt(void)
{
	char *buffer = "$ ";
	ssize_t input;
	char *line = NULL;
	size_t len = 0;

	while (1)
	{
		write(STDOUT_FILENO, buffer, 3);
		input = getline(&line, &len, stdin);
		if (input == -1)
		{	write(1, "\n", 1);
			free(line);
			break;
		}
		printf("%s", line);
	}
	return (0);
}