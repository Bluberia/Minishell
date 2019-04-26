/*
** EPITECH PROJECT, 2017
** minishell2
** File description:
** Return the index of the given str
*/

/* File created the 06/04/2018 at 19:03:54 by julian.frabel@epitech.eu */

#include "my.h"

int my_array_index(char *word, char **array)
{
	for (int j = 0; array[j] != NULL; j++) {
		if (my_strncmp(word, array[j], my_strlen(array[j])) == 0) {
			return (j);
		}
	}
	return (-1);
}