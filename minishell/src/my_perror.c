/*
** EPITECH PROJECT, 2017
** minishell2
** File description:
** mimic perror
*/

/* File created the 30/03/2018 at 18:00:34 by julian.frabel@epitech.eu */

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "mysh.h"
#include "my.h"

int my_perror(const char *premessage)
{
	int byte_written = 0;
	char *error_msg = strerror(errno);

	if (premessage != NULL) {
		byte_written += write(2, premessage, my_strlen(premessage));
		byte_written += write(2, ": ", 2);
	}
	if (my_strcmp(error_msg, "Exec format error") == 0)
		byte_written += write(2, EXEC_FORMAT_ERROR, \
strlen(EXEC_FORMAT_ERROR));
	else
		byte_written += write(2, error_msg, my_strlen(error_msg));
	byte_written += write(2, ".\n", 2);
	return (byte_written);
}