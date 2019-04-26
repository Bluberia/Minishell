/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** Builtin
*/

/* File created the 23/05/2018 at 10:52:26 by julian.frabel@epitech.eu */

#include <stdio.h>
#include "my.h"
#include "mysh.h"

int builtin_builtins(UNUSED terminal_t *term, UNUSED char **cmd_args)
{
	printf("exit ");
	for (int i = 0; builtin[i].cmd_name != NULL; i++)
		printf("%s ", builtin[i].cmd_name);
	printf("\n");
	fflush(stdout);
	return (0);
}