/*
** EPITECH PROJECT, 2017
** minishell2
** File description:
** strdup with a limit
*/

/* File created the 06/04/2018 at 19:12:15 by julian.frabel@epitech.eu */

#include <unistd.h>
#include "my.h"

char *my_strndup(char const *str, int n)
{
	char *new_str = malloc(sizeof(*new_str) * (n + 1));

	if (new_str == NULL)
		return (NULL);
	my_strncpy(new_str, str, n);
	new_str[n] = '\0';
	return (new_str);
}