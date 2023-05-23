#include "shell.h"

/**
 * exit_shell - Exits the shell with a specified return status.
 * @argv: Array of words from the entered command line.
 */
void exit_shell(char **argv)
{
	int status = 0;

	if (argv[1] != NULL)
	{
		status = atoi(argv[1]);
		if (status <= -1)
			status = 2;
		free_arguments(argv);
		exit(status);
	}

	int i;
	for (i = 0; argv[i] != NULL; i++)
		free(argv[i]);

	free(argv);
	exit(0);
}

/**
 * atoi_custom - Converts a string to an integer.
 * @str: Pointer to the string.
 * Return: The converted integer value.
 */
int atoi_custom(char *str)
{
	int i = 0;
	int num = 0;
	int sign = 1;

	while (str[i] != '\0')
	{
		if (str[i] == '-')
			sign *= -1;
		else if (str[i] >= '0' && str[i] <= '9')
			num = num * 10 + (str[i] - '0');
		else
			break;
		i++;
	}

	return num * sign;
}

/**
 * print_environment - Prints the current environment variables.
 * @argv: Array of arguments (unused in the function).
 */
void print_environment(char **argv)
{
	int i;
	char **env = environ;

	for (i = 0; env[i] != NULL; i++)
	{
		printf("%s\n", env[i]);
	}
}

/**
 * set_environment_variable - Sets a new environment variable or modifies an existing one.
 * @argv: Array of entered words.
 */
void set_environment_variable(char **argv)
{
	int i, j, k;

	if (argv[1] == NULL || argv[2] == NULL)
	{
		perror(get_environment_variable("_"));
		return;
	}

	for (i = 0; environ[i] != NULL; i++)
	{
		j = 0;
		while (argv[1][j] != '\0')
		{
			if (argv[1][j] != environ[i][j])
				break;
			j++;
		}

		if (argv[1][j] == '\0')
		{
			k = 0;
			while (argv[2][k] != '\0')
			{
				environ[i][j + 1 + k] = argv[2][k];
				k++;
			}
			environ[i][j + 1 + k] = '\0';
			return;
		}
	}

	if (environ[i] == NULL)
	{
		environ[i] = concat_strings(argv[1], "=", argv[2]);
		environ[i + 1] = NULL;
	}
}

/**
 * unset_environment_variable - Removes an environment variable.
 * @argv: Array of entered words.
 */
void unset_environment_variable(char **argv)
{
	int i, j;

	if (argv[1] == NULL)
	{
		perror(get_environment_variable("_"));
		return;
	}

	for (i = 0; environ[i] != NULL; i++)
	{
		j = 0;
		while (argv[1][j] != '\0')
		{
			if (argv[1][j] != environ[i][j])
				break;
			j++;
		}

		if (argv[1][j] == '\0')
		{
			free(environ[i]);
			while (environ[i + 1] != NULL)
			{
				environ[i] = environ[i + 1];
				i++;
			}
			environ[i] = NULL;
			return;
		}
	}
}
