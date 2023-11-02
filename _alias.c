#include "shell.h"

/**
 * set_alias - structure to add, or override alias
 * @alias_string: structure for alias to be set in form
 * @data: structure for the program's data
 * Return: if success(0),or other number if its declare in arguments
 */


int set_alias(char *alias_string, data_of_program *data)
{
	int i, j;
	char buffer[250] = {'0'}, *temp = NULL;

	/**** To validate the args ****/
	if (alias_string == NULL ||  data->alias_list == NULL)
		return (1);
	/**** loops through alias to find = char ****/
	for (i = 0; alias_string[i]; i++)
		if (alias_string[i] != '=')
			buffer[i] = alias_string[i];
		else
		{/**** to search if the val of the alias is another alias ****/
			temp = get_alias(data, alias_string + i + 1);
			break;
		}

	/**** loops thru alias list n check for coicidence of varname ****/
	for (j = 0; data->alias_list[j]; j++)
		if (str_compare(buffer, data->alias_list[j], i) &&
			data->alias_list[j][i] == '=')
		{/**** to checks if the alias alredy exist ****/
			free(data->alias_list[j]);
			break;
		}

	/**** to add the alias ****/
	if (temp)
	{/**** to check if the alias already exist ****/
		buffer_add(buffer, "=");
		buffer_add(buffer, temp);
		data->alias_list[j] = str_duplicate(buffer);
	}
	else /**** this checks if alias does not exist ****/
		data->alias_list[j] = str_duplicate(alias_string);
	return (0);
}
