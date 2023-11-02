#include "shell.h"

/**
 * builtin_unset_env - structure to unset the env
 * @data: the structure for the program's data
 * Return: ..
 */
int builtin_unset_env(data_of_program *data)
{
	/**** validate args ****/
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	env_remove_key(data->tokens[1], data);

	return (0);
}
