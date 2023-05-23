#include "shell.h"

/**
 * checkbuild - checks if the command is a built-in command
 * @arv: array of arguments
 * Return: pointer to a function that takes arv and returns void
 */
void (*checkbuild(char **arv))(char **arv)
{
	int i, j;
	mybuild T[] = {
		{"exit", exitt},
		{"env", env},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{NULL, NULL}
	};

	for (i = 0; T[i].name; i++)
	{
		j = 0;
		while (T[i].name[j] && arv[0][j])
		{
			if (T[i].name[j] != arv[0][j])
				break;
			j++;
		}
		if (!T[i].name[j] && !arv[0][j])
			return T[i].func;
	}

	return NULL;
}
