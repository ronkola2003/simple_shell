#include "shell.h"

/**
 * check_logic_ops - Function to check and split for && and || operators
 * @array_commands: Array of commands
 * @i: Index in the array_commands to be checked
 * @array_operators: Array of the logical operators
 *
 * Return: Index of the last command in the array_commands
 */
int check_logic_ops(char *array_commands[], int i, char array_operators[]) {
    char *temp = NULL;
    int j;

    /* Check for & chars in the command line */
    for (j = 0; array_commands[i] != NULL && array_commands[i][j]; j++) {
        if (array_commands[i][j] == '&' && array_commands[i][j + 1] == '&') {
            /* Split line when && is found */
            temp = array_commands[i];
            array_commands[i][j] = '\0';
            array_commands[i] = str_duplicate(array_commands[i]);
            array_commands[i + 1] = str_duplicate(temp + j + 2);
            i++;
            array_operators[i] = '&';
            free(temp);
            j = 0;
        }
        if (array_commands[i][j] == '|' && array_commands[i][j + 1] == '|') {
            /* Split the line when || was found */
            temp = array_commands[i];
            array_commands[i][j] = '\0';
            array_commands[i] = str_duplicate(array_commands[i]);
            array_commands[i + 1] = str_duplicate(temp + j + 2);
            i++;
            array_operators[i] = '|';
            free(temp);
            j = 0;
        }
    }
    return (i);
}

/**
 * _getline - Reads one line from the prompt
 * @data: Structure for the program's data
 * Return: Reading count of bytes
 */
int _getline(data_of_program *data) {
    char buff[BUFFER_SIZE] = {'\0'};
    static char *array_commands[10] = {NULL};
    static char array_operators[10] = {'\0'};
    ssize_t bytes_read, i = 0;

    /* Check logical operators */
    if (!array_commands[0] || (array_operators[0] == '&' && errno != 0) ||
        (array_operators[0] == '|' && errno == 0)) {
        /* Free allocated memory in the array if there is any */
        for (i = 0; array_commands[i]; i++) {
            free(array_commands[i]);
            array_commands[i] = NULL;
        }

        /* Read from file descriptor into buff */
        bytes_read = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);
        if (bytes_read == 0)
            return (-1);

        /* Split lines for a new line or ; */
        i = 0;
        do {
            array_commands[i] = str_duplicate(_strtok(i ? NULL : buff, "\n;"));
            /* Check and split for && and || operators */
            i = check_logic_ops(array_commands, i, array_operators);
        } while (array_commands[i++]);
    }

    /* Obtain next command and remove it from array */
    data->input_line = array_commands[0];
    for (i = 0; array_commands[i]; i++) {
        array_commands[i] = array_commands[i + 1];
        array_operators[i] = array_operators[i + 1];
    }

    return (str_length(data->input_line));
}
