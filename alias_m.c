#include "shell.h"

/**
 * get_alias - structure to add, remove or show aliases
 * @data: the program's data
 * @name: name of requested alias.
 * Return: zero if suces, or other number if its declared in the argument
 */
char *get_alias(data_of_program *data, char *name)
{
	int i, alias_length;

	/**** validate the arguments ****/
	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_length = str_length(name);

	for (i = 0; data->alias_list[i]; i++)
	{/**** Iterates thru the enviro and check for coincidence of the varname ****/
		if (str_compare(name, data->alias_list[i], alias_length) &&
			data->alias_list[i][alias_length] == '=')
		{/**** returns value of the key NAME=  when find it ****/
			return (data->alias_list[i] + alias_length + 1);
		}
	}
	/**** returns NULL if did not find it ****/
	return (NULL);

}
