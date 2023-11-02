#include "shell.h"

/**
 * main - structure initializes the vars of the program
 * @argc: the number of vals received from comand line
 * @argv: the val received from comand line
 * @env: the number of vals received from the comand line
 * Return: returns 0 on succes.
 */
int main(int argc, char *argv[], char *env[])
{
data_of_program data_struct = {NULL}, *data = &data_struct;
char *prompt = "";
initialize_data(data, argc, argv, env);
signal(SIGINT, handle_ctrl_c);

if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
{
errno = 2;
prompt = PROMPT_MSG;
}
}
errno = 0;
sisifo(prompt, data);
return (0);
}
/**
 * handle_ctrl_c - structure prints the prompt in a new line
 * when the signal SIGINT (control C) is send to program
 * @UNUSED: option of the prototype
 */
void handle_ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}
/**
 * initialize_data - initialize struct with info of the program
 * @data: the pointer to the struct of data
 * @argv: array of arg passed to program execution
 * @env: environ passed to program execution
 * @argc: number of values received from comand line
 */
void initialize_data(data_of_program *data, int argc, char *argv[], char **env)
{
	int i = 0;
	
	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;
	/***** defines the file descriptor to be read *****/

	if (argc == 1)

		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			_printe(data->program_name);
			_printe(": 0: Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
		{
			data->env[i] = str_duplicate(env[i]);
		}
	}
	data->env[i] = NULL;
	env = data->env;
	data->alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data->alias_list[i] = NULL;
	}
}


/**
 * sisifo - the structure of an infinite loop that shows the prompt
 * @prompt: the prompt to be printed
 * @data: an infinite loop to shows the prompt
 */
void sisifo(char *prompt, data_of_program *data)
{
int error_code = 0, string_len = 0;

while (++(data->exec_counter))
{
_print(prompt);
error_code = string_len = _getline(data);
if (error_code == EOF)
{
free_all_data(data);
exit(errno); /*** if EOF is the first char of string, and exit***/
}
if (string_len >= 1)
{
expand_alias(data);
expand_variables(data);
tokenize(data);
if (data->tokens[0])
{ /*** its checks if text is given to prompt, and execute ***/
error_code = execute(data);
if (error_code != 0)
_print_error(error_code, data);
}
free_recurrent_data(data);
}
}
}
